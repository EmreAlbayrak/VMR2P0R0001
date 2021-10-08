
// Library includes
#include <Arduino.h>
#include <EEPROM.h>

// User defined includes
#include <parameters.h>

//--------------------------------------------------------------------- Motor Pin Parameters
const int direction_pin_x = 2;
const int direction_pin_y = 4;
const int pulse_pin_x = 3;
const int pulse_pin_y = 5;
//--------------------------------------------------------------------- Serial Communication Parameters
String serial_package;
//---------------------------------------------------------------------
void system_monitor_parameters(){
  Serial.println("---------------------------------------------------------------------- System Monitor Start");

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

  Serial.print("Thread Distance x-axis (mm): ");
  Serial.println(thread_distance_x);
  
  Serial.print("Thread Distance y-axis (mm): ");
  Serial.println(thread_distance_y);
  
  Serial.print("Pulley Diameter x-axis (mm): ");
  Serial.println(pulley_diameter_x);

  Serial.print("Pulley Diameter y-axis (mm): ");
  Serial.println(pulley_diameter_y);

  Serial.print("Motor Full Cycle x-axis (# of steps): ");
  Serial.println(motor_fullcycle_step_x);

  Serial.print("Motor Full Cycle y-axis (# of Steps): ");
  Serial.println(motor_fullcycle_step_y);

  Serial.print("Microstep Coeff x-axis: ");
  Serial.println(microstep_coeff_x);

  Serial.print("Microstep Coeff y-axis: ");
  Serial.println(microstep_coeff_y);

  Serial.print("Max Speed x-axis (mm/s): ");
  Serial.println(max_speed_x);

  Serial.print("Max Speed y-axis (mm/s): ");
  Serial.println(max_speed_y);

  Serial.print("Step Delay Speed Steady x-axis (us): ");
  Serial.println(step_delay_speed_steady_x);

  Serial.print("Step Delay Speed Steady y-axis (us): ");
  Serial.println(step_delay_speed_steady_y);

  Serial.print("Step Delay Speed Min x-axis (us): ");
  Serial.println(step_delay_speed_min_x);

  Serial.print("Step Delay Speed Min y-axis (us): ");
  Serial.println(step_delay_speed_min_y);

  Serial.print("Step Delay Speed Instantaneous x-axis (us): ");
  Serial.println(step_delay_instantaneous_x);

  Serial.print("Step Delay Speed Instantaneous y-axis (us): ");
  Serial.println(step_delay_instantaneous_y);

  Serial.print("Step Delay Acceleration Average x-axis (us): ");
  Serial.println(step_delay_acceleration_avg_x);

  Serial.print("Step Delay Acceleration Average y-axis (us): ");
  Serial.println(step_delay_acceleration_avg_y);

  Serial.print("Step Count Acceleration Calculated x-axis (# of steps): ");
  Serial.println(step_count_acceleration_calculated_x);
  
  Serial.print("Step Count Acceleration Calculated y-axis (# of steps): ");
  Serial.println(step_count_acceleration_calculated_y);

  Serial.print("Step Count Acceleration x-axis (Applied) (# of steps): ");
  Serial.println(step_count_acceleration_x);

  Serial.print("Step Count Acceleration y-axis (Applied) (# of steps): ");
  Serial.println(step_count_acceleration_y);

  Serial.print("Input Speed Steady x-axis (mm/s): ");
  Serial.println(input_speed_steady_x);

  Serial.print("Input Speed Steady y-axis (mm/s): ");
  Serial.println(input_speed_steady_y);

  Serial.print("Input Acceleration x-axis (mm/s^2): ");
  Serial.println(input_acceleration_x);

  Serial.print("Input Acceleration y-axis (mm/s^2): ");
  Serial.println(input_acceleration_y);

  Serial.print("Delta t x-axis (s): ");
  Serial.println(delta_t_x);

  Serial.print("Delta y y-axis (s): ");
  Serial.println(delta_t_y);

  Serial.print("Driving Mechanism (0->Pulley, 1->Lead Screw): ");
  Serial.println(driving_mechanism);

  Serial.println("---------------------------------------------------------------------- System Monitor End");

}

float_t parse_distance(String package_income,char axis){
  String delta_string;
  float_t delta_float = 0;
  if(axis == 'x'){
    delta_string = package_income.substring(3,10);
    delta_float = delta_string.toFloat();
    return delta_float / 1000; // Unit convertion of micrometers to millimeters 
  }
  else if(axis == 'y'){
    delta_string = package_income.substring(11,18);
    delta_float = delta_string.toFloat();
    return delta_float / 1000; // Unit convertion of micrometers to millimeters
  }
  else{
    Serial.println(">EF0003");
    return 0;
  }
}

