
// Library includes
#include <Arduino.h>
#include <EEPROM.h>
#include "defines.h"

// User defined includes
#include <parameters.h>

const char compile_date[] = __DATE__ " " __TIME__;

EthernetUDP Udp;

//--------------------------------------------------------------------- Serial Communication Parameters
String serial_package;
//---------------------------------------------------------------------

void get_parameters_eeprom(){
  EEPROM.get(address_thread_distance_x, thread_distance_x);
  EEPROM.get(address_thread_distance_y, thread_distance_y);
  EEPROM.get(address_pulley_diameter_x, pulley_diameter_y);
  EEPROM.get(address_pulley_diameter_y, pulley_diameter_y);
  EEPROM.get(address_motor_fullcycle_step_x, motor_fullcycle_step_x);
  EEPROM.get(address_motor_fullcycle_step_y, motor_fullcycle_step_y);
  EEPROM.get(address_microstep_coeff_x, microstep_coeff_x);
  EEPROM.get(address_microstep_coeff_y, microstep_coeff_y);
  EEPROM.get(address_input_speed_steady_x, input_speed_steady_x);
  EEPROM.get(address_input_speed_steady_y, input_speed_steady_y);
  EEPROM.get(address_input_acceleration_x, input_acceleration_x);
  EEPROM.get(address_input_acceleration_y, input_acceleration_y);
  EEPROM.get(address_driving_mechanism, driving_mechanism);
  EEPROM.get(address_step_delay_speed_min_x, step_delay_speed_min_x);
  EEPROM.get(address_step_delay_speed_min_y, step_delay_speed_min_y);
}

void system_monitor_parameters(){

 Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());

  Serial.println(F("---------------------------------------------------------------------- System Monitor Start"));
  Udp.write("\n//// System Monitor Start ////");
  get_parameters_eeprom();

