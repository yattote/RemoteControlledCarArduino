// CMotors.h

#ifndef _CMOTORS_h
#define _CMOTORS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

enum EMovements { Stop, Up, Down, LeftUp, LeftDown, RightUp, RightDown };
enum ESpeedMode { None, Slow, Normal, Fast, Turbo };	//0, 55, 110, 165, 220
const int SPEED_UNIT = 55;

class CMotors
{
public:
	// Contructors
	CMotors()
	{
		m_CurrentMovement = Stop;
		SetSpeedMode(Normal);
		m_bVirtualMotor = true;
	}

	CMotors(int iPinAxisLeft1, int iPinAxisLeft2, int iPinAxisRight1, int iPinAxisRight2, int iPinENA, int iPinENB) : CMotors()
	{
		m_iPinAxisLeft1 = iPinAxisLeft1;
		m_iPinAxisLeft2 = iPinAxisLeft2;
		m_iPinAxisRight1 = iPinAxisRight1;
		m_iPinAxisRight2 = iPinAxisRight2;
		m_iPinENA = iPinENA;
		m_iPinENB = iPinENB;
		m_bVirtualMotor = false;

		pinMode(iPinAxisLeft1, OUTPUT);
		pinMode(iPinAxisLeft2, OUTPUT);
		pinMode(iPinAxisRight1, OUTPUT);
		pinMode(iPinAxisRight2, OUTPUT);
		pinMode(iPinENA, OUTPUT);
		pinMode(iPinENB, OUTPUT);
	};

	// Public methods
	String GetCurrMovString()
	{
		switch (m_CurrentMovement)
		{
			case Up:
				return "Up";

			case LeftUp:
				return "LeftUp";

			case LeftDown:
				return "LeftDown";

			case Down:
				return "Down";

			case RightUp:
				return "RightUp";

			case RightDown:
				return "RightDown";

			case Stop:
				return "Stop";

			default:
				return "Unknown";
		}
	}

	EMovements GetCurrentMovement()
	{
		return m_CurrentMovement;
	}

	int GetCurrentSpeed()
	{
		return m_iCurrentSpeed;
	}

	ESpeedMode GetSpeedMode()
	{
		return m_CurrentSpeedMode;
	}

	void SetSpeedMode(ESpeedMode speedMode)
	{
		m_CurrentSpeedMode = speedMode;
		m_iMaxSpeed = SPEED_UNIT * speedMode;
	}

	void ProcessMotors(String sCommand);
	void ProcessMotors(const byte byteX, const byte byteY);

	private:
		// Fields
		int m_iPinAxisLeft1, m_iPinAxisLeft2, m_iPinAxisRight1, m_iPinAxisRight2;
		int m_iPinENA, m_iPinENB;
		EMovements m_CurrentMovement;
		ESpeedMode m_CurrentSpeedMode;
		int m_iCurrentSpeed;
		int m_iMaxSpeed;
		bool m_bVirtualMotor;

		// Private methods
		void SetMovement(EMovements movement);
		void SetSpeed(int iSpeed);
};

#endif

