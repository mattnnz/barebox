/*
 * (C) Copyright 2010 Juergen Beisert - Pengutronix
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */
#include <common.h>
#include <init.h>
#include <gpio.h>
#include <environment.h>
#include <errno.h>
#include <mci.h>
#include <asm/armlinux.h>
#include <asm/io.h>
#include <generated/mach-types.h>
#include <mach/imx-regs.h>
#include <mach/clock.h>
#include <mach/mci.h>

static struct memory_platform_data ram_pdata = {
	.name = "ram0",
	.flags = DEVFS_RDWR,
};

static struct device_d sdram_dev = {
	.name     = "mem",
	.map_base = IMX_MEMORY_BASE,
	.size     = 64 * 1024 * 1024,
	.platform_data = &ram_pdata,
};

static struct stm_mci_platform_data mci_pdata = {
	.caps = MMC_MODE_4BIT | MMC_MODE_HS | MMC_MODE_HS_52MHz,
	.voltages = MMC_VDD_32_33 | MMC_VDD_33_34,	/* fixed to 3.3 V */
};

static struct device_d mci_dev = {
	.name     = "stm_mci",
	.map_base = IMX_SSP1_BASE,
	.platform_data = &mci_pdata,
};

static const uint32_t pad_setup[] = {
	/* may be not required as already done by the bootlet code */
#if 0
	/* SDRAM data signals */
	EMI_D15 | STRENGTH(0) | VE_2_5V,
	EMI_D14 | STRENGTH(0) | VE_2_5V,
	EMI_D13 | STRENGTH(0) | VE_2_5V,
	EMI_D12 | STRENGTH(0) | VE_2_5V,
	EMI_D11 | STRENGTH(0) | VE_2_5V,
	EMI_D10 | STRENGTH(0) | VE_2_5V,
	EMI_D9 | STRENGTH(0) | VE_2_5V,
	EMI_D8 | STRENGTH(0) | VE_2_5V,
	EMI_D7 | STRENGTH(0) | VE_2_5V,
	EMI_D6 | STRENGTH(0) | VE_2_5V,
	EMI_D5 | STRENGTH(0) | VE_2_5V,
	EMI_D4 | STRENGTH(0) | VE_2_5V,
	EMI_D3 | STRENGTH(0) | VE_2_5V,
	EMI_D2 | STRENGTH(0) | VE_2_5V,
	EMI_D1 | STRENGTH(0) | VE_2_5V,
	EMI_D0 | STRENGTH(0) | VE_2_5V,

	/* SDRAM data control signals */
	EMI_DQM0 | STRENGTH(0) | VE_2_5V,	/* LDM */
	EMI_DQM1 | STRENGTH(0) | VE_2_5V,	/* UDM */

	/* SDRAM address signals */
	EMI_A0 | STRENGTH(0) | VE_2_5V,
	EMI_A1 | STRENGTH(0) | VE_2_5V,
	EMI_A2 | STRENGTH(0) | VE_2_5V,
	EMI_A3 | STRENGTH(0) | VE_2_5V,
	EMI_A4 | STRENGTH(0) | VE_2_5V,
	EMI_A5 | STRENGTH(0) | VE_2_5V,
	EMI_A6 | STRENGTH(0) | VE_2_5V,
	EMI_A7 | STRENGTH(0) | VE_2_5V,
	EMI_A8 | STRENGTH(0) | VE_2_5V,
	EMI_A9 | STRENGTH(0) | VE_2_5V,
	EMI_A10 | STRENGTH(0) | VE_2_5V,
	EMI_A11 | STRENGTH(0) | VE_2_5V,
	EMI_A12 | STRENGTH(0) | VE_2_5V,

	/* SDRAM address control signals */
	EMI_RASN | STRENGTH(0) | VE_2_5V,
	EMI_CASN | STRENGTH(0) | VE_2_5V,

	/* SDRAM control signals */
	EMI_CE0N | STRENGTH(0) | VE_2_5V,
	EMI_CLK | STRENGTH(0) | VE_2_5V,
	EMI_CLKN | STRENGTH(0) | VE_2_5V,
	EMI_CKE | STRENGTH(0) | VE_2_5V,
	EMI_WEN | STRENGTH(0) | VE_2_5V,
	EMI_BA0 | STRENGTH(0) | VE_2_5V,
	EMI_BA1 | STRENGTH(0) | VE_2_5V,
	EMI_DQS0 | STRENGTH(0) | VE_2_5V,
	EMI_DQS1 | STRENGTH(0) | VE_2_5V,
#endif
	/* debug port */
	PWM1_DUART_TX | STRENGTH(S4MA),	/*  strength is TBD */
	PWM0_DUART_RX | STRENGTH(S4MA),	/*  strength is TBD */

	/* lcd */
	LCD_VSYNC,	/* kernel tries with 12 mA for all LCD related pins */
	LCD_HSYNC,
	LCD_ENABE,
	LCD_DOTCLOCK,
	LCD_D17,
	LCD_D16,
	LCD_D15,
	LCD_D14,
	LCD_D13,
	LCD_D12,
	LCD_D11,
	LCD_D10,
	LCD_D9,
	LCD_D8,
	LCD_D7,
	LCD_D6,
	LCD_D5,
	LCD_D4,
	LCD_D3,
	LCD_D2,
	LCD_D1,
	LCD_D0,

	/* LCD usage currently unknown */
	LCD_CS,	/* used as SPI SS */
	LCD_RS,	/* used as SPI CLK */
	LCD_RESET,
	LCD_WR,	/* used as SPI MOSI */

	/* I2C to the MMA7455L, KXTE9, AT24C08 (DCID), AT24C128B (ID EEPROM) and QN8005B */
	I2C_SDA,
	I2C_CLK,

	/* Rotary decoder (external pull ups) */
	ROTARYA,
	ROTARYB,

	/* the chumby bend (external pull up) */
	PWM4_GPIO | GPIO_IN,

	/* backlight control, to be controled by PWM, here we only want to disable it */
	PWM2_GPIO | GPIO_OUT | GPIO_VALUE(0),	/* 1 enables, 0 disables the backlight */

	/* send a reset signal to the USB hub */
	AUART1_TX_GPIO | GPIO_OUT | GPIO_VALUE(0),

	/* USB power disable (FIXME what level to be switched off) */
	AUART1_CTS_GPIO | GPIO_OUT | GPIO_VALUE(0),

	/* Detecting if a display is connected (0 = display attached) (external pull up) */
	AUART1_RTS_GPIO | GPIO_IN,

	/* disable the audio amplifier */
	GPMI_D08_GPIO | GPIO_OUT | GPIO_VALUE(0),

	/* Head Phone detection (FIXME what level when plugged in) (external pull up) */
	GPMI_D11_GPIO | GPIO_IN,

#if 0
	/* Enable the local 5V (FIXME what to do when the bootloader runs) */
	GPMI_D12_GPIO | GPIO_OUT | GPIO_VALUE(1),
#endif

	/* not used pins */
	GPMI_D09_GPIO | GPIO_IN | PULLUP(1),
	GPMI_D10_GPIO | GPIO_IN | PULLUP(1),
	GPMI_D13_GPIO | GPIO_IN | PULLUP(1),

	/* unknown. Not connected to anything than test pin J113 */
	GPMI_D14_GPIO | GPIO_IN | PULLUP(1),

	/* unknown. Not connected to anything than test pin J114 */
	GPMI_D15_GPIO | GPIO_IN | PULLUP(1),

	/* NAND controller (Note: There is no NAND device on the board) */
	GPMI_D00 | PULLUP(1),
	GPMI_D01 | PULLUP(1),
	GPMI_D02 | PULLUP(1),
	GPMI_D03 | PULLUP(1),
	GPMI_D04 | PULLUP(1),
	GPMI_D05 | PULLUP(1),
	GPMI_D06 | PULLUP(1),
	GPMI_D07 | PULLUP(1),
	GPMI_CE0N,
	GPMI_RDY0 | PULLUP(1),
	GPMI_WRN,	/* kernel tries here with 12 mA */
	GPMI_RDN,	/* kernel tries here with 12 mA */
	GPMI_WPM,	/* kernel tries here with 12 mA */
	GPMI_CLE,
	GPMI_ALE,

	/* SD card interface */
	SSP1_DATA0 | PULLUP(1),	/* available at J201 */
	SSP1_DATA1 | PULLUP(1),	/* available at J200 */
	SSP1_DATA2 | PULLUP(1),	/* available at J205 */
	SSP1_DATA3 | PULLUP(1),	/* available at J204 */
	SSP1_SCK,		/* available at J202 */
	SSP1_CMD | PULLUP(1),	/* available at J203 */
	SSP1_DETECT | PULLUP(1),	/* only connected to test pin J115 */

	/* other not used pins */
	GPMI_CE1N_GPIO | GPIO_IN | PULLUP(1),
	GPMI_CE2N_GPIO | GPIO_IN | PULLUP(1),
	GPMI_RDY1_GPIO | GPIO_IN | PULLUP(1),
	GPMI_RDY2_GPIO | GPIO_IN | PULLUP(1),
	GPMI_RDY3_GPIO | GPIO_IN | PULLUP(1),
};

