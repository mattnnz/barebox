/*
 * Copyright 2013 Freescale Semiconductor, Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __MACH_VF610_CCM_REGS_H__
#define __MACH_VF610_CCM_REGS_H__

#ifndef __ASSEMBLY__

/* Clock Controller Module (CCM) */
struct ccm_reg {
	u32 ccr;
	u32 csr;
	u32 ccsr;
	u32 cacrr;
	u32 cscmr1;
	u32 cscdr1;
	u32 cscdr2;
	u32 cscdr3;
	u32 cscmr2;
	u32 cscdr4;
	u32 ctor;
	u32 clpcr;
	u32 cisr;
	u32 cimr;
	u32 ccosr;
	u32 cgpr;
	u32 ccgr0;
	u32 ccgr1;
	u32 ccgr2;
	u32 ccgr3;
	u32 ccgr4;
	u32 ccgr5;
	u32 ccgr6;
	u32 ccgr7;
	u32 ccgr8;
	u32 ccgr9;
	u32 ccgr10;
	u32 ccgr11;
	u32 cmeor0;
	u32 cmeor1;
	u32 cmeor2;
	u32 cmeor3;
	u32 cmeor4;
	u32 cmeor5;
	u32 cppdsr;
	u32 ccowr;
	u32 ccpgr0;
	u32 ccpgr1;
	u32 ccpgr2;
	u32 ccpgr3;
};

/* Analog components control digital interface (ANADIG) */
struct anadig_reg {
	u32 reserved_0x000[4];
	u32 pll3_ctrl;
	u32 reserved_0x014[3];
	u32 pll7_ctrl;
	u32 reserved_0x024[3];
	u32 pll2_ctrl;
	u32 reserved_0x034[3];
	u32 pll2_ss;
	u32 reserved_0x044[3];
	u32 pll2_num;
	u32 reserved_0x054[3];
	u32 pll2_denom;
	u32 reserved_0x064[3];
	u32 pll4_ctrl;
	u32 reserved_0x074[3];
	u32 pll4_num;
	u32 reserved_0x084[3];
	u32 pll4_denom;
	u32 reserved_0x094[3];
	u32 pll6_ctrl;
	u32 reserved_0x0A4[3];
	u32 pll6_num;
	u32 reserved_0x0B4[3];
	u32 pll6_denom;
	u32 reserved_0x0C4[7];
	u32 pll5_ctrl;
	u32 reserved_0x0E4[3];
	u32 pll3_pfd;
	u32 reserved_0x0F4[3];
	u32 pll2_pfd;
	u32 reserved_0x104[3];
	u32 reg_1p1;
	u32 reserved_0x114[3];
	u32 reg_3p0;
	u32 reserved_0x124[3];
	u32 reg_2p5;
	u32 reserved_0x134[7];
	u32 ana_misc0;
	u32 reserved_0x154[3];
	u32 ana_misc1;
	u32 reserved_0x164[63];
	u32 anadig_digprog;
	u32 reserved_0x264[3];
	u32 pll1_ctrl;
	u32 reserved_0x274[3];
	u32 pll1_ss;
	u32 reserved_0x284[3];
	u32 pll1_num;
	u32 reserved_0x294[3];
	u32 pll1_denom;
	u32 reserved_0x2A4[3];
	u32 pll1_pdf;
	u32 reserved_0x2B4[3];
	u32 pll_lock;
};
#endif

