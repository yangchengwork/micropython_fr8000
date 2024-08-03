
#define WEAK    __attribute__((weak))

WEAK void Reset_Handler(void);
WEAK void NMI_Handler(void);
WEAK void HardFault_Handler(void);
WEAK void MemManage_Handler(void);
WEAK void BusFault_Handler(void);
WEAK void UsageFault_Handler(void);
WEAK void SVC_Handler(void);
WEAK void DebugMon_Handler(void);
WEAK void PendSV_Handler(void);
WEAK void SysTick_Handler(void);

WEAK void rwble_isr_ram(void);
WEAK void dma_isr(void);
WEAK void timer0_isr(void);
WEAK void timer1_isr(void);
WEAK void i2c0_isr(void);
WEAK void i2c1_isr(void);
WEAK void spim0_isr(void);
WEAK void spim1_isr(void);
WEAK void spis_isr(void);
WEAK void uart0_isr(void);
WEAK void uart1_isr(void);
WEAK void pdm_isr(void);
WEAK void exti_isr(void);
WEAK void pmu_isr(void);
WEAK void pwm_isr(void);
WEAK void usb_isr(void);
WEAK void lcd_isr(void);
WEAK void i2s_isr(void);

typedef void (* const pHandler)(void);

__attribute__ ((section(".isr_vector"), used)) pHandler __isr_vectors[] =
{
    0x00000000,             // The initial stack pointer
    Reset_Handler,          // The reset handler
    NMI_Handler,            // The NMI handler
    HardFault_Handler,      // The hard fault handler
    MemManage_Handler,      // The MPU fault handler
    BusFault_Handler,       // The bus fault handler
    UsageFault_Handler,     // The usage fault handler
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    0,                      // Reserved
    SVC_Handler,            // SVCall handler
    DebugMon_Handler,       // Debug monitor handler
    0,                      // Reserved
    PendSV_Handler,         // The PendSV handler
    SysTick_Handler,        // The SysTick handler

    // ----------------------------------------------------------------------
    // DEVICE vectors
    // ----------------------------------------------------------------------
    rwble_isr_ram,          // 0
    dma_isr,                // 1
    timer0_isr,             // 2
    timer1_isr,             // 3
    i2c0_isr,               // 4
    i2c1_isr,               // 5
    spim0_isr,              // 6
    spim1_isr,              // 7
    spis_isr,               // 8
    uart0_isr,              // 9
    uart1_isr,              // 10
    pdm_isr,                // 11
    0,                      // 12
    0,                      // 13
    exti_isr,               // 14
    pmu_isr,                // 15
    0,                      // 16
    0,                      // 17
    pwm_isr,                // 18
    usb_isr,                // 19
    0,                      // 20
    lcd_isr,                // 21
    0,                      // 22
    i2s_isr,                // 23
    0,
    0,
};
