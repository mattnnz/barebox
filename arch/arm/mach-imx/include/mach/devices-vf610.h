
#include <mach/devices.h>
#include <mach/vf610-regs.h>

static inline struct device_d *vf610_add_i2c0(struct i2c_platform_data *pdata)
{
	return imx_add_i2c((void *)VF610_I2C0_BASE_ADDR, 0, pdata);
}

static inline struct device_d *vf610_add_i2c1(struct i2c_platform_data *pdata)
{
	return imx_add_i2c((void *)VF610_I2C1_BASE_ADDR, 1, pdata);
}

static inline struct device_d *vf610_add_i2c2(struct i2c_platform_data *pdata)
{
       return imx_add_i2c((void *)VF610_I2C2_BASE_ADDR, 2, pdata);
}

static inline struct device_d *vf610_add_i2c3(struct i2c_platform_data *pdata)
{
       return imx_add_i2c((void *)VF610_I2C3_BASE_ADDR, 2, pdata);
}

static inline struct device_d *vf610_add_uart0(void)
{
	return imx_add_uart_imx21((void *)VF610_UART0_BASE_ADDR, 0);
}

static inline struct device_d *vf610_add_uart1(void)
{
	return imx_add_uart_imx21((void *)VF610_UART1_BASE_ADDR, 1);
}

static inline struct device_d *vf610_add_uart2(void)
{
	return imx_add_uart_imx21((void *)VF610_UART2_BASE_ADDR, 2);
}

static inline struct device_d *vf610_add_uart3(void)
{
	return imx_add_uart_imx21((void *)VF610_UART3_BASE_ADDR, 3);
}

static inline struct device_d *vf610_add_uart4(void)
{
	return imx_add_uart_imx21((void *)VF610_UART4_BASE_ADDR, 3);
}

static inline struct device_d *vf610_add_uart5(void)
{
	return imx_add_uart_imx21((void *)VF610_UART5_BASE_ADDR, 3);
}

static inline struct device_d *vf610_add_fec(struct fec_platform_data *pdata)
{
	return imx_add_fec_imx27((void *)VF610_FEC_BASE_ADDR, pdata);
}

static inline struct device_d *vf610_add_mmc0(struct esdhc_platform_data *pdata)
{
	return imx_add_esdhc((void *)VF610_ESDHC1_BASE_ADDR, 0, pdata);
}

static inline struct device_d *vf610_add_mmc1(struct esdhc_platform_data *pdata)
{
	return imx_add_esdhc((void *)VF610_ESDHC2_BASE_ADDR, 1, pdata);
}

static inline struct device_d *vf610_add_nand(struct imx_nand_platform_data *pdata)
{
    return imx_add_nand_vf610((void *)VF610_NFC_BASE_ADDR, pdata);
}

