# Laverna | Line Follower Robot | 3i INC

Laverna is made with Qtrsensor 4.0.0 Library which is capable of following Black as well as White lines on contrasting backgrounds. This bot is extremely proficient since PID is interpreted with the motor speed by utilising the enable pins on L298N Module. 

The code includes automatic calibration. Whether you wish for automatic or manual calibration is completely upto you, So make the necessary changes in the code which is absolutely easy since the code is documented properly. LCD Display is interfaced to know exactly what the state of bot is. Usage of the same is completely optional. If there's power issue, then try to interpret an LED indicator with the bot instead of the 16x2 LCD preffered over the code.

#### *Special Mentions to elementzonline.com (Elementz Engineers Guild Pvt Ltd.). They provided all the components at an absolutely reasonable price and gave us all the necessary support that we didn't ask for.

### Prerequisites

Qtrsensor 4.0.0 Library | https://github.com/pololu/qtr-sensors-arduino 
Wire Library <br/>
Liquidcrystal | Optional-(If you're suing LCD Display) | https://github.com/arduino-libraries/LiquidCrystal <br/>
Button | https://www.arduinolibraries.info/libraries/button <br/>

*Try to Download right from the Arduino IDE for the latest version and from the right source as inteded. <br/>
All Libraries are included in our repository but make sure that you either upgrade or use the latest ones.

##### Components we used

*Cheap Dual Shaft BO Motor and Wheel (x2) <br/>
*L298N Motor Driver* (Make Sure that the voltage regular pins are not shorted. Then the
input will limit to 5V) <br/>
*Smallest Chassis* we could find (Prefer the Smallest One) <br/>
*Arduino Mega* (Select any arduino board with sufficient pins) <br/>
*LIPO 11.1V 2200 mAh*     (2200 mAh isn't necessary but select the one with smaller size and weight, <br/>
                           Even Li ION Cells are fine) <br/>
*9V Battery* for Arduino  (Small Lipo/Li ION is better, we have ton of Non Rechargeable 9V Batteries as waste <br/>
                           So better use rechargeable ones or utilise long A to B cable if you have a laptop or <br/>
                           portable power supply) <br/>
*16x2 LCD Display with a Breakout Board <br/>
*One Button Switch and Two Regular Switches* (Prefer Small Ones) <br/>

## Authors

Abish Vijayan (https://github.com/abish7643/ | abishvijayan7643@gmail.com)

### Contributers

Abhijit M (abhimadhu523@gmail.com) <br/>
Adith GM (adithgm14@gmail.com)

