#include "CMotors.h"

CMotors motors(12, 13, 10, 11, 5, 6);
int m_iSpeed;

void setup()
{
	m_iSpeed = 51;
	motors.SetSpeedMode(Slow);

	Serial.begin(9600);
	Serial.println("Debugging Motors module");
}

void loop()
{
	String sCommand;

	//read from keyboard
	sCommand = ReadKeyboard();

	//execute received command
	if (sCommand.length() > 0)
	{
		motors.ProcessMotors(127, m_iSpeed);
		if (m_iSpeed > 255)
			m_iSpeed = 12;
		else
			m_iSpeed += 12;
	}
}