#define VF610_CCM_CCR			0x00
#define VF610_CCM_CSR			0x04
#define VF610_CCM_CCSR  		0x08
#define VF610_CCM_CACRR	    	0x0c
#define VF610_CCM_CSCMR1		0x10
#define VF610_CCM_CSCDR1		0x14
#define VF610_CCM_CSCDR2		0x18
#define VF610_CCM_CSCDR3		0x1c
#define VF610_CCM_CSCMR2		0x20
#define VF610_CCM_CSCDR4		0x24
#define VF610_CCM_CLPCR		    0x2c
#define VF610_CCM_CISR  		0x30
#define VF610_CCM_CIMR	    	0x34
#define VF610_CCM_CGPR	    	0x3c
#define VF610_CCM_CCGR0		    0x40
#define VF610_CCM_CCGR1 		0x44
#define VF610_CCM_CCGR2	    	0x48
#define VF610_CCM_CCGR3	    	0x4c
#define VF610_CCM_CCGR4	    	0x50
#define VF610_CCM_CCGR5	    	0x54
#define VF610_CCM_CCGR6	    	0x58
#define VF610_CCM_CCGR7	    	0x5c
#define VF610_CCM_CCGR8	    	0x60
#define VF610_CCM_CCGR9	    	0x64
#define VF610_CCM_CCGR10		0x68
#define VF610_CCM_CCGR11		0x6c
#define VF610_CCM_CCGRx(x)		(CCM_CCGR0 + (x) * 4)
#define VF610_CCM_CMEOR0		0x70
#define VF610_CCM_CMEOR1		0x74
#define VF610_CCM_CMEOR2		0x78
#define VF610_CCM_CMEOR3		0x7c
#define VF610_CCM_CMEOR4		0x80
#define VF610_CCM_CMEOR5		0x84
#define VF610_CCM_CPPDSR		0x88
#define VF610_CCM_CCOWR		    0x8c
#define VF610_CCM_CCPGR0		0x90
#define VF610_CCM_CCPGR1		0x94
#define VF610_CCM_CCPGR2		0x98
#define VF610_CCM_CCPGR3		0x9c

#define VF610_CCM_CCGRx_CGn(n)	((n) * 2)

#define VF610_PFD_PLL1_BASE		(anatop_base + 0x2b0)
#define VF610_PFD_PLL2_BASE		(anatop_base + 0x100)
#define VF610_PFD_PLL3_BASE		(anatop_base + 0xf0)
#define VF610_PLL1_CTRL	    	(anatop_base + 0x270)
#define VF610_PLL2_CTRL	    	(anatop_base + 0x30)
#define VF610_PLL3_CTRL	    	(anatop_base + 0x10)
#define VF610_PLL4_CTRL	    	(anatop_base + 0x70)
#define VF610_PLL5_CTRL	    	(anatop_base + 0xe0)
#define VF610_PLL6_CTRL	    	(anatop_base + 0xa0)
#define VF610_PLL7_CTRL	    	(anatop_base + 0x20)
#define VF610_CCM_CCR_FIRC_EN				(1 << 16)
#define VF610_CCM_CCR_OSCNT_MASK			0xff
#define VF610_CCM_CCR_OSCNT(v)		    	((v) & 0xff)

#define VF610_CCM_CCSR_PLL2_PFD_CLK_SEL_OFFSET  	19
#define VF610_CCM_CCSR_PLL2_PFD_CLK_SEL_MASK		(0x7 << 19)
#define VF610_CCM_CCSR_PLL2_PFD_CLK_SEL(v)	    	(((v) & 0x7) << 19)

#define VF610_CCM_CCSR_PLL1_PFD_CLK_SEL_OFFSET	    16
#define VF610_CCM_CCSR_PLL1_PFD_CLK_SEL_MASK		(0x7 << 16)
#define VF610_CCM_CCSR_PLL1_PFD_CLK_SEL(v)	    	(((v) & 0x7) << 16)

#define VF610_CCM_CCSR_PLL2_PFD4_EN			(1 << 15)
#define VF610_CCM_CCSR_PLL2_PFD3_EN			(1 << 14)
#define VF610_CCM_CCSR_PLL2_PFD2_EN			(1 << 13)
#define VF610_CCM_CCSR_PLL2_PFD1_EN			(1 << 12)
#define VF610_CCM_CCSR_PLL1_PFD4_EN			(1 << 11)
#define VF610_CCM_CCSR_PLL1_PFD3_EN			(1 << 10)
#define VF610_CCM_CCSR_PLL1_PFD2_EN			(1 << 9)
#define VF610_CCM_CCSR_PLL1_PFD1_EN			(1 << 8)

