# **Visiomex VMR2P0R0001 Documentation**

*Visiomex Industrial Image Processing Solutions Inc. 2021*

*This project is in development process. Some parts of the code migth not work as expected.*   

## Protocol Information

The system communicates over UART protocol, 9600 baud rate, 8-bit, no handshake.

The current verion tested on STM32F303RE Nucleo Board With built-in ST-Link V2 UART Converter.

### 1. Set Commands:

- #### List of the IDs of "set" parameter and package structure:
#### Example Package: SXX######NNNNNNNNN   

Where first and second element of the array ("S" is the zeroth element) is the parameter ID represented by "P P".

Continues following 6 digits are the parameter values represented by "XXXXXX".

Following nine digits are null bits to match the package size expected from robot's controller.

*List of set parameters and IDs:*

| Package ID | Parameter Name | Parameter Unit | Example Package | Usage |
| ---------- | -------------- | -------------- | --------------- | ---- |
| 01 | thread_distance_x | *mm* | *15mm Thread Distance:* S01000015NNNNNNNNN | Service |
| 02 | thread_distance_y | *mm* | *20mm Thread Distance:* S01000020NNNNNNNNN | Service |
| 03 | pulley_diameter_x | *mm\*10* | *38.2mm diameter:* S03000382NNNNNNNNN | Service |
| 04 | pulley_diameter_y | *mm\*10* | *42.6mm diameter:* S04000426NNNNNNNNN | Service |
| 05 | motor_fullcycle_step_x | *# of steps* | *400 Steps per cycle:* S05000400NNNNNNNNN | Service |
| 06 | motor_fullcycle_step_y | *# of steps* | *200 Steps per cycle:* S06000200NNNNNNNNN | Service |
| 07 | microstep_coeff_x | *Coeff* | *1/32 microstep:* S07000032NNNNNNNNN | Service |
| 08 | microstep_coeff_y | *Coeff* | *1/16 microstep:* S08000016NNNNNNNNN | Service |
| 09 | max_speed_x | *mm/s* | *10 (mm/s)* S09000010NNNNNNNNN* | Service |
| 10 | max_speed_y | *mm/s* | *20 (mm/s)* S10000020NNNNNNNNN* | Service |
| 11 | step_delay_speed_steady_x | *us* | *4000 us:* S11004000NNNNNNNNN | Test |
| 12 | step_delay_speed_steady_y | *us* | *5000 us:* S12005000NNNNNNNNN | Test |
| 13 | step_delay_speed_min_x | *us* | *400 us:* S13000400NNNNNNNNN | Test |
| 14 | step_delay_speed_min_y | *us* | *500 us:* S14000500NNNNNNNNN | Test |
| 15 | step_delay_instantaneous_x | *us* | | Test |
| 16 | step_delay_instantaneous_y | *us* | | Test |
| 17 | step_delay_acceleration_avg_x | *us* | | Test |
| 18 | step_delay_acceleration_avg_y | *us* | | Test |
| 19 | step_count_acceleration_x | *# of steps* | Test |
| 20 | step_count_acceleration_y | *# of steps* | Test |
| 21 | input_speed_steady_x | *mm/s* | | Test |
| 22 | input_speed_steady_y | *mm/s* | | Test |
| 23 | input_acceleration_x | *mm/s^2* | Test |
| 24 | input_acceleration_y | *mm/s^2* | Test |
| 25 | delta_t_x | *s* | | Test |
| 26 | delta_t_y | *s* | | Test |
| 27 | driving_mechanism | \- | | Test |

### 2. Move Commands structure
- #### Command ID and structure:
  #### Example Package: MXX#######X#######

	Fix package size: 18 element string

	Where the zeroth element of the array (array[0]) is command type ("M" for move).

	The first element of the array (array[1]) is the motion input type ("L" for linear, "R" for rotational, "S" for step).

	The second element of the array (array[2]) is the direction of motion on x-axis ("P" for positive, "N" for negative).

	Element number three to nine are delta motion on x-axis in units of micrometers for linear, degrees for rotational, steps for step inputs..

	The tenth element of the array (array[10]) is the direction of montion on y-axis ("P" for positive, "N" for negative).

	Element number eleven to seventeen are delta motion on y-axis in units of micrometers for linear, degrees for rotational, steps for step inputs.

	*Note: "P" Positive direction of motion means clockwise (CW), "N" Negative direction of motion means counter clockwise (CCW) on rotational inputs.*

