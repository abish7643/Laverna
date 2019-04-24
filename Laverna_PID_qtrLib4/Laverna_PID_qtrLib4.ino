//                        Laverna | 3i INC
//Code changed accordingly to the Latest Version of QTRSensors 4.0.0 (Previous: 3.1.0)

#include <Button.h>
#include <QTRSensors.h>
#include <Wire.h>
#include <LiquidCrystal.h>
                       
Button button = Button(8,BUTTON_PULLUP_INTERNAL); // Pin 8 - Button


QTRSensors qtrrc;
const uint8_t SensorCount = 5;
uint16_t sensorValues[SensorCount];
//QTRSensorsRC qtrrc((unsigned char[]) {14, 15, 16, 17, 18}, 5, 2000, QTR_NO_EMITTER_PIN);

// display in the pins: R/W - 13, Enable - 12, data - 9, 8, 7 4
LiquidCrystal lcd(42, 44, 46, 48, 50, 52);

// Variables definition
int pinButton = 13; // Button pin
//unsigned int sensors[5]; //  Array to store the sensors values
int inA1 = A0; //  Dual H-Bridge pins
int inA2 = A1;
int inB1 = A2;
int inB2 = A3;
int ENa = 2;
int ENb = 3;

int last_proportional;
int integral;

void setup(){
  qtrrc.setTypeRC(); //Call the fuction specifying the type of sensor, setTypeRC for QTR-xRC
  qtrrc.setSensorPins((const uint8_t[]){25, 27, 29, 31, 33}, SensorCount); 
  //the 5 sensor inputs 25, 27, 29, 31, 33
  qtrrc.setEmitterPin(22); //LEDON Pin - 22
  
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
  lcd.print("Press Button");
  
  while(button.isPressed()){    
  }
  
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Auto-calibration");
  Serial.println("Auto-calibration"); 

  // Autocalibration: turns to right and after to left and returns to the start position
  
  unsigned int i;
  for(i=0; i<115; i++){
    if(i < 20 || i >= 60){
      set_motors(100,-100); // Call the function set_motors to turn right
    }
    else{
      set_motors(-100,100); // Call the function set_motors to turn left
    }
    
    qtrrc.calibrate();  
    // This function stores a set of reads of the sensors and keep information about the maximum and minimum values found.
    delay(10); 
    // Total Time takes around 10ms * max value holding "i"
  }
  
  set_motors(0,0); //Motors are stopped after Calibration
  lcd.setCursor(0, 1);
  lcd.print("Calibrated");
  delay(1000);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press Again");
  //Press Again to follow the line

}

void loop(){
  while(button.isPressed()){
  }
  delay(200);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Go!");
  delay(500);

  while(1){
    unsigned int position = qtrrc.readLineBlack(sensorValues); //the sensorValues is given as argument to the function readLineBlack or readLineWhite
    
    int proportional = ((int)position) - 2000;
    int derivative = proportional - last_proportional;
    integral += proportional;
    last_proportional = proportional;
    int m_power_difference = proportional/10 + integral/10000 + derivative*3/2;
    int power_difference = (m_power_difference);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(power_difference);
    
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
    analogWrite(ENa, right_speed);
    analogWrite(ENb, left_speed);
    digitalWrite(inA1, HIGH);
    digitalWrite(inA2, LOW);
    digitalWrite(inB1, HIGH);
    digitalWrite(inB2, LOW);
  }
  if(right_speed >= 0 && left_speed < 0){
    left_speed = -left_speed;
    analogWrite(ENa, right_speed);
    analogWrite(ENb, left_speed);
    digitalWrite(inA1, LOW);
    digitalWrite(inA2, HIGH);
    digitalWrite(inB1, HIGH);
    digitalWrite(inB2, LOW);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("L");
  }
  if(right_speed < 0 && left_speed >= 0){
    right_speed = -right_speed;
    analogWrite(ENa, right_speed);
    analogWrite(ENb, left_speed);
    digitalWrite(inA1, HIGH);
    digitalWrite(inA2, LOW);
    digitalWrite(inB1, LOW);
    digitalWrite(inB2, HIGH);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("R");
  } 
}
