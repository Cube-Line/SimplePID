// Libraries
#include <PIDController.h>

// Objects
PIDController pid; // Create an instance of the PID controller class, called "pid"

// Pins
int outputPin = 3;  // The pin the digital output PMW is connected to
int sensorPin = A0; // The pin the analog sensor is connected to
uint8_t count = 0;

void setup()
{
	Serial.begin(9600); // Some methods require the Serial.begin() method to be called first

	pinMode(outputPin, OUTPUT);
	pinMode(sensorPin, INPUT);

	pid.begin();		   // initialize the PID instance
	pid.setpoint(429);	 // The "goal" the PID controller tries to "reach"
	pid.tune(0.2, 1, 900); // Tune the PID, arguments: kP, kI, kD
	pid.limit(0, 255);	 // Limit the PID output between 0 and 255, this is important to get rid of integral windup!
}

void loop()
{
	int sensorValue = analogRead(sensorPin); // Read the value from the sensor

	int output = pid.compute(sensorValue); // Let the PID compute the value, returns the optimal output
	// analogWrite(outputPin, output);          // Write the output to the output pin
	digitalWrite(outputPin, output);
	if (count >= 1)
	{
		double Temp = 0;
		double Voltage = 0;
		//温度=B值*绝对温度K值+25℃（常温）/（绝对温度K值+25℃（常温）*ln（Rt（当前温度下阻值））-ln（100K)(25℃下电阻值)）+B值-绝对温度273.15℃
		Temp = (4250 * 298.15) / (298.15 * (log(map(4.751 * sensorValue, 1764, 4418, 5829, 102300) / 1023) - 4.60517) + 4250) - 273.15;
		Voltage = 4.751 * sensorValue / 1023;
		// Serial.print("OUTPUT IS :");
		// Serial.println(output);
		// Serial.print("sensorValue :");
		Serial.print(sensorValue);
		// Serial.print("Voltage is :");
		// Serial.println(Voltage);
		// Serial.print("Temp is:");
		Serial.print(',');

		Serial.println(Temp);
		// Serial.println("**************************");
		count = 0;
	}
	count++;
	delay(30); // Delay for 30 ms
}
