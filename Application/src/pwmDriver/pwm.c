#include "pwm.h"

// PA10 and PA11 should be changed PA24 and PA25 in our own project
// PA24 and PA25 corresponds to WO2 and WO3 of TCC1 respectively

void configure_tcc(void) {
    tcc_get_config_defaults(&config_tcc, TCC2); // Use TCC0

    config_tcc.counter.clock_prescaler = TCC_CLOCK_PRESCALER_DIV1024;

    // Set up the TCC for PWM generation on PA10 (WO6)
    config_tcc.counter.period = 936;
    config_tcc.compare.wave_generation = TCC_WAVE_GENERATION_SINGLE_SLOPE_PWM;
    config_tcc.compare.match[1] = 70; // Use channel 2 (WO2) for PA10
    config_tcc.pins.enable_wave_out_pin[1] = true;
    config_tcc.pins.wave_out_pin[1] = PIN_PA17E_TCC2_WO1;
    config_tcc.pins.wave_out_pin_mux[1] = MUX_PA17E_TCC2_WO1; // Set the correct pinmux

    // Initialize and enable the TCC module
    tcc_init(&tcc_instance, TCC2, &config_tcc); // Initialize TCC0
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
    tcc_init(&tcc_instance, TCC2, &config_tcc);

    // Re-enable the TCC module
    tcc_enable(&tcc_instance);
}