
// Library includes
#include <Arduino.h>
#include <EEPROM.h>

// User defined includes
#include <parameters.h>

//--------------------------------------------------------------------- Motor Pin Parameters
int direction_pin_x = 2;
int direction_pin_y = 4;
int pulse_pin_x = 3;
int pulse_pin_y = 5;
//--------------------------------------------------------------------- Serial Communication Parameters
String serial_package;
//---------------------------------------------------------------------
float parse_distance(String package_income,char axis){
  float delta = 0;
  if(axis == 'x'){
    delta = (package_income[3]-'0')*1000000;
    delta = delta + (package_income[4]-'0')*100000;
    delta = delta + (package_income[5]-'0')*10000;
    delta = delta + (package_income[6]-'0')*1000;
    delta = delta + (package_income[7]-'0')*100;
    delta = delta + (package_income[8]-'0')*10;
    delta = delta + (package_income[9]-'0');
    return delta / 1000; // Unit convertion of micrometers to millimeters 
  }
  else if(axis == 'y'){
    delta = (package_income[3]-'0')*1000000;
    delta = delta + (package_income[11]-'0')*100000;
    delta = delta + (package_income[12]-'0')*10000;
    delta = delta + (package_income[13]-'0')*1000;
    delta = delta + (package_income[14]-'0')*100;
    delta = delta + (package_income[15]-'0')*10;
    delta = delta + (package_income[16]-'0');
    return delta / 1000; // Unit convertion of micrometers to millimeters
  }
  else{
    return 0;
  }
}

