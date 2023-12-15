#include "asf.h"


typedef unsigned char uint8;


#define ACTUATOR_TASK_SIZE 256
#define ACTUATOR_PRIORITY (configMAX_PRIORITIES - 1)

extern SemaphoreHandle_t xAccidentDetectedSemaphore;

extern uint8 cur_accident;
extern uint8 prev_accident;

void vActuatorHandlerTask(void *pvParameters);