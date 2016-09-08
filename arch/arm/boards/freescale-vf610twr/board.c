/*
 * Copyright (C) 2007 Sascha Hauer, Pengutronix
 * Copyright (C) 2011 Marc Kleine-Budde <mkl@pengutronix.de>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 */

#include <common.h>
#include <environment.h>
#include <fcntl.h>
#include <fec.h>
#include <fs.h>
#include <init.h>
#include <nand.h>
#include <net.h>
#include <partition.h>
#include <linux/sizes.h>
#include <gpio.h>

#include <generated/mach-types.h>

#include <mach/vf610-regs.h>
#include <mach/iomux-vf610.h>
#include <mach/vf610_crm_regs.h>
#include <mach/devices-vf610.h>
#include <mach/generic.h>
#include <mach/imx-nand.h>
#include <mach/iim.h> 
#include <mach/vf610.h>

#include <asm/armlinux.h>
#include <io.h>
#include <asm/mmu.h>

static struct ddrmc_cr_setting vf610twr_cr_settings[] = {
    /* levelling */
    { DDRMC_CR97_WRLVL_EN, 97 },
    { DDRMC_CR98_WRLVL_DL_0(0), 98 },
    { DDRMC_CR99_WRLVL_DL_1(0), 99 },
    { DDRMC_CR102_RDLVL_REG_EN | DDRMC_CR102_RDLVL_GT_REGEN, 102 },
    { DDRMC_CR105_RDLVL_DL_0(0), 105 },
    { DDRMC_CR106_RDLVL_GTDL_0(4), 106 },
    { DDRMC_CR110_RDLVL_DL_1(0) | DDRMC_CR110_RDLVL_GTDL_1(4), 110 },
    /* AXI */
    { DDRMC_CR117_AXI0_W_PRI(0) | DDRMC_CR117_AXI0_R_PRI(0), 117 },
    { DDRMC_CR118_AXI1_W_PRI(1) | DDRMC_CR118_AXI1_R_PRI(1), 118 },
    { DDRMC_CR120_AXI0_PRI1_RPRI(2) |
           DDRMC_CR120_AXI0_PRI0_RPRI(2), 120 },
    { DDRMC_CR121_AXI0_PRI3_RPRI(2) |
           DDRMC_CR121_AXI0_PRI2_RPRI(2), 121 },
    { DDRMC_CR122_AXI1_PRI1_RPRI(1) | DDRMC_CR122_AXI1_PRI0_RPRI(1) |
           DDRMC_CR122_AXI0_PRIRLX(100), 122 },
    { DDRMC_CR123_AXI1_P_ODR_EN | DDRMC_CR123_AXI1_PRI3_RPRI(1) |
           DDRMC_CR123_AXI1_PRI2_RPRI(1), 123 },
    { DDRMC_CR124_AXI1_PRIRLX(100), 124 },
    { DDRMC_CR126_PHY_RDLAT(8), 126 },
    { DDRMC_CR132_WRLAT_ADJ(5) |
           DDRMC_CR132_RDLAT_ADJ(6), 132 },
    { DDRMC_CR137_PHYCTL_DL(2), 137 },
    { DDRMC_CR138_PHY_WRLV_MXDL(256) |
           DDRMC_CR138_PHYDRAM_CK_EN(1), 138 },
    { DDRMC_CR139_PHY_WRLV_RESPLAT(4) | DDRMC_CR139_PHY_WRLV_LOAD(7) |
           DDRMC_CR139_PHY_WRLV_DLL(3) |
           DDRMC_CR139_PHY_WRLV_EN(3), 139 },
    { DDRMC_CR140_PHY_WRLV_WW(64), 140 },
    { DDRMC_CR143_RDLV_GAT_MXDL(1536) |
           DDRMC_CR143_RDLV_MXDL(128), 143 },
    { DDRMC_CR144_PHY_RDLVL_RES(4) | DDRMC_CR144_PHY_RDLV_LOAD(7) |
           DDRMC_CR144_PHY_RDLV_DLL(3) |
           DDRMC_CR144_PHY_RDLV_EN(3), 144 },
    { DDRMC_CR145_PHY_RDLV_RR(64), 145 },
    { DDRMC_CR146_PHY_RDLVL_RESP(64), 146 },
    { DDRMC_CR147_RDLV_RESP_MASK(983040), 147 },
    { DDRMC_CR148_RDLV_GATE_RESP_MASK(983040), 148 },
    { DDRMC_CR151_RDLV_GAT_DQ_ZERO_CNT(1) |
           DDRMC_CR151_RDLVL_DQ_ZERO_CNT(1), 151 },

    { DDRMC_CR154_PAD_ZQ_EARLY_CMP_EN_TIMER(13) |
           DDRMC_CR154_PAD_ZQ_MODE(1) |
           DDRMC_CR154_DDR_SEL_PAD_CONTR(3) |
           DDRMC_CR154_PAD_ZQ_HW_FOR(1), 154 },
    { DDRMC_CR155_PAD_ODT_BYTE1(1) | DDRMC_CR155_PAD_ODT_BYTE0(1), 155 },
    { DDRMC_CR158_TWR(6), 158 },
    { DDRMC_CR161_ODT_EN(1) | DDRMC_CR161_TODTH_RD(2) |
           DDRMC_CR161_TODTH_WR(2), 161 },
    /* end marker */
    { 0, -1 }
};

