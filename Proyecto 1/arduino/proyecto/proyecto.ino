#include <math.h>

int digit_pin[] = {6, 9, 10, 11}; // PWM Display digit pins from left to right
int speakerPin = 15; // PIN DEL BUZZER

#define DIGIT_ON  LOW
#define DIGIT_OFF  HIGH
// NOTAS DE LA CANCION ----------------------------------------------------------------------------------------
#define NOTE_C4  262   //Defining note frequency
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784
#define NOTE_A5  880
#define NOTE_B5  988
//----------------------------------------------------------------------------------------
int notes[] = {       //Note of the song, 0 is a rest/pulse
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0, 
   NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
   NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
   
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_D5, NOTE_E5, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
   NOTE_C5, NOTE_A4, NOTE_B4, 0,

   NOTE_A4, NOTE_A4, 
   //Repeat of first part
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,

   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0, 
   NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
   NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
   
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_D5, NOTE_E5, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
   NOTE_C5, NOTE_A4, NOTE_B4, 0,
   //End of Repeat

   NOTE_E5, 0, 0, NOTE_F5, 0, 0,
   NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
   NOTE_D5, 0, 0, NOTE_C5, 0, 0,
   NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,

   NOTE_E5, 0, 0, NOTE_F5, 0, 0,
   NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
   NOTE_D5, 0, 0, NOTE_C5, 0, 0,
   NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4
};
//----------------------------------------------------------------------------------------
// SEGMENTOS PARA EL DISPLAY DE 3 BITS
int segA = 2; 
int segB = 3; 
int segC = 4; 
int segD = 5; 
int segE = A0; //pin 6 is used bij display 1 for its pwm function
int segF = 7; 
int segG = 8; 
//int segPD = ; 

// ASIGNACION DE PIN DIGITAL A CADA BOTON (provisional)
int button1=13; // RESETEAR E INICIAR EL DISPLAY
int button2=12;
int button3=16;
int button4=17;

const int buzzer = 24;
const int songspeed = 1.5;

int countdown_time = 124;

// DURACION DE LAS NOTAS DE LA CANCION -------------------------------------------------------------------
int duration[] = {         //duration of each note (in ms) Quarter Note is set to 250 ms
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,

  125, 125, 250, 125, 125, 
  250, 125, 250, 125, 
  125, 125, 250, 125, 125,
  125, 125, 375, 375,

  250, 125,
  //Rpeat of First Part
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,

  125, 125, 250, 125, 125, 
  250, 125, 250, 125, 
  125, 125, 250, 125, 125,
  125, 125, 375, 375,
  //End of Repeat
  
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 125, 125, 125, 375,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 500,

  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 125, 125, 125, 375,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 500
};
//----------------------------------------------------------------------------------------
struct struct_digits { // STRUCT DONDE SE DEFINEN LOS DIGITOS
  int digit[4] = {0,0,0,0};
};


void setup() {
  Serial.begin(9600);
  // PINES SALIDA PARA EL DISPLAY
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);

  // SE DEFINEN LOS DIGITOS INICIALES DEL DISPLAY COMO 0123
  for (int i=0; i<4; i++) {
    pinMode(digit_pin[i], OUTPUT);
  }

  //PIN DE SALIDA PARA EL BUZZER
  pinMode(speakerPin, OUTPUT);

  // PINES DE ENTARDA PARA LOS BOTONES
  pinMode(button1,INPUT_PULLUP);
  pinMode(button2,INPUT_PULLUP);
  pinMode(button3,INPUT_PULLUP);
  pinMode(button4,INPUT_PULLUP);
}


