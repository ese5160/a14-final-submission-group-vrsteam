#include "asf.h"

#define ACCIDENT_TASK_SIZE 256
#define ACCIDENT_PRIORITY (configMAX_PRIORITIES - 1)

int counter = 0;

extern SemaphoreHandle_t xAccidentDetectedSemaphore;

void vAccidentHandlerTask(void *pvParameters);