#define VF610_CCM_CCSR_DDRC_CLK_SEL(v)		((v) << 6)
#define VF610_CCM_CCSR_FAST_CLK_SEL(v)		((v) << 5)

#define VF610_CCM_CCSR_SYS_CLK_SEL_OFFSET		    0
#define VF610_CCM_CCSR_SYS_CLK_SEL_MASK	    	    0x7
#define VF610_CCM_CCSR_SYS_CLK_SEL(v)			    ((v) & 0x7)

#define VF610_CCM_CACRR_IPG_CLK_DIV_OFFSET		    11
#define VF610_CCM_CACRR_IPG_CLK_DIV_MASK		    (0x3 << 11)
#define VF610_CCM_CACRR_IPG_CLK_DIV(v)	        	(((v) & 0x3) << 11)
#define VF610_CCM_CACRR_BUS_CLK_DIV_OFFSET		    3
#define VF610_CCM_CACRR_BUS_CLK_DIV_MASK		    (0x7 << 3)
#define VF610_CCM_CACRR_BUS_CLK_DIV(v)	    	    (((v) & 0x7) << 3)
#define VF610_CCM_CACRR_ARM_CLK_DIV_OFFSET		    0
#define VF610_CCM_CACRR_ARM_CLK_DIV_MASK		    0x7
#define VF610_CCM_CACRR_ARM_CLK_DIV(v)	    	    ((v) & 0x7)

#define VF610_CCM_CSCMR1_ESDHC1_CLK_SEL_OFFSET	    18
#define VF610_CCM_CSCMR1_ESDHC1_CLK_SEL_MASK	    (0x3 << 18)
#define VF610_CCM_CSCMR1_ESDHC1_CLK_SEL(v)    	    (((v) & 0x3) << 18)

#define VF610_CCM_CSCDR1_RMII_CLK_EN			    (1 << 24)

#define VF610_CCM_CSCDR2_ESDHC1_EN		    	    (1 << 29)
#define VF610_CCM_CSCDR2_ESDHC1_CLK_DIV_OFFSET	    20
#define VF610_CCM_CSCDR2_ESDHC1_CLK_DIV_MASK	    (0xf << 20)
#define VF610_CCM_CSCDR2_ESDHC1_CLK_DIV(v)	    	(((v) & 0xf) << 20)
#define VF610_CCM_CSCDR2_NFC_CLK_INV		    	(1 << 14)
#define VF610_CCM_CSCDR2_NFC_CLK_FRAC_DIV_EN	    (1 << 13)
#define VF610_CCM_CSCDR2_NFC_EN					    (1 << 9)
#define VF610_CCM_CSCDR2_NFC_CLK_FRAC_DIV_OFFSET    4
#define VF610_CCM_CSCDR2_NFC_CLK_FRAC_DIV_MASK		(0xf << 4)
#define VF610_CCM_CSCDR2_NFC_CLK_FRAC_DIV(v)		(((v) & 0xf) << 4)

#define VF610_CCM_CSCDR3_NFC_PRE_DIV_OFFSET			13
#define VF610_CCM_CSCDR3_NFC_PRE_DIV_MASK			(0x7 << 13)
#define VF610_CCM_CSCDR3_NFC_PRE_DIV(v)				(((v) & 0x7) << 13)

#define VF610_CCM_CSCMR2_RMII_CLK_SEL_OFFSET		4
#define VF610_CCM_CSCMR2_RMII_CLK_SEL_MASK		    (0x3 << 4)
#define VF610_CCM_CSCMR2_RMII_CLK_SEL(v)		    (((v) & 0x3) << 4)

