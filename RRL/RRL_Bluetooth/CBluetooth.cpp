#include "CBluetooth.h"

const char INI_STR_CMD = '^';
const char INI_BYT_CMD = '@';
const char END_CMD = '#';

// Public methods
void CBluetooth::Begin(long lBauds)
{
	m_bluetooth.begin(lBauds);
}

void CBluetooth::SendATCommandHC06(EATCommand command, String sValue)
{
	if (m_adapter != HC_06)
	{
		return;
	}

	switch (command)
	{
		case AT:
			Send("AT");
			break;

		case AT_VERSION:
			Send("AT+VERSION");
			break;

		case AT_DEVICE_NAME:
			if (sValue.length() > 0 && sValue.length() <= 20)
				Send("AT+NAME" + sValue);
			break;

		case AT_BAUD:
			if (sValue.length() == 1)
				Send("AT+BAUD" + sValue);	//1 = 1200 bps, 2 = 2400 bps, 3 = 4800 bps, 4 = 9600 bps(por defecto), 5 = 19200 bps, 6 = 38400 bps, 7 = 57600 bps, 8 = 115200 bps
			break;

		case AT_PIN:
			if (sValue.length() == 4)
				Send("AT+PIN" + sValue);
			break;

		case AT_PARITY:
			Send("AT+PN");					//PN = None, PO = Odd, PE = Even
			break;

		default:
			break;
	}
}

void CBluetooth::SendATCommandHC05(EATCommand command, String sValue)
{
	if (m_adapter != HC_05)
	{
		return;
	}

	//Send("AT+UART=9600,0,0");			//baud, stop bit (0 = 1 bit, 1 = 2 bits), parity (0 = none, 1 = Odd, 2 = Even)
	//Send("AT+ROLE=1");				//0 = Slave, 1 = Master
	//Send("AT+CMODE=0");				//0 = connect to device specified in AT+BIND. 1 = connect to any available device
	//Send("AT+BIND=3014,11,032390");	//connect to MAC 30:14:11:03:23:90

	switch (command)
	{
		case AT:
			Send("AT");
			break;

		case AT_VERSION:
			Send("AT+VERSION?");
			break;

		case AT_DEVICE_NAME:
			if (sValue.length() > 0 && sValue.length() <= 20)
				Send("AT+NAME=" + sValue);	//Setteable only if ROLE = 0 (Slave mode)
			break;

		case AT_BAUD:
			if (sValue.length() > 1)		//Bauds (4800, 9600, 19200, 38400, 57600, 115200)
				Send("AT+UART=" + sValue);	//Stop bits (0 = 1 bit, 1 = 2 bits). Parity (0 = None, 1 = Odd, 2 = Even)
			break;							//Ex.: AT+UART=9600,0,0	(9600 bps, 1 bit stop, No parity)

		case AT_PIN:
			if (sValue.length() == 4)
				Send("AT+PSWD=" + sValue);	//Setteable only if ROLE = 0 (Slave mode)
			break;

		case AT_RESET:
			Send("AT+RESET");
			break;

		case AT_ROLE:
			if (sValue.length() == 1)
				Send("AT+ROLE=" + sValue);	//0 = Slave, 1 = Master
			break;

		case AT_CMODE:
			if (sValue.length() == 1)
				Send("AT+CMODE=" + sValue);	//0 = connect to device specified in AT+BIND. 1 = connect to any available device, 2 = slave-Loop 
			break;

		case AT_BIND:
			if (sValue.length() == 14)
				Send("AT+BIND=" + sValue);	//Ex.: AT+BIND=3014,11,032390 -> connect to MAC 30:14:11:03:23:90
			break;

		case AT_STATE:
			Send("AT+STATE?");				//can return: "INITIALIZED" "READY" "PAIRABLE" "PAIRED" "INQUIRING" "CONNECTING" "CONNECTED""DISCONNECTED" "NUKNOW"
			break;

		case AT_PAIR:
			if (sValue.length() >= 16)
				Send("AT+PAIR=" + sValue);	//Ex.: AT+PAIR=3014,11,032390,20 -> pair with device MAC 30:14:11:03:23:90 for 20 sec.
			break;

		case AT_LINK:
			if (sValue.length() >= 16)
				Send("AT+LINK=" + sValue);	//Ex.: AT+LINK=3014,11,032390 -> link with device MAC 30:14:11:03:23:90 without inquiring
			break;

		case AT_DELETE_PAIRED:
			if (sValue.length() == 14)
				Send("AT+PMSAD=" + sValue);	//Ex.: AT+PMSAD=3014,11,032390 -> delete authenticated device MAC 30:14:11:03:23:90
			break;

		case AT_DELETE_ALL_PAIRED:
			Send("AT+RMAAD");				//delete all authenticated devices
			break;

		case AT_DISCONNECT:
			Send("AT+DISC");				//can return: 1.+DISC:SUCCESS OK   2.+DISC:LINK_LOSS OK   3.+DISC:NO_SLC OK   4.+DISC:TIMEOUT OK   5.+DISC:ERROR OK
			break;

		//case AT_IPSCAN:
		//	Send("AT+IPSCAN=" + sValue);	//Ex.: AT+IPSCAN=1024,1,1024,1 -> configures <Query time interval> <Query duration> <Paging interval> <Call duration>. Default: 1024,512,1024,512
		//	break;

		//case AT_SNIFF:
		//	Send("AT+SNIFF=" + sValue);		//Ex.: AT+SNIFF=40,20,1,8 -> configures <Max time> <Min time> <Retry time> <Time out> for SNIFF mode. Default: 0,0,0,0
		//	break;							//combine with IPSCAN to allow consumption reduction

		//case AT_START_ENERGY:
		//	Send("AT+ENSNIFF=");	//Enters SNIFF saving mode and needs configuration with AT+SNIFF. Usage: AT+ENSNIFF=3014,11,032390
		//	break;

		//case AT_STOP_ENERGY:
		//	Send("AT+EXSNIFF=");	//Exits SNIFF saving mode. Usage: AT+EXSNIFF=3014,11,032390
		//	break;

		case AT_PARITY:
		default:
			break;
	}
}

