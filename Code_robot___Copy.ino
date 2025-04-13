  #include <Bluepad32.h>
  #include <ESP32Servo.h>


  // Déclaration des contrôleurs
  ControllerPtr myControllers[BP32_MAX_GAMEPADS];
  // Broches moteurs
const int motor1Pin1 = 22;  // Motor 1 forward, normalement 26 , fonctionne dans la 22
const int motor1Pin2 = 21;  // Motor 1 backward, normalement 35, fonctionne dans la 21
const int enablePin1 = 13;  // Motor 1 speed control, normalement 25

const int motor2Pin1 = 14;  // Motor 2 forward
const int motor2Pin2 = 27;  // Motor 2 backward
const int enablePin2 = 12;  // Motor 2 speed control

const int motor3Pin1 = 2;   // Motor 3 forward
const int motor3Pin2 = 4;   // Motor 3 backward
const int enablePin3 = 15;  // Motor 3 speed control

const int motor4Pin1 = 18;  // Motor 4 forward
const int motor4Pin2 = 19;  // Motor 4 backward
const int enablePin4 = 5;   // Motor 4 speed control



  // Initialisation des moteurs
  void setupMotor() {
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enablePin1, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enablePin2, OUTPUT);
  pinMode(motor3Pin1, OUTPUT);
  pinMode(motor3Pin2, OUTPUT);
  pinMode(enablePin3, OUTPUT);
  pinMode(motor4Pin1, OUTPUT);
  pinMode(motor4Pin2, OUTPUT);
  pinMode(enablePin4, OUTPUT);
  stopMotors();
  }
  // Contrôle du moteur HG 7881 permet de faire monter et descendre le
  





 

  void moveForward(int speed) {

  analogWrite(enablePin3, speed);
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, HIGH);
  analogWrite(enablePin1, speed);
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  }
  void moveBackward(int speed) {

  analogWrite(enablePin3, speed);
  digitalWrite(motor3Pin1, HIGH);
  digitalWrite(motor3Pin2, LOW);
  analogWrite(enablePin1, speed);
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);

  }
  // speedx est en variable pour faire varier la vitesse, il faut

  void turnLeft(int speedx) {
  analogWrite(enablePin1, speedx);
  analogWrite(enablePin3, speedx);
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor3Pin1, HIGH);
  digitalWrite(motor3Pin2, LOW);

  }
  void turnRight(int speedx) {
  analogWrite(enablePin1, speedx);
  analogWrite(enablePin3, speedx);
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, HIGH);

  }
  
  

  void stopMotors() {
  analogWrite(enablePin1, 0);
  analogWrite(enablePin2, 0);
  analogWrite(enablePin3, 0);
  analogWrite(enablePin4, 0);
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, LOW);
  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, LOW);
  }
  // Fonction de traitement des boutons de la manette permet de contrôler

  void processGamepad(ControllerPtr ctl) {
  int leftY = ctl->axisY();
  int speed = map(abs(leftY), 0, 512, 0, 255); // Map la valeur de

  int leftX = ctl->axisX();
  int speedx = map(abs(leftX), 0, 512, 0, 255); // Map la valeur de

  // Déplacement du robot
  if (leftY < -200 && abs(leftX) < 100) {
  moveForward(speed);

  } else if (leftY > 200 && abs(leftX) < 100) {
  moveBackward(speed);

  } else if (leftX > 200 && abs(leftY) < 100) {
  turnLeft(speedx);

  } else if (leftX < -200 && abs(leftY) < 100) {  
  turnRight(speedx);

  } else {
  stopMotors();
  }
  // Contrôle du moteur HG 7881

  if (ctl->a()) {
  analogWrite(enablePin2, 255);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  } else if (ctl->y()) {
  analogWrite(enablePin2, 255);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  } 
    else{
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);

  }
  /*else {
  stopMotor5();
  }*/
  
  // Contrôle du servomoteur avec les boutons X et B
  if (ctl->x()) {
  analogWrite(enablePin4, 255);
  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, HIGH);
  }
  else if (ctl->b()) {
  analogWrite(enablePin4, 255);
  digitalWrite(motor4Pin2, LOW);
  digitalWrite(motor4Pin1, HIGH);

  }
  else{
  digitalWrite(motor4Pin2, LOW);
  digitalWrite(motor4Pin1, LOW);

  }

  }
  // Gestion des contrôleurs connectés
  void processControllers() {
  for (auto myController : myControllers) {
  if (myController && myController->isConnected() &&
  myController->hasData()) {
  if (myController->isGamepad()) {
  processGamepad(myController);
  }
  }
  }
  }
  // Callback de connexion et déconnexion des contrôleurs

  void onConnectedController(ControllerPtr ctl) {
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
  if (myControllers[i] == nullptr) {
  myControllers[i] = ctl;
  break;
  }
  }
  }
  void onDisconnectedController(ControllerPtr ctl) {
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
  if (myControllers[i] == ctl) {
  myControllers[i] = nullptr;
  break;
  }
  }
  }
  // Initialisation et boucle principale
  void setup() {
  setupMotor();
  BP32.setup(&onConnectedController, &onDisconnectedController);
  BP32.enableVirtualDevice(false);
  }

  void loop() {
  bool dataUpdated = BP32.update();
  if (dataUpdated) {
  processControllers();
  }    
  delay(10); // Délai pour ajuster la vitesse de réponse avec la

  }

