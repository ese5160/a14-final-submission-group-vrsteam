#include "IMU/lsm6dso_reg.h"
#include "IMU/lsm6dsm_reg.h"
#include <asf.h>

extern float global_acc[3];
extern float global_gyro[3];

void acc_ang_get_val(bool acc_or_ang);