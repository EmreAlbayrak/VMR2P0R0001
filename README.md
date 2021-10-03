# **Visiomex VMR2P0R0001 Documentation**

*Visiomex Industrial Image Processing Solutions Inc. 2021*  

# Protocol Information

### 1. Set Commands:

- #### List of the IDs of "SET" parameter and package structure:
#### Example Package: SPPXXXXXXNNNNNNNNN   

Where first and second element of the array ("S" is the zeroth element) is the parameter ID represented by "P P".

Continues following 6 digits are the parameter values represented by "XXXXXX".

Following nine digits are null bits to match the package size expected from robot's controller.

*List of set parameters and IDs:*

		01 -> threat_distance_x
		02 -> threat_distance_y
		03 -> pulley_diameter_x
		04 -> pulley_diameter_y
		05 -> motor_fullcycle_step_x
		06 -> motor_fullcycle_step_y
		07 -> microstep_coeff_x
		08 -> microstep_coeff_y
		09 -> max_speed_x
		10 -> max_speed_y
		11 -> step_delay_speed_steady_x
		12 -> step_delay_speed_steady_y
		13 -> step_delay_speed_min_x
		14 -> step_delay_speed_min_y
		15 -> step_delay_instantaneous_x
		16 -> step_delay_instantaneous_y
		17 -> step_delay_acceleration_avg_x
		18 -> step_delay_acceleration_avg_y
		19 -> step_count_acceleration_x
		20 -> step_count_acceleration_y
		21 -> input_speed_steady_x
		22 -> input_speed_steady_y
		23 -> input_acceleration_x
		24 -> input_acceleration_y
		25 -> delta_t_x
		26 -> delta_t_y
		27 -> driving_mechanism_x
		27 -> driving_mechanism_y


### 3. Feedback Commands
- #### List of error ID and structure:
	#### Example Package: EPXXXX

Where the zeroth element of the array (array[0]) is command type ("E" for errors).

The first element of the array (array[1]) is the return type (P for package, F for functions).

*List of Package Errors:*

		EP0001 -> Package size mismatch
		EP0002 -> Invalid command type (array[0] error)
		EP0003 -> Invalid motion type (array[1] error)
		EP0004 -> Invalid direction of rotation for x-axis (array[2])
		EP0005 -> Invalid direction of rotation for y-axis (array[10])

	*List of Funtion Errors:*
	  EF0001 -> "Parse Function" error in code

- #### List of feedback ID and structure:
#### Example Package: FSXXXX

Where the zeroth element of the array (array[0]) is  the return type ("F" for feedback).

The first element of the array (array[1]) is the feedback type ("S" for set feedback).

Next four element of the array is the feedback ID.

*List of Feedback Packages:*

		 FS0001 -> threat_distance_x set done.
		 FS0002 -> threat_distance_y set done.
		 FS0003 -> pulley_diameter_x set done.
		 FS0004 -> pulley_diameter_y set done.
		 FS0005 -> motor_fullcycle_step_x set done.
		 FS0006 -> motor_fullcycle_step_y set done.
		 FS0007 -> microstep_coeff_x set done.
		 FS0008 -> microstep_coeff_y set done.
		 FS0009 -> max_speed_x set done.
		 FS0010 -> max_speed_y set done.
		 FS0011 -> step_delay_speed_steady_x set done.
		 FS0012 -> step_delay_speed_steady_y set done.
		 FS0013 -> step_delay_speed_min_x set done.
		 FS0014 -> step_delay_speed_min_y set done.
		 FS0015 -> step_delay_instantaneous_x set done.
		 FS0016 -> step_delay_instantaneous_y set done.
		 FS0017 -> step_delay_acceleration_avg_x set done.
		 FS0018 -> step_delay_acceleration_avg_y set done.
		 FS0019 -> step_count_acceleration_x set done.
		 FS0020 -> step_count_acceleration_y set done.
		 FS0021 -> input_speed_steady_x set done.
		 FS0022 -> input_speed_steady_y set done.
		 FS0023 -> input_acceleration_x set done.
		 FS0024 -> input_acceleration_y set done.
		 FS0025 -> delta_t_x set done.
		 FS0026 -> delta_t_y set done.
		 FS0027 -> driving_mechanism_x set done.
		 FS0028 -> driving_mechanism_y set done.

-	#### List of Move commands and package structure