void playTone(int tone, int duration) { // ALARMA PARA CUANDO SE ACABA EL TIEMPO
  for (long k = 0; k < duration * 1000L; k += tone * 2) {  
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone); 
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void lightNumber(int numberToDisplay) { // FUNCION DE NUMERO A ENCENDER
#define SEGMENT_ON  HIGH
#define SEGMENT_OFF LOW

  switch (numberToDisplay){ // OBTIENE EL NUMERO Y LO MUESTRA EN EL DISPLAY
  case 0:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 1:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 2:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 3:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 4:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 5:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 6:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 7:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 8:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 9:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 10: // NO MUESTRA NADA
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;  
  }
 
}

// APAGAR Y ENCENDER EL DIGITO DEL DISPLAY
void SwitchDigit(int digit) {
  for (int i=0; i<4; i++) {
    if (i == digit) {
      digitalWrite(digit_pin[i], DIGIT_ON);
    } else {
      digitalWrite(digit_pin[i], DIGIT_OFF);
    }
  }
}

// STRUCT 
struct struct_digits IntToDigits(int n){
  Serial.print("struct_digits n -> ");
  Serial.println(n);
  struct struct_digits dig; 
  int zeros=0;
  int d;

  // provisional
  float div = n/60;
  float minutos = floor(div);
  float segundos = floor((div - minutos)*100);
  if (minutos > 0) {
    String minutos_s = String(minutos);
    String segundos_s = String(segundos);
    if (minutos_s.length() == 2) {
      // Prepare the character array (the buffer) 
      char char_array[minutos_s.length()];
      // Copy it over 
      minutos_s.toCharArray(char_array, minutos_s.length());

      dig.digit[0] = String(char_array[0]).toInt();
      dig.digit[1] = String(char_array[1]).toInt();
    } else if (minutos_s.length() == 1) {
      //split
      dig.digit[1] = minutos_s.toInt();
    }
    if (segundos_s.length() == 2) {
      // Prepare the character array (the buffer) 
      char char_array[segundos_s.length()];
      // Copy it over 
      segundos_s.toCharArray(char_array, segundos_s.length());

      dig.digit[2] = String(char_array[0]).toInt();
      dig.digit[3] = String(char_array[1]).toInt();
    } else if (segundos_s.length() == 1) {
      //split
      dig.digit[1] = segundos_s.toInt();
    }
  } else {
    float segs = floor(div*100);
    String segundos_s = String(segs);
    if (segundos_s.length() == 2) {
      // Prepare the character array (the buffer) 
      char char_array[segundos_s.length()];
      // Copy it over 
      segundos_s.toCharArray(char_array, segundos_s.length());

      dig.digit[2] = String(char_array[0]).toInt();
      dig.digit[3] = String(char_array[1]).toInt();
    } else if (segundos_s.length() == 1) {
      //split
      dig.digit[3] = segundos_s.toInt();
    } 
  }    
  /*
  for (int i=0; i < 4; i++) {
    d = n / pow(10,3-i);
    zeros += d;
    n = n - d * pow(10,3-i);
    if (zeros != 0 || i == 3) {
      dig.digit[i]=d;
    } else {
      dig.digit[i]=10;
    }
    if(dig.digit[2] == 6){
      delay(962);
      dig.digit[2] == 0;
    }
    if(dig.digit[i] == dig.digit[2]){
      if(dig.digit[i] == 6){
        dig.digit[i] = 0;
      }
    }
    if(dig.digit[i] == dig.digit[0]){
      if(dig.digit[i] == 6){
        dig.digit[i] = 5;
      }
    }
*/
  return dig;
  
}

// IMPRIMER LOS 4 DIGITOS EN EL DISPLAY 
void PrintNumber(int n, int time) {

  struct struct_digits dig;
  dig = IntToDigits(n); // convierte el numero a un digito
  for (int i=0; i<= time/20; i++) {
    Serial.print("PrintNumber i -> ");
    Serial.println(i);
    if (digitalRead(button2)==LOW) { // BOTON 2 resetear timer
      return;
    }
    for (int j=0; j<4; j++) {
      SwitchDigit(j);
      lightNumber(dig.digit[j]); // se muestra el digito
      Serial.print("PrintNumber dig.digit[j] -> ");
      Serial.println(dig.digit[j]);
      delay(5);
    }
  }
}

bool Countdown(int n, int del){
  for (int q=n; q>0; q--){ // for donde disminuye el valor del conteo (Timer)
    PrintNumber(q,del); // se muestra el valor en el disaplay
    if (digitalRead(button2)==LOW) { // BOTON 2 de reset
      return false;
    }
  }
  PrintNumber(0,0); // el display se settea en 0 y suena la cancion
  for (int i=0;i<203;i++){ //203 is the total number of music notes in the song
    int wait = duration[i] * songspeed;
    tone(buzzer,notes[i],wait); //tone(pin,frequency,duration)
    delay(wait);}     
  return true;
}

void reset() {
  int m, zeros, d, pressed3 = 0, pressed4 = 0; // valores de 
  m=countdown_time;
  struct struct_digits dig;
  
  Serial.print("reset countdown_time -> ");
  Serial.println(countdown_time);
  Serial.print("reset countdown_time -> ");
  Serial.println(countdown_time);

  dig = IntToDigits(countdown_time); // conviente el tiempo de conteo (124 default) en un digito
  Serial.print("reset dig -> ");
  Serial.print(dig.digit[0]);
  Serial.print(" ");
  Serial.print(dig.digit[1]);
  Serial.print(" ");
  Serial.print(dig.digit[2]);
  Serial.print(" ");
  Serial.println(dig.digit[3]);

  while (digitalRead(button1)==HIGH) { // BOTON 1 -> empezar timer

    for (int j=0; j<4; j++) { // SE SETEAN LOS VALORES
      SwitchDigit(j);
      lightNumber(dig.digit[j]);
      delay(5);
    }
    
    if (digitalRead(button3)==LOW) {  // BOTON 3 -> incrementar el tiempo
      if (pressed3 == 0 || pressed3 > 30) {
        if (countdown_time > 0) {
          countdown_time -= 1 ;
        }
        dig = IntToDigits(countdown_time);
      } 
      pressed3 += 1;
    }  else if (digitalRead(button4)==LOW) {  // BOTON 4 -> decrementar el tiempo
      if (pressed4 == 0 || pressed4 > 30) {
        if (countdown_time <9999) {
          countdown_time += 1 ;
        }
        dig = IntToDigits(countdown_time);
      } 
      pressed4 += 1;
    }
    if (digitalRead(button3)==HIGH) {
      pressed3=0;
    }
    if (digitalRead(button4)==HIGH) {
      pressed4=0;
    }
    
  }
}


void loop(){
  //SwitchDigit(0);
  //lightNumber(2);
  
  reset();
  while (!Countdown(countdown_time,962)) {
    reset();
  }
  while (digitalRead(button2)==1){};
}
/*
  BOTON 1  -> START
  BOTON 2  -> RESET
  BOTON 3  -> INC
  BOTON 4  -> 
*/
 