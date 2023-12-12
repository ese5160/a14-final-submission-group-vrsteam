#include "tempHum.h"

struct i2c_master_module i2c_master_instance;

uint8_t temp_hum_write_buffer[2] = {
	0x00, 0x01,
};

uint8_t temp_hum_read_buffer[DATA_LENGTH];

uint16_t timeout = 0;
/* Init i2c packet. */
struct i2c_master_packet temp_hum_packet = {
    .address     = SLAVE_ADDRESS,
    .data_length = 2,
    .data        = temp_hum_write_buffer,
    .ten_bit_address = false,
    .high_speed      = false,
    .hs_master_code  = 0x0,
};

void temp_hum_configure_i2c_master(void)
{
	/* Initialize config structure and software module. */
	struct i2c_master_config config_i2c_master;
	i2c_master_get_config_defaults(&config_i2c_master);
	/* Change buffer timeout to something longer. */
	config_i2c_master.buffer_timeout = 10000;
	config_i2c_master.pinmux_pad0 = PINMUX_PA08C_SERCOM0_PAD0;
	config_i2c_master.pinmux_pad1 = PINMUX_PA09C_SERCOM0_PAD1;
	/* Initialize and enable device with config. */
	i2c_master_init(&i2c_master_instance, SERCOM0, &config_i2c_master);
	i2c_master_enable(&i2c_master_instance);
}

