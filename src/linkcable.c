
#include "linkcable.h"
#include "pico/stdlib.h"
bool gLinkcable_isSlave = false;
uint gLinkgcable_pio_slave_pc = 0;
uint gLinkgcable_pio_master_pc = 0;

void linkcable_init(irq_handler_t irq_handler){
    gpio_set_function(PIN_SCK, GPIO_FUNC_PIO1);
    gpio_set_function(PIN_SIN, GPIO_FUNC_PIO1);
    gpio_set_function(PIN_SOUT, GPIO_FUNC_PIO1);

    gLinkgcable_pio_slave_pc = pio_add_program(LINKCABLE_PIO, &linkcable_slave_program);
    gLinkgcable_pio_master_pc = pio_add_program(LINKCABLE_PIO, &linkcable_master_program);

    pio_set_irq0_source_enabled(LINKCABLE_PIO, pis_interrupt0, true);
    irq_set_exclusive_handler(PIO1_IRQ_0, irq_handler);
    irq_set_enabled(PIO1_IRQ_0, true);
    gLinkcable_isSlave = false;
    linkcable_set_slave(true);
}

void __not_in_flash_func(linkcable_shutdown)(void){
//     irq_set_enabled(LINK_DMA_IRQ, false);
//     dma_channel_set_irq1_enabled(gLinkcable_dma_rx, false);
//     dma_channel_abort(gLinkcable_dma_rx);
//     dma_channel_abort(gLinkcable_dma_tx);
//     dma_unclaim_mask((1u << gLinkcable_dma_tx) | (1u << gLinkcable_dma_rx));
//     spi_deinit(spi1);
}