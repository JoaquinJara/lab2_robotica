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

// Ajustes
#define VELOCITY 88 // Velocidad de movimiento
#define FIX_ANGLE 30 // Ángulo de ajuste para direccionar el vehículo
#define CELL 200 // Tamaño de una celda

// Marcas
#define N 0 // No explorado
#define A 1 // Camino válido
#define O 2 // Obstáculo
#define R 3 // Usado para retorno

// Direcciones
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

// defines variables
long duration;
int distance, angle, velocity = 100, i = 0,x = 0, y = 0, dir = WEST,inicioX=x,inicioY=y;
bool exploring = true;
bool reversing = false;

// Cambiar según tamaño de la matriz
int width = 10, height = 5;


int matrix[5][10] = {
  { A, N, N, O, O, O, O, O, O, O },
  { O, O, N, N, O, O, O, O, O, O },
  { O, O, O, O, O, O, O, O, O, O },
  { O, O, O, O, O, O, O, O, O, O },
  { O, O, O, O, O, O, O, O, O, O }
};



void setup() {
  Serial.begin(9600);
}

void loop() {
  distance = hcsr04.distanceInMillimeters();
  if(!exploring) {
    if(!reversing) reversing=true;
    else{
      exit(0);
    }
    // Si termino la exploración, empieza a regresar
    delay(2000);
    
    reverseMap();
    matrix[y][x]=A;
    exploring=!mapExplored();
  } else if(distance <= CELL || isThereObstacle()) {
    // Si se detecta presencia de un objeto, se marca un obstáculo
    setObstacle();
    // Y se cambia la dirección
    turn();
  } else {
    avanzar();
    // Marca la casilla como camino válido
    matrix[y][x] = A;
    // Consulta si se ha explorado el área completa
    exploring = !mapExplored();
  }
}



/**
 * Indica si existe un obstáculo (conocido) en frente del vehículo.
 * @return Verdadero si existe un obstáculo marcado en frente del vehículo.
 */
bool isThereObstacle() {
  if(dir == NORTH) {
    return y - 1 < 0 || matrix[y - 1][x] == O;
  } else if(dir == SOUTH) {
    return y + 1 >= height || matrix[y + 1][x] == O;
  } else if(dir == EAST) {
    return x + 1 >= width || matrix[y][x + 1] == O;
  } else {
    return x - 1 < 0 || matrix[y][x - 1] == O;
  }
}

/**
 * Marca un obstáculo en el mapa.
 */
void setObstacle() {
  // Marcar obstáculo
  if(dir == NORTH) {
    matrix[y - 1][x] = O;
  } else if(dir == SOUTH) {
    matrix[y + 1][x] = O;
  } else if(dir == EAST) {
    matrix[y][x + 1] = O;
  } else {
    matrix[y][x - 1] = O;
  }
}

/**
 * Gira el vehículo. Esta función se llama cuando el vehículo
 * se encuentra con un obstáculo, ya sea conocido o detectado.
 */
void turn() {
  if(dir == NORTH) {
    turnFromNorth();
  } else if(dir == SOUTH) {
    turnFromSouth();
  } else if(dir == EAST) {
    turnFromEast();
  } else {
    turnFromWest();
  }
}

/**
 * Dedice hacia dónde girar, cuando el auto previamente iba
 * en dirección norte.
 */
void turnFromNorth() {
  if(x - 1 < 0 || matrix[y][x - 1] == O)
    right();
  else if(x + 1 >= width || matrix[y][x + 1] == O)
    left();
  else
    right();
}

/**
 * Dedice hacia dónde girar, cuando el auto previamente iba
 * en dirección sur.
 */
void turnFromSouth() {
  if(x - 1 < 0 || matrix[y][x - 1] == O)
    left();
  else if(x + 1 >= width || matrix[y][x + 1] == O)
    right();
  else
    left();
}

/**
 * Dedice hacia dónde girar, cuando el auto previamente iba
 * en dirección este.
 */
void turnFromEast() {
  if(y - 1 < 0 || matrix[y - 1][x] == O)
    right();
  else if(y + 1 >= height || matrix[y + 1][x] == O)
    left();
  else
    right();
}

/**
 * Dedice hacia dónde girar, cuando el auto previamente iba
 * en dirección oeste.
 */
void turnFromWest() {
  if(y - 1 < 0 || matrix[y - 1][x] == O)
    left();
  else if(y + 1 >= height || matrix[y + 1][x] == O)
    right();
  else
    left();
}

/**
 * Gira a la derecha
 */
void right() {
  // Cambiar dirección
  dir++;
  if(dir == 4) dir = NORTH;

  // Girar
  control.Motor(VELOCITY, -100);
  delay(400); // Incrementar o disminuir para ajustar giro
}

/**
 * Gira a la izquierda.
 */
void left() {
  // Cambiar dirección
  dir--;
  if(dir < 0) dir = WEST;

  // Girar
  control.Motor(VELOCITY, 100);
  delay(380); // Incrementar o disminuir para ajustar giro
}

void avanzar() {
  // Incrementa la posición
  if(dir == NORTH) {
    y--;
  } else if(dir == SOUTH) {
    y++;
  } else if(dir == EAST) {
    x++;
  } else {
    x--;
  }

  // Avanza
  control.Motor(VELOCITY, FIX_ANGLE);
  delay(300);

  // Si se está explorando el área, realiza una pequeña pausa
  if(exploring) {    
    control.Motor(0, 0);
    delay(1000);
  }
}

/**
 * Indica si se ha explorado toda el área (celdas)
 * @return Verdadero si se cubrió toda el área de exploración.
 */
bool mapExplored() {
  for(int i = 0; i < height; i++)
    for(int j = 0; j < width; j++)
      if(matrix[i][j] == N) return false;
  return true;
}

void reverseMap(){
  for(int i = 0; i < height; i++)
    for(int j = 0; j < width; j++)
      if(matrix[i][j] == A) matrix[i][j]=N;
}






