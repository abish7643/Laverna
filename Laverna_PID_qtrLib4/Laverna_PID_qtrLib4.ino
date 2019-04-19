//                Laverna | 3i INC
//Code changed accordingly to the 
//Latest Version of QTRSensors 4.0.0 (Previous: 3.1.0)

#include <Button.h>
#include <QTRSensors.h>
#include <Wire.h>
#include <LiquidCrystal.h>
                       
Button button = Button(2,BUTTON_PULLUP_INTERNAL); // pin 2 - button


// the 5 sensor are in the analogic pins
// used as digital pins named 14, 15, 16, 17 and 18
// time-out 2000 and without LED pin
QTRSensors qtrrc;
const uint8_t SensorCount = 6;
uint16_t sensorValues[SensorCount];
//QTRSensorsRC qtrrc((unsigned char[]) {14, 15, 16, 17, 18}, 5, 2000, QTR_NO_EMITTER_PIN);

// display in the pins: R/W - 13, Enable - 12, data - 9, 8, 7 4
LiquidCrystal lcd(13, 12, 9, 8, 7, 4);

// Variables definition
int pinButton = 2; // Button pin
//unsigned int sensors[5]; //  Array to store the sensors values
int inA1 = 10; //  Dual H-Bridge pins
int inA2 = 11;
int inB1 = 5;
int inB2 = 6;

int last_proportional;
int integral;

void setup(){
  qtrrc.setTypeRC();
  qtrrc.setSensorPins((const uint8_t[]){14, 15, 16, 17, 18}, SensorCount);
//  qtrrc.setEmitterPin(2);
  lcd.begin(16, 2);
  Serial.begin(9600);    
  set_motors(0,0);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("3I INC");
  lcd.setCursor(0, 1);
  lcd.print("Laverna");
  delay(2000);  
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Initializing");
  delay(1500);
  
  lcd.setCursor(0, 1);
  lcd.print("OK!");
  delay(1000);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pressione Botao");
  
  while(!button.isPressed()){    
  }
  
  delay(500); // Delay to allow time to take your finger off the button
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Auto-calibration");
  Serial.println("Auto-calibration");
  // Autocalibration: turns to right and after to left and returns to the start position
  // sensors' calibration
  
  unsigned int counter; // used as a simple counter
  for(counter=0; counter<80; counter++){
    if(counter < 20 || counter >= 60){
      set_motors(50,-50); // turn to right
    }
    else{
      set_motors(-50,50); // turn to left
    }
    // This function stores a set of reads of the sensors and 
    // keep information about the maximum and minimum values found.
    
    qtrrc.calibrate();
    // Since w count till 80, the whole time of calibration will be: 80 * 10 = 800 ms
    delay(10);
  }
  set_motors(0,0); // ensures that the motors are stopped after calibration proccess
  lcd.setCursor(0, 1);
  lcd.print("Calibrated");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press Karo");
  // While button is not pressed shows the position of the line relative to the sensors;

}

void loop(){
  while(!button.isPressed()){
  }
  delay(200);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Go! go! go! ...");
  delay(500);
  
  while(1){
    // Get the position of the line.  Note that we *must* provide
    // the "sensors" argument to read_line() here, even though we
    // are not interested in the individual sensor readings.
    
    unsigned int position = qtrrc.readLineWhite(sensorValues);
    
    int proportional = ((int)position) - 2000;
    int derivative = proportional - last_proportional;
    integral += proportional;
    
    last_proportional = proportional;
    int power_difference = proportional/10 + integral/10000 + derivative*3/2;
    
    const int max = 180;
    if(power_difference > max)
      power_difference = max;
    if(power_difference < -max)
      power_difference = -max;
    if(power_difference < 0)
      set_motors(max+power_difference, max);
    else
      set_motors(max, max-power_difference);
  }
}

void set_motors(int left_speed, int right_speed){
  if(right_speed >= 0 && left_speed >= 0){
    analogWrite(inA1, 0);
    analogWrite(inA2, right_speed);
    analogWrite(inB1, 0);
    analogWrite(inB2, left_speed);
  }
  if(right_speed >= 0 && left_speed < 0){
    left_speed = -left_speed;
    analogWrite(inA1, 0);
    analogWrite(inA2, right_speed);
    analogWrite(inB1, left_speed);
    analogWrite(inB2, 0);
  }
  if(right_speed < 0 && left_speed >= 0){
    right_speed = -right_speed;
    analogWrite(inA1, right_speed);
    analogWrite(inA2, 0);
    analogWrite(inB1, 0);
    analogWrite(inB2, left_speed);
  } 
}
