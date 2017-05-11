// CBluetooth.h

#ifndef _CBLUETOOTH_h
#define _CBLUETOOTH_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include "SoftwareSerial.h"
#else
	#include "WProgram.h"
#endif

enum EBluetoothAdapter { HC_05, HC_06 };
enum EATCommand { AT, AT_VERSION, AT_DEVICE_NAME, AT_BAUD, AT_PIN, AT_PARITY,		//common to both adapters
AT_RESET, AT_ROLE, AT_CMODE, AT_BIND, AT_STATE, AT_PAIR, AT_LINK,					//specific for HC-05
AT_DELETE_PAIRED, AT_DELETE_ALL_PAIRED,	AT_DISCONNECT
/*AT_IPSCAN, AT_SNIFF, AT_START_ENERGY, AT_STOP_ENERGY*/ };
enum ECommandType { Unknown, ArrayBytes, StringCommand };

class CBluetooth
{
	public:
		// Constructors
		CBluetooth(int iPinRx, int iPinTx, EBluetoothAdapter adapter) : m_bluetooth(iPinRx, iPinTx)
		{
			m_adapter = adapter;
		};

		// Public methods
		void Begin(long lBauds);
		void SendATCommandHC05(EATCommand command, String sValue);
		void SendATCommandHC06(EATCommand command, String sValue);

		String Receive();
		void Send(String sMessage);
		
		void SendCommand(String sMessage);
		void SendCommand(byte byteX, byte byteY);
		ECommandType CommandType(String sCommand);
		int* ProcessArrayBytesCommand(String sCommand);
		String ProcessStringCommand(String sCommand);

	private:
		// Fields
		SoftwareSerial m_bluetooth;
		EBluetoothAdapter m_adapter;
		String m_sMessage;

		// Private methods
};

#endif
