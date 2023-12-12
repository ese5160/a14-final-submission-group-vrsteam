#include "gpsDriver.h"

int32_t gpsI2CRead(uint8_t *buffer, uint8_t count){
    uint8_t cmd[] = {GPS_START_BYTE, GPS_LENGTH_BYTE, GPS_PAYLOAD_BYTE, GPS_END_BYTE};
    gpsData.address = GPS_ADDR;
    gpsData.msgOut = &cmd;
    gpsData.lenOut = sizeof(cmd);
    gpsData.msgIn = buffer;
    gpsData.lenIn = count;

	int error = I2cReadDataWait(&gpsData, 0, 100);

	if(ERROR_NONE != error)
	{
		SerialConsoleWriteString("Error reading GPS counts!/r/n");
	}
	return error;
}