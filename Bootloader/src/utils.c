#include "utils.h"

static void CRC_validation(uint8_t* firmwareBuffer, uint32_t opAddress, uint32_t *resultCrcSd, uint32_t *resultCrcNvm){
	*resultCrcSd = 0;
	*resultCrcNvm = 0; 
	*((volatile unsigned int*) 0x41007058) &= ~0x30000UL;

	//CRC of SD Card
	enum status_code crcres = dsu_crc32_cal	(firmwareBuffer	,256, &resultCrcSd); //Instructor note: Was it the third parameter used for? Please check how you can use the third parameter to do the CRC of a long data stream in chunks - you will need it!
	
	//Errata Part 2 - To be done after RAM CRC
	*((volatile unsigned int*) 0x41007058) |= 0x20000UL;
	 
	//CRC of memory (NVM)
	crcres |= dsu_crc32_cal	(opAddress	,256, &resultCrcNvm);
	
	char helpStr[64];

	if (crcres != STATUS_OK)
	{
		SerialConsoleWriteString("Could not calculate CRC!!\r\n");
	}
}

bool readFirmwareFromSDCard(const char* firmwareFileName) {
    FIL file_object;
    if(f_open(&file_object, firmwareFileName, FA_READ) != FR_OK){
        SerialConsoleWriteString("File has not been written!\r\n");
		return false;
	}

    uint8_t firmwareBuffer[FIRMWARE_BUFFER_SIZE];
    uint32_t numBytesRead;
    uint32_t opAddress = APP_START_ADDRESS;

    while(f_read(&file_object, firmwareBuffer, FIRMWARE_BUFFER_SIZE, &numBytesRead) == FR_OK && numBytesRead > 0){
        if(nvm_erase_row(opAddress) != STATUS_OK){
			SerialConsoleWriteString("erase NVM not succeeded!\r\n");
			return false;
		};
		for(int i = 0; i < 4; i++){
            if(nvm_write_buffer(opAddress + i * 64, &firmwareBuffer[i * 64], 64) != FR_OK){
                SerialConsoleWriteString("Write to NVM not succeeded! \r\n");
				return false;
			}
        }
		uint32_t resultCrcSd, resultCrcNvm;
		CRC_validation(firmwareBuffer, opAddress, &resultCrcSd, &resultCrcNvm);
		if(resultCrcSd != resultCrcNvm){
			SerialConsoleWriteString("CRC check isn't passed! \r\n");
			return false;
		}
        opAddress += FIRMWARE_BUFFER_SIZE;
    }
	return true;
}