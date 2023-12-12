#include <asf.h>

#define DATA_LENGTH 10
#define SLAVE_ADDRESS 0x70 //Sensor Address
#define TIMEOUT 1000
extern struct i2c_master_module i2c_master_instance;
void temp_hum_configure_i2c_master(void);

extern uint8_t temp_hum_write_buffer[2];

extern uint8_t temp_hum_read_buffer[DATA_LENGTH];

extern uint16_t timeout;
/* Init i2c packet. */
extern struct i2c_master_packet temp_hum_packet;