int dram_init(void)
{
    static const struct ddr3_jedec_timings timings = {
        .tinit             = 5,
        .trst_pwron        = 80000,
        .cke_inactive      = 200000,
        .wrlat             = 5,
        .caslat_lin        = 12,
        .trc               = 21,
        .trrd              = 4,
        .tccd              = 4,
        .tbst_int_interval = 0,
        .tfaw              = 20,
        .trp               = 6,
        .twtr              = 4,
        .tras_min          = 15,
        .tmrd              = 4,
        .trtp              = 4,
        .tras_max          = 28080,
        .tmod              = 12,
        .tckesr            = 4,
        .tcke              = 3,
        .trcd_int          = 6,
        .tras_lockout      = 0,
        .tdal              = 12,
        .bstlen            = 3,
        .tdll              = 512,
        .trp_ab            = 6,
        .tref              = 3120,
        .trfc              = 44,
        .tref_int          = 0,
        .tpdex             = 3,
        .txpdll            = 10,
        .txsnr             = 48,
        .txsr              = 468,
        .cksrx             = 5,
        .cksre             = 5,
        .freq_chg_en       = 0,
        .zqcl              = 256,
        .zqinit            = 512,
        .zqcs              = 64,
        .ref_per_zq        = 64,
        .zqcs_rotate       = 0,
        .aprebit           = 10,
        .cmd_age_cnt       = 64,
        .age_cnt           = 64,
        .q_fullness        = 7,
        .odt_rd_mapcs0     = 0,
        .odt_wr_mapcs0     = 1,
        .wlmrd             = 40,
        .wldqsen           = 25,
    };

    ddrmc_setup_iomux(NULL, 0);

    ddrmc_ctrl_init_ddr3(&timings, vf610twr_cr_settings, NULL, 1, 3);
    gd->ram_size = get_ram_size((void *)PHYS_SDRAM, PHYS_SDRAM_SIZE);

    return 0;
}

static struct fec_platform_data fec_info = {
	.xcv_type = PHY_INTERFACE_MODE_RMII,
};

static struct imx_nand_platform_data nand_info = {
	.width	= 1,
	.hw_ecc	= 1,
	.flash_bbt = 1,
};

