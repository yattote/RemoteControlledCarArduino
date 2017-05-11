#include "CMotors.h"

const int CENTER_Y_MINUS = 127 - 30;
const int CENTER_Y_PLUS  = 127 + 30;
const int SECTION = 70;

// Public methods
void CMotors::ProcessMotors(String sCommand)
{
	if (sCommand == "u")
	{
		SetMovement(Up);
	}
	else if (sCommand == "d")
	{
		SetMovement(Down);
	}
	else if (sCommand == "ru")
	{
		SetMovement(RightUp);
	}
	else if (sCommand == "rd")
	{
		SetMovement(RightDown);
	}
	else if (sCommand == "lu")
	{
		SetMovement(LeftUp);
	}
	else if (sCommand == "ld")
	{
		SetMovement(LeftDown);
	}
	else if (sCommand == "s")
	{
		SetMovement(Stop);
	}
	else
	{
		return;
	}

	SetSpeed(192);
	delay(50);     //wait some time in order to give time for motor relays setting the new state
}

void CMotors::ProcessMotors(const byte valueX, const byte valueY)
{
	int iSpeed;
	EMovements movement;

	//process command
	iSpeed = map( abs(valueY - 127) * 2 , 0, 255, 50, m_iMaxSpeed );
	if (valueY > (CENTER_Y_MINUS) && valueY < (CENTER_Y_PLUS))	//Stop -> [Y = 98 to Y = 157]
	{
		iSpeed = 0;
		movement = Stop;
	}
	else
	{
		if (valueY <= CENTER_Y_MINUS)		//from Y = 0 to Y = 97
		{
			if (valueX > (255 - SECTION))	//from X = 185 to X = 255
			{
				movement = LeftUp;
			}
			else if (valueX < SECTION)		//from X = 0 to X = 70
			{
				movement = RightUp;
			}
			else							//from X = 70 to X = 185
			{
				movement = Up;
			}
		}
		else								//from Y = 158 to Y = 255
		{
			if (valueX > (255 - SECTION))	//from X = 185 to X = 255
			{
				movement = LeftDown;
			}
			else if (valueX < SECTION)		//from X = 0 to X = 70
			{
				movement = RightDown;
			}
			else							//from X = 70 to X = 185
			{
				movement = Down;
			}
		}
	}

	//set speed accordingly to command
	SetSpeed(iSpeed);

	//set movements according to command
	if (m_CurrentMovement != movement)
	{
		SetMovement(movement);
		delay(50);     //wait some time in order to give time for motor relays setting the new state
	}
}

// Private methods
void CMotors::SetMovement(EMovements movement)
{
	int iLeftValue1, iLeftValue2;
	int iRightValue1, iRightValue2;

	m_CurrentMovement = movement;
	switch (m_CurrentMovement)
	{
		case LeftUp:
			iLeftValue1 = 0;  iLeftValue2 = 0;
			iRightValue1 = 0; iRightValue2 = 1;
			break;

		case RightUp:
			iLeftValue1 = 0;  iLeftValue2 = 1;
			iRightValue1 = 0; iRightValue2 = 0;
			break;

		case Up:
			iLeftValue1 = 0;  iLeftValue2 = 1;
			iRightValue1 = 0; iRightValue2 = 1;
			break;

		case LeftDown:
			iLeftValue1 = 0;  iLeftValue2 = 0;
			iRightValue1 = 1; iRightValue2 = 0;
			break;

		case RightDown:
			iLeftValue1 = 1;  iLeftValue2 = 0;
			iRightValue1 = 0; iRightValue2 = 0;
			break;

		case Down:
			iLeftValue1 = 1;  iLeftValue2 = 0;
			iRightValue1 = 1; iRightValue2 = 0;
			break;

		case Stop:
		default:
			iLeftValue1 = 0;  iLeftValue2 = 0;
			iRightValue1 = 0; iRightValue2 = 0;
			break;
	}
	if (!m_bVirtualMotor)
	{
		digitalWrite(m_iPinAxisLeft1, iLeftValue1);
		digitalWrite(m_iPinAxisLeft2, iLeftValue2);
		digitalWrite(m_iPinAxisRight1, iRightValue1);
		digitalWrite(m_iPinAxisRight2, iRightValue2);
	}
}

void CMotors::SetSpeed(int iSpeed)
{
	m_iCurrentSpeed = iSpeed;
	if (!m_bVirtualMotor)
	{
		if (iSpeed <= SPEED_UNIT)			//slow down speed to avoid sudden stop.
		{
			analogWrite(m_iPinENA, SPEED_UNIT / 3);	//ENA needs more time to stop so set smaller speed value
			analogWrite(m_iPinENB, SPEED_UNIT / 2);
			delay(50);
		}

		analogWrite(m_iPinENA, iSpeed);
		analogWrite(m_iPinENB, iSpeed - 3);	//there is a hardware offset in ENB, so we compesate it by software
	}
}

