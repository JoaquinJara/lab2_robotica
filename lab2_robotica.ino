#include <hcsr04.h>
#include <LEANTEC_ControlMotor.h>

#define TRIGGER_PIN 12
#define ECHO_PIN 13
HCSR04 hcsr04(TRIGGER_PIN, ECHO_PIN, 20, 4000);

#define PWM_DERECHO 3 //El pin EnA del L298N
#define MOTOR_DER_1 4 //El pin In1 del L298N
#define MOTOR_DER_2 2 //El pin In2 del L298N
#define PWM_IZQUIERDO 5 //El pin EnB del L298N
#define MOTOR_IZQ_1 6 //El pin In3 del L298N
#define MOTOR_IZQ_2 7 //El pin In4 del L298N
ControlMotor control(MOTOR_DER_1, MOTOR_DER_2, MOTOR_IZQ_1, MOTOR_IZQ_2, PWM_DERECHO, PWM_IZQUIERDO);

#define MAX_VELOCITY 150
#define DISTANCE_FACTOR 4

#define AVANZAR 0
#define RETROCEDER 1
#define DERECHA 2
#define IZQUIERDA 3
int angles[] = { 15, 15, -75, 105 };
int instructions[] = { AVANZAR, DERECHA, AVANZAR, IZQUIERDA };
int distances[] = { 1000, 100, 500, 100 };
int idx = 0, ins;

// defines variables
long duration;
int distance, angle, velocity = 150, nextVelocity;
int insLength = 4;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if(idx >= insLength) {
    velocity = angle = 0;
  } else {
    ins = instructions[idx];
    angle = angles[ins];

    // Distancia de obstáculoas
    distance = hcsr04.distanceInMillimeters();
    nextVelocity = distance / DISTANCE_FACTOR;
    velocity = distance <= 50 ? 0 : nextVelocity > MAX_VELOCITY ? MAX_VELOCITY: nextVelocity;
    if(ins == RETROCEDER) velocity *= -1;
  }

  distances[idx] -= velocity / 5;
  if(distances[idx] <= 0) idx++;
  
  control.Motor(velocity, angle);
  Serial.print(velocity);
  Serial.print(" ");
  Serial.print(angle);
  Serial.print(" ");
  Serial.print(idx);
  Serial.print("\n");
  delay(100);
}

