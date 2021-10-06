#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <Arduino.h>

//--------------------------------------------------------------------- Motor Control Parameters
float_t thread_distance_x = 10; // In units of millimeter
float_t thread_distance_y = 10; // In units of millimeter
float_t pulley_diameter_x = 38.2; //In units of millimeter
float_t pulley_diameter_y = 38.2; //In units of millimeter
uint32_t motor_fullcycle_step_x = 400; // Motor's full cycle number of steps
uint32_t motor_fullcycle_step_y = 400; // Motor's full cycle number of steps
float_t microstep_coeff_x = 1; // Motor driver's microstep setting
float_t microstep_coeff_y = 1; // Motor driver's microstep setting
uint32_t max_speed_x = 3; // In units of cm/s
uint32_t max_speed_y = 3; // In Units of cm/s
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
uint32_t input_speed_steady_x = 100; // In units of mm/s
uint32_t input_speed_steady_y = 100; // In units of mm/s
uint32_t input_acceleration_x = 10; // In units of mm/(s^2)
uint32_t input_acceleration_y = 10; // In units of mm/(s^2)
char driving_mechanism = '0'; // "0" -> Pulley System, "1" -> Lead Screw 
float_t delta_t_x; // Time that acceleration is going to apply on x-axis
float_t delta_t_y; // Time that acceleration is going to apply on y-axis
uint32_t step_count_acceleration_calculated_x; //Memory for step_count_acceleration_x calculation 
uint32_t step_count_acceleration_calculated_y; //Memory for step_count_acceleration_y calculation
float_t system_cycle_linear_distance_x; // The varible keeps linear distance of one cycle for x-axis
float_t system_cycle_linear_distance_y; // The varible keeps linear distance of one cycle for y-axis
float_t pi = 3.141592;

#endif PARAMETERS_H