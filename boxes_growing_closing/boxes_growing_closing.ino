#include <Arduino_LED_Matrix.h>

ArduinoLEDMatrix matrix;

int index = 0;
unsigned long previousMillis = 0; // Variable to store the last time an action was taken
const unsigned long interval = 200; // Interval at which to run the action (e.g., 1000 milliseconds = 1 second)
unsigned long previousLEDMillis = 0; // Variable to store the last time an action was taken
const unsigned long ledInterval = 100; // Interval at which to run the action (e.g., 1000 milliseconds = 1 second)
bool isOn = false;

const uint32_t animation[][4] = {
	{
		0xfff80180,
		0x18018018,
		0x1801fff,
		66
	},
	{
		0x7fe40,
		0x24024024,
		0x27fe000,
		66
	},
	{
		0x3f,
		0xc2042043,
		0xfc000000,
		66
	},
	{
		0x0,
		0x1f81f80,
		0x0,
		66
	},
	{
		0x0,
		0xf00f00,
		0x0,
		66
	},
	{
		0x0,
		0x600600,
		0x0,
		66
	},
	{
		0x0,
		0x600600,
		0x0,
		66
	},
	{
		0x6,
		0x600600,
		0x60000000,
		66
	},
	{
		0xf009,
		0x900900,
		0x900f0000,
		66
	},
	{
		0x1f810810,
		0x81081081,
		0x81081f8,
		66
	},
	{
		0x20420420,
		0x42642642,
		0x4204204,
		66
	},
	{
		0x40240246,
		0x24624624,
		0x62402402,
		66
	},
	{
		0x8018f189,
		0x18918918,
		0x918f1801,
		66
	},
	{
		0x1f810810,
		0x81081081,
		0x81081f8,
		66
	},
	{
		0x20420420,
		0x42642642,
		0x4204204,
		66
	},
	{
		0x40240240,
		0x24f24f24,
		0x2402402,
		66
	},
	{
		0x80180180,
		0x19f99f98,
		0x1801801,
		66
	},
	{
		0x3f,
		0xc2042043,
		0xfc000000,
		66
	},
	{
		0x7fe40,
		0x24024024,
		0x27fe000,
		66
	},
	{
		0xfff80180,
		0x18018018,
		0x1801fff,
		66
	}
};

const int arrayLen = sizeof(animation) / sizeof(animation[0]) - 2;

void setup() {
  matrix.begin();
	pinMode(12, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis(); // Get the current time

  // Check if the interval has passed since the last time the action was run
  if (currentMillis - previousMillis >= interval) {
    matrix.loadFrame(animation[index]);
    if (index > arrayLen) {
      index = 0;
    } else {
      index = index + 1;
    }
		// Save the current time as the last time the action was run
		// NOTE: this is a crucial step to reset the timer
		previousMillis = currentMillis;		
  }

	if (currentMillis - previousLEDMillis >= ledInterval) {
		if (isOn) {
			digitalWrite(12, LOW);
			isOn = false;
		} else {
			digitalWrite(12, HIGH);
			isOn = true;
		}
		// Save the current time as the last time the action was run
		// NOTE: this is a crucial step to reset the timer
		previousLEDMillis = currentMillis;	
  }
	
}