//*****************************************************************************
//
// Startup code for use with TI's Code Composer Studio.
// This version uses clean comments and corrects symbol visibility (no 'static'
// on system handlers) and updates application vector entries.
//
//*****************************************************************************

#include <stdint.h>

//*****************************************************************************
// Forward declaration of the essential system handlers.
// The 'static' qualifier is intentionally removed to ensure global linkage
// and resolve the linker errors seen previously.
//*****************************************************************************
void ResetISR(void);
void NmiSR(void);
void FaultISR(void);
void IntDefaultHandler(void);

//*****************************************************************************
// External declaration for the reset handler and stack top.
//*****************************************************************************
extern void _c_int00(void);
extern uint32_t __STACK_TOP;

//*****************************************************************************
// External declarations for the interrupt handlers defined in main.c.
//*****************************************************************************
extern void SysTick_Handler(void);
extern void GPIOF_Handler(void);

//*****************************************************************************
// The vector table.
//*****************************************************************************
#pragma DATA_SECTION(g_pfnVectors, ".intvecs")
void (* const g_pfnVectors[])(void) =
{
    (void (*)(void))((uint32_t)&__STACK_TOP), // The initial stack pointer
    ResetISR,                                 // The reset handler
    NmiSR,                                    // The NMI handler
    FaultISR,                                 // The hard fault handler
    IntDefaultHandler,                        // The MPU fault handler
    IntDefaultHandler,                        // The bus fault handler
    IntDefaultHandler,                        // The usage fault handler
    0,                                        // Reserved
    0,                                        // Reserved
    0,                                        // Reserved
    0,                                        // Reserved
    IntDefaultHandler,                        // SVCall handler
    IntDefaultHandler,                        // Debug monitor handler
    0,                                        // Reserved
    IntDefaultHandler,                        // The PendSV handler
    SysTick_Handler,                          // SysTick handler (Index 15)
    IntDefaultHandler,                        // GPIO Port A
    IntDefaultHandler,                        // GPIO Port B
    IntDefaultHandler,                        // GPIO Port C
    IntDefaultHandler,                        // GPIO Port D
    IntDefaultHandler,                        // GPIO Port E
    IntDefaultHandler,                        // UART0 Rx and Tx
    IntDefaultHandler,                        // UART1 Rx and Tx
    IntDefaultHandler,                        // SSI0 Rx and Tx
    IntDefaultHandler,                        // I2C0 Master and Slave
    IntDefaultHandler,                        // PWM Fault
    IntDefaultHandler,                        // PWM Generator 0
    IntDefaultHandler,                        // PWM Generator 1
    IntDefaultHandler,                        // PWM Generator 2
    IntDefaultHandler,                        // Quadrature Encoder 0
    IntDefaultHandler,                        // ADC Sequence 0
    IntDefaultHandler,                        // ADC Sequence 1
    IntDefaultHandler,                        // ADC Sequence 2
    IntDefaultHandler,                        // ADC Sequence 3
    IntDefaultHandler,                        // Watchdog timer
    IntDefaultHandler,                        // Timer 0 subtimer A
    IntDefaultHandler,                        // Timer 0 subtimer B
    IntDefaultHandler,                        // Timer 1 subtimer A
    IntDefaultHandler,                        // Timer 1 subtimer B
    IntDefaultHandler,                        // Timer 2 subtimer A
    IntDefaultHandler,                        // Timer 2 subtimer B
    IntDefaultHandler,                        // Analog Comparator 0
    IntDefaultHandler,                        // Analog Comparator 1
    IntDefaultHandler,                        // Analog Comparator 2
    IntDefaultHandler,                        // System Control (PLL, OSC, BO)
    IntDefaultHandler,                        // FLASH Control
    GPIOF_Handler,                            // GPIO Port F (IRQ 30)
    IntDefaultHandler,                        // GPIO Port G
    IntDefaultHandler,                        // GPIO Port H
    // ... (Vector table continues with IntDefaultHandler for unused peripherals)
};

//*****************************************************************************
//
// Reset Handler definition. Jumps to the C runtime initialization.
//
//*****************************************************************************
void ResetISR(void)
{
    __asm("     .global _c_int00\n"
          "     b.w     _c_int00");
}

//*****************************************************************************
//
// System fault handlers (made globally visible).
//
//*****************************************************************************
void NmiSR(void)
{
    while(1) {}
}
void FaultISR(void)
{
    while(1) {}
}
void IntDefaultHandler(void)
{
    while(1) {}
}