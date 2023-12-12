#include "asf.h"	
#include "ASF/sam0/drivers/dsu/crc32/crc32.h"
#include "SerialConsole/SerialConsole.h"

#define FIRMWARE_BUFFER_SIZE 256
#define APP_START_ADDRESS  ((uint32_t)0x12000) ///<Start of main application. Must be address of start of main application

bool readFirmwareFromSDCard(const char* firmwareFileName);
