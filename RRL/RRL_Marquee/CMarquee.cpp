#include "CMarquee.h"

// Public methods
void CMarquee::Start()
{
	/*writeByte(255);
	delay(500);
	writeByte(0);
	delay(500);*/

	ShiftWrite(0, HIGH);
	delay(100);
	ShiftWrite(6, LOW);
	delay(50);
	ShiftWrite(1, HIGH);
	delay(100);
	ShiftWrite(7, LOW);
	delay(50);
	ShiftWrite(2, HIGH);
	delay(100);
	ShiftWrite(0, LOW);
	delay(50);
	ShiftWrite(3, HIGH);
	delay(100);
	ShiftWrite(1, LOW);
	delay(50);
	ShiftWrite(4, HIGH);
	delay(100);
	ShiftWrite(2, LOW);
	delay(50);
	ShiftWrite(5, HIGH);
	delay(100);
	ShiftWrite(3, LOW);
	delay(50);
	ShiftWrite(6, HIGH);
	delay(100);
	ShiftWrite(4, LOW);
	delay(50);
	ShiftWrite(7, HIGH);
	delay(100);
	ShiftWrite(5, LOW);
	delay(50);
}

void CMarquee::Stop()
{

}

// Private methods
void CMarquee::WriteByte(byte data)
{
	digitalWrite(m_iPinLatch, HIGH);

	//dataPin  = 2 = SER
	//clockpin = 3 = SRCLK
	//latchpin = 4 = RCLK
	shiftOut(m_iPinData, m_iPinClock, MSBFIRST, data);
	// toggle the latch pin so that the data appears as an output

	digitalWrite(m_iPinLatch, LOW);
}

void CMarquee::ShiftWrite(int iPin, boolean bState)
{
	byte data = 0;	//NOTE: can be declared as global so can concatenate different states


	digitalWrite(m_iPinLatch, LOW);

	// write a bit to the pin we want to turn on
	bitWrite(data, iPin, bState);
	// send the byte to the shift register
	shiftOut(m_iPinData, m_iPinClock, MSBFIRST, data);
	// toggle the latch pin so that the data appears as an output

	digitalWrite(m_iPinLatch, HIGH);

	//
	/*for (int i = numOfRegisterPins - 1; i >= 0; i--)
	{
		digitalWrite(SRCLK_Pin, LOW);

		int val = registers[i];

		digitalWrite(SER_Pin, val);
		digitalWrite(SRCLK_Pin, HIGH);
	}*/
}