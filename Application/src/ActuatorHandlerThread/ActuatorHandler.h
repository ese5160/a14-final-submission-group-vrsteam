#include "asf.h"

#define ACTUATOR_TASK_SIZE 256
#define ACTUATOR_PRIORITY (configMAX_PRIORITIES - 1)

void vActuatorHandlerTask(void *pvParameters);