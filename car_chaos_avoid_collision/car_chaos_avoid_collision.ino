
const int motor1PinA = 2;
const int motor1PinB = 3;

const int motor2PinA = 4;
const int motor2PinB = 5;

const int rightButton = 6;
const int leftButton = 7;

const int goButton = 8;

int speed = 255;


//distance stuff
// defines pins numbers
const int trigPin = 6;
const int echoPin = 7;
// defines variables
long duration;
int distance;
long collisionTimer = 0;
bool colliding = false;
int initiateRunningAway = 0;
int runningAwayTimer = 0;



void setup() {
  // set the pushbutton as an input:
  // pinMode(switchPin, INPUT);

  // set all the other pins you're using as outputs:
  pinMode(motor1PinA, OUTPUT);
  pinMode(motor1PinB, OUTPUT);
  pinMode(motor2PinA, OUTPUT);
  pinMode(motor2PinB, OUTPUT);
  pinMode(rightButton, INPUT);
  pinMode(leftButton, INPUT);
  pinMode(goButton, INPUT);

  //distance stuff
  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);   // Sets the echoPin as an Input
  Serial.begin(9600);
}

void loop() {

  int rightButtonState = digitalRead(rightButton);
  int leftButtonState = digitalRead(leftButton);
  int goButtonState = digitalRead(goButton);


  if (goButtonState) {
    initiateRunningAway = 1;
    runningAwayTimer = millis();
  }

  if (initiateRunningAway == 1) {
    startRunningAway();
  }

  if (colliding == false) {
    moveForward();
  } else {
    stopWheels();
  }


  // if (goButtonState == HIGH) {
  //   moveForward();
  // } else if (rightButtonState == HIGH && leftButtonState == LOW) {
  //   turnRight();
  // } else if (rightButtonState == LOW && leftButtonState == HIGH) {
  //   turnLeft();
  // } else if (rightButtonState == HIGH && leftButtonState == HIGH) {
  //   moveBackwards();
  // } else {
  //   stopWheels();
  // }
}




void turnLeft() {
  digitalWrite(motor1PinA, LOW);
  digitalWrite(motor1PinB, speed);
  digitalWrite(motor2PinA, LOW);
  digitalWrite(motor2PinB, speed);
}


void turnRight() {
  digitalWrite(motor1PinA, speed);
  digitalWrite(motor1PinB, LOW);
  digitalWrite(motor2PinA, speed);
  digitalWrite(motor2PinB, LOW);
}

void moveForward() {
  digitalWrite(motor1PinA, LOW);
  digitalWrite(motor1PinB, speed);
  digitalWrite(motor2PinA, speed);
  digitalWrite(motor2PinB, LOW);
}

void moveBackwards() {
  digitalWrite(motor1PinA, speed);
  digitalWrite(motor1PinB, LOW);
  digitalWrite(motor2PinA, LOW);
  digitalWrite(motor2PinB, speed);
}

void stopWheels() {
  digitalWrite(motor1PinA, LOW);
  digitalWrite(motor1PinB, LOW);
  digitalWrite(motor2PinA, LOW);
  digitalWrite(motor2PinB, LOW);
}

void startRunningAway() {

  if (millis() - runningAwayTimer < 500) turnRight();
  else if (millis() - runningAwayTimer < 7000) {
    preventCollision();
    if (colliding == false) {
      moveForward();
    }
  } else {
    stopWheels();
    initiateRunningAway = 0;
  }
}

void preventCollision() {
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
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  // Serial.println(distance);



  if (distance < 15) {

    colliding = true;
    // we might not need that
    // if (millis() - collisionTimer > 2000) {
    //   stopWheels();
    //   collisionTimer = millis();
    // }

    if (millis() - collisionTimer > 10) {
      turnRight();
      collisionTimer = millis();
    }

    Serial.println("stop!!!");
  } else {
    Serial.println("I'm good to go");
    colliding = false;
  }
}