void speed_acceleration_calculator_leadscrew(){
  step_delay_speed_steady_x = threat_distance_x*(10^6) / (input_speed_steady_x*motor_fullcycle_step_x*microstep_coeff_x*2);
  step_delay_speed_steady_y = threat_distance_y*(10^6) / (input_speed_steady_y*motor_fullcycle_step_y*microstep_coeff_y*2);
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

void move_motor(String package_income){
//--------------------------------------------------------------------- Motor Direction of Rotation
  if(package_income[2] == 'P'){
    digitalWrite(direction_pin_x, HIGH);
  }
  else if(package_income[2] == 'N'){
    digitalWrite(direction_pin_x, LOW);
  }
  else {
    Serial.println("EP0003");
  }
  if(package_income[10] == 'P'){
    digitalWrite(direction_pin_y, HIGH);
  }
  else if(package_income[10] == 'N'){
    digitalWrite(direction_pin_y, LOW);
  }
  else {
    Serial.println("EP0003");
  }
//--------------------------------------------------------------------- Parse distance from package
  float distance_x = parse_distance(package_income,'x');
  float distance_y = parse_distance(package_income,'y');
//--------------------------------------------------------------------- Distance to Degree & Degree to Step Conversions
  float degree_x = (distance_x / system_cycle_linear_distance_x) * 360;
  float degree_y = (distance_y / system_cycle_linear_distance_y) * 360;
  int step_x = degree_x * (360 / motor_fullcycle_step_x) / microstep_coeff_x;
  int step_y = degree_y * (360 / motor_fullcycle_step_y) / microstep_coeff_y;
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
  Serial.println("FP0001");
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
//---------------------------------------------------------------------- Driving y-axis motor
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
  Serial.print("FA0001");
}

void goto_point(String package_income){

}

void set_parameters(String package_income){

  int package_id_set = ((package_income[1]-'0') * 10)+(package_income[2] - '0');
  int parameter_value_set = ((package_income[3]-'0')*100000)+((package_income[4]-'0')*10000)+((package_income[5]-'0')*1000)+((package_income[6]-'0')*100)+((package_income[7]-'0')*10)+((package_income[8]-'0'));     
  
  switch (package_id_set){
    case 1:
      threat_distance_x = parameter_value_set;
      Serial.println("FS0001");
      break;
    case 2:
      threat_distance_y = parameter_value_set;
      Serial.println("FS0002");
      break;
    case 3:
      pulley_diameter_x = parameter_value_set;
      Serial.println("FS0003");
      break;
    case 4:
      pulley_diameter_y = parameter_value_set;
      Serial.println("FS0004");
      break;    
    case 5:
      motor_fullcycle_step_x = parameter_value_set;
      Serial.println("FS0005");
      break;    
    case 6:
      motor_fullcycle_step_y = parameter_value_set;
      Serial.println("FS0006");
      break;
    case 7:
      microstep_coeff_x = parameter_value_set;
      Serial.println("FS0007");
      break;
    case 8:
      microstep_coeff_y = parameter_value_set;
      Serial.println("FS0008");
      break;
    case 9:
      max_speed_x = parameter_value_set;
      Serial.println("FS0009");
      break;
    case 10:
      max_speed_y = parameter_value_set;
      Serial.println("FS0010");
      break;
    case 11:
      step_delay_speed_steady_x = parameter_value_set;
      Serial.println("FS0011");
      break;
    case 12:
      step_delay_speed_steady_y = parameter_value_set;
      Serial.println("FS0012");
      break;
    case 13:
      step_delay_speed_min_x = parameter_value_set;
      Serial.println("FS0013");
      break;
    case 14:
      step_delay_speed_min_y = parameter_value_set;
      Serial.println("FS0014");
      break;
    case 15:
      step_delay_instantaneous_x = parameter_value_set;
      Serial.println("FS0015");
      break;
    case 16:
      step_delay_instantaneous_y = parameter_value_set;
      Serial.println("FS0016");
      break;
    case 17:
      step_delay_acceleration_avg_x = parameter_value_set;
      Serial.println("FS0017");
      break;
    case 18:
      step_delay_acceleration_avg_y = parameter_value_set;
      Serial.println("FS0018");
      break;
    case 19:
      step_count_acceleration_x = parameter_value_set;
      Serial.println("FS0019");
      break;
    case 20:
      step_count_acceleration_y = parameter_value_set;
      Serial.println("FS0020");
      break;
    case 21:
      input_speed_steady_x = parameter_value_set;
      Serial.println("FS0021");
      break;
    case 22:
      input_speed_steady_y = parameter_value_set;
      Serial.println("FS0022");
      break;
    case 23:
      input_acceleration_x = parameter_value_set;
      Serial.println("FS0023");
      break;
    case 24:
      input_acceleration_y = parameter_value_set;
      Serial.println("FS0024");
      break;
    case 25:
      delta_t_x = parameter_value_set;
      Serial.println("FS0025");
      break;
    case 26:
      delta_t_y = parameter_value_set;
      Serial.println("FS0026");
      break;
    case 27:
      driving_mechanism = parameter_value_set;
      speed_acceleration_calculator_pulley();
      Serial.println("FS0027");
      break;
    case 28:
      driving_mechanism = parameter_value_set;
      speed_acceleration_calculator_leadscrew();
      Serial.println("FS0028");
      break;
    default:
      Serial.println("EP0006");
      break;
  }
}

void command_analyser(String package_income){
  if(package_income[0] == 'M'){
    move_motor(package_income);
  }
  else if(package_income[0] == 'S'){
    set_parameters(package_income);
  }
  else if(package_income[0] == 'G'){
    goto_point(package_income);
  }
  else{
    Serial.println("EP0002");
  }

}

void setup() {
  Serial.begin(9600);
//---------------------------------------- Motor Pin Definitions
  pinMode(direction_pin_x, OUTPUT);
  pinMode(direction_pin_y, OUTPUT);
  pinMode(pulse_pin_x, OUTPUT);
  pinMode(pulse_pin_y, OUTPUT);
//----------------------------------------
  if(driving_mechanism = 0){
    system_cycle_linear_distance_x = pi*pulley_diameter_x;
    system_cycle_linear_distance_y = pi*pulley_diameter_y;
    speed_acceleration_calculator_pulley();
  }
  else{
    system_cycle_linear_distance_x = threat_distance_x;
    system_cycle_linear_distance_y = threat_distance_y;
    speed_acceleration_calculator_leadscrew();
  }
}

void loop() {
  if(Serial.available() > 0){
    serial_package = Serial.readString();
    command_analyser(serial_package);
  }
}