/*
  Serial.print("Size of uint64_t: ");
  Serial.println(sizeof(uint64_t));

  Serial.print("Size of uint32_t: ");
  Serial.println(sizeof(uint32_t));

  Serial.print("Size of uint16_t: ");
  Serial.println(sizeof(uint16_t));

  Serial.print("Size of int: ");
  Serial.println(sizeof(int));

  Serial.print("Size of float_t: ");
  Serial.println(sizeof(float_t));

  Serial.print("Size of float: ");
  Serial.println(sizeof(float));
*/

  Serial.print(F("Built Date: "));
  Serial.println(compile_date);
  Udp.write("\nBuild Date: ");
  Udp.write(compile_date);

  Serial.print(F("IP Address: "));
  Serial.println(Ethernet.localIP());
  Udp.write("\nIP Address: ");
  Udp.print(Ethernet.localIP());

  Serial.print(F("Local Port: "));
  Serial.println(localPort);
  Udp.write("\nLocal Port: ");
  Udp.print(localPort);

  Serial.print(F("Thread Distance x-axis (mm): "));
  Serial.println(thread_distance_x);
  Udp.write("\nThread Distance x-axis (mm): ");
  Udp.print(thread_distance_x);

  Serial.print(F("Thread Distance y-axis (mm): "));
  Serial.println(thread_distance_y);
  Udp.write("\nThread Distance y-axis (mm): ");
  Udp.print(thread_distance_y);
  
  Serial.print(F("Pulley Diameter x-axis (mm): "));
  Serial.println(pulley_diameter_x);
  Udp.write("\nPulley Diameter x-axis (mm): ");
  Udp.print(pulley_diameter_x);

  Serial.print(F("Pulley Diameter y-axis (mm): "));
  Serial.println(pulley_diameter_y);
  Udp.write("\nPulley Diameter y-axis (mm): ");
  Udp.print(pulley_diameter_y);

  Serial.print(F("System Cycle Linear Distance x (mm): "));
  Serial.println(system_cycle_linear_distance_x);
  Udp.write("\nSystem Cycle Linear Distance x (mm): ");
  Udp.print(system_cycle_linear_distance_x);

  Serial.print(F("System Cycle Linear Distance y (mm): "));
  Serial.println(system_cycle_linear_distance_y);
  Udp.write("\nSystem Cycle Linear Distance y (mm): ");
  Udp.print(system_cycle_linear_distance_y);

  Serial.print(F("Motor Full Cycle x-axis (# of steps): "));
  Serial.println(motor_fullcycle_step_x);
  Udp.write("\nMotor Full Cycle x-axis (# of steps): ");
  Udp.print(motor_fullcycle_step_x);

  Serial.print(F("Motor Full Cycle y-axis (# of Steps): "));
  Serial.println(motor_fullcycle_step_y);
  Udp.write("\nMotor Full Cycle y-axis (# of steps): ");
  Udp.print(motor_fullcycle_step_y);

  Serial.print(F("Microstep Coeff x-axis: "));
  Serial.println(microstep_coeff_x);
  Udp.write("\nMicrostep Coeff x-axis: ");
  Udp.print(microstep_coeff_x);  

  Serial.print(F("Microstep Coeff y-axis: "));
  Serial.println(microstep_coeff_y);
  Udp.write("\nMicrostep Coeff y-axis: ");
  Udp.print(microstep_coeff_y);  

  Serial.print(F("Max Speed x-axis (mm/s): "));
  Serial.println(max_speed_x);
  Udp.write("\nMax Speed x-axis (mm/s): ");
  Udp.print(max_speed_x);  

  Serial.print(F("Max Speed y-axis (mm/s): "));
  Serial.println(max_speed_y);
  Udp.write("\nMax Speed y-axis (mm/s): ");
  Udp.print(max_speed_y);

  Serial.print(F("Step Delay Speed Steady x-axis (us): "));
  Serial.println(step_delay_speed_steady_x);
  Udp.write("\nStep Delay Speed Steady x-axis (us): ");
  Udp.print(step_delay_speed_steady_x);

  Serial.print(F("Step Delay Speed Steady y-axis (us): "));
  Serial.println(step_delay_speed_steady_y);
  Udp.write("\nStep Delay Speed Steady y-axis (us): ");
  Udp.print(step_delay_speed_steady_y);

  Serial.print(F("Step Delay Speed Min x-axis (us): "));
  Serial.println(step_delay_speed_min_x);
  Udp.write("\nStep Delay Speed Min x-axis (us): ");
  Udp.print(step_delay_speed_min_x);

  Serial.print(F("Step Delay Speed Min y-axis (us): "));
  Serial.println(step_delay_speed_min_y);
  Udp.write("\nStep Delay Speed Min y-axis (us): ");
  Udp.print(step_delay_speed_min_y);

  Serial.print(F("Step Delay Speed Instantaneous x-axis (us): "));
  Serial.println(step_delay_instantaneous_x);
  Udp.write("\nStep Delay Speed Instantaneous x-axis (us): ");
  Udp.print(step_delay_instantaneous_x);

  Serial.print(F("Step Delay Speed Instantaneous y-axis (us): "));
  Serial.println(step_delay_instantaneous_y);
  Udp.write("\nStep Delay Speed Instantaneous y-axis (us): ");
  Udp.print(step_delay_instantaneous_y);

  Serial.print(F("Step Delay Acceleration Average x-axis (us): "));
  Serial.println(step_delay_acceleration_avg_x);
  Udp.write("\nStep Delay Acceleration Average x-axis (us): ");
  Udp.print(step_delay_acceleration_avg_x);

  Serial.print(F("Step Delay Acceleration Average y-axis (us): "));
  Serial.println(step_delay_acceleration_avg_y);
  Udp.write("\nStep Delay Acceleration Average y-axis (us): ");
  Udp.print(step_delay_acceleration_avg_y);

  Udp.endPacket();
  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());

  Serial.print(F("Step Count Acceleration Calculated x-axis (# of steps): "));
  Serial.println(step_count_acceleration_calculated_x);
  Udp.write("\nStep Count Acceleration Calculated x-axis (# of steps): ");
  Udp.print(step_count_acceleration_calculated_x);
  
  Serial.print(F("Step Count Acceleration Calculated y-axis (# of steps): "));
  Serial.println(step_count_acceleration_calculated_y);
  Udp.write("\nStep Count Acceleration Calculated y-axis (# of steps): ");
  Udp.print(step_count_acceleration_calculated_y);

  Serial.print(F("Step Count Acceleration x-axis (Applied) (# of steps): "));
  Serial.println(step_count_acceleration_x);
  Udp.write("\nStep Count Acceleration x-axis (Applied) (# of steps): ");
  Udp.print(step_count_acceleration_x);
  
  Serial.print(F("Step Count Acceleration y-axis (Applied) (# of steps): "));
  Serial.println(step_count_acceleration_y);
  Udp.write("\nStep Count Acceleration y-axis (Applied) (# of steps): ");
  Udp.print(step_count_acceleration_y);

  Serial.print(F("Input Speed Steady x-axis (mm/s): "));
  Serial.println(input_speed_steady_x);
  Udp.write("\nInput Speed Steady x-axis (mm/s): ");
  Udp.print(input_speed_steady_x);

  Serial.print(F("Input Speed Steady y-axis (mm/s): "));
  Serial.println(input_speed_steady_y);
  Udp.write("\nInput Speed Steady y-axis (mm/s): ");
  Udp.print(input_speed_steady_y);

  Serial.print(F("Input Acceleration x-axis (mm/s^2): "));
  Serial.println(input_acceleration_x);
  Udp.write("\nInput Acceleration x-axis (mm/s^2): ");
  Udp.print(input_acceleration_x);

  Serial.print(F("Input Acceleration y-axis (mm/s^2): "));
  Serial.println(input_acceleration_y);
  Udp.write("\nInput Acceleration y-axis (mm/s^2): ");
  Udp.print(input_acceleration_y);

  Serial.print(F("Delta t x-axis (s): "));
  Serial.println(delta_t_x);
  Udp.write("\nDelta t x-axis (s): ");
  Udp.print(delta_t_x);

  Serial.print(F("Delta y y-axis (s): "));
  Serial.println(delta_t_y);
  Udp.write("\nDelta t y-axis (s): ");
  Udp.print(delta_t_y);

  Serial.print(F("Driving Mechanism (0->Pulley, 1->Lead Screw): "));
  Serial.println(char(driving_mechanism));
  Udp.write("\nDriving Mechanism (0->Pulley, 1->Lead Screw): ");
  Udp.print(char(delta_t_x));

  Serial.println(F("---------------------------------------------------------------------- System Monitor End"));
  Udp.write("\n////System Monitor End////");
  
  Udp.endPacket();
}

