#include "asf.h"

#define ACCIDENT_TASK_SIZE 256
#define ACCIDENT_PRIORITY (configMAX_PRIORITIES - 1)
#define GET_TEMP_VAL true
#define GET_HUM_VAL false

extern SemaphoreHandle_t xAccidentDetectedSemaphore;

void vAccidentHandlerTask(void *pvParameters);
bool accidentHappened(int temp, int hum);