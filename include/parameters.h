#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <Arduino.h>

//--------------------------------------------------------------------- Motor Control Parameters
uint16_t thread_distance_x = 10; // In units of millimeter
uint16_t thread_distance_y = 10; // In units of millimeter
float_t pulley_diameter_x = 38.2; //In units of millimeter
float_t pulley_diameter_y = 38.2; //In units of millimeter
uint16_t motor_fullcycle_step_x = 400; // Motor's full cycle number of steps
uint16_t motor_fullcycle_step_y = 400; // Motor's full cycle number of steps
uint8_t microstep_coeff_x = 1; // Motor driver's microstep setting
uint8_t microstep_coeff_y = 1; // Motor driver's microstep setting
uint16_t max_speed_x = 150; // In units of mm/s
uint16_t max_speed_y = 150; // In Units of mm/s
uint32_t step_delay_speed_steady_x = 1000; // In units of microsecond
uint32_t step_delay_speed_steady_y = 1000; // In units of microsecond
uint32_t step_delay_speed_min_x = 5000; // In units of microsecond
uint32_t step_delay_speed_min_y = 5000; // In units of microsecond
uint32_t step_delay_instantaneous_x = 4000; // In units of microsecond
uint32_t step_delay_instantaneous_y = 4000; // In units of microsecond
uint32_t step_delay_acceleration_avg_x = 500; // In units of microsecond
uint32_t step_delay_acceleration_avg_y = 500; // In units of microsecond
uint32_t step_count_acceleration_x = 50; // Number of steps that acceleration going to applied on x-axis
uint32_t step_count_acceleration_y = 50; // Number of steps that acceleration going to applied on y-axis
uint16_t input_speed_steady_x = 100; // In units of mm/s
uint16_t input_speed_steady_y = 100; // In units of mm/s
uint8_t input_acceleration_x = 10; // In units of mm/(s^2)
uint8_t input_acceleration_y = 10; // In units of mm/(s^2)
char16_t driving_mechanism = '0'; // "0" -> Pulley System, "1" -> Lead Screw 
float_t delta_t_x; // Time that acceleration is going to apply on x-axis
float_t delta_t_y; // Time that acceleration is going to apply on y-axis
uint32_t step_count_acceleration_calculated_x; //Memory for step_count_acceleration_x calculation 
uint32_t step_count_acceleration_calculated_y; //Memory for step_count_acceleration_y calculation
float_t system_cycle_linear_distance_x; // The varible keeps linear distance of one cycle for x-axis
float_t system_cycle_linear_distance_y; // The varible keeps linear distance of one cycle for y-axis
float_t pi = 3.141592;


uint8_t address_thread_distance_x = 0;
uint8_t address_thread_distance_y = 2;
uint8_t address_pulley_diameter_x = 4;
uint8_t address_pulley_diameter_y = 8;
uint8_t address_motor_fullcycle_step_x = 12;
uint8_t address_motor_fullcycle_step_y = 14;
uint8_t address_microstep_coeff_x = 16;
uint8_t address_microstep_coeff_y = 17;
uint8_t address_input_speed_steady_x = 18;
uint8_t address_input_speed_steady_y = 20;
uint8_t address_input_acceleration_x = 22;
uint8_t address_input_acceleration_y = 23;
uint8_t address_driving_mechanism = 24;


#endif PARAMETERS_H