float_t parse_distance(String package_income,char axis){
  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
  String delta_string;
  float_t delta_float = 0;
  if(axis == 'x'){
    delta_string = package_income.substring(3,7);
    delta_float = delta_string.toFloat();
    return delta_float; // Unit convertion of micrometers to millimeters 
  }
  else if(axis == 'y'){
    delta_string = package_income.substring(8,12);
    delta_float = delta_string.toFloat();
    return delta_float; // Unit convertion of micrometers to millimeters
  }
  else{
    Serial.println(">EF0003");
    Udp.write("EF0003");
  }

 Udp.endPacket();

}

void speed_acceleration_calculator_leadscrew(){
  step_delay_speed_steady_x = thread_distance_x*pow(10, 6) / (input_speed_steady_x*motor_fullcycle_step_x*microstep_coeff_x*2);
  step_delay_speed_steady_y = thread_distance_y*pow(10, 6) / (input_speed_steady_y*motor_fullcycle_step_y*microstep_coeff_y*2);
  delta_t_x = input_speed_steady_x / input_acceleration_x; // Delta time that acceleration going to be applied on x-axis
  delta_t_y = input_speed_steady_y / input_acceleration_y; // Delta time that acceleration going to be applied on y-axis
  step_delay_acceleration_avg_x = (step_delay_speed_min_x - step_delay_speed_steady_x) / 2; // Assuming acceleration is 0 and speed is constant at step_delay_speed_steady_x/2 on x-axis
  step_delay_acceleration_avg_y = (step_delay_speed_min_y - step_delay_speed_steady_y) / 2; // Assuming acceleration is 0 and speed is constant at step_delay_speed_steady_x/2 on y-axis
  step_count_acceleration_calculated_x = delta_t_x*pow(10, 6) / (step_delay_acceleration_avg_x * 2); //Number of steps that acceleration going to be applied on x-axis (2 delay for one step)
  step_count_acceleration_calculated_y = delta_t_y*pow(10, 6) / (step_delay_acceleration_avg_y * 2); //Number of steps that acceleration going to be applied on y-axis (2 delay for one step)
}