void speed_acceleration_calculator_leadscrew(){
  step_delay_speed_steady_x = thread_distance_x*(10^6) / (input_speed_steady_x*motor_fullcycle_step_x*microstep_coeff_x*2);
  step_delay_speed_steady_y = thread_distance_y*(10^6) / (input_speed_steady_y*motor_fullcycle_step_y*microstep_coeff_y*2);
  delta_t_x = input_speed_steady_x / input_acceleration_x; // Delta time that acceleration going to be applied on x-axis
  delta_t_y = input_speed_steady_y / input_acceleration_y; // Delta time that acceleration going to be applied on y-axis
  step_delay_acceleration_avg_x = (step_delay_speed_min_x - step_delay_speed_steady_x) / 2; // Assuming acceleration is 0 and speed is constant at step_delay_speed_steady_x/2 on x-axis
  step_delay_acceleration_avg_y = (step_delay_speed_min_y - step_delay_speed_steady_y) / 2; // Assuming acceleration is 0 and speed is constant at step_delay_speed_steady_x/2 on y-axis
  step_count_acceleration_calculated_x = delta_t_x*(10^6) / (step_delay_acceleration_avg_x * 2); //Number of steps that acceleration going to be applied on x-axis (2 delay for one step)
  step_count_acceleration_calculated_y = delta_t_y*(10^6) / (step_delay_acceleration_avg_y * 2); //Number of steps that acceleration going to be applied on y-axis (2 delay for one step)
}

void speed_acceleration_calculator_pulley(){
  step_delay_speed_steady_x = pi*pulley_diameter_x*(10^6) / (input_speed_steady_x*motor_fullcycle_step_x*microstep_coeff_x*2);
  step_delay_speed_steady_y = pi*pulley_diameter_y*(10^6) / (input_speed_steady_y*motor_fullcycle_step_y*microstep_coeff_y*2);
  delta_t_x = input_speed_steady_x / input_acceleration_x; // Delta time that acceleration going to be applied on x-axis
  delta_t_y = input_speed_steady_y / input_acceleration_y; // Delta time that acceleration going to be applied on y-axis
  step_delay_acceleration_avg_x = (step_delay_speed_min_x - step_delay_speed_steady_x) / 2; // Assuming acceleration is 0 and speed is constant at step_delay_speed_steady_x/2 on x-axis
  step_delay_acceleration_avg_y = (step_delay_speed_min_y - step_delay_speed_steady_y) / 2; // Assuming acceleration is 0 and speed is constant at step_delay_speed_steady_x/2 on y-axis
  step_count_acceleration_calculated_x = delta_t_x*(10^6) / step_delay_acceleration_avg_x * 2; //Number of steps that acceleration going to be applied on x-axis (2 delay for one step)
  step_count_acceleration_calculated_y = delta_t_y*(10^6) / step_delay_acceleration_avg_y * 2; //Number of steps that acceleration going to be applied on y-axis (2 delay for one step)
}

uint16_t degree_to_step_converter(float_t degree, uint32_t motor_full_cycle_step,uint32_t micrestep_coeff){
  return (degree * motor_full_cycle_step * micrestep_coeff / 360);
}

float_t linear_to_rotational_converter(float_t distance, uint32_t system_cycle_linear_distance){
  return ((distance / system_cycle_linear_distance) * 360);
}

