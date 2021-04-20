#ifndef THEINTERCEPT_DIP_H
#define THEINTERCEPT_DIP_H

#define DIP1 (1 << 7)
#define DIP2 (1 << 6)
#define DIP3 (1 << 5)
#define DIP4 (1 << 4)
#define DIP5 (1 << 3)
#define DIP6 (1 << 2)
#define DIP7 (1 << 1)
#define DIP8 (1 << 0)
#define DIP9 (1 << 15)
#define DIP10 (1 << 14)

#define UNLOCK_CODE (DIP1 | DIP5 | DIP5 | DIP8 | DIP10)

uint16_t read_state(spi_device_handle_t);
void load_registers(spi_transaction_t *t);

#endif //THEINTERCEPT_DIP_H