/**
 * Try to register an environment storage on the attached MCI card
 * @return 0 on success
 *
 * We relay on the existance of a useable SD card, already attached to
 * our system, to get someting like a persistant memory for our environment.
 * If this SD card is also the boot media, we can use the second partition
 * for our environment purpose (if present!).
 */
static int register_persistant_environment(void)
{
	struct cdev *cdev;

	/*
	 * The chumby one only has one MCI card socket.
	 * So, we expect its name as "disk0".
	 */
	cdev = cdev_by_name("disk0");
	if (cdev == NULL) {
		pr_err("No MCI card preset\n");
		return -ENODEV;
	}

	/* MCI card is present, also a useable partition on it? */
	cdev = cdev_by_name("disk0.1");
	if (cdev == NULL) {
		pr_err("No second partition available\n");
		pr_info("Please create at least a second partition with"
			" 256 kiB...512 kiB in size (your choice)\n");
		return -ENODEV;
	}

	/* use the full partition as our persistant environment storage */
	return devfs_add_partition("disk0.1", 0, cdev->size, DEVFS_PARTITION_FIXED, "env0");
}

static int falconwing_devices_init(void)
{
	int i, rc;

	/* initizalize gpios */
	for (i = 0; i < ARRAY_SIZE(pad_setup); i++)
		imx_gpio_mode(pad_setup[i]);

	register_device(&sdram_dev);
	imx_set_ioclk(480U * 1000U);	/* enable IOCLK to run at the PLL frequency */
	/* run the SSP unit clock at 100,000 kHz */
	imx_set_sspclk(0, 100U * 1000U, 1);
	register_device(&mci_dev);

	armlinux_add_dram(&sdram_dev);
	armlinux_set_bootparams((void*)(sdram_dev.map_base + 0x100));
	armlinux_set_architecture(MACH_TYPE_CHUMBY);

	rc = register_persistant_environment();
	if (rc != 0)
		printf("Cannot create the 'env0' persistant environment storage (%d)\n", rc);

	return 0;
}

