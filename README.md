# ProyRoboticaBasica
Proyecto de robotica basica Universidad Rafael Landivar Programa Educación Continua

#include <AFMotor.h> //import your motor shield library
#define trigPin 7 // define the pins of your sensor
#define echoPin 6

AF_DCMotor motor1(1,MOTOR12_64KHZ); // set up motors.
AF_DCMotor motor2(2, MOTOR12_8KHZ);

void setup() 

{
	Serial.begin(9600); // begin serial communitication 
	Serial.println("Motor test!");
	
	pinMode(trigPin, OUTPUT);// set the trig pin to output (Send sound waves)
	pinMode(echoPin, INPUT);// set the echo pin to input (recieve sound waves)
	
	motor1.setSpeed(155); //set the speed of the motors, between 0-255
	motor2.setSpeed (155); 
}

void loop() 

{
 
   long duration, distance; // start the scan
	digitalWrite(trigPin, LOW); 
	delayMicroseconds(2); // delays are required for a succesful sensor operation.
	digitalWrite(trigPin, HIGH);
 
	delayMicroseconds(10); //this delay is required as well!
	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin, HIGH);
	distance = (duration/2) / 29.1;// convert the distance to centimeters.
  
	if (distance < 25)/*Si existe obstaculo 25 centimetros cerca hacer: */ 
		{  
			Serial.println ("Close Obstacle detected!" );
			Serial.println ("Obstacle Details:");
			Serial.print ("Distance From Robot is " );
			Serial.print ( distance);
			Serial.print ( " CM!");// print out the distance in centimeters.
 
			Serial.println (" The obstacle is declared a threat due to close distance. ");
			Serial.println (" Turning !");
			motor1.run(RELEASE);
			motor2.run(RELEASE);
			delay(500);
			motor1.setSpeed(250);
			motor2.setSpeed(150);
			motor1.run(BACKWARD);
			motor2.run (FORWARD);
			delay(1000);
			motor1.run(RELEASE);
			motor2.run(RELEASE);
			delay(1000);
			digitalWrite(trigPin, LOW); 
			delayMicroseconds(2);
			digitalWrite(trigPin, HIGH);
 
			delayMicroseconds(10);
			digitalWrite(trigPin, LOW);
			duration = pulseIn(echoPin, HIGH);
			distance = (duration/2) / 29.1;

			if(distance <25)
			{
				motor1.run(RELEASE);
				motor2.run(RELEASE);
				delay(500);
				motor1.setSpeed(250);
				motor2.setSpeed(150);
				motor1.run(BACKWARD);
				motor2.run (FORWARD);
				delay(1000);
				motor1.run(RELEASE);
				motor2.run(RELEASE);
				delay(500);
			}
		}
  else {
		Serial.println ("No obstacle detected. going forward");
		delay (15);
		motor1.run(BACKWARD); //if there's no obstacle ahead, Go Forward!
		motor2.run(BACKWARD); 
		} 
  
}