static iomux_v3_cfg_t twr_pads[] = {
	/* UART1 */
	VF610_PAD_PTB4__UART1_TX,
	VF610_PAD_PTB5__UART1_RX,

	/* FEC */
	VF610_PAD_PTA6__RMII0_CLKIN,
	VF610_PAD_PTC1__RMII0_MDIO,
	VF610_PAD_PTC0__RMII0_MDC,
	VF610_PAD_PTC2__RMII0_CRS_DV,
	VF610_PAD_PTC3__RMII0_RD1,
	VF610_PAD_PTC4__RMII0_RD0,
	VF610_PAD_PTC5__RMII0_RXER,
	VF610_PAD_PTC6__RMII0_TD1,
	VF610_PAD_PTC7__RMII0_TD0,
	VF610_PAD_PTC8__RMII0_TXEN,

	/* SD1 */
	VF610_PAD_PTA24__ESDHC1_CLK,
	VF610_PAD_PTA25__ESDHC1_CMD,
	VF610_PAD_PTA26__ESDHC1_DAT0,
	VF610_PAD_PTA27__ESDHC1_DAT1,
	VF610_PAD_PTA28__ESDHC1_DAT2,
	VF610_PAD_PTA29__ESDHC1_DAT3,
    /* SD1_CD */
	VF610_PAD_PTA7__GPIO_134,
    /* SD1_WP */
    /* NC */	
    
    /* DDR SRAM */
    VF610_PAD_DDR_A15__DDR_A_15,
	VF610_PAD_DDR_A14__DDR_A_14,
	VF610_PAD_DDR_A13__DDR_A_13,
    VF610_PAD_DDR_A12__DDR_A_12,
	VF610_PAD_DDR_A11__DDR_A_11,
	VF610_PAD_DDR_A10__DDR_A_10,
	VF610_PAD_DDR_A9__DDR_A_9,
	VF610_PAD_DDR_A8__DDR_A_8,
	VF610_PAD_DDR_A7__DDR_A_7,
	VF610_PAD_DDR_A6__DDR_A_6,
	VF610_PAD_DDR_A5__DDR_A_5,
	VF610_PAD_DDR_A4__DDR_A_4,
	VF610_PAD_DDR_A3__DDR_A_3,
	VF610_PAD_DDR_A2__DDR_A_2,
	VF610_PAD_DDR_A1__DDR_A_1,
	VF610_PAD_DDR_BA2__DDR_BA_2,
	VF610_PAD_DDR_BA1__DDR_BA_1,
	VF610_PAD_DDR_BA0__DDR_BA_0,
	VF610_PAD_DDR_CAS__DDR_CAS_B,
	VF610_PAD_DDR_CKE__DDR_CKE_0,
	VF610_PAD_DDR_CLK__DDR_CLK_0,
	VF610_PAD_DDR_CS__DDR_CS_B_0,
	VF610_PAD_DDR_D15__DDR_D_15,
	VF610_PAD_DDR_D14__DDR_D_14,
	VF610_PAD_DDR_D13__DDR_D_13,
	VF610_PAD_DDR_D12__DDR_D_12,
	VF610_PAD_DDR_D11__DDR_D_11,
	VF610_PAD_DDR_D10__DDR_D_10,
	VF610_PAD_DDR_D9__DDR_D_9,
	VF610_PAD_DDR_D8__DDR_D_8,
	VF610_PAD_DDR_D7__DDR_D_7,
	VF610_PAD_DDR_D6__DDR_D_6,
	VF610_PAD_DDR_D5__DDR_D_5,
	VF610_PAD_DDR_D4__DDR_D_4,
	VF610_PAD_DDR_D3__DDR_D_3,
	VF610_PAD_DDR_D2__DDR_D_2,
	VF610_PAD_DDR_D1__DDR_D_1,
	VF610_PAD_DDR_D0__DDR_D_0,
	VF610_PAD_DDR_DQM1__DDR_DQM_1,
	VF610_PAD_DDR_DQM0__DDR_DQM_0,
	VF610_PAD_DDR_DQS1__DDR_DQS_1,
	VF610_PAD_DDR_DQS0__DDR_DQS_0,
	VF610_PAD_DDR_RAS__DDR_RAS_B,
	VF610_PAD_DDR_WE__DDR_WE_B,
	VF610_PAD_DDR_ODT1__DDR_ODT_0,
	VF610_PAD_DDR_ODT0__DDR_ODT_1,

    /* NAND */
	VF610_PAD_PTD31__NFC_IO15,
	VF610_PAD_PTD30__NFC_IO14,
	VF610_PAD_PTD29__NFC_IO13,
	VF610_PAD_PTD28__NFC_IO12,
	VF610_PAD_PTD27__NFC_IO11,
	VF610_PAD_PTD26__NFC_IO10,
	VF610_PAD_PTD25__NFC_IO9,
	VF610_PAD_PTD24__NFC_IO8,
	VF610_PAD_PTD23__NFC_IO7,
	VF610_PAD_PTD22__NFC_IO6,
	VF610_PAD_PTD21__NFC_IO5,
	VF610_PAD_PTD20__NFC_IO4,
	VF610_PAD_PTD19__NFC_IO3,
	VF610_PAD_PTD18__NFC_IO2,
	VF610_PAD_PTD17__NFC_IO1,
	VF610_PAD_PTD16__NFC_IO0,
	VF610_PAD_PTB24__NFC_WEB,
	VF610_PAD_PTB25__NFC_CE0B,
	VF610_PAD_PTB27__NFC_REB,
	VF610_PAD_PTC26__NFC_RBB,
	VF610_PAD_PTC27__NFC_ALE,
	VF610_PAD_PTC28__NFC_CLE,

    /* I2C0 */
	VF610_PAD_PTB14__I2C0_SCL,
	VF610_PAD_PTB15__I2C0_SDA,
};


static int twr_mem_init(void)
{
	arm_add_mem_device("ram0", VF610_SDRAM_BASE, VF610_SDRAM_SIZE);

	return 0;
}
mem_initcall(twr_mem_init);

#define LOCO_SD1_CD			IMX_GPIO_NR(5, 6)

static struct esdhc_platform_data loco_sd1_data = {
	.cd_gpio = LOCO_SD1_CD,
	.wp_gpio = LOCO_SD1_WP,
	.cd_type = ESDHC_CD_GPIO,
	.wp_type = ESDHC_WP_NONE,
};

static int twr_devices_init(void)
{
	vf610_iim_register_fec_ethaddr();
	vf610_add_fec(&fec_info);
	vf610_add_mmc0(&loco_sd1_data);
    /*TODO port vf610 nand driver*/
	/*vf610_add_nand(&nand_info); */

	if (IS_ENABLED(CONFIG_ARCH_IMX_EXTERNAL_BOOT_NAND)) {
		vf610_barebox_boot_nand_external(0);
    }

	armlinux_set_architecture(MACH_TYPE_VYBRID_VF6XX);

	return 0;
}
device_initcall(twr_devices_init);

static int twr_part_init(void)
{
	devfs_add_partition("disk0", 0x00000, 0x40000, DEVFS_PARTITION_FIXED, "self0");
	devfs_add_partition("disk0", 0x40000, 0x20000, DEVFS_PARTITION_FIXED, "env0");

	return 0;
}
late_initcall(twr_part_init);

static int twr_console_init(void)
{
	mxc_iomux_v3_setup_multiple_pads(twr_pads, ARRAY_SIZE(twr_pads));

	barebox_set_model("Freescale Vf610-twr");
	barebox_set_hostname("vf610-twr");
	
	vf610_add_uart1();
	return 0;
}
console_initcall(twr_console_init);