#define VF610_CCM_REG_CTRL_MASK		            0xffffffff
#define VF610_CCM_CCGR0_UART0_CTRL_MASK         (0x3 << 14)
#define VF610_CCM_CCGR0_UART1_CTRL_MASK	       	(0x3 << 16)
#define VF610_CCM_CCGR1_PIT_CTRL_MASK			(0x3 << 14)
#define VF610_CCM_CCGR1_WDOGA5_CTRL_MASK		(0x3 << 28)
#define VF610_CCM_CCGR2_IOMUXC_CTRL_MASK		(0x3 << 16)
#define VF610_CCM_CCGR2_PORTA_CTRL_MASK		    (0x3 << 18)
#define VF610_CCM_CCGR2_PORTB_CTRL_MASK		    (0x3 << 20)
#define VF610_CCM_CCGR2_PORTC_CTRL_MASK		    (0x3 << 22)
#define VF610_CCM_CCGR2_PORTD_CTRL_MASK		    (0x3 << 24)
#define VF610_CCM_CCGR2_PORTE_CTRL_MASK		    (0x3 << 26)
#define VF610_CCM_CCGR3_ANADIG_CTRL_MASK		0x3
#define VF610_CCM_CCGR4_WKUP_CTRL_MASK		    (0x3 << 20)
#define VF610_CCM_CCGR4_CCM_CTRL_MASK			(0x3 << 22)
#define VF610_CCM_CCGR4_GPC_CTRL_MASK			(0x3 << 24)
#define VF610_CCM_CCGR4_I2C0_CTRL_MASK	    	(0x3 << 12)
#define VF610_CCM_CCGR6_OCOTP_CTRL_MASK	    	(0x3 << 10)
#define VF610_CCM_CCGR6_DDRMC_CTRL_MASK	    	(0x3 << 28)
#define VF610_CCM_CCGR7_SDHC1_CTRL_MASK	    	(0x3 << 4)
#define VF610_CCM_CCGR9_FEC0_CTRL_MASK		    0x3
#define VF610_CCM_CCGR9_FEC1_CTRL_MASK	    	(0x3 << 2)
#define VF610_CCM_CCGR10_NFC_CTRL_MASK  		0x3

#define VF610_ANADIG_PLL5_CTRL_BYPASS           (1 << 16)
#define VF610_ANADIG_PLL5_CTRL_ENABLE           (1 << 13)
#define VF610_ANADIG_PLL5_CTRL_POWERDOWN        (1 << 12)
#define VF610_ANADIG_PLL5_CTRL_DIV_SELECT		1
#define VF610_ANADIG_PLL2_CTRL_ENABLE			(1 << 13)
#define VF610_ANADIG_PLL2_CTRL_POWERDOWN		(1 << 12)
#define VF610_ANADIG_PLL2_CTRL_DIV_SELECT		1
#define VF610_ANADIG_PLL1_CTRL_ENABLE			(1 << 13)
#define VF610_ANADIG_PLL1_CTRL_POWERDOWN		(1 << 12)
#define VF610_ANADIG_PLL1_CTRL_DIV_SELECT		1

#define VF610_FASE_CLK_FREQ		    24000000
#define VF610_SLOW_CLK_FREQ		    32000
#define VF610_PLL1_PFD1_FREQ		500000000
#define VF610_PLL1_PFD2_FREQ		452000000
#define VF610_PLL1_PFD3_FREQ		396000000
#define VF610_PLL1_PFD4_FREQ		528000000
#define VF610_PLL1_MAIN_FREQ		528000000
#define VF610_PLL2_PFD1_FREQ		500000000
#define VF610_PLL2_PFD2_FREQ		396000000
#define VF610_PLL2_PFD3_FREQ		339000000
#define VF610_PLL2_PFD4_FREQ		413000000
#define VF610_PLL2_MAIN_FREQ		528000000
#define VF610_PLL3_MAIN_FREQ		480000000
#define VF610_PLL3_PFD3_FREQ		298000000
#define VF610_PLL5_MAIN_FREQ		500000000

#define VF610_ENET_EXTERNAL_CLK	    50000000
#define VF610_AUDIO_EXTERNAL_CLK	24576000

#endif /*__MACH_VF610_CCM_REGS_H__ */
