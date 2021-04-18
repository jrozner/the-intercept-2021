#include <string.h>
#include <machine/endian.h>
#include "driver/gpio.h"
#include "driver/spi_master.h"

#include "dip.h"

uint16_t read_state(spi_device_handle_t dip_spi) {
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = 16;
    t.flags = SPI_TRANS_USE_RXDATA;

    esp_err_t ret = spi_device_polling_transmit(dip_spi, &t);
    ESP_ERROR_CHECK(ret);

    // FIXME(joe): mask off top 5 bits until we tie them high
    return *(uint16_t *) t.rx_data & 0xc0ff;
}

void load_registers(spi_transaction_t *t) {
    gpio_set_level(GPIO_NUM_2, 0);
    gpio_set_level(GPIO_NUM_2, 1);
}
