#ifndef DIP_H
#define DIP_H

#define DIP0 (1 << 7)
#define DIP1 (1 << 6)
#define DIP2 (1 << 5)
#define DIP3 (1 << 4)
#define DIP4 (1 << 3)
#define DIP5 (1 << 2)
#define DIP6 (1 << 1)
#define DIP7 (1 << 0)
#define DIP8 (1 << 15)
#define DIP9 (1 << 14) 

uint16_t read_state(spi_device_handle_t);
void load_registers(spi_transaction_t *t);

#endif
