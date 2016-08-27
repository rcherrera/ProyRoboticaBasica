//Roberto Herrera
#include <Servo.h>
#include <AFMotor.h> //libreria para motores
#define trigPin 8 // definir pin 8 para Trigger
#define echoPin 13 //definir pin 13 para Echo
AF_DCMotor motor1(3,MOTOR12_64KHZ); // setear motores.
AF_DCMotor motor2(4, MOTOR12_8KHZ);
Servo myservo;  // create servo object to control a servo

//int pos=0;

void setup() {
  Serial.begin(9600); // comienza comunicacion serial
  Serial.println("Probando motores!");
   pinMode(trigPin, OUTPUT);// configurar el Trigger al pin (Enviar sound waves)
  pinMode(echoPin, INPUT);// Configurar el pin Echo (para recibir ondas de sonido)
  motor1.setSpeed(155); //configurar velocidad de los motores 0-255
  motor2.setSpeed (155);
 //myservo.attach(9);  // Eso es para configurar el servo (si tienen servo para que gire el HCSR04
}
void loop() {
 
   long duration, distance; // comenzar el scaneo
   digitalWrite(trigPin, LOW); 
   delayMicroseconds(2); // Delay necesario tras la configuracion del sensor.
   digitalWrite(trigPin, HIGH);
 
   delayMicroseconds(10); //DELAY EN MICROSEGUNDOS
   digitalWrite(trigPin, LOW);
   duration = pulseIn(echoPin, HIGH);
   distance = (duration/2) / 29.1;// CONVIERTE DISTANCIA A CENTIMETROS.
   if (distance < 25)// si la distancia es menor a 20 cms probar evadir PRIMER INTENTO
   {  
    Serial.print ("Distance From Robot is " );
    Serial.print ( distance);
    Serial.print ( " CM!");// print out the distance in centimeters.
 
    Serial.println (" Turning !");
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    delay(500);
    motor2.setSpeed(250);
    motor1.setSpeed(150);
    motor2.run(BACKWARD);
    motor1.run (FORWARD);
    delay(500);
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

  //segundo intento de evasion
    if(distance <25){
        motor1.run(RELEASE);
        motor2.run(RELEASE);
        delay(500);
        motor2.setSpeed(250);
        motor1.setSpeed(150);
        motor2.run(BACKWARD);
        motor1.run (FORWARD);
        delay(500);
        motor1.run(RELEASE);
        motor2.run(RELEASE);
        delay(500);
      }
// si son mas de dos intentos... probar invertir el giro
    if(distance <25){
        motor1.run(RELEASE);
        motor2.run(RELEASE);
        delay(500);
        motor2.setSpeed(150);
        motor1.setSpeed(250);
        motor2.run(FORWARD);
        motor1.run (BACKWARD);
        delay(500);
        motor1.run(RELEASE);
        motor2.run(RELEASE);
        delay(500);
    }
}
  else {
   Serial.println ("No hay obstaculos: ir al frente");
   delay (15);
   motor1.run(BACKWARD); //Si no hay obstaculos ir al frente
   motor2.run(BACKWARD);
  } 
}