void speed_acceleration_calculator_pulley(){
  
  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
  
  step_delay_speed_steady_x = round((pi*pulley_diameter_x*pow(10, 6)) / (input_speed_steady_x * motor_fullcycle_step_x * microstep_coeff_x * 2));
  step_delay_speed_steady_y = round((pi*pulley_diameter_y*pow(10, 6)) / (input_speed_steady_y * motor_fullcycle_step_y * microstep_coeff_y * 2));

  Serial.print("Service Info: step_delay_speed_steady_x = ");
  Serial.println(step_delay_speed_steady_x);
  Udp.write("Service Info: step_delay_speed_steady_x = ");
  Udp.print(step_delay_speed_steady_x);
  Serial.print("Service Info: step_delay_speed_steady_y = ");
  Serial.println(step_delay_speed_steady_y);
  Udp.write("Service Info: step_delay_speed_steady_y = ");
  Udp.print(step_delay_speed_steady_y);
  
  delta_t_x = input_speed_steady_x / input_acceleration_x; // Delta time that acceleration going to be applied on x-axis
  delta_t_y = input_speed_steady_y / input_acceleration_y; // Delta time that acceleration going to be applied on y-axis
  step_delay_acceleration_avg_x = ((step_delay_speed_min_x / microstep_coeff_x) - step_delay_speed_steady_x) / 2; // Assuming acceleration is 0 and speed is constant at step_delay_speed_steady_x/2 on x-axis
  step_delay_acceleration_avg_y = ((step_delay_speed_min_y / microstep_coeff_y) - step_delay_speed_steady_y) / 2; // Assuming acceleration is 0 and speed is constant at step_delay_speed_steady_x/2 on y-axis
  step_count_acceleration_calculated_x = round((delta_t_x * pow(10, 6)) / (step_delay_acceleration_avg_x * 2)); //Number of steps that acceleration going to be apply on x-axis (2 delay for one step)
  step_count_acceleration_calculated_y = round((delta_t_y * pow(10, 6)) / (step_delay_acceleration_avg_y * 2)); //Number of steps that acceleration going to be apply on y-axis (2 delay for one step)

  Serial.print("Service Info: step_count_acceleration_calculated_x = ");
  Serial.println(step_count_acceleration_calculated_x);
  Udp.write("Service Info: step_count_acceleration_calculated_x = ");
  Udp.print(step_count_acceleration_calculated_x);
  Serial.print("Service Info: step_count_acceleration_calculated_y = ");
  Serial.println(step_count_acceleration_calculated_y);
  Udp.write("Service Info: step_count_acceleration_calculated_y = ");
  Udp.print(step_count_acceleration_calculated_y);

  Udp.endPacket();

}

uint16_t degree_to_step_converter(float_t degree, float_t motor_full_cycle_step, float_t micrestep_coeff){
  return round((degree * motor_full_cycle_step * micrestep_coeff) / 360);
}

float_t linear_to_rotational_converter(float_t distance, float_t system_cycle_linear_distance){ //Returns Degrees
  return ((distance / system_cycle_linear_distance) * 360);
}

void set_direction_x(char direction){

   Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());  

  if(direction == 'P'){
    digitalWrite(direction_pin_x_1, HIGH);
    digitalWrite(direction_pin_x_2, LOW);
  }
  else if(direction == 'N'){
    digitalWrite(direction_pin_x_1, LOW);
    digitalWrite(direction_pin_x_2, HIGH);
  }
  else {
    Serial.println(">EP0003");
    Udp.write(">EP0003");
  }

  Udp.endPacket();

}

void set_direction_y(char direction){

   Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());

  if(direction == 'P'){
    digitalWrite(direction_pin_y, HIGH);
  }
  else if(direction == 'N'){
    digitalWrite(direction_pin_y, LOW);
  }
  else {
    Serial.println(">EP0003");
    Udp.write(">EP0003");
  }

  Udp.endPacket();

}

void move_type_selector_step_calculator(String package_income){
  if(package_income[1] == 'L'){ // Input unit: Millimeters
    //--------------------------------------------------------------------- Parse distance from package
      float_t distance_x = parse_distance(package_income,'x');
      float_t distance_y = parse_distance(package_income,'y');
    //--------------------------------------------------------------------- Distance to Degree & Degree to Step Conversions
      degree_x = linear_to_rotational_converter(distance_x, system_cycle_linear_distance_x);
      degree_y = linear_to_rotational_converter(distance_y, system_cycle_linear_distance_y);
      step_x = degree_to_step_converter(degree_x, motor_fullcycle_step_x, microstep_coeff_x);
      step_y = degree_to_step_converter(degree_y, motor_fullcycle_step_y, microstep_coeff_y);
  }
  else if(package_income[1] == 'R'){ // Input Unit: Degrees
    degree_x = package_income.substring(3,7).toFloat();
    degree_y = package_income.substring(8,12).toFloat();
    step_x = degree_to_step_converter(degree_x, motor_fullcycle_step_x, microstep_coeff_x);
    step_y = degree_to_step_converter(degree_y, motor_fullcycle_step_y, microstep_coeff_y);
  }
  else if(package_income[1] == 'S'){ // Input Unit: Steps
    step_x = package_income.substring(3,7).toInt();
    step_y = package_income.substring(8,12).toInt();
  }
}

