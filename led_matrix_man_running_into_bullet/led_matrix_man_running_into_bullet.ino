#include <Arduino_LED_Matrix.h>

ArduinoLEDMatrix matrix;

int index = 0;
unsigned long previousMillis = 0; // Variable to store the last time an action was taken
const unsigned long interval = 100; // Interval at which to run the action (e.g., 1000 milliseconds = 1 second)

const uint32_t animation[][4] = {
	{
		0xc0,
		0x400c008,
		0x800800,
		66
	},
	{
		0xe0,
		0xa00e004,
		0x400400,
		66
	},
	{
		0x70,
		0x5007002,
		0x200200,
		66
	},
	{
		0x38,
		0x2803801,
		0x100100,
		66
	},
	{
		0x1c,
		0x1401c00,
		0x80080080,
		66
	},
	{
		0xe,
		0xa00e00,
		0x40040040,
		66
	},
	{
		0x7,
		0x500700,
		0x20020020,
		66
	},
	{
		0x3,
		0x80280380,
		0x10010010,
		66
	},
	{
		0x1,
		0xc01401c0,
		0x8008008,
		66
	},
	{
		0x1,
		0xc01501c0,
		0x8008008,
		66
	},
	{
		0x1,
		0xc01601c0,
		0x8008008,
		66
	},
	{
		0x1,
		0xc01c01c0,
		0x8008008,
		66
	},
	{
		0x1,
		0xc03401c0,
		0x8008008,
		66
	},
	{
		0x3,
		0x80c80380,
		0x10008004,
		66
	},
	{
		0x0,
		0x3700500,
		0x38004002,
		66
	},
	{
		0x0,
		0x6000700,
		0x50058006,
		66
	},
	{
		0x0,
		0xc000000,
		0x7005005e,
		66
	},
	{
		0x0,
		0x8000000,
		0x7005005e,
		66
	}
};

const int arrayLen = sizeof(animation) / sizeof(animation[0]) - 2;

void setup() {
  matrix.begin();
}

void loop() {
  unsigned long currentMillis = millis(); // Get the current time

  // Check if the interval has passed since the last time the action was run
  if (currentMillis - previousMillis >= interval) {
    // Save the current time as the last time the action was run
    // NOTE: this is a crucial step to reset the timer
    previousMillis = currentMillis; 

    matrix.loadFrame(animation[index]);
    if (index > arrayLen) {
      index = 0;
    } else {
      index = index + 1;
    }
  }
}