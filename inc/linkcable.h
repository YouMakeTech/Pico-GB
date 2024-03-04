
#ifndef LINKCABLE_H
#define LINKCABLE_H


#include "hardware/irq.h"
#include "hardware/pio.h"
#include "hardware/gpio.h"
#include "linkcable_slave.pio.h"
#include "linkcable_master.pio.h"

#define LINKCABLE_PIO       pio1
#define LINKCABLE_SM        0

extern bool gLinkcable_isSlave;
extern uint gLinkgcable_pio_slave_pc;
extern uint gLinkgcable_pio_master_pc;

static inline void linkcable_isr_clear(void) {
    pio_interrupt_clear(LINKCABLE_PIO, 0);
}

static inline void linkcable_set_slave(bool slave){
    if (gLinkcable_isSlave != slave){
        gLinkcable_isSlave = slave;
        pio_sm_set_enabled(LINKCABLE_PIO, LINKCABLE_SM, false);
        pio_sm_clear_fifos(LINKCABLE_PIO, LINKCABLE_SM);
        pio_sm_restart(LINKCABLE_PIO, LINKCABLE_SM);
        pio_sm_clkdiv_restart(LINKCABLE_PIO, LINKCABLE_SM);
        if (slave){
            linkcable_slave_program_init(LINKCABLE_PIO, LINKCABLE_SM, gLinkgcable_pio_slave_pc);
        }else{
            linkcable_master_program_init(LINKCABLE_PIO, LINKCABLE_SM, gLinkgcable_pio_master_pc);        
        }
        pio_sm_set_enabled(LINKCABLE_PIO, LINKCABLE_SM, true);   
    }    
}

static inline void linkcable_start(uint8_t byte){
    pio_sm_clear_fifos(LINKCABLE_PIO, LINKCABLE_SM);
    pio_sm_put(LINKCABLE_PIO, LINKCABLE_SM, byte);
}

static inline uint8_t linkcable_receive(void) {
    return pio_sm_get(LINKCABLE_PIO, LINKCABLE_SM);
}

void linkcable_init(irq_handler_t irq_handler);

void linkcable_shutdown(void);

#endif //LINKCABLE_H
