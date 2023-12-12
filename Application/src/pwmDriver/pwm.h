#include <asf.h>
struct tcc_module tcc_instance;
struct tcc_config config_tcc;
void configure_tcc(void);
void disable_pwm_waveform(void);
void update_pwm_duty_cycle(uint32_t duty_cycle, uint32_t idx);
