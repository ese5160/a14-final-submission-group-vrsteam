#include "imu.h"

void acc_ang_get_val(bool acc_or_ang){
    static int16_t data_raw[3];
    uint8_t reg;
    stmdev_ctx_t *dev_ctx = GetImuStruct();

    /* Read output only if new xl value is available */
    lsm6dsm_xl_flag_data_ready_get(dev_ctx, &reg);
    
    if (reg) {
	    memset(data_raw, 0x00, 3 * sizeof(int16_t));
        if(acc_or_ang){
            lsm6dsm_angular_rate_raw_get(dev_ctx, data_raw);
            global_acc[0] = lsm6dsm_from_fs2_to_mg(data_raw[0]);
            global_acc[1] = lsm6dsm_from_fs2_to_mg(data_raw[1]);
            global_acc[2] = lsm6dsm_from_fs2_to_mg(data_raw[2]);  
        }
        else{
            lsm6dsm_acceleration_raw_get(dev_ctx, data_raw);
            global_gyro[0] = lsm6dsm_from_fs2_to_mg(data_raw[0]);
            global_gyro[1] = lsm6dsm_from_fs2_to_mg(data_raw[1]);
            global_gyro[2] = lsm6dsm_from_fs2_to_mg(data_raw[2]);  
        }
    }
    return pdFALSE;
}