const int buttonPin = 3;
const int trigPin = 4;
const int echoPin = 5;
const int greenLED = 9;
const int redLED = 8;

volatile bool buttonPressed = false;
bool greenState = false;
bool redState = false;

void handleButtonInterrupt() {
  buttonPressed = true;
}

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(buttonPin), handleButtonInterrupt, FALLING);
}

void loop() {
  // Handle button press outside interrupt
  if (buttonPressed) {
    buttonPressed = false;
    greenState = !greenState;
    digitalWrite(greenLED, greenState);
    Serial.println("Button pressed: Green LED toggled");
  }

  // Ultrasonic distance check
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  if (distance > 0 && distance < 20) {
    redState = !redState;
    digitalWrite(redLED, redState);
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm → Red LED toggled");
    delay(500); // Prevent rapid toggling
  }
}