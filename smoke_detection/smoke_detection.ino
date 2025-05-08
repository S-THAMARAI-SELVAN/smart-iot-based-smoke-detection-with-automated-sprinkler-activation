#include <Servo.h>

#define MQ135_PIN A0       // Analog input pin for MQ-135
#define BUZZER_PIN 14      // D5 = GPIO14
#define SERVO_PIN 12       // D6 = GPIO12

Servo myServo;

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  myServo.attach(SERVO_PIN);
  myServo.write(0);  // Start at 0 degrees
}

void loop() {
  int sensorValue = analogRead(MQ135_PIN);
  Serial.print("Gas Value: ");
  Serial.println(sensorValue);

  if (sensorValue > 80 && sensorValue <100) {  // Threshold for smoke
    Serial.println("🚨 Smoke Detected!");

    digitalWrite(BUZZER_PIN, HIGH);  // Turn on buzzer
    myServo.write(90);               // Rotate servo to 90 degrees
    delay(1000);                     // Wait for 1 second
    myServo.write(0);                // Return to 0 degrees
    delay(1000);                     // Optional delay to complete reset
  } else {
    digitalWrite(BUZZER_PIN, LOW);   // Turn off buzzer
    myServo.write(0);                // Ensure servo is at 0
  }

  delay(500);  // Small delay before next reading
}

