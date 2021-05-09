#include "driver/spi_master.h"

#include "pins.h"

void eeprom_read() {
    spi_bus_config_t flash_cfg = {
            .miso_io_num = FLASH_MISO,
            .mosi_io_num = FLASH_MOSI,
            .sclk_io_num = FLASH_SCK,
            .quadwp_io_num = -1,
            .quadhd_io_num = -1,
            .max_transfer_sz = 32,
    };

    esp_err_t ret = spi_bus_initialize(SPI3_HOST, &flash_cfg, 0);
    ESP_ERROR_CHECK(ret);

    spi_device_interface_config_t devcfg = {
        .command_bits = 8,
        .address_bits = 24,
        .clock_speed_hz = 10 * 1000 * 1000,
        .mode = 0,          //SPI mode 0
        .spics_io_num = FLASH_CE,
        .queue_size = 1,
        .flags = SPI_DEVICE_HALFDUPLEX,
    };

    spi_device_handle_t flash_handle;

    ret = spi_bus_add_device(SPI3_HOST, &devcfg, &flash_handle);
    ESP_ERROR_CHECK(ret);

    const char flag[] = "flag{did_Y0u_dUmp_m3_f1rst}";
    for (int i = 0; i < sizeof(flag); i++) {
        spi_transaction_t t = {
                .cmd = 0x03,
                .rxlength = 8,
                .flags = SPI_TRANS_USE_RXDATA,
                .addr = flag[i],
        };

        ret = spi_device_polling_transmit(flash_handle, &t);
        ESP_ERROR_CHECK(ret);
    }
}