void move_motors(String package_income){
//--------------------------------------------------------------------- Definition of Parameters
float_t degree_x;
float_t degree_y;
uint32_t step_x;
uint32_t step_y;
//--------------------------------------------------------------------- Motor Direction of Rotation
  if(package_income[2] == 'P'){
    digitalWrite(direction_pin_x, HIGH);
  }
  else if(package_income[2] == 'N'){
    digitalWrite(direction_pin_x, LOW);
  }
  else {
    Serial.println(">EP0003");
  }
  if(package_income[10] == 'P'){
    digitalWrite(direction_pin_y, HIGH);
  }
  else if(package_income[10] == 'N'){
    digitalWrite(direction_pin_y, LOW);
  }
  else {
    Serial.println(">EP0003");
  }
  if(package_income[1] == 'L'){
    //--------------------------------------------------------------------- Parse distance from package
      float_t distance_x = parse_distance(package_income,'x');
      float_t distance_y = parse_distance(package_income,'y');
    //--------------------------------------------------------------------- Distance to Degree & Degree to Step Conversions
      degree_x = linear_to_rotational_converter(distance_x, system_cycle_linear_distance_x);
      degree_y = linear_to_rotational_converter(distance_y, system_cycle_linear_distance_y);
      step_x = degree_to_step_converter(degree_x, motor_fullcycle_step_x, microstep_coeff_x);
      step_y = degree_to_step_converter(degree_y, motor_fullcycle_step_y, microstep_coeff_y);
  }
  else if(package_income[1] == 'R'){
    degree_x = package_income.substring(3,10).toFloat();
    degree_y = package_income.substring(11,18).toFloat();
    step_x = degree_to_step_converter(degree_x, motor_fullcycle_step_x, microstep_coeff_x);
    step_y = degree_to_step_converter(degree_y, motor_fullcycle_step_y, microstep_coeff_y);
  }
  else if(package_income[1] == 'S'){
    step_x = package_income.substring(3,10).toInt();
    step_y = package_income.substring(11,18).toInt();
  }
//--------------------------------------------------------------------- Easter Egg
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
  system_monitor_parameters();
//--------------------------------------------------------------------- Driving x-axis motor
  for(int step_counter_x = 0 ; step_counter_x < step_x ; step_counter_x++){
    digitalWrite(pulse_pin_x, HIGH);
    delayMicroseconds(step_delay_instantaneous_x);
    digitalWrite(pulse_pin_x, LOW);
    delayMicroseconds(step_delay_instantaneous_y);
//---------------------------------------------------------------------- Applying acceleration for x-axis
    if(step_counter_x < step_count_acceleration_x){
      step_delay_instantaneous_x = map(step_counter_x, 0, step_count_acceleration_calculated_x, step_delay_speed_min_x, step_delay_speed_steady_x);
    }
    else if(step_counter_x > step_x - step_count_acceleration_x){
      step_delay_instantaneous_x = map(step_counter_x, step_x - step_count_acceleration_calculated_x, step_x, step_delay_speed_steady_x, step_delay_speed_min_x);
    }
  }
//--------------------------------------------------------------------- Driving y-axis motor
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
//---------------------------------------------------------------------- Send Feedback (Action Accomplished)
  Serial.println(">FA0001"); 
}

void goto_point(String package_income){ //TODO: Add destination point feature here 

}

