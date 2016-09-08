/*
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
 */

#include <init.h>
#include <common.h>
#include <io.h>
#include <notifier.h>
#include <linux/sizes.h>
#include <mach/vf610-regs.h>
#include <mach/revision.h>
#include <mach/clock-imx51_53.h>
#include <mach/generic.h>

#define SI_REV 0x80

static char soc_type[] = "xx0";

static int vf610_silicon_revision(void)
{
	struct mscm *mscm = (struct mscm *)VF610_MSCM_BASE_ADDR;
	void __iomem *rom = VF610_IROM_BASE_ADDR;
    
    u32 rev;
    u32 vf610_silicon_revision;
	
    soc_type[0] = mscm->cpxcount ? '6' : '5'; /*Dual Core => VF6x0 */
	soc_type[1] = mscm->cpxcfg1 ? '1' : '0'; /* L2 Cache => VFx10 */

	char soc[6];

	strcat(soc, "vf");
	strcat(soc, soc_type);

	rev = readl(rom + SI_REV);
	switch (rev) {
	case 0x10:
		vf610_silicon_revision = IMX_CHIP_REV_1_0;
		break;
	case 0x11:
		vf610_silicon_revision = IMX_CHIP_REV_1_1;
		break;
	default:
		vf610_silicon_revision = 0;
	}

	imx_set_silicon_revision(soc, vf610_silicon_revision);

	return 0;
}

int vf610_init(void)
{
	vf610_silicon_revision();
	vf610_boot_save_loc((void *)VF610_SRC_BASE_ADDR);

	return 0;
}

int vf610_devices_init(void)
{

	add_generic_device("ocotp", 0, NULL, VF610_OCOTP_BASE, 0xCF0, IORESOURCE_MEM, NULL);
	add_generic_device("imx-iomuxv3", 0, NULL, VF610_IOMUXC_BASE_ADDR, 0x1000, IORESOURCE_MEM, NULL);
	add_generic_device("vf610-ccm", 0, NULL, VF610_CCM_BASE_ADDR, 0x1000, IORESOURCE_MEM, NULL);
	add_generic_device("imx31-gpt", 0, NULL, MX53_GPT1_BASE_ADDR, 0x1000, IORESOURCE_MEM, NULL);
	add_generic_device("imx31-gpio", 0, NULL, VF610_GPIO1_BASE_ADDR, 0x1000, IORESOURCE_MEM, NULL);
	add_generic_device("imx31-gpio", 1, NULL, VF610_GPIO2_BASE_ADDR, 0x1000, IORESOURCE_MEM, NULL);
	add_generic_device("imx31-gpio", 2, NULL, VF610_GPIO3_BASE_ADDR, 0x1000, IORESOURCE_MEM, NULL);
	add_generic_device("imx31-gpio", 3, NULL, VF610_GPIO4_BASE_ADDR, 0x1000, IORESOURCE_MEM, NULL);
	add_generic_device("imx31-gpio", 4, NULL, VF610_GPIO5_BASE_ADDR, 0x1000, IORESOURCE_MEM, NULL);
	add_generic_device("imx21-wdt", 0, NULL, VF610_WDOG1_BASE_ADDR, 0x1000, IORESOURCE_MEM, NULL);
    /*TODO add pit driver*/

	return 0;
}

