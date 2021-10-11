# **Visiomex VMR2P0R0001 Documentation**

*Visiomex Industrial Image Processing Solutions Inc. 2021*

*This project is in development process. Some parts of the code migth not work as expected.*   

## Protocol Information

The system communicates over UART protocol, 9600 baud rate, 8-bit, no handshake.

The current verion tested on STM32F303RE Nucleo Board With built-in ST-Link V2 UART Converter.

### 1. Set Commands:

- #### List of the IDs of "set" parameter and package structure:
#### Example Package: SXX######NNNNNNNNN   

Where first and second element of the array ("S" is the zeroth element) is the parameter ID represented by "XX".

Continues following 6 digits are the parameter values represented by "######".

Following nine digits are null bits to match the package size expected from robot's controller.

*List of set parameters and IDs:*

| Package ID | Parameter Name | Parameter Unit | Example Package | Parameter Type | Usage |
| ---------- | -------------- | -------------- | --------------- | -------------- | ----- |
| 01 | thread_distance_x | *mm* | *15mm Thread Distance:* S01000015NNNNNNNNN | Input | Service |
| 02 | thread_distance_y | *mm* | *20mm Thread Distance:* S01000020NNNNNNNNN | Input |Service |
| 03 | pulley_diameter_x | *mm\*10* | *38.2mm diameter:* S03000382NNNNNNNNN | Input |Service |
| 04 | pulley_diameter_y | *mm\*10* | *42.6mm diameter:* S04000426NNNNNNNNN | Input |Service |
| 05 | motor_fullcycle_step_x | *# of steps* | *400 Steps per cycle:* S05000400NNNNNNNNN | Input | Service |
| 06 | motor_fullcycle_step_y | *# of steps* | *200 Steps per cycle:* S06000200NNNNNNNNN | Input | Service |
| 07 | microstep_coeff_x | *Coeff* | *1/32 microstep:* S07000032NNNNNNNNN | Input | Service |
| 08 | microstep_coeff_y | *Coeff* | *1/16 microstep:* S08000016NNNNNNNNN | Input | Service |
| 09 | max_speed_x | *mm/s* | *10 (mm/s):* S09000010NNNNNNNNN* | Input | Service |
| 10 | max_speed_y | *mm/s* | *20 (mm/s):* S10000020NNNNNNNNN* | Input | Service |
| 11 | step_delay_speed_steady_x | *microseconds* | *4000 us:* S11004000NNNNNNNNN | Output | Test |
| 12 | step_delay_speed_steady_y | *microseconds* | *5000 us:* S12005000NNNNNNNNN | Output | Test |
| 13 | step_delay_speed_min_x | *microseconds* | *400 us:* S13000400NNNNNNNNN | Input | Service |
| 14 | step_delay_speed_min_y | *microseconds* | *500 us:* S14000500NNNNNNNNN | Input | Service |
| 15 | step_delay_instantaneous_x | *microseconds* | *1000 us:* S15001000NNNNNNNNN | Output | Test |
| 16 | step_delay_instantaneous_y | *microseconds* | *1300 us:* S16001300NNNNNNNNN | Output | Test |
| 17 | step_delay_acceleration_avg_x | *microseconds* | *500 us:* S17000500NNNNNNNNN | Output | Test |
| 18 | step_delay_acceleration_avg_y | *microseconds* | *700 us:* S18000700NNNNNNNNN | Output | Test |
| 19 | step_count_acceleration_x | *# of steps* | *400 Steps:* S19000400NNNNNNNNN | Output | Test |
| 20 | step_count_acceleration_y | *# of steps* | *800 Steps:* S20000800NNNNNNNNN | Output | Test |
| 21 | input_speed_steady_x | *mm/s* | *100 mm/s:* S21000100NNNNNNNNN | Input | Service |
| 22 | input_speed_steady_y | *mm/s* | *120 mm/s:* S22000120NNNNNNNNN | Input | Service |
| 23 | input_acceleration_x | *mm/s^2* | *50 mm/s^2:* S23000050NNNNNNNNN | Input | Service |
| 24 | input_acceleration_y | *mm/s^2* | *60 mm/s^2:* S24000060NNNNNNNNN | Input | Service |
| 25 | delta_t_x | *seconds* | *2 s:* S25000002NNNNNNNNN | Output | Test |
| 26 | delta_t_y | *seconds* | *2 s:* S26000002NNNNNNNNN | Output | Test |
| 27 | driving_mechanism | 0 -> Pulley, 1 -> Lead Screw | *Pulley System:* S27000000NNNNNNNNN | Input | Service |

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

