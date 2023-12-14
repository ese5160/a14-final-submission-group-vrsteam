#include "asf.h"

#define ACTUATOR_TASK_SIZE 256
#define ACTUATOR_PRIORITY (configMAX_PRIORITIES - 1)

extern SemaphoreHandle_t xAccidentDetectedSemaphore;

extern int global_hum;
extern int global_temp;
//extern int prev_temp;
extern int global_acc_value;
extern int global_gyro_value;

void vActuatorHandlerTask(void *pvParameters);