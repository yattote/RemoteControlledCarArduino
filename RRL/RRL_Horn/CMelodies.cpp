#include "CMelodies.h"

void ToneMelody::PlayMelody(EMelodies melody)
{
	switch (melody)
	{
		case Fanfarria:
			melody0();
			break;
		case DogPower:
			melody1();
			break;
		case ThirdPhase:
			melody2();
			break;
		case R2D2:
			melody3();
			break;
		case Ohhh:
			melody4();
			break;
		case Uhoh:
			melody5();
			break;
	}
}

void ToneMelody::melody0() { // MELODIA_FANFARRIA 0
	tone(m_pin, NOTE_C4, NOTE_NEGRA); delay(NOTE_NEGRA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_G3, NOTE_CORCHEA); delay(NOTE_CORCHEA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_G3, NOTE_CORCHEA); delay(NOTE_CORCHEA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_A3, NOTE_NEGRA); delay(NOTE_NEGRA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_G3, NOTE_NEGRA); delay(NOTE_NEGRA_PAUSA); noTone(m_pin);
	tone(m_pin, 0, NOTE_CORCHEA); delay(NOTE_CORCHEA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_B3, NOTE_NEGRA); delay(NOTE_NEGRA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_C4, NOTE_NEGRA); delay(NOTE_NEGRA_PAUSA); noTone(m_pin);
	delay(10);
}

void ToneMelody::melody1() { // MELODIA_PODER_PERRUNO
	tone(m_pin, NOTE_B4, NOTE_CORCHEA); delay(NOTE_CORCHEA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_B4, NOTE_CORCHEA); delay(NOTE_CORCHEA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_B4, NOTE_CORCHEA); delay(NOTE_CORCHEA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_GS5, NOTE_NEGRA); delay(NOTE_NEGRA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_B4, NOTE_CORCHEA); delay(NOTE_CORCHEA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_GS5, NOTE_NEGRA); delay(NOTE_NEGRA_PAUSA); noTone(m_pin);
	delay(10);
}

void ToneMelody::melody2() { // MELODIA_ENCUENTROS_3A_FASE
							   // Based on work by Erik Kringen
							   //http://www.mycontraption.com/sound-effects-with-and-arduino/
	tone(m_pin, NOTE_AS5, NOTE_NEGRA); delay(NOTE_NEGRA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_C6, NOTE_NEGRA); delay(NOTE_NEGRA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_GS4, NOTE_NEGRA); delay(NOTE_NEGRA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_GS3, NOTE_NEGRA); delay(NOTE_NEGRA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_DS5, NOTE_BLANCA); delay(NOTE_BLANCA_PAUSA); noTone(m_pin);
	delay(500);

	tone(m_pin, NOTE_AS4, NOTE_NEGRA); delay(NOTE_NEGRA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_C5, NOTE_NEGRA); delay(NOTE_NEGRA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_GS3, NOTE_NEGRA); delay(NOTE_NEGRA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_GS2, NOTE_NEGRA); delay(NOTE_NEGRA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_DS4, NOTE_BLANCA); delay(NOTE_BLANCA_PAUSA); noTone(m_pin);
	delay(500);

	tone(m_pin, NOTE_AS3, NOTE_NEGRA); delay(NOTE_NEGRA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_C4, NOTE_NEGRA); delay(NOTE_NEGRA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_GS2, NOTE_BLANCA); delay(NOTE_BLANCA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_GS1, NOTE_BLANCA); delay(NOTE_BLANCA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_DS3, NOTE_REDONDA); delay(NOTE_REDONDA_PAUSA); noTone(m_pin);
	delay(10);
}

void ToneMelody::melody3() { // MELODIA_R2D2
							   // Based on work by Erik Kringen and Dave Tucker
							   //http://www.mycontraption.com/sound-effects-with-and-arduino/
							   //http://dtucker.co.uk/make/arduino-using-my-melodyutils-library-for-r2-d2-style-chirps.html
	tone(m_pin, NOTE_A7, NOTE_CORCHEA); delay(NOTE_CORCHEA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_G7, NOTE_CORCHEA); delay(NOTE_CORCHEA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_E7, NOTE_CORCHEA); delay(NOTE_CORCHEA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_C7, NOTE_CORCHEA); delay(NOTE_CORCHEA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_D7, NOTE_CORCHEA); delay(NOTE_CORCHEA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_B7, NOTE_CORCHEA); delay(NOTE_CORCHEA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_F7, NOTE_CORCHEA); delay(NOTE_CORCHEA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_C8, NOTE_CORCHEA); delay(NOTE_CORCHEA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_A7, NOTE_CORCHEA); delay(NOTE_CORCHEA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_G7, NOTE_CORCHEA); delay(NOTE_CORCHEA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_E7, NOTE_CORCHEA); delay(NOTE_CORCHEA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_C7, NOTE_CORCHEA); delay(NOTE_CORCHEA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_D7, NOTE_CORCHEA); delay(NOTE_CORCHEA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_B7, NOTE_CORCHEA); delay(NOTE_CORCHEA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_F7, NOTE_CORCHEA); delay(NOTE_CORCHEA_PAUSA); noTone(m_pin);
	tone(m_pin, NOTE_C8, NOTE_CORCHEA); delay(NOTE_CORCHEA_PAUSA); noTone(m_pin);
	delay(10);
}


void ToneMelody::melody4() { // MELODIA_OHHH
	Glis(NOTE_C6, NOTE_C7, 6);
	Glis(NOTE_C7, NOTE_C6, 5);
	//for (int i=1000; i<2000; i=i*1.02) { tone(m_pin,i,10); };
	//for (int i=2000; i>1000; i=i*.98) { tone(m_pin,i,10); delay(10);};
}


void ToneMelody::melody5() { // MELODIA_UHOH
	Glis(NOTE_C6, NOTE_DS6, 6);
	delay(200);
	Glis(NOTE_DS6, NOTE_CS6, 5);
	//for (int i=1000; i<1244; i=i*1.01) { tone(m_pin,i,30); };
	//delay(200);
	//for (int i=1244; i>1108; i=i*.99) { tone(m_pin,i,30);  delay(30);};

}


void ToneMelody::Glis(int nota1, int nota2, int tasa) {
	// By Dave Tucker
	//http://dtucker.co.uk/make/arduino-using-my-melodyutils-library-for-r2-d2-style-chirps.html
	// Glissando = Slide
	// Slides up or down from note1 to note2
	// rate = 0 is fast and can be increased to slow the effect down

	if (nota1 < nota2) { //Slide up
		for (int nota = nota1; nota < nota2; nota++) {
			tone(m_pin, nota, tasa); delay(tasa); noTone(m_pin);
		}
	}
	else { //Slide down
		for (int nota = nota1; nota > nota2; nota--) {
			tone(m_pin, nota, tasa); delay(tasa); noTone(m_pin);
		}
	}
	noTone(m_pin);
}

void ToneMelody::Trem(int note, int length, int rate) {
	// By Dave Tucker
	//http://dtucker.co.uk/make/arduino-using-my-melodyutils-library-for-r2-d2-style-chirps.html
	// Tremolo = Fast repetition of a note
	// note = the note (from pitches.h)
	// length = duration of the effect in msec
	// rate = number of repetitions

	int note_duration = length / rate;
	int pauseBetweenNotes = rate * (1 + rate / length);

	for (int i = 0; i <= rate; i++) {
		tone(m_pin, note, note_duration);
		delay(pauseBetweenNotes);
		noTone(m_pin);
	}
}