void move_motors(String package_income){

 Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());

//--------------------------------------------------------------------- Set Motors' Direction of Rotation
  set_direction_x(package_income[2]);
  set_direction_y(package_income[7]);
//--------------------------------------------------------------------- Calculates required # steps for action according to move type
  move_type_selector_step_calculator(package_income);
//--------------------------------------------------------------------- System Info, Delete after test 05.11.2021
  Serial.print("System Info: system_cycle_linear_distance_x (mm): ");
  Serial.println(system_cycle_linear_distance_x);
  Udp.write("\nSystem Info: system_cycle_linear_distance_x (mm): ");
  Udp.print(system_cycle_linear_distance_x);

  Serial.print("System Info: system_cycle_linear_distance_y (mm): ");
  Serial.println(system_cycle_linear_distance_y);
  Udp.write("\nSystem Info: system_cycle_linear_distance_y (mm): ");
  Udp.print(system_cycle_linear_distance_y);

  Serial.print("System Info: degree_x (deg): ");
  Serial.println(degree_x);
  Udp.write("\nSystem Info: degree_x (deg): ");
  Udp.print(degree_x);

  Serial.print("System Info: degree_y (deg): ");
  Serial.println(degree_y);
  Udp.write("\nSystem Info: degree_y (deg): ");
  Udp.print(degree_y);

  Serial.print("System Info: step_x (step): ");
  Serial.println(step_x);
  Udp.write("\nSystem Info: step_x (step): ");
  Udp.print(step_x);

  Serial.print("System Info: step_y (step): ");
  Serial.println(step_y);
  Udp.write("\nSystem Info: step_x (step): ");
  Udp.print(step_y);
//--------------------------------------------------------------------- Magic. Ask Emre Albayrak for more info.
  if(step_x / 2 > step_count_acceleration_calculated_x){
    step_count_acceleration_x = step_count_acceleration_calculated_x;
  }
  else{
    step_count_acceleration_x = step_x/2;
  }
  if(step_y / 2 > step_count_acceleration_calculated_y){
    step_count_acceleration_y = step_count_acceleration_calculated_y;
  }
  else{
    step_count_acceleration_y = step_y/2;
  }
//--------------------------------------------------------------------- Send Feedback (Move Command Confirmed)
  Serial.println(">FP0001");
  Udp.write(">FP0001");
  Serial.print("System Info: step_x = ");
  Serial.println(step_x);
  Udp.write("\nSystem Info: step_x = ");
  Udp.print(step_x);

  Serial.print("System Info: step_y = ");
  Serial.println(step_y);
  Udp.write("\nSystem Info: step_y = ");
  Udp.print(step_y);

//--------------------------------------------------------------------- Driving x-axis motor

  digitalWrite(enable_pin_x_1, LOW); //Let the motor power on
  digitalWrite(enable_pin_x_2, LOW); //Let the motor power on
  delay(100);

  for(int step_counter_x = 0 ; step_counter_x < step_x ; step_counter_x++){
    digitalWrite(pulse_pin_x_1, HIGH);
    digitalWrite(pulse_pin_x_2, HIGH);
    delayMicroseconds(step_delay_instantaneous_x);
    digitalWrite(pulse_pin_x_1, LOW);
    digitalWrite(pulse_pin_x_2, LOW);
    delayMicroseconds(step_delay_instantaneous_x);
//---------------------------------------------------------------------- Applying acceleration for x-axis
    if(step_counter_x < step_count_acceleration_x){
      step_delay_instantaneous_x = map(step_counter_x, 0, step_count_acceleration_calculated_x, step_delay_speed_min_x, step_delay_speed_steady_x);
    }
    else if(step_counter_x > step_x - step_count_acceleration_x){
      step_delay_instantaneous_x = map(step_counter_x, step_x - step_count_acceleration_calculated_x, step_x, step_delay_speed_steady_x, step_delay_speed_min_x);
    }
  }

  digitalWrite(enable_pin_x_1, HIGH); //Let the motor x_1 power off
  digitalWrite(enable_pin_x_2, HIGH); //Let the motor x_2 power off

