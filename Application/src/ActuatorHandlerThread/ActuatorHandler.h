#include "asf.h"

#define ACTUATOR_TASK_SIZE 256
#define ACTUATOR_PRIORITY (configMAX_PRIORITIES - 1)

extern SemaphoreHandle_t xAccidentDetectedSemaphore;

void vActuatorHandlerTask(void *pvParameters);