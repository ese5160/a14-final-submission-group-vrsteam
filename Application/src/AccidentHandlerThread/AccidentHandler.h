#include "asf.h"

#define ACCIDENT_TASK_SIZE 256
#define ACCIDENT_PRIORITY (configMAX_PRIORITIES - 1)

void vAccidentHandlerTask(void *pvParameters);