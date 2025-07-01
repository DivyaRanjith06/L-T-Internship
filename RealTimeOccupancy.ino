#define IR_ENTRY 2
#define IR_EXIT 3
#define RELAY 8
#define LDR A0

int peopleCount = 0;
int lightThreshold = 500;

void setup() {
  pinMode(IR_ENTRY, INPUT_PULLUP);  // Use internal pull-up
  pinMode(IR_EXIT, INPUT_PULLUP);   // Use internal pull-up
  pinMode(RELAY, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Pushbutton is pressed when pin goes LOW
  if (digitalRead(IR_ENTRY) == LOW) {
    peopleCount++;
    Serial.println("Entry detected");
    delay(500); // Debounce delay
  }

  if (digitalRead(IR_EXIT) == LOW) {
    if (peopleCount > 0) peopleCount--;
    Serial.println("Exit detected");
    delay(500); // Debounce delay
  }

  int light = analogRead(LDR);

  if (peopleCount > 0 && light < lightThreshold) {
    digitalWrite(RELAY, HIGH); // Light ON
  } else {
    digitalWrite(RELAY, LOW);  // Light OFF
  }

  Serial.print("People: ");
  Serial.print(peopleCount);
  Serial.print(" | Light: ");
  Serial.println(light);

  delay(200);
}
