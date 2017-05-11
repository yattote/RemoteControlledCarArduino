/* Robot controlado vía bluetooth. Desarrollado por LEANTEC ELECTRONICS & ROBOTICS.
Esta permitido el uso de este código a todo aquel que lo necesite.
No esta permitido el uso de este código con fines comerciales*/

// Variables de motores:
int inA = 4; //Los cuatro “in” son  los pines a los que va conectado el motor driver
int inB = 5; 
int inC = 6;
int inD = 7;
int pwmMIpin= 10; //Los dos pines conectados a los motores para regular la velocidad.
int pwmMDpin=11;

//Variables de luces:
int pwmL1pin=3; //Los dos pines PWM a los que van conectados los leds blancos
int pwmL2pin=9;
int lednarD=2; //Y los dos pines a los que van conectados los intermitentes
int lednarI=8;
int estadoled=LOW;
long intervalo=200;
long previousMillis=0;
unsigned long currentMillis=0;

// Variables de comunicacion:
int value=0; 
int pwmMvalue=255; //Velocidad del coche
//int pwmLvalue=0; //Intensidad de los faros
int incomingByte; //Último bit recibido
int esx=0;  //Indica si es la barra de arriba o la de abajo sobre la que estamos deslizando.
int esy=0;
boolean lectura=0; //Puede ser uno o cero. Reconoce si estamos mandando algo.

void setup()
{
  pinMode (inA, OUTPUT);
  pinMode(inB, OUTPUT);
  pinMode(inC, OUTPUT);
  pinMode(inD, OUTPUT); //Establece los cuatro pines del motor driver como salidas.
  //pinMode(lednarD, OUTPUT);
  //pinMode(lednarI,OUTPUT);
  Serial.begin(9600); //Establece conexión con el puerto serie
}
void go_forward()
{ //Función para que el robot avance
  digitalWrite(inA, HIGH); 
  digitalWrite(inB, LOW);
  digitalWrite(inC, LOW);
  digitalWrite(inD, HIGH);
}
void go_back()
{ //Función para que el robot retroceda
  digitalWrite(inA, LOW);
  digitalWrite(inB, HIGH);
  digitalWrite(inC, HIGH);
  digitalWrite(inD, LOW);
}
void turn_right()
{ //Función para que el robot gire a la derecha
  digitalWrite(inA, LOW);
  digitalWrite(inB, HIGH);
  digitalWrite(inC, LOW);
  digitalWrite(inD, HIGH);
}
void turn_left()
{ //Función para que el robot gire a la izquierda
  digitalWrite(inA, HIGH);
  digitalWrite(inB, LOW);
  digitalWrite(inC, HIGH);
  digitalWrite(inD, LOW);
}
void parar()
{ //Función para que el robot pare
  digitalWrite(inA, LOW);
  digitalWrite(inB, LOW);
  digitalWrite(inC, LOW);
  digitalWrite(inD, LOW);
}
void loop()
{
  unsigned long currentMillis=millis();
  if (Serial.available() > 0)
  { //Si recibe datos,
    incomingByte = Serial.read(); //Acumula el último bit en incomingByte

    if (incomingByte == 'f')
    { //SI es “f” (botón de arriba),
      go_forward(); //Va hacia alante
      digitalWrite(lednarD, LOW);
      digitalWrite(lednarI, LOW);
    }
    if (incomingByte == 'b')
    { //Si es “b” (botón de abajo),
      go_back(); //Va hacia atrás
      digitalWrite(lednarD, LOW);
      digitalWrite(lednarI, LOW);
    }
    if (incomingByte == 'r')
    { //Si es “r” (botón de la derecha);
      turn_right(); //Gira a la derecha
      digitalWrite(lednarD, HIGH);
      digitalWrite(lednarI, LOW);
    }
    if (incomingByte == 'l')
    { //Si es “l” (botón de la izquierda), 
      turn_left(); //Gira a la izquierda
      digitalWrite(lednarD, LOW);
      digitalWrite(lednarI, HIGH);
    }
    if (incomingByte == 's')
    { //Si es “s”  (no se pulsa nada),
      parar();  //El coche se para.
      digitalWrite(lednarD, LOW);
      digitalWrite(lednarI, LOW);
    }

    if(incomingByte==60)
    { //Si lee un 60 (< en ASCII),
      lectura=1; // Empieza a leer
    }
    if (incomingByte == 'x')
    { //Si lee una x, es la barra de arriba
      esx=1;
    }
    if (incomingByte== 'y')
    { //Si lee una y, es la barra de abajo
      esy=1;
    }
    if (lectura==1)
    { 
      if(incomingByte>= '0' && incomingByte<= '9')
      { // Si es un caracter ASCII entre 0 y el 9
        value=(value*10)+(incomingByte-'0');    // Acumula el valor, en codigo ASCII el 0=48, 1=49...
      }
      else if (incomingByte==62) // > uso como finalizador
      {
        if(esx==1)
        { //Si es x (la barra de arriba)
          pwmLvalue=value;     // Guarda el valor en la variable pwmLvalue (focos)
          Serial.print("pwmLvalue=");     // Lo imprime por pantalla
          Serial.println(pwmLvalue);     // Imprime el valor
          value=0;    // Dejamos lista para volver a escribir en ella
          lectura=0; //Deja de leer
          esy=0; //Fija esy a 0.   
        }
        if(esy==1)
        { //Si es y (la barra de abajo)
          pwmMvalue=value;     // Guarda el valor en la variable pwmMvalue (velocidad)
          Serial.print("pwmMvalue=");     // Lo imprime por pantalla
          Serial.println(pwmMvalue);     //Imprime el valor
          value=0;    // Dejamos lista para volver a escribir en ella
          lectura=0; //Deja de leer
          esx=0; //Fija esx a 0
        }
      }
      analogWrite(pwmMIpin,pwmMvalue);    // Fija la velocidad al valor impuesto
      analogWrite(pwmMDpin,pwmMvalue);   
      analogWrite(pwmL1pin,pwmLvalue); // Fija la luz al valor impuesto
      analogWrite(pwmL2pin,pwmLvalue);
    }
  } 
}


















