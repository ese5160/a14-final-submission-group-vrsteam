#include "pwm.h"

// PA10 and PA11 should be changed PA24 and PA25 in our own project
// PA24 and PA25 corresponds to WO2 and WO3 of TCC1 respectively

void configure_tcc(void) {
    struct system_pinmux_config tcc_pinmux_config;
	system_pinmux_get_config_defaults(&tcc_pinmux_config);
    tcc_pinmux_config.direction = SYSTEM_PINMUX_PIN_DIR_OUTPUT;
    tcc_pinmux_config.mux_position = MUX_PA24F_TCC1_WO2;
    system_pinmux_pin_set_config(PIN_PA24F_TCC1_WO2, &tcc_pinmux_config);
    tcc_pinmux_config.mux_position = MUX_PA25F_TCC1_WO3;
    system_pinmux_pin_set_config(PIN_PA25F_TCC1_WO3, &tcc_pinmux_config);

    tcc_get_config_defaults(&config_tcc, TCC1); // Use TCC0
    // Configure the pinmux for the TCC PWM output
    // struct port_config pin_conf;
    // port_get_config_defaults(&pin_conf);
    // pin_conf.direction = PORT_PIN_DIR_OUTPUT;
    // port_pin_set_config(PIN_PA24F_TCC1_WO2, &pin_conf); // Configure PA10 as TCC0, WO2
    // port_pin_set_config(PIN_PA25F_TCC1_WO3, &pin_conf); // Configure PA11 as TCC0, WO3

    // Set up the TCC for PWM generation on PA10 (WO6)
     config_tcc.counter.period = 960000;
    //config_tcc.counter.period = 10000;
    config_tcc.compare.wave_generation = TCC_WAVE_GENERATION_SINGLE_SLOPE_PWM;
    config_tcc.compare.match[2] = 72000; // Use channel 2 (WO2) for PA10
    config_tcc.pins.enable_wave_out_pin[2] = true;
    config_tcc.pins.wave_out_pin[2] = PIN_PA24F_TCC1_WO2;
    config_tcc.pins.wave_out_pin_mux[2] = MUX_PA24F_TCC1_WO2; // Set the correct pinmux

    // PA11 - Channel 3 (WO3) configuration
    config_tcc.compare.match[3] = 72000; // Use channel 3 (WO3) for PA11
    config_tcc.pins.enable_wave_out_pin[3] = true;
    config_tcc.pins.wave_out_pin[3] = PIN_PA25F_TCC1_WO3;
    config_tcc.pins.wave_out_pin_mux[3] = MUX_PA25F_TCC1_WO3 ; // Set the correct pinmux for PA11

    // Initialize and enable the TCC module
    tcc_init(&tcc_instance, TCC1, &config_tcc); // Initialize TCC0
    tcc_enable(&tcc_instance);
}

void update_pwm_duty_cycle(uint32_t duty_cycle, uint32_t idx) {
    // Ensure the duty cycle does not exceed the configured period
    if (duty_cycle > config_tcc.counter.period) {
        duty_cycle = config_tcc.counter.period;
    }

    // Disable TCC module to update the configuration
    tcc_disable(&tcc_instance);

    // Update the duty cycle for channel 2 (WO2)
    config_tcc.compare.match[idx] = duty_cycle;

    // Reset and re-initialize the TCC module with the updated configuration
    tcc_reset(&tcc_instance);
    tcc_init(&tcc_instance, TCC1, &config_tcc);

    // Re-enable the TCC module
    tcc_enable(&tcc_instance);
}