String CBluetooth::Receive()
{
	m_sMessage = "";
	do
	{
		if (m_bluetooth.available() > 0)
		{
			m_sMessage += (char)m_bluetooth.read();	//append char to String
		}
		delay(3);     //delay to allow buffer to fill -> NEEDED!!
	} while (m_bluetooth.available());

	return m_sMessage;
}

void CBluetooth::Send(String sMessage)
{
	if (sMessage.length() > 0)
	{
		if (m_adapter == HC_05 && sMessage.length() >= 2 && sMessage[0] == 'A' && sMessage[1] == 'T')
			m_bluetooth.println(sMessage + "\n");	//Add carriage + line feed only when sending AT commands
		else
			m_bluetooth.print(sMessage);
	
		//Make code wait for a string to be finished sending because Serial.print() function returns almost immediately
		m_bluetooth.flush();
	}
}

void CBluetooth::SendCommand(String sMessage)
{
	m_sMessage = String(INI_STR_CMD);
	m_sMessage += sMessage;
	m_sMessage += String(END_CMD);
	Send(m_sMessage);					//example of what's sending: "^Hello world#"
}

void CBluetooth::SendCommand(byte byteX, byte byteY)
{
	m_sMessage = String(INI_BYT_CMD);
	m_sMessage += String(byteX) + ",";
	m_sMessage += String(byteY) + String(END_CMD);	//example of what's sending: "@243,240#"
	Send(m_sMessage);
}

ECommandType CBluetooth::CommandType(String sCommand)
{
	if (sCommand.length() > 0)
	{
		if (sCommand[0] == INI_STR_CMD)
			return StringCommand;
		else if (sCommand[0] == INI_BYT_CMD)
			return ArrayBytes;
	}
	return Unknown;
}

int* CBluetooth::ProcessArrayBytesCommand(String sCommand)
{
	int arrayValues[2];
	char c;
	String s = "";
	int j = 0;

	//example of what's receiving: "@243,240#"
	for (int i = 0; i < sCommand.length(); i++)
	{
		c = sCommand[i];
		if (c == ',' || c == END_CMD)
		{
			arrayValues[j] = s.toInt();
			j++;
			s = "";
		}
		else if (c == INI_BYT_CMD || c == INI_STR_CMD)
		{
			continue;
		}
		else
		{
			s += c;
		}

		//extra checks just in case
		if (c == END_CMD || j >= (sizeof(arrayValues) / sizeof(int)))
		{
			break;
		}
	}

	return arrayValues;
}

String CBluetooth::ProcessStringCommand(String sCommand)
{
	char c;
	String sValue = "";

	//example of what's receiving: "^Hello world#"
	for (int i = 0; i < sCommand.length(); i++)
	{
		c = sCommand[i];
		if (c == INI_BYT_CMD || c == INI_STR_CMD)
		{
			continue;
		}
		else if (c == END_CMD)
		{
			break;
		}
		else
		{
			sValue += c;
		}
	}

	return sValue;
}

// Private methods