void set_parameters(String package_income){ 

  String package_id_set_string = package_income.substring(1,3);
  int package_id_set_int = package_id_set_string.toInt();
  String parameter_value_set_string = package_income.substring(3,9);     
  uint32_t parameter_value_set_int = parameter_value_set_string.toInt();

  switch (package_id_set_int){
    case 1:
      thread_distance_x = parameter_value_set_int;
      EEPROM.put(address_thread_distance_x, thread_distance_x);
      Serial.println(">FS0001");
      break;
    case 2:
      thread_distance_y = parameter_value_set_int;
      EEPROM.put(address_thread_distance_y, thread_distance_y);
      Serial.println(">FS0002");
      break;
    case 3:
      pulley_diameter_x = parameter_value_set_int / 10;
      EEPROM.put(address_pulley_diameter_x, pulley_diameter_x);
      Serial.println(">FS0003");
      break;
    case 4:
      pulley_diameter_y = parameter_value_set_int / 10;
      EEPROM.put(address_pulley_diameter_y, pulley_diameter_y);
      Serial.println(">FS0004");
      break;    
    case 5:
      motor_fullcycle_step_x = parameter_value_set_int;
      EEPROM.put(address_motor_fullcycle_step_x, motor_fullcycle_step_x);
      Serial.println(">FS0005");
      break;    
    case 6:
      motor_fullcycle_step_y = parameter_value_set_int;
      EEPROM.put(address_motor_fullcycle_step_y, motor_fullcycle_step_y);
      Serial.println(">FS0006");
      break;
    case 7:
      microstep_coeff_x = parameter_value_set_int;
      EEPROM.put(address_microstep_coeff_x, microstep_coeff_x);
      Serial.println(">FS0007");
      break;
    case 8:
      microstep_coeff_y = parameter_value_set_int;
      EEPROM.put(address_microstep_coeff_y, microstep_coeff_y);
      Serial.println(">FS0008");
      break;
    case 9:
      max_speed_x = parameter_value_set_int;
      Serial.println(">FS0009");
      break;
    case 10:
      max_speed_y = parameter_value_set_int;
      Serial.println(">FS0010");
      break;
    case 11:
      step_delay_speed_steady_x = parameter_value_set_int;
      Serial.println(">FS0011");
      break;
    case 12:
      step_delay_speed_steady_y = parameter_value_set_int;
      Serial.println(">FS0012");
      break;
    case 13:
      step_delay_speed_min_x = parameter_value_set_int;
      Serial.println(">FS0013");
      break;
    case 14:
      step_delay_speed_min_y = parameter_value_set_int;
      Serial.println(">FS0014");
      break;
    case 15:
      step_delay_instantaneous_x = parameter_value_set_int;
      Serial.println(">FS0015");
      break;
    case 16:
      step_delay_instantaneous_y = parameter_value_set_int;
      Serial.println(">FS0016");
      break;
    case 17:
      step_delay_acceleration_avg_x = parameter_value_set_int;
      Serial.println(">FS0017");
      break;
    case 18:
      step_delay_acceleration_avg_y = parameter_value_set_int;
      Serial.println(">FS0018");
      break;
    case 19:
      step_count_acceleration_x = parameter_value_set_int;
      Serial.println(">FS0019");
      break;
    case 20:
      step_count_acceleration_y = parameter_value_set_int;
      Serial.println(">FS0020");
      break;
    case 21:
      input_speed_steady_x = parameter_value_set_int;
      EEPROM.put(address_input_speed_steady_x, input_speed_steady_x);
      Serial.println(">FS0021");
      break;
    case 22:
      input_speed_steady_y = parameter_value_set_int;
      EEPROM.put(address_input_speed_steady_y, input_speed_steady_y);
      Serial.println(">FS0022");
      break;
    case 23:
      input_acceleration_x = parameter_value_set_int;
      EEPROM.put(address_input_acceleration_x, input_acceleration_x);
      Serial.println(">FS0023");
      break;
    case 24:
      input_acceleration_y = parameter_value_set_int;
      EEPROM.put(address_input_acceleration_y, input_acceleration_y);
      Serial.println(">FS0024");
      break;
    case 25:
      delta_t_x = parameter_value_set_int;
      Serial.println(">FS0025");
      break;
    case 26:
      delta_t_y = parameter_value_set_int;
      Serial.println(">FS0026");
      break;
    case 27:
      driving_mechanism = parameter_value_set_int;
      EEPROM.put(address_driving_mechanism, driving_mechanism);
      Serial.println(">FS0027");
      break;
    case 28:
      driving_mechanism = parameter_value_set_int;
      EEPROM.put(address_driving_mechanism, driving_mechanism);
      Serial.println(">FS0028");
      break;
    default:
      Serial.println(">EP0006");
      break;
  }
  if(driving_mechanism = 0){
    speed_acceleration_calculator_pulley();
  }
  else if(driving_mechanism = 1){
    speed_acceleration_calculator_leadscrew();
  }
  else{
    Serial.println(">EF0002");
  }
}

void get_parameters_eeprom(){
  EEPROM.get(address_thread_distance_x, thread_distance_x);
  EEPROM.get(address_thread_distance_y, thread_distance_y);
  EEPROM.get(address_pulley_diameter_x, pulley_diameter_y);
  EEPROM.get(address_pulley_diameter_y, pulley_diameter_y);
}

void command_analyser(String package_income){ 
  uint32_t package_income_length = package_income.length();
/*  //------------------------------- Test monitor here
  Serial.print("Package Length: ");
  Serial.println(package_income_length);
*/
  if(package_income_length = 18){
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
    else{
      Serial.println(">EP0002");
    }
  }
  else{
    Serial.println(">EP0001");
  }
}

void setup() { //TODO: Check "diriving_mechanism: 1" bug. Change the type from "int" to "char" and try again. 
  Serial.begin(9600);
//---------------------------------------------------------------------- Motor Pin Definitions
  pinMode(direction_pin_x, OUTPUT);
  pinMode(direction_pin_y, OUTPUT);
  pinMode(pulse_pin_x, OUTPUT);
  pinMode(pulse_pin_y, OUTPUT);
//---------------------------------------------------------------------- Driving Mechanism Selection
  if(driving_mechanism == '0'){
    system_cycle_linear_distance_x = pi*pulley_diameter_x;
    system_cycle_linear_distance_y = pi*pulley_diameter_y;
    speed_acceleration_calculator_pulley();
    Serial.println("Checkpoint 1");
  }
  else if(driving_mechanism == '1'){
    system_cycle_linear_distance_x = thread_distance_x;
    system_cycle_linear_distance_y = thread_distance_y;
    speed_acceleration_calculator_leadscrew();
    Serial.println("Checkpoint 2");
  }
  else{
    Serial.print(">EF0002");
  }
//---------------------------------------------------------------------- System Monitor
get_parameters_eeprom();
system_monitor_parameters();
}

void loop() {
  if(Serial.available() > 0){
    serial_package = Serial.readString();
    command_analyser(serial_package);
  }
}
