#include <ArduinoGraphics.h>
#include <Arduino_LED_Matrix.h>
#include <DHT.h>

#define DHTPIN 7
#define DHTTYPE DHT11

ArduinoLEDMatrix matrix;
DHT dht(DHTPIN, DHTTYPE);

unsigned long previousDisplayMillis = 0;
const unsigned long displayInterval = 4000; // toggle display every 1 second

unsigned long previousSensorMillis = 0;
const unsigned long sensorInterval = 2000; // read sensor every 2 seconds

float temperature = 0;
float humidity = 0;

void setup() {
  dht.begin();
  matrix.begin();
}

void loop() {
  unsigned long currentMillis = millis();

  // --- Read sensor every 2 seconds ---
  if (currentMillis - previousSensorMillis >= sensorInterval) {
    previousSensorMillis = currentMillis;

    float t = dht.readTemperature();
    float h = dht.readHumidity();

    if (isnan(t) || isnan(h)) {
      temperature = -1;
      humidity = -1;
    } else {
      temperature = (t * 9.0 / 5.0) + 32.0; // in Fahrenheit
      humidity = h;
    }
  }

	if (currentMillis - previousDisplayMillis >= displayInterval) {
    previousDisplayMillis = currentMillis;

		char text[10] = " ";
		char tempText[20];

		dtostrf(temperature, 4, 1, tempText);

		strcat(text, tempText);
		strcat(text, "F ");
	

		char humidText[20];
		// 2 chars, no decimal
		dtostrf(humidity, 2, 0, humidText);

		strcat(text, humidText);
		strcat(text, "%");
		displayValue(text);
	}
}

// Display two digits + symbol on 8x12 matrix
void displayValue(char text[]) {
  matrix.beginDraw();
	matrix.stroke(0xFFFFFFFF);
	matrix.textScrollSpeed(100);
	matrix.textFont(Font_4x6);
	matrix.beginText(0, 1, 0xFFFFFFF);
	matrix.println(text);
	matrix.endText(SCROLL_LEFT);
	matrix.endDraw();
}