//--------------------------------------------------------------------- Driving y-axis motor

  digitalWrite(enable_pin_y, LOW); //Let the motor y power on
  delay(100);

  for(int step_counter_y = 0; step_counter_y < step_count_acceleration_y; step_counter_y++){
    digitalWrite(pulse_pin_y, HIGH);
    delayMicroseconds(step_delay_instantaneous_y);
    digitalWrite(pulse_pin_y, LOW);
    delayMicroseconds(step_delay_instantaneous_y);
//---------------------------------------------------------------------- Applying acceleration for y-axis
    if(step_counter_y < step_count_acceleration_y){
      step_delay_instantaneous_y = map(step_counter_y, 0, step_count_acceleration_calculated_y, step_delay_speed_min_y, step_delay_speed_steady_y);
    }
    else if(step_counter_y > step_y - step_count_acceleration_y){
      step_delay_instantaneous_y = map(step_counter_y, step_y - step_count_acceleration_calculated_y, step_y, step_delay_speed_steady_y, step_delay_speed_min_y);
    }
  }

  digitalWrite(enable_pin_y, HIGH); //Let the motor y power off

//---------------------------------------------------------------------- Send Feedback (Action Accomplished)
  Serial.println(">FA0001");
  Udp.write("\n>FA0001");

  Udp.endPacket();
}

void destination_home_x_axis(){ 

  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
  Serial.println(">FP0002");
  Udp.write("\n>FP0002");
  
  bool limit_switch_flag_x = true;
  bool toggle = true;
  unsigned long time_1 = 0;
  set_direction_x('N');
  digitalWrite(enable_pin_x_1, LOW);
  digitalWrite(enable_pin_x_2, LOW);
  while(limit_switch_flag_x){
    if(digitalRead(limit_switch_pin_x) == HIGH){
      if(toggle == true){
        time_1 = millis();
        toggle = false;
      }
      if(millis() - time_1 >= 1){
        Serial.println(">FA0001");
        Udp.write("FA0001");
        limit_switch_flag_x = false;
      }
    }
    else{
      toggle = true;
    }
    // Serial.println("*");
    digitalWrite(pulse_pin_x_1,HIGH);
    digitalWrite(pulse_pin_x_2, HIGH);
    delayMicroseconds(step_delay_speed_home_x/microstep_coeff_x);
    digitalWrite(pulse_pin_x_1, LOW);
    digitalWrite(pulse_pin_x_2, LOW);
    delayMicroseconds(step_delay_speed_home_x/microstep_coeff_x);
  }
  digitalWrite(enable_pin_x_1, HIGH);
  digitalWrite(enable_pin_x_2, HIGH);

  Udp.endPacket();
}

void destination_home_y_axis(){ 
  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
  Serial.println(">FP0002");
  Udp.write(">FP0002");
  bool limit_switch_flag_y;
  bool toggle = true;
  unsigned long time_1 = 0;
  set_direction_y('N');
  while(limit_switch_flag_y = false){
    if(digitalRead(limit_switch_pin_y) == HIGH){ //Switch debounce for spikes
      if(toggle == true){
        time_1 = millis();
        toggle = false;
      }
      if(millis() - time_1 >= 1){
        Serial.println(">FA0001");
        Udp.write("\n>FA0001");
        limit_switch_flag_y = false;
      }
    }
    else{
      toggle = true;
    }
    digitalWrite(pulse_pin_y,HIGH);
    delayMicroseconds(step_delay_speed_home_y);
    digitalWrite(pulse_pin_y, LOW);
    delayMicroseconds(step_delay_speed_home_y); 
  }
  Udp.endPacket();
}

void destination_point(String package_income){ //TODO: Add destination point feature

}

