#include "CMelodies.h"

ToneMelody melodies(13);

void setup()
{
	Serial.begin(9600);
	Serial.println("Debugging Horn module");
}

void loop()
{
	String sValue = ReadKeyboard();
	if (sValue.length() > 0)
	{
		if (sValue == "0")
			melodies.PlayMelody(Fanfarria);
		else if (sValue == "1")
			melodies.PlayMelody(DogPower);
		else if (sValue == "2")
			melodies.PlayMelody(ThirdPhase);
		else if (sValue == "3")
			melodies.PlayMelody(R2D2);
		else if (sValue == "4")
			melodies.PlayMelody(Ohhh);
		else if (sValue == "5")
			melodies.PlayMelody(Uhoh);

		Serial.println(sValue);
		delay(100);
	}
}

