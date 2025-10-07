#include <stdint.h>
#include "tm4c123gh6pm.h" // Device register definitions

// Function Prototypes - Required by startup code
void SysTick_Handler(void);
void GPIOF_Handler(void);

// Local Function Prototypes
void SysTick_Init(void);
void PortF_Init(void);

int main(void)
{
    // 1. Initialization
    PortF_Init();
    SysTick_Init();

    // 2. Enable Master Interrupts
    __asm("    CPSIE I\n");

    while(1)
    {
        // Idle loop
    }
}

// Configures SysTick for 1 second periodic interrupt
void SysTick_Init(void)
{
    NVIC_ST_CTRL_R = 0;
    NVIC_ST_RELOAD_R = 16000000 - 1;
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_CTRL_R = 0x07;
}

// Configures GPIO Port F for LEDs and two switch interrupts
void PortF_Init(void)
{
    SYSCTL_RCGCGPIO_R |= 0x20;
    while((SYSCTL_PRGPIO_R & 0x20) == 0){};

    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R = 0x1F;

    GPIO_PORTF_DIR_R = 0x0E;        // PF1,2,3 output (LEDs), PF0,4 input (switches)
    GPIO_PORTF_DEN_R = 0x1F;
    GPIO_PORTF_PUR_R = 0x11;        // Pull-ups on PF0 (SW2) and PF4 (SW1)

    // Configure interrupts on PF0 and PF4 (falling edge)
    GPIO_PORTF_IS_R &= ~0x11;
    GPIO_PORTF_IBE_R &= ~0x11;
    GPIO_PORTF_IEV_R &= ~0x11;

    GPIO_PORTF_ICR_R = 0x11;        // Clear flags
    GPIO_PORTF_IM_R |= 0x11;        // Unmask interrupts

    // Set priority and enable Port F in NVIC
    NVIC_PRI7_R = (NVIC_PRI7_R & 0xFF3FFFFF) | 0x00A00000;
    NVIC_EN0_R |= 0x40000000;
}

// SysTick Interrupt Service Routine: Toggles the Red LED (PF1)
void SysTick_Handler(void)
{
    GPIO_PORTF_DATA_R ^= 0x02;
}

// GPIO Port F Interrupt Service Routine: Handles button presses
void GPIOF_Handler(void)
{
    // Handle SW2 (PF0)
    if (GPIO_PORTF_RIS_R & 0x01) {
        GPIO_PORTF_ICR_R = 0x01;
        GPIO_PORTF_DATA_R ^= 0x04;  // Toggle BLUE LED (PF2)
    }

    // Handle SW1 (PF4)
    if (GPIO_PORTF_RIS_R & 0x10) {
        GPIO_PORTF_ICR_R = 0x10;
        GPIO_PORTF_DATA_R ^= 0x08;  // Toggle GREEN LED (PF3)
    }
}