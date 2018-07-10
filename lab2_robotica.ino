#include <LEANTEC_ControlMotor.h>//Incluimos la librería control de motores 

// defines pins numbers
const int trigPin = 12;
const int echoPin = 13;
ControlMotor control(9,8,11,10,5,6); 
int MotorDer1=9;//El pin 9 de arduino se conecta con el pin In1 del L298N
int MotorDer2=8;//El pin 8 de arduino se conecta con el pin In2 del L298N
int MotorIzq1=11;//El pin 11 de arduino se conecta con el pin In3 del L298N
int MotorIzq2=10;//El pin 10 de arduino se conecta con el pin In4 del L298N
int PWM_Derecho=5;//El pin 5 de arduino se conecta con el pin EnA del L298N
int PWM_Izquierdo=6;//El pin 6 de arduino se conecta con el pin EnB del L298N

// defines variables
long duration;
int distance;
int velocidad=150;//Declaramos una variable para guardar la velocidad. 150 es la velocidad en la que empezará.

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
  //Configuramos los pines como salida
  pinMode(MotorDer1, OUTPUT); 
  pinMode(MotorDer2, OUTPUT);
  pinMode(MotorIzq1, OUTPUT); 
  pinMode(MotorIzq2, OUTPUT); 
  pinMode(PWM_Derecho, OUTPUT);
  pinMode(PWM_Izquierdo, OUTPUT);
}

void virar_izquierda(){ 
/*En esta fución la rueda derecha girará en sentido antihorario y la
izquierda en sentido horario.
En este caso, si las ruedas estuvieran en el chasis de un robot, el
robot retrocederia.*/
  digitalWrite(MotorDer1,HIGH);
  digitalWrite(MotorDer2,LOW);
  digitalWrite(MotorIzq1,HIGH);
  digitalWrite(MotorIzq2,LOW);
  analogWrite(PWM_Derecho,200);//Velocidad motor derecho 200
  analogWrite(PWM_Izquierdo,200);//Velocidad motor izquierdo 200

}
void virar_derecha(){ 
/*En esta fución la rueda derecha girará en sentido horario y la
izquierda en sentido antihorario.
En este caso, si las ruedas estuvieran en el chasis de un robot, el
robot avanzaría.*/  
  digitalWrite(MotorDer1,LOW);
  digitalWrite(MotorDer2,HIGH);
  digitalWrite(MotorIzq1,LOW);
  digitalWrite(MotorIzq2,HIGH);
  analogWrite(PWM_Derecho,200);//Velocidad motor derecho 200
  analogWrite(PWM_Izquierdo,200);//Velocidad motor izquierdo 200

}
void avanzar(){ 
/*En esta fución ambas ruedas girarán en sentido horario.
En este caso, si las ruedas estuvieran en el chasis de un robot, el
robot giraria a la derecha.*/
  digitalWrite(MotorDer1,HIGH);
  digitalWrite(MotorDer2,LOW);
  digitalWrite(MotorIzq1,LOW);
  digitalWrite(MotorIzq2,HIGH);
  analogWrite(PWM_Derecho,200);//Velocidad motor derecho 200
  analogWrite(PWM_Izquierdo,200);//Velocidad motor izquierdo 200

}
void retroceder(){ 
/*En esta fución ambas ruedas girarán en sentido antihorario.
En este caso, si las ruedas estuvieran en el chasis de un robot, el
robot giraria a la izquierda.*/
  digitalWrite(MotorDer1,LOW);
  digitalWrite(MotorDer2,HIGH);
  digitalWrite(MotorIzq1,HIGH);
  digitalWrite(MotorIzq2,LOW);
  analogWrite(PWM_Derecho,200);//Velocidad motor derecho 200
  analogWrite(PWM_Izquierdo,200);//Velocidad motor izquierdo 200

}
void parar(){ 
/*Función para que las ruedas paren*/
  digitalWrite(MotorDer1,LOW);
  digitalWrite(MotorDer2,LOW);
  digitalWrite(MotorIzq1,LOW);
  digitalWrite(MotorIzq2,LOW);
  analogWrite(PWM_Derecho,200);//Velocidad motor derecho 200
  analogWrite(PWM_Izquierdo,200);//Velocidad motor izquierdo 200

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
  /* // Codigo de prueba funciones
  avanzar();//Llamamos a la función giro_horario
  delay(3000);//Durante 3 segundos ejecutamos esa función
  retroceder();//Llamamos a la función giro_antihorario
  delay(3000);//Durante 3 segundos ejecutamos esa función
  virar_derecha();//Llamamos a la función derecha_horario_izquierda_antihorario
  delay(3000);//Durante 3 segundos ejecutamos esa función
  virar_izquierda();//Llamamos a la función derecha_antihorario_izquierda_horario
  delay(3000);//Durante 3 segundos ejecutamos esa función
  parar();//Llamamos a la función parar
  delay(3000);//Durante 3 segundos ejecutamos esa función
  */
  
}

