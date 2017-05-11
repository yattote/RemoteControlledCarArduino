// CMarquee.h

#ifndef _CMARQUEE_h
#define _CMARQUEE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class CMarquee
{
public:
	// Constructors
	CMarquee(int iPinData, int iPinClock, int iPinLatch)
	{
		m_iPinData = iPinData;
		m_iPinClock = iPinClock;
		m_iPinLatch = iPinLatch;

		pinMode(iPinData, OUTPUT);
		pinMode(iPinClock, OUTPUT);
		pinMode(iPinLatch, OUTPUT);
	};

	// Public methods
	void Start();
	void Stop();

private:
	// Fields
	int m_iPinData, m_iPinClock, m_iPinLatch;

	// Private methods
	void WriteByte(byte data);
	void ShiftWrite(int iPin, boolean bState);
};

#endif

