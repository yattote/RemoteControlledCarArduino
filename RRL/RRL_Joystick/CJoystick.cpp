#include "CJoystick.h"

// Public methods
int CJoystick::ReadAxisX()
{
	// Analog inputs	   range: 0 - 1023 (0V - 5V)
	// Analog outpus (PWM) range: 0 - 255  (0V - 5V)
	return map(analogRead(m_iPinAxisX), 0, 1023, 0, 255);
}

int CJoystick::ReadAxisY()
{
	return map(analogRead(m_iPinAxisY), 0, 1023, 0, 255);
}

int CJoystick::ReadButton()
{
	return digitalRead(m_iPinButton);
}

// Private methods
