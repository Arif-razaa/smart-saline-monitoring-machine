#define BLYNK_TEMPLATE_ID "TMPL3pQvaOy2L"
#define BLYNK_TEMPLATE_NAME "DHT"
#define BLYNK_AUTH_TOKEN "8yJeh5sLUzZiiSkYoz4bFKIfeqNuZ8K5"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// Wi-Fi credentials
char ssid[] = "shhh";
char pass[] = "12345678";

// DHT setup
#define DHTPIN D7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Buzzer
#define BUZZER_PIN D2

// Ultrasonic Sensor Pins
#define TRIG_PIN D6
#define ECHO_PIN D5

// LED pin
#define LED_PIN D3

BlynkTimer timer;
bool notified = false;  // To avoid repeated notifications

// Function to measure distance (in cm)
long readDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
}

void sendSensorData() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  long distance = readDistanceCM();

  // Send humidity to V1
  if (!isnan(humidity)) {
    Blynk.virtualWrite(V1, humidity);
  }

  // Send temperature to V0 and handle buzzer
  if (!isnan(temperature)) {
    Blynk.virtualWrite(V0, temperature);
    digitalWrite(BUZZER_PIN, temperature >= 45.0 ? HIGH : LOW);
  }

  // Send distance to V2
  Blynk.virtualWrite(V2, distance);

  // Turn on LED if distance > 12 cm
  digitalWrite(LED_PIN, distance > 12 ? HIGH : LOW);

  // Notify ONCE if distance is low
  if (distance <= 7 && !notified) {
    Blynk.logEvent("low_distance", "⚠ Saline level is low!");
    notified = true;
  }

  // Reset the notification flag if distance goes back above 7
  if (distance > 7) {
    notified = false;
  }

  // Debugging to Serial Monitor
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  dht.begin();

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  timer.setInterval(2000L, sendSensorData);  // Call every 2 seconds
}

void loop() {
  Blynk.run();
  timer.run();
}
