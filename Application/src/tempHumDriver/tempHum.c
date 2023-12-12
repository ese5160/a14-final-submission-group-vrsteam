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

int temp_hum_get_val(bool temp_or_hum){
		temp_hum_write_buffer[0] = 0x35;
		temp_hum_write_buffer[1] = 0x17;
		temp_hum_packet.data_length = 2;
		while (i2c_master_write_packet_wait(&i2c_master_instance, &temp_hum_packet) !=
		STATUS_OK) {
			/* Increment timeout counter and check if timed out. */
			if (timeout++ == TIMEOUT) {
				break;
			}
		}		
		
		/* Write buffer to slave until success. */
		//packet.data = write_buffer;
        //Read RH first
		temp_hum_packet.data_length = 2;		
		temp_hum_write_buffer[0] = (temp_or_hum) ? 0x7C : 0x5C;
		temp_hum_write_buffer[1] = (temp_or_hum) ? 0xA2 : 0x24;
		/*timeout=0;*/
		while (i2c_master_write_packet_wait(&i2c_master_instance, &temp_hum_packet) !=
		STATUS_OK) {
			/* Increment timeout counter and check if timed out. */
			if (timeout++ == TIMEOUT) {
				break;
			}
		}		
		    
			/* Read from slave until success. */
	    temp_hum_packet.data = temp_hum_read_buffer;
		temp_hum_packet.data_length  = 6;
	    while (i2c_master_read_packet_wait(&i2c_master_instance, &temp_hum_packet) !=
	    STATUS_OK) {
		    /* Increment timeout counter and check if timed out. */
		    if (timeout++ == TIMEOUT) {
			    break;
		    }
	    }
		//printf("Data value: %d\r\n", packet.data[0]);
		
		/*sleep*/
		temp_hum_packet.data = temp_hum_write_buffer;
		temp_hum_write_buffer[0] = 0xB0;
		temp_hum_write_buffer[1] = 0x98;
		temp_hum_packet.data_length  = 2;
		while (i2c_master_write_packet_wait(&i2c_master_instance, &temp_hum_packet) !=
		STATUS_OK) {
			/* Increment timeout counter and check if timed out. */
			if (timeout++ == TIMEOUT) {
				break;
			}
		}		
		return (temp_or_hum) ? ((((temp_hum_read_buffer[0]/16.0)*4096 + (temp_hum_read_buffer[0]%16)*256 + (temp_hum_read_buffer[1]/16)*16 + temp_hum_read_buffer[1]%16)*175)/65536-45) : ((((temp_hum_read_buffer[0]/16.0)*4096 + (temp_hum_read_buffer[0]%16)*256 + (temp_hum_read_buffer[1]/16)*16 + temp_hum_read_buffer[1]%16)*100)/65536);
}
