#ifndef __FT_EXIT_H
#define __FT_EXIT_H

typedef void (*exit_irq_handler_t) (void);

void exit_init(void);

void exit_irq_enable_set(bool status);

void exit_irq_handler_register(exit_irq_handler_t handler);

#endif

