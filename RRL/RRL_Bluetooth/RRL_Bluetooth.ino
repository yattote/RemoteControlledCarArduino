#include "CBluetooth.h"

CBluetooth m_bluetooth(4, 2, HC_05);				//Rx, Tx, Adapter, OutPinForAT_Commands
String m_sValue;

void setup()
{
	m_bluetooth.Begin(9600);
	
	Serial.begin(9600);
	Serial.println("Debugging Bluetooth module");

	m_sValue = "";
}

void loop()
{
	//Read and send bluetooth after read of keyboard
	m_sValue = m_bluetooth.Receive();
	if (m_sValue.length() > 0)
		Serial.println("BT-> " + m_sValue);
	m_sValue = ReadKeyboard();
	m_bluetooth.Send(m_sValue);
	if (m_sValue.length() > 0)
		Serial.println("-> " + m_sValue);


}
