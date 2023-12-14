#include "asf.h"

#define ACCIDENT_TASK_SIZE 256
#define ACCIDENT_PRIORITY (configMAX_PRIORITIES - 1)
#define GET_TEMP_VAL true
#define GET_HUM_VAL false
#define GET_ACC_VAL true
#define GET_ANG_VAL false
#define CLI_MSG_LEN						8


extern SemaphoreHandle_t xAccidentDetectedSemaphore;
extern bool handled;
extern int prev_temp;
extern float global_acc[3];
extern float global_gyro[3];
extern int global_acc_value;
extern int global_gyro_value;

void vAccidentHandlerTask(void *pvParameters);
bool accidentHappened(int temp, int hum, int acc, int gyro);