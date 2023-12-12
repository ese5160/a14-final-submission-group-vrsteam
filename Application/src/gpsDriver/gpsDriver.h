#include "I2cDriver/I2cDriver.h"

I2C_Data gpsData;

enum{
    GPS_ADDR = 0x10,
    GPS_START_BYTE = 0xA0,
    GPS_LENGTH_BYTE = 0x01,
    GPS_PAYLOAD_BYTE = 0x00,
    GPS_END_BYTE = 0x0A,
    GPS_CMD_LEN = 4,
    GPS_DATA_LEN = 66
};

int32_t gpsI2CRead(uint8_t *buffer, uint8_t count);