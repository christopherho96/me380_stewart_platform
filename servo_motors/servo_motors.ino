
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

const int SERVOMIN = 175; // 'minimum' pulse length count (out of 4096)
const int SERVOMAX = 475; // 'maximum' pulse length count (out of 4096)
const int SERVOMID = floor((SERVOMAX+SERVOMIN)/2); // 'mid' pulse length count (out of 4096)
const int SERVOCHG = 20; // 'change' pulse length count

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

String valInput; // Serial input var.
int val[6] = {309, 325, 330, 287, 310, 332}; // PWM var
int mins[6] = {140, 132, 142, 90, 90, 138}; // lower bounds for each motor
int mids[6] = {309, 325, 330, 295, 295, 332}; // reset points
int maxs[6] = {478, 518, 518, 500, 500, 527}; // upper bounds for each motor

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  Serial.setTimeout(10); // change default (1000ms) to have faster response time
  Serial.println("Running example: Servo motor actuation using messaging");
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
}

void balance(){
   for (int i=0; i<6; i++) {
       val[i] = mids[i];
   }
   update();
}

void update(){
  for (int i=0; i<6; i++) {
     pwm.setPWM(i+1, 0, val[i]); // added +1 to match PWM port numbering (pins 1..6 used)
  };
  Serial.print(" Servo values = [");
    for (int i=0; i<6; i++) {
      Serial.print(val[i]);
      Serial.print(" ");
    }
    Serial.println("]");
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

      case '4':
        val[3]= min( val[3]+SERVOCHG, SERVOMAX );
        update();
        break;
      case 'r':
        val[3]= max( val[3]-SERVOCHG, SERVOMIN );
        update();
        break;

      case '@':
        balance();
        delay(3000);

        // move ball to corner
        val[5]= min( val[5]+100, maxs[5] );
        val[3]= max( val[3]+100, mins[3] );
        update();
        delay(3000);

        //begin slight tilts, repeat
        val[0]= max( val[0]-10, mins[0]);
        val[4]= max( val[4]-10, mins[4]);
        update();
        delay(2000);

        val[0]= max( val[0]-10, mins[0]);
        val[4]= max( val[4]-10, mins[4]);
        update();
        delay(2000);

        val[0]= max( val[0]-10, mins[0]);
        val[4]= max( val[4]-10, mins[4]);
        update();
        delay(2000);

        val[0]= max( val[0]-10, mins[0]);
        val[4]= max( val[4]-10, mins[4]);
        update();
        delay(2000);


        ///
        
        val[0]= max( val[0]-SERVOCHG, mins[0]);
        val[4]= max( val[4]-SERVOCHG, mins[4]);
        update();
        delay(1000);


        //should start rolling now
        
//        val[0]= max( val[0]-SERVOCHG, mins[0]);
//        val[4]= max( val[4]-SERVOCHG, mins[4]);
//        update();
//        delay(750);

//        val[0]= max( val[0]-SERVOCHG, mins[0]);
//        val[4]= max( val[4]-SERVOCHG, mins[4]);
//        update();
//        delay(2000);
//
//        val[0]= max( val[0]-SERVOCHG, mins[0]);
//        val[4]= max( val[4]-SERVOCHG, mins[4]);
//        update();
//        delay(750);

         //hit the sharp turn right here
        val[0]= max( val[0]-45, mins[0]);
        val[4]= max( val[4]-45, mins[4]);
        update();
        delay(3000);

//        val[5]= mids[5];
//        update();
//        delay(1200);
//
//        // straighten up
//        val[5] = mids[5];
//        val[0] = max( val[0]-SERVOCHG, mins[0]);
//        update();
//        delay(3000);
//
//        // tilt ball into finish position
//        val[0]= max( val[0]-SERVOCHG, mins[0]);
//        val[4]= max( val[4]-SERVOCHG, mins[4]);
//        update();
//        delay(2000);
//
//        val[0]= max( val[0]-SERVOCHG, mins[0]);
//        val[4]= max( val[4]-SERVOCHG, mins[4]);
//        update();
//        delay(2000);
   
        Serial.println("Finished Solving");
        break;   

       // reset case for middle positions of all motors
      case 'm':
        balance();
        break;

      case '1': 
        val[0]= min( val[0]+SERVOCHG, SERVOMAX );
        update();
        break;
      case 'q': 
        val[0]= max( val[0]-SERVOCHG, SERVOMIN );
        update();
        break;
        
      default: Serial.print(" No action taken");
    } // end switch statement
  }
}
