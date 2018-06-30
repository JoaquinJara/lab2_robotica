#include <LEANTEC_ControlMotor.h>

/*
* Ultrasonic Sensor HC-SR04 and Arduino Tutorial
*
* by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
*/
/*
// defines pins numbers
const int trigPin = 12;
const int echoPin = 13;

// defines variables
long duration;
int distance;

void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
}

void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;

// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
delay(500);
}
*/
#include <LEANTEC_ControlMotor.h>//Incluimos la librería control de motores 
// Configuramos los pines que vamos a usar
ControlMotor control(9,8,11,10,5,6); // MotorDer1,MotorDer2,MotorIzq1,MotorIzq2,PWM_Derecho,PWM_Izquierdo

int velocidad=150;//Declaramos una variable para guardar la velocidad. 150 es la velocidad en la que empezará.

void setup() 
{ //En esta ocasión no necesitamos configurar pines ya que la librería lo hace.
} 
 
void loop() 
{//Un motor gira en sentido horario y el otro antihorario
//Si estuvierán montados en un robot el robot avanzaria. 
 while(velocidad<254){
 velocidad++;
 control.Motor(velocidad,1); 
 delay (200);}
//Un motor gira en sentido horario y el otro antihorario
//Si estuvierán montados en un robot el robot retrocedería. 
  control.Motor(-180,1);
  delay(3000);
//Los dos motores giran en sentido horario.
//Si estuvieran montados en un robot este giraria a la derecha. 
  control.Motor(200,100);
  delay(3000);
//Los dos motores giran en sentido antihorario.
//Si estuvieran montados en un robot este giraria a la derecha.  
  control.Motor(200,-100);
  delay(3000);
//Los motores se paran.
  control.Motor(0,1);
  delay(3000);
  
  velocidad=150;//Reseteamos la velocidad
  }
