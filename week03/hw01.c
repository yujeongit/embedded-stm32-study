#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
    int i;

    volatile uint32_t *gpioc_crh=(uint32_t *)(0x40011000+0x04);
    volatile uint32_t *gpioc_odr=(uint32_t *)(0x40011000+0x0c);

    /* System initialization */
    *((volatile uint32_t *)(0x40021000)) |= 0x00000001;
    *((volatile uint32_t *)(0x40021004)) &= 0xF8FF0000;
    *((volatile uint32_t *)(0x40021000)) &= 0xFEF6FFFF;
    *((volatile uint32_t *)(0x40021000)) &= 0xFFFBFFFF;
    *((volatile uint32_t *)(0x40021004)) &= 0xFF80FFFF;
    *((volatile uint32_t *)(0x40021008))  = 0x009F0000;
    *((volatile uint32_t *)(0xE000ED08))  = 0x08000000;

    *gpioc_crh = 0x30000;

    *gpioc_odr = 0x1000;


    /* Loop forever */
    for(;;){

    	*gpioc_odr = 0x0000;

    	for (i=0; i<100000000; i++);

        *gpioc_odr = 0x1000;

        for (i=0; i<100000000; i++);
    };

    /*
     gpioc_odr = 0x0000; →초록 LED가 꺼짐,
     gpioc_odr = 0x1000; → 초록 LED가 켜짐
    */


    return 0;
}