### 3. Feedback Packages

Every feedback package starts with ">" character as an indicator. Computer software should just tooks the feedback packages starting with ">" character (FeedbackString[0]). MCU sends different kind of informations as a feedback (calculation results, current status etc.) for service monitoring. Computer software should only took the packages starting with ">" to avoid took wrong feedback.

- #### Error Package structure and IDs:
	#### Example Package: EPXXXX

Where the zeroth element of the array (array[0]) is command type ("E" for errors).

The first element of the array (array[1]) is the return type (P for package, F for functions).

*Package Errors:*

		>EP0001 -> Package size mismatch
		>EP0002 -> Invalid command type (array[0] error)
		>EP0003 -> Invalid motion type (array[1] error)
		>EP0004 -> Invalid direction of rotation for x-axis (array[2])
		>EP0005 -> Invalid direction of rotation for y-axis (array[10])
		>EP0006 -> Invalid set parameter ID (array[1], array[2])

*List of Funtion Errors:*
		>EF0001 -> "Parse Distance" Function error
		>EF0002 -> Invalid Driving Mechanism
		>EF0003 -> Invalid Axis Input Function

- #### Feedback ID and structure:
  #### Example Package: FSXXXX

Where the zeroth element of the array (array[0]) is  the return type ("F" for feedback).

The first element of the array (array[1]) is the feedback type ("S" for set feedback).

Next four element of the array is the feedback ID.

*List of Feedback Packages:*

		 >FS0001 -> threat_distance_x set done.
		 >FS0002 -> threat_distance_y set done.
		 >FS0003 -> pulley_diameter_x set done.
		 >FS0004 -> pulley_diameter_y set done.
		 >FS0005 -> motor_fullcycle_step_x set done.
		 >FS0006 -> motor_fullcycle_step_y set done.
		 >FS0007 -> microstep_coeff_x set done.
		 >FS0008 -> microstep_coeff_y set done.
		 >FS0009 -> max_speed_x set done.
		 >FS0010 -> max_speed_y set done.
		 >FS0011 -> step_delay_speed_steady_x set done.
		 >FS0012 -> step_delay_speed_steady_y set done.
		 >FS0013 -> step_delay_speed_min_x set done.
		 >FS0014 -> step_delay_speed_min_y set done.
		 >FS0015 -> step_delay_instantaneous_x set done.
		 >FS0016 -> step_delay_instantaneous_y set done.
		 >FS0017 -> step_delay_acceleration_avg_x set done.
		 >FS0018 -> step_delay_acceleration_avg_y set done.
		 >FS0019 -> step_count_acceleration_x set done.
		 >FS0020 -> step_count_acceleration_y set done.
		 >FS0021 -> input_speed_steady_x set done.
		 >FS0022 -> input_speed_steady_y set done.
		 >FS0023 -> input_acceleration_x set done.
		 >FS0024 -> input_acceleration_y set done.
		 >FS0025 -> delta_t_x set done.
		 >FS0026 -> delta_t_y set done.
		 >FS0027 -> driving_mechanism_x set done.
		 >FS0028 -> driving_mechanism_y set done.

		 >FP0001 -> Move Package Confirmed

		 >FA0001 -> Action Accomplished

## EEPROM Adress List of Parameters

Some parameters are available to set from user, and those parameters requires to store in the EEPROM to enable to use them after reset.

*List of Feedback Packages*

| Parameter | Variable Type | Address |
| --------- | ------------- | ------- |
| thread_distance_x | uint16_t | 0 |
| thread_distance_y | uint16_t | 2 |
| pulley_diameter_x | float_t | 4 |
| pulley_diameter_y | float_t | 8 |
| motor_fullcycle_step_x | uint16_t | 12 |
| motor_fullcycle_step_y | uint16_t | 14 |
| microstep_coeff_x | uint8_t | 16 |
| microstep_coeff_y | uint8_t | 17 |
| input_speed_steady_x | uint16_t | 18 |
| input_speed_steady_y | uint16_t | 20 |
| input_acceleration_x | uint8_t | 22 |
| input_acceleration_y | uint8_t | 23 |
| driving_mechanism | char16_t | 24 |

##