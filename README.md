# Laverna
Line Follower Robot | 3i INC

Laverna is made with Qtrsensor 4.0.0 Library which is capable of following Black as well as White lines 
on contrasting backgrounds. This bot is extremely proficient since PID is interpreted with the motor speed 
by utilising the enable pins of L298N Module.

The code includes automatic calibration. Whether you wish for automatic or manual calibration is completely upto you,
So make the necessary changes in the code which is absolutely easy since the code is documented properly.
LCD Display is interfaced to know exactly what the state of bot is. Usage of the same is completely optional.
If there's power issue, then try to intrepret an LED indicator with the bot instead of the 16*2 LCD preffered
over the code.

Components we used,

Cheap Dual Shaft BO Motor and Wheel (* 2)
L298N Motor Driver
Smallest Chassis we could find (Prefer the Smallest One)
Arduino Mega (Select any arduino board with sufficient pins)

LIPO 11.1V 2200 mAh    (2200 mAh isn't necessary but select the one with smaller size and weight, 
                        Even Li ION Cells are fine)
                        
9V Battery for Arduino (Small Lipo/Li ION is better, we have ton of Non Rechargeable 9V Batteries as waste
                        So better use rechargeable ones or utilise long A to B cable if you have a laptop or 
                        portable power supply)
                        
16*2 LCD Display with a Breakout Board

One Button Switch and Two Regular Switeches (Prefer Small Ones)

