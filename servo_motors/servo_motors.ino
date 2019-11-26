#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

String valInput; // Serial input var.
float val[6] = {309, 325, 330, 287, 310, 332}; // PWM var
float mins[6] = {140, 132, 142, 90, 90, 138}; // lower bounds for each motor
float mids[6] = {309, 325, 330, 295, 295, 332}; // reset points
float maxs[6] = {478, 518, 518, 500, 500, 527}; // upper bounds for each motor


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
void turn(){
  for (int i=0; i<10; i++) {
    val[0]= max( val[0]- MINICHG*1.3, mins[0] );
    val[4]= max( val[4]- MINICHG*1.3, mins[4] );
  } 
  update();
}

void start(){
  val[0]= min( val[0]+ 25, maxs[0] );
  val[1]= max( val[1]- 25, mins[1] );
  val[4]= min( val[4]+ 25, maxs[4] );
  val[5]= max( val[5]- 25, mins[5] );
}

void loop() {
  if (Serial.available() > 0) {
    valInput = Serial.readString();
    Serial.print("I received: ");
    Serial.print(valInput);
    
    int inc = 0;
    int inc2 = 0;
    
    switch (valInput[0]) {
      case 'n':
       //TURN
        val[0]= max( val[0]- 50, mins[0] );
        val[4]= max( val[4]- 80, mins[4] );
        update();
        delay(500);

        //kick into turn
        val[1]= min( val[1]+ 50, maxs[1] );
        ///////////// testing
        val[0]= mids[0];
        val[5]= mids[5];
        /////////////
        //
        val[3]= mids[3];
        update();
        //1500
        delay(500);
        break;

      case 'o':         
        //ride the wall
        val[4]= min( val[4]+32, maxs[4] );
        val[5]= max( val[5]-32, mins[5] );
        update();

        //delay(1200) gives 6/10 success on turn
        delay(1000);
        break;

      case 'y':
        while (inc<12) {
            val[1]= max( val[1]-10, mins[1] );
            val[2]= min( val[2]+10, maxs[2] );
            val[5]= mids[5];
            update();
            inc++;
          }
          delay(1500);
          //tilt it into finish
          while (inc<20) {
            val[0]= min( val[0]+ 10, maxs[0] );
            val[4]= max( val[4]- 10, mins[4] );
            update();
            inc++;
          }
          delay(1500);
          val[0]= min( val[0]+ 50, maxs[0] );
          val[1] = mids[1];
          val[4]= max( val[4]- 25, mins[4] );
          update();
          break;

      case 't':
        while (inc<30) {
          val[3]= max( val[3]-(MINICHG*1.2)*1.6, mins[3] );
          val[5]= min( val[5]+ MINICHG*1.3, maxs[5] );
          delay(15);
          update();
          inc++;
        }
        inc=0;
        delay(4000);
   
        while (inc<70) {
          val[3]= min( val[3]+(MINICHG*1.2), mids[3] +40);
          val[5]= max( val[5]- MINICHG*0.8, mids[5] );
          delay(20);
          update();
          inc++;
        }
        inc=0;
        //val[3]= min( val[3]+40, maxs[3] );
        val[3]= min( val[3]+60, maxs[3] );
        update();
        delay(3000);
        break;
      
      case '@':

        // going downnnnn
        while (inc<30) {
          val[3]= max( val[3]-(MINICHG*1.2)*1.6, mins[3] );
          val[5]= min( val[5]+ MINICHG*1.3, maxs[5] );
          delay(15);
          update();
          inc++;
        }
        inc=0;
        delay(4000);

        while (inc<70) {
          val[3]= min( val[3]+(MINICHG*1.2), mids[3] +40);
          val[5]= max( val[5]- MINICHG*0.8, mids[5] );
          delay(20);
          update();
          inc++;
        }
        inc=0;
        //val[3]= min( val[3]+40, maxs[3] );
        val[3]= min( val[3]+60, maxs[3] );
        update();
        delay(3000);

        
        //ride the wall
        val[4]= min( val[4]+32, maxs[4] );
        val[5]= max( val[5]-32, mins[5] );
        update();

        //delay(1200) gives 6/10 success on turn
        delay(1000);

        //TURN
        val[0]= max( val[0]- 50, mins[0] );
        val[4]= max( val[4]- 80, mins[4] );
        update();
        delay(500);

        //kick into turn
        val[1]= min( val[1]+ 50, maxs[1] );
        ///////////// testing
        val[0]= mids[0];
        val[5]= mids[5];
        /////////////
        //
        val[3]= mids[3];
        update();
        //1500
        delay(500);

        //get into corner
        while (inc<12) {
          val[1]= max( val[1]-10, mins[1] );
          val[2]= min( val[2]+10, maxs[2] );
          val[5]= mids[5];
//          val[0]= min( val[0]+ 5, maxs[0] );
//          val[4]= max( val[4]- 5, mins[4] );
          update();
          inc++;
        }

//        inc =0;
//        val[1]= max( val[1]-140, mins[1] );
//        val[2]= min( val[2]+100, maxs[2] );
//        //val[2]= max( val[2]-80, mins[2] );
//        val[5]= mids[5];
//        val[3]=mids[3];
//        update();
        delay(1500);

        //middle it
//        val[1]= mids[1];
//        val[2]= mids[2];
//        update();
//        delay(1500);

        //tilt it into finish
        while (inc<20) {
          val[0]= min( val[0]+ 10, maxs[0] );
          val[4]= max( val[4]- 10, mins[4] );
          update();
          inc++;
        }
        delay(1500);
        val[0]= min( val[0]+ 50, maxs[0] );
        val[1] = mids[1];
        val[4]= max( val[4]- 25, mins[4] );
        update();
        break;
     
      // reset case for middle positions of all motors
      case 'm':
        balance();
        break;

      //to stop clicking of stupid motor
      case '1': 
        val[0]= min( val[0]+SERVOCHG, SERVOMAX );
        update();
        break;
        
      default: Serial.print(" No action taken");
    } // end switch statement
  }
}
