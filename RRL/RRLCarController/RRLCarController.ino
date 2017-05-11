#include "CMotors.h"
#include "CJoystick.h"
#include "CBluetooth.h"

const int iInButtonX = 4;
const int iInButtonA = 3;
const int iInButtonB = 5;
const int outLed = 13;

///#define DEBUG = true;
#ifdef DEBUG
bool m_bContinuouslyPrint;
#endif

int m_iX, m_iY, m_iJoystickButton;
int m_iCurrentSpeed, m_iCurrentMovement;
String m_sButtons;

CBluetooth m_bluetooth(11, 12, HC_05);	//RX, TX, EBluetoothAdapter
CJoystick m_joystick(0, 1, 8);			//analogInputX, analogInputY, digitalInputButton
CMotors* m_motors;						//create virtual motor to calculate motor movement, so send command only when needed

void setup()
{
	m_bluetooth.Begin(9600);
#ifdef DEBUG
	Serial.begin(9600);
	Serial.println("Debugging RRL CarController");
	m_bContinuouslyPrint = true;
#endif

	m_motors = new CMotors();
	m_iCurrentSpeed = 0;
	m_iCurrentMovement = 0;
	pinMode(iInButtonX, INPUT_PULLUP);
	pinMode(iInButtonA, INPUT_PULLUP);
	pinMode(iInButtonB, INPUT_PULLUP);
	pinMode(outLed, OUTPUT);			//activates Led output when a button press is detected
}

void loop()
{
	m_sButtons = "";

#ifdef DEBUG
	Debug();
#endif
#ifndef DEBUG
	//read from buttons and send through Bluetooth
	if (digitalRead(iInButtonX) == LOW)
		m_sButtons += "x";
	if (digitalRead(iInButtonA) == LOW)
		m_sButtons += "a";
	if (digitalRead(iInButtonB) == LOW)
		m_sButtons += "b";
	if (m_joystick.ReadButton() == LOW)
		m_sButtons += "j";
	if (m_sButtons.length() > 0)
	{
		m_bluetooth.Send(" ");		//WORKAROUND: send dummy value to ¿wake up? bluetooth
		m_bluetooth.SendCommand(m_sButtons);
		digitalWrite(outLed, HIGH);
		while ( digitalRead(iInButtonX) == LOW ||
				digitalRead(iInButtonA) == LOW ||
				digitalRead(iInButtonB) == LOW ||
				m_joystick.ReadButton() == LOW )	//wait while buttons are pressed instead of setting a fixed delay
		{
			delay(30);
		}
	}
	else
	{
		digitalWrite(outLed, LOW);
	}

	//read from joystick and send through Bluetooth
	m_iX = m_joystick.ReadAxisX();
	m_iY = m_joystick.ReadAxisY();
	m_motors->ProcessMotors((byte)m_iX, (byte)m_iY);
	if (abs(m_motors->GetCurrentSpeed() - m_iCurrentSpeed) > 3 ||
		m_motors->GetCurrentMovement() != m_iCurrentMovement)
	{
		m_iCurrentSpeed = m_motors->GetCurrentSpeed();
		m_iCurrentMovement = m_motors->GetCurrentMovement();

		m_bluetooth.Send(" ");		//WORKAROUND: send dummy value to ¿wake up? bluetooth
		m_bluetooth.SendCommand(m_iX, m_iY);
		delay(150);					//wait between transmissions
	}
#endif
}

void Debug()
{
#ifdef DEBUG
	//read from buttons and send through Bluetooth
	if (digitalRead(iInButtonX) == LOW)
		m_sButtons += "x";
	if (digitalRead(iInButtonA) == LOW)
		m_sButtons += "a";
	if (digitalRead(iInButtonB) == LOW)
		m_sButtons += "b";
	if (m_joystick.ReadButton() == LOW)
		m_sButtons += "j";

	if (m_bContinuouslyPrint)
	{
		if(m_sButtons.length() > 0)
		{
			Serial.println("Buttons:" + m_sButtons);
			digitalWrite(outLed, HIGH);
		}
		else
		{
			digitalWrite(outLed, LOW);
		}
	}

	//read from joystick and send through Bluetooth
	m_iX = m_joystick.ReadAxisX();
	m_iY = m_joystick.ReadAxisY();
	if (m_bContinuouslyPrint)
	{
		m_motors->ProcessMotors((byte)m_iX, (byte)m_iY);
		if (m_motors->GetCurrentMovement() != m_iCurrentMovement)
		{
			Serial.print("Axis: ");
			Serial.print(String(m_iX));
			Serial.print(",");
			Serial.println(String(m_iY));
			m_iCurrentMovement = m_motors->GetCurrentMovement();
		}
		if (abs(m_motors->GetCurrentSpeed() - m_iCurrentSpeed) > 3)
		{
			Serial.print("Speed: ");
			Serial.println(String(m_motors->GetCurrentSpeed()));
			m_iCurrentSpeed = m_motors->GetCurrentSpeed();
		}
	}

	//AT command only in DEBUG mode. Don't FORGET press module button in order to send AT commands!!!!!
	m_sButtons = ReadKeyboard();		//re-use global variable
	if (m_sButtons.length() > 0)
	{
		if (m_sButtons == "c")
			m_bContinuouslyPrint = true;
		else if (m_sButtons == "s")
			m_bContinuouslyPrint = false;

		Serial.println("-> " + m_sButtons);
		m_bluetooth.Send(m_sButtons);
		m_sButtons = m_bluetooth.Receive();
		Serial.println("BT -> " + m_sButtons);
	}
#endif
}
