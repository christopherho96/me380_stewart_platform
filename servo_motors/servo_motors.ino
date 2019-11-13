
/* =================================================================================================== 
 *  This code has been provided as an example to help you get started on your project. The objective 
 *  is to provide user input to the Arduino board and have the servo motors actuate. Several lines of 
 *  code are accredited to the Adafruit PWM Servo Driver Library example code. To use the Adafruit 
 *  PWM Servo Shield, be sure to add the Adafruit library to your Arduino IDE. 
 *  (Adafruit example: File menu > Examples > Adafruit PWM Servo Drivers Library > servo)
 *  
 *  Add Adafruit Library: In the Arduino IDE application select: Sketch menu > Include Libraries > 
 *  Manage Libraries. In the Library Manager window, search and install the "Adafruit PWM Servo 
 *  Driver Library".
 *  
 *  NOTE: Depending on your servo motor, the pulse width min/max may be different. Adjust to match 
 *  your servo motor.
 =================================================================================================== */

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

const int SERVOMIN = 175; // 'minimum' pulse length count (out of 4096)
const int SERVOMAX = 475; // 'maximum' pulse length count (out of 4096)
const int SERVOMID = floor((SERVOMAX+SERVOMIN)/2); // 'mid' pulse length count (out of 4096)
const int SERVOCHG = 20; // 'change' pulse length count

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

String valInput; // Serial input var.
int i=0; // loop index var.
int val[6] = {309, 325, 330, 287, 310, 332}; // PWM var
int mins[6] = {140, 132, 142, 113, 136, 138}; // lower bounds for each motor
int mids[6] = {309, 325, 330, 287, 310, 332}; // reset points
int maxs[6] = {478, 518, 518, 462, 485, 527}; // upper bounds for each motor

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  Serial.setTimeout(10); // change default (1000ms) to have faster response time
  Serial.println("Running example: Servo motor actuation using messaging");
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
}

void balance(){
   for (i=0; i<6; i++) {
       val[i] = mids[i];
   }
   update();
}

void update(){
  for (i=0; i<6; i++) {
     pwm.setPWM(i+1, 0, val[i]); // added +1 to match PWM port numbering (pins 1..6 used)
  }
}

void loop() {
  if (Serial.available() > 0) {

    valInput = Serial.readString();
    Serial.print("I received: ");
    Serial.print(valInput);

    switch (valInput[0]) {
      // Input of "1" to "6" -> increase respective (1..6) values
      // Input of [q,w,e,r,t,y] -> decrease respective (1..6) values

      // paired motors 
      // index+1 = motor number
      // example: index 2 controls motor 3 

      // motor 1,3 paired

      case '@':
        balance();
        delay(3000);
        val[0]= min( val[0]+100, maxs[0] );
        val[4]= max( val[4]-100, mins[4] );
        update();
        delay(3000);
        val[3]= max( val[3]-SERVOCHG, mins[3] );
        val[5]= min( val[5]+SERVOCHG, maxs[5] );
        val[1]= max( val[1]-SERVOCHG, mins[1] );
        val[2]= min( val[2]+SERVOCHG, maxs[2] );
        update();
        delay(2000);
        val[3]= max( val[3]-SERVOCHG, mins[3] );
        val[5]= min( val[5]+SERVOCHG, maxs[5] );
        val[1]= max( val[1]-SERVOCHG, mins[1] );
        val[2]= min( val[2]+SERVOCHG, maxs[2] );
        update();
        delay(2000);
        val[3]= max( val[3]-SERVOCHG, mins[3] );
        val[5]= min( val[5]+SERVOCHG, maxs[5] );
        val[1]= max( val[1]-SERVOCHG, mins[1] );
        val[2]= min( val[2]+SERVOCHG, maxs[2] );
        update();
        delay(2000);
        val[1]= max( val[1]-SERVOCHG, mins[1] );
        val[2]= min( val[2]+SERVOCHG, maxs[2] );
        update();
        delay(2000);
        val[1]= max( val[1]-SERVOCHG, mins[1] );
        val[2]= min( val[2]+SERVOCHG, maxs[2] );
        update();
        delay(2000);
        val[1]= max( val[1]-SERVOCHG, mins[1] );
        val[2]= min( val[2]+SERVOCHG, maxs[2] );
        update();
        val[1]= max( val[1]-SERVOCHG, mins[1] );
        val[2]= min( val[2]+SERVOCHG, maxs[2] );
        update();
        delay(700);
        val[3]= max( val[3]-100, mins[3] );
        val[5]= min( val[5]+100, maxs[5] );
        update();
        //up to here, the ball should have made the sharp turn
        
        delay(1100);
        val[3]= max( val[3]-100, mins[3] );
        val[5]= min( val[5]+100, maxs[5] );
        update();
        
        Serial.println("Finished Solving");
        break;
        
      case 'i': 
        val[0]= min( val[0]+SERVOCHG, maxs[0] );
        val[4]= max( val[4]-SERVOCHG, mins[4] );
        break;

      case 'o': 
        val[0]= max( val[0]-SERVOCHG, mins[0] );
        val[4]= min( val[4]+SERVOCHG, maxs[4] );
        break;

      // motor 4,6 paired
      case 'k': 
        val[3]= max( val[3]-SERVOCHG, mins[3] );
        val[5]= min( val[5]+SERVOCHG, maxs[5] );
        break;
        
      case 'l': 
        val[3]= min( val[3]+SERVOCHG, maxs[3] );
        val[5]= max( val[5]-SERVOCHG, mins[5] );
        break;

      // motor 2, 3
      case 'b': 
        val[1]= min( val[1]+SERVOCHG, maxs[1] );
        val[2]= max( val[2]-SERVOCHG, mins[2] );
        break;
        
      case 'n': 
        val[1]= max( val[1]-SERVOCHG, mins[1] );
        val[2]= min( val[2]+SERVOCHG, maxs[2] );
        break;

      case '9':
        val[2]= max( val[2]-SERVOCHG, mins[2] );
        val[3]= max( val[3]-SERVOCHG, mins[3] );
        break;

      case '0':
        val[3]= max( val[3]-150, mins[3] );
        val[5]= max( val[5]-SERVOCHG, mins[5] );
        delay(1000);
        break;
        

//      case 'l': 
//        val[1]= min( val[1]+SERVOCHG, maxs[1] );
//        val[4]= min( val[4]-SERVOCHG, maxs[4] );
//        break;
//      case 'j': 
//        val[1]= max( val[1]-SERVOCHG, mins[1] );
//        val[4]= max( val[4]+SERVOCHG, mins[4] );
//        break;
//
//       
//      case 'u': 
//        val[2]= min( val[2]+SERVOCHG, maxs[2] );
//        val[5]= min( val[5]-SERVOCHG, maxs[5] );
//        break;
//      case 'o': 
//        val[2]= max( val[2]-SERVOCHG, mins[2] );
//        val[5]= max( val[5]+SERVOCHG, mins[5] );
//        break;

      // reset case for middle positions of all motors
      case 'm':
        for (i=0; i<6; i++) {
          val[i] = mids[i];
        }
        update();
        break;
        
      default: Serial.print(" No action taken");
    } // end switch statement
    
    Serial.print(" Servo values = [");
    for (i=0; i<6; i++) {
      Serial.print(val[i]);
      Serial.print(" ");
    }
    Serial.println("]");

    // Update servo commands:
//    for (i=0; i<6; i++) {
//      pwm.setPWM(i+1, 0, val[i]); // added +1 to match PWM port numbering (pins 1..6 used)
//    }
  }
}