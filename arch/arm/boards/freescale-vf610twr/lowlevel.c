#include <common.h>
#include <mach/esdctl.h> /* not need possibly replace with vf610 SRAM Controller driver */
#include <mach/generic.h>
#include <mach/vf610-regs.h>
#include <asm/barebox-arm-head.h>

void __naked barebox_arm_reset_vector(void)
{
	arm_cpu_lowlevel_init();
	arm_setup_stack(IRAM_BASE_ADDR + IRAM_SIZE - 8);
	imx53_barebox_entry(NULL);
}