device_initcall(falconwing_devices_init);

static struct device_d falconwing_serial_device = {
	.name     = "stm_serial",
	.map_base = IMX_DBGUART_BASE,
	.size     = 8192,
};

static int falconwing_console_init(void)
{
	return register_device(&falconwing_serial_device);
}

console_initcall(falconwing_console_init);

/** @page chumbyone Chumby Industrie's Falconwing

This device is also known as "chumby one" (http://www.chumby.com/)

This CPU card is based on a Freescale i.MX23 CPU. The card is shipped with:

- 64 MiB synchronous dynamic RAM (DDR type)

Memory layout when @b barebox is running:

- 0x40000000 start of SDRAM
- 0x40000100 start of kernel's boot parameters
  - below malloc area: stack area
  - below barebox: malloc area
- 0x42000000 start of @b barebox

@section get_falconwing_binary How to get the bootloader binary image:

Using the default configuration:

@verbatim
make ARCH=arm chumbyone_defconfig
@endverbatim

Build the bootloader binary image:

@verbatim
make ARCH=arm CROSS_COMPILE=armv5compiler
@endverbatim

@note replace the armv5compiler with your ARM v5 cross compiler.

@section setup_falconwing How to prepare an MCI card to boot the "chumby one" with barebox

- Create four primary partitions on the MCI card
 - the first one for the bootlets (about 256 kiB)
 - the second one for the persistant environment (size is up to you, at least 256k)
 - the third one for the kernel (2 MiB ... 4 MiB in size)
 - the 4th one for the root filesystem which can fill the rest of the available space

- Mark the first partition with the partition ID "53" and copy the bootlets
  into this partition (currently not part of @b barebox!).

- Copy the default @b barebox environment into the second partition (no filesystem required).

- Copy the kernel into the third partition (no filesystem required).

- Create the root filesystem in the 4th partition. You may copy an image into this
  partition or you can do it in the classic way: mkfs on it, mount it and copy
  all required data and programs into it.

*/