Every feedback package starts with ">" character as an indicator. Computer software should just tooks the feedback packages starting with ">" character (FeedbackString[0]). MCU sends different kind of informations as a feedback (calculation results, status information etc.) for service monitoring. Computer software should only took the packages starting with ">" to avoid problems.

- #### Error Package structure and IDs:
	#### Example Package: EPXXXX

Where the zeroth element of the array (array[0]) is command type ("E" for errors).

The first element of the array (array[1]) is the return type (P for package, F for functions).

*Package Errors:*

| Package | Description |
| ------- | ----------- |
| EP0001 | Package size mismatch |
| EP0002 | Invalid command type (array[0] error) |
| EP0003 | Invalid motion type (array[1] error) |
| EP0004 | Invalid direction of rotation for x-axis (array[2]) |
| EP0005 | Invalid direction of rotation for y-axis (array[10]) |
| EP0006 | Invalid set parameter ID (array[1], array[2]) |

*List of Funtion Errors:*
| Package | Description |
| ------- | ----------- |
| EF0001 | "Parse Distance" Function error |
| EF0002 | Invalid Driving Mechanism |
| EF0003 | Invalid Axis Input Function |

- #### Feedback ID and structure:
  #### Example Package: FSXXXX

Where the zeroth element of the array (array[0]) is  the return type ("F" for feedback).

The first element of the array (array[1]) is the feedback type ("S" for set feedback).

Next four element of the array is the feedback ID.

*List of Feedback Packages:*

| Package | Description |
| ------- | ----------- |
| FS0001 | threat_distance_x set done. |
| FS0002 | threat_distance_y set done. |
| FS0003 | pulley_diameter_x set done. |
| FS0004 | pulley_diameter_y set done. |
| FS0005 | motor_fullcycle_step_x set done. |
| FS0006 | motor_fullcycle_step_y set done. |
| FS0007 | microstep_coeff_x set done. |
| FS0008 | microstep_coeff_y set done. |
| FS0009 | max_speed_x set done. |
| FS0010 | max_speed_y set done. |
| FS0011 | step_delay_speed_steady_x set done. |
| FS0012 | step_delay_speed_steady_y set done. |
| FS0013 | step_delay_speed_min_x set done. |
| FS0014 | step_delay_speed_min_y set done. |
| FS0015 | step_delay_instantaneous_x set done. |
| FS0016 | step_delay_instantaneous_y set done. |
| FS0017 | step_delay_acceleration_avg_x set done. |
| FS0018 | step_delay_acceleration_avg_y set done. |
| FS0019 | step_count_acceleration_x set done. |
| FS0020 | step_count_acceleration_y set done. |
| FS0021 | input_speed_steady_x set done. |
| FS0022 | input_speed_steady_y set done. |
| FS0023 | input_acceleration_x set done. |
| FS0024 | input_acceleration_y set done. |
| FS0025 | delta_t_x set done. |
| FS0026 | delta_t_y set done. |
| FS0027 | driving_mechanism_x set done. |
| FS0028 | driving_mechanism_y set done. |
| | |
| FP0001 | Move Package Confirmed |
| | |
| FA0001 | Action Accomplished |

## EEPROM Adress List of Parameters

Some parameters are available to set from user, and those parameters requires to store in the EEPROM to enable to use them after reset.

*List of EEPROM adresses*

| Parameter | Variable Type | EEPROM Address |
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
| step_delay_speed_min_x | uint32_t | 26 |
| step_delay_speed_min_y | uint32_t | 30 |

## Hardware Connections 