void set_parameters(String package_income){ 

  String package_id_set_string = package_income.substring(1,3);
  uint8_t package_id_set_int = package_id_set_string.toInt();
  String parameter_value_set_string = package_income.substring(3,9);     
  uint32_t parameter_value_set_int = parameter_value_set_string.toInt();
  float_t parameter_memory = 0;

  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());

  switch (package_id_set_int){
    case 1:
      thread_distance_x = parameter_value_set_int;
      EEPROM.put(address_thread_distance_x, thread_distance_x);
      Serial.println(">FS0001");
      Udp.print(">\nFS0001");
      break;
    case 2:
      thread_distance_y = parameter_value_set_int;
      EEPROM.put(address_thread_distance_y, thread_distance_y);
      Serial.println(">FS0002");
      Udp.print("\n>FS0002");
      break;
    case 3:
      parameter_memory = parameter_value_set_int;
      pulley_diameter_x = parameter_memory / 10;
      EEPROM.put(address_pulley_diameter_x, pulley_diameter_x);
      Serial.println(">FS0003");
      Udp.print("\n>FS0003");
      break;
    case 4:
      parameter_memory = parameter_value_set_int;
      pulley_diameter_y = parameter_memory / 10;
      EEPROM.put(address_pulley_diameter_y, pulley_diameter_y);
      Serial.println(">FS0004");
      Udp.print("\n>FS0004");
      break;    
    case 5:
      motor_fullcycle_step_x = parameter_value_set_int;
      EEPROM.put(address_motor_fullcycle_step_x, motor_fullcycle_step_x);
      Serial.println(">FS0005");
      Udp.print("\n>FS0005");
      break;    
    case 6:
      motor_fullcycle_step_y = parameter_value_set_int;
      EEPROM.put(address_motor_fullcycle_step_y, motor_fullcycle_step_y);
      Serial.println(">FS0006");
      Udp.print("\n>FS0006");
      break;
    case 7:
      microstep_coeff_x = parameter_value_set_int;
      EEPROM.put(address_microstep_coeff_x, microstep_coeff_x);
      Serial.println(">FS0007");
      Udp.print("\n>FS0007");
      break;
    case 8:
      microstep_coeff_y = parameter_value_set_int;
      EEPROM.put(address_microstep_coeff_y, microstep_coeff_y);
      Serial.println(">FS0008");
      Udp.print("\n>FS0008");
      break;
    case 9:
      max_speed_x = parameter_value_set_int;
      Serial.println(">FS0009");
      Udp.print("\n>FS0009");
      break;
    case 10:
      max_speed_y = parameter_value_set_int;
      Serial.println(">FS0010");
      Udp.print("\n>FS0010");
      break;
    case 11:
      step_delay_speed_steady_x = parameter_value_set_int;
      Serial.println(">FS0011");
      Udp.print("\n>FS0011");
      break;
    case 12:
      step_delay_speed_steady_y = parameter_value_set_int;
      Serial.println(">FS0012");
      Udp.print("\n>FS0012");
      break;
    case 13:
      step_delay_speed_min_x = parameter_value_set_int;
      EEPROM.put(address_step_delay_speed_min_x, step_delay_speed_min_x);
      Serial.println(">FS0013");
      Udp.print("\n>FS0013");
      break;
    case 14:
      step_delay_speed_min_y = parameter_value_set_int;
      EEPROM.put(address_step_delay_speed_min_y, step_delay_speed_min_y);
      Serial.println(">FS0014");
      Udp.print("\n>FS0014");
      break;
    case 15:
      step_delay_instantaneous_x = parameter_value_set_int;
      Serial.println(">FS0015");
      Udp.print("\n>FS0015");
      break;
    case 16:
      step_delay_instantaneous_y = parameter_value_set_int;
      Serial.println(">FS0016");
      Udp.print("\n>FS0016");
      break;
    case 17:
      step_delay_acceleration_avg_x = parameter_value_set_int;
      Serial.println(">FS0017");
      Udp.print("\n>FS0017");
      break;
    case 18:
      step_delay_acceleration_avg_y = parameter_value_set_int;
      Serial.println(">FS0018");
      Udp.print("\n>FS0018");
      break;
    case 19:
      step_count_acceleration_x = parameter_value_set_int;
      Serial.println(">FS0019");
      Udp.print("\n>FS0019");
      break;
    case 20:
      step_count_acceleration_y = parameter_value_set_int;
      Serial.println(">FS0020");
      Udp.print("\n>FS0020");
      break;
    case 21:
      input_speed_steady_x = parameter_value_set_int;
      EEPROM.put(address_input_speed_steady_x, input_speed_steady_x);
      Serial.println(">FS0021");
      Udp.print("\n>FS0021");
      break;
    case 22:
      input_speed_steady_y = parameter_value_set_int;
      EEPROM.put(address_input_speed_steady_y, input_speed_steady_y);
      Serial.println(">FS0022");
      Udp.print("\n>FS0022");
      break;
    case 23:
      input_acceleration_x = parameter_value_set_int;
      EEPROM.put(address_input_acceleration_x, input_acceleration_x);
      Serial.println(">FS0023");
      Udp.print("\n>FS0023");
      break;
    case 24:
      input_acceleration_y = parameter_value_set_int;
      EEPROM.put(address_input_acceleration_y, input_acceleration_y);
      Serial.println(">FS0024");
      Udp.print("\n>FS0024");
      break;
    case 25:
      delta_t_x = parameter_value_set_int;
      Serial.println(">FS0025");
      Udp.print("\n>FS0025");
      break;
    case 26:
      delta_t_y = parameter_value_set_int;
      Serial.println(">FS0026");
      Udp.print("\n>FS0026");
      break;
    case 27:
      driving_mechanism = package_income[8];
      EEPROM.put(address_driving_mechanism, driving_mechanism);
      Serial.println(">FS0027");
      Udp.print("\n>FS0027");
      break;
    case 28:
      driving_mechanism = package_income[8];
      EEPROM.put(address_driving_mechanism, driving_mechanism);
      Udp.print(">FS0028");
      Serial.println("\n>FS0028");
      break;
    default:
      Serial.println(">EP0006");
      Udp.print("\n>EP0006");
      break;
  }
  if(driving_mechanism == '0'){
    speed_acceleration_calculator_pulley();
  }
  else if(driving_mechanism == '1'){
    speed_acceleration_calculator_leadscrew();
  }
  else{
    Serial.println(">EF0002");
    Udp.print("\n>EF0002");
  }
  Udp.endPacket();
}

