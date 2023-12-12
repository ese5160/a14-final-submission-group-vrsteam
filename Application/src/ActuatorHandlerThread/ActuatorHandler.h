#include "asf.h"

#define ACTUATOR_TASK_SIZE 256
#define ACTUATOR_PRIORITY (configMAX_PRIORITIES - 1)

extern SemaphoreHandle_t xAccidentDetectedSemaphore;

extern int global_hum;
extern int global_temp;

void vActuatorHandlerTask(void *pvParameters);