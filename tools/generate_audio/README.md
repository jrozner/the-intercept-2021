# Generate Audio

This is a modified verison of the the tool provided in the [i2s\_adc\_adc](https://github.com/espressif/esp-idf/blob/master/examples/peripherals/i2s_adc_dac/tools/generate_audio_file.py) demo provided by espressif. The original tool scaled down 16bit audio to 8bit because they were using the internal DACs which are much lower bit than the ones used here. Instead we just pull the raw 16bit PCM data out of the file and turn it into a `uint16_t[]`. The DACs used [max98375a](https://datasheets.maximintegrated.com/en/ds/MAX98357A-MAX98357B.pdf) support 16, 24, and 32bit audio at up to 96kHz. This script can be updated to use a `uint32_t[]` instead and unpack the 24 or 32bit source audio if desired.

## LICENSE

The original code is Apache 2.0 so this probably is too