void command_analyser(String package_income){ 
  uint32_t package_income_length = package_income.length();
  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
/*  //------------------------------- Test monitor here
  Serial.print("Package Length: ");
  Serial.println(package_income_length);
*/
  if(package_income_length = 12){
    if(package_income[0] == 'M'){
      move_motors(package_income);
    }
    else if(package_income[0] == 'S'){
      set_parameters(package_income);
    }
    else if(package_income[0] == 'G'){
      get_parameters_eeprom();
      system_monitor_parameters();
    }
    else if(package_income[0] == 'D'){
      destination_home_x_axis();
    }
    else{
      Serial.println(">EP0002");
      Udp.write("\n>EP0002");
    }
  }
  else{
    Serial.println(">EP0001");
    Udp.write("\n>EP0001");
  }

  Udp.endPacket();

}

void setup() {
  Serial.begin(115200);
//---------------------------------------------------------------------- Motor Pin Definitions
  pinMode(direction_pin_x_1, OUTPUT);
  pinMode(direction_pin_x_2, OUTPUT);
  pinMode(direction_pin_y, OUTPUT);
  pinMode(pulse_pin_x_1, OUTPUT);
  pinMode(pulse_pin_x_2, OUTPUT);
  pinMode(pulse_pin_y, OUTPUT);
  pinMode(enable_pin_x_1, OUTPUT);
  pinMode(enable_pin_x_2, OUTPUT);
  pinMode(enable_pin_y, OUTPUT);
  pinMode(limit_switch_pin_x, INPUT);
  pinMode(limit_switch_pin_y, INPUT);
  digitalWrite(enable_pin_x_1, HIGH);
  digitalWrite(enable_pin_x_2, HIGH);
  digitalWrite(enable_pin_y, HIGH);
  get_parameters_eeprom();

//---------------------------------------------------------------------- Motor Pin Definitions

  uint16_t index = millis() % NUMBER_OF_MAC;
  char16_t packetBuffer[255];          // buffer to hold incoming packet
  Ethernet.begin(mac[index], ip); // Use Static IP
  Udp.begin(localPort);

//---------------------------------------------------------------------- Driving Mechanism Selection
  if(driving_mechanism == '0'){
    system_cycle_linear_distance_x = pi*pulley_diameter_x;
    system_cycle_linear_distance_y = pi*pulley_diameter_y;
    speed_acceleration_calculator_pulley();
    //Serial.println("Checkpoint 0");
  }
  else if(driving_mechanism == '1'){
    system_cycle_linear_distance_x = thread_distance_x;
    system_cycle_linear_distance_y = thread_distance_y;
    speed_acceleration_calculator_leadscrew();
    //Serial.println("Checkpoint 1");
    
  }
  else{
    Serial.print(">EF0002");
  }
//---------------------------------------------------------------------- System Monitor
system_monitor_parameters();
}

void loop() {
  int packetSize = Udp.parsePacket();

  if(packetSize){  // if there's data available, read a packet
    int len = Udp.read(packetBuffer, 255);
    if(len > 0){
      packetBuffer[len] = 0;
    }
    command_analyser(packetBuffer);
  }

  if(Serial.available() > 0){
    serial_package = Serial.readString();
    command_analyser(serial_package);
  }
}
