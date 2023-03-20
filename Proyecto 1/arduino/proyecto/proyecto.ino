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

int countdown_time = 90;
int rest_time = 30;
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
  float div = (float)n/60;
  int minutos = (int)floor(div);
  int segundos = (int)round((div - minutos)*60);
  
  /*Serial.print("minutos -> ");
  Serial.println(minutos);
  Serial.print("segundos -> ");
  Serial.println(segundos);*/
  if (minutos > 0) {
    String minutos_s = String(minutos);
    String segundos_s = String(segundos);
    /*Serial.print("string minutos -> ");
    Serial.println(minutos_s);
    Serial.print("string segundos -> ");
    Serial.println(segundos_s);*/
    //Serial.print("minutos length -> ");
    //Serial.println(minutos_s.length());
    if (minutos_s.length() == 2) {
      // Prepare the character array (the buffer) 
      char char_array[minutos_s.length()];
      // Copy it over 
      minutos_s.toCharArray(char_array, minutos_s.length());
      /*
      Serial.print("char minutos -> ");
      Serial.print(char_array[0]);
      Serial.print(" ");
      Serial.println(char_array[0]);*/
      dig.digit[0] = String(char_array[0]).toInt();
      dig.digit[1] = String(char_array[1]).toInt();
    } else if (minutos_s.length() == 1) {
      //split      
      dig.digit[1] = minutos_s.toInt();
      /*Serial.print("char minutos digit - toint-> ");
      Serial.print(dig.digit[1]);
      Serial.print(" ");
      Serial.println(minutos_s.toInt());*/
    }
    //Serial.print("segundos length -> ");
    //Serial.println(segundos_s.length());
    if (segundos_s.length() == 2) {
      // prueba
      String n1 = segundos_s.substring(0,1);
      String n2 = segundos_s.substring(1,2);
      /*
      Serial.print("string segundos n1 n2 -> ");
      Serial.print(n1);
      Serial.print(" ");
      Serial.print(n2);*/
      dig.digit[2] = n1.toInt();
      dig.digit[3] = n2.toInt();
    } else if (segundos_s.length() == 1) {
      //split
      dig.digit[3] = segundos_s.toInt();
    }
  } else {
    int segs = (int)round(div*60);
    String segundos_s = String(segs);
    //Serial.print("segundos ### 2 -> "); Serial.println(segundos_s);
    if (segundos_s.length() == 2) {      // prueba
      String n1 = segundos_s.substring(0,1);
      String n2 = segundos_s.substring(1,2);
      /*
      Serial.print("string segundos n1 n2 -> ");
      Serial.print(n1);
      Serial.print(" ");
      Serial.print(n2);*/
      dig.digit[2] = n1.toInt();
      dig.digit[3] = n2.toInt();
    } else if (segundos_s.length() == 1) {
      //split
      dig.digit[3] = segundos_s.toInt();
    } 
  }
  return dig;
}

// IMPRIMER LOS 4 DIGITOS EN EL DISPLAY 
void PrintNumber(int n, int time) {
  struct struct_digits dig;
  dig = IntToDigits(n); // convierte el numero a un digito
  //Serial.print("PrintNumber IntToDigits dig -> "); Serial.print(dig.digit[0]); Serial.print(" "); Serial.print(dig.digit[1]); 
  //Serial.print(" "); Serial.print(dig.digit[2]); Serial.print(" "); Serial.println(dig.digit[3]); 
  int tm = time/20;
  //Serial.print("PrintNumber time /// tm -> "); Serial.print(time); Serial.print(" /// "); Serial.print(tm);
  for (int i=0; i<= tm; i++) {
    //Serial.print("PrintNumber i -> "); Serial.println(i);
    if (digitalRead(button2)==LOW) { // BOTON 2 resetear timer
      return;
    }
    for (int j=0; j<4; j++) {
      SwitchDigit(j);
      lightNumber(dig.digit[j]); // se muestra el digito
      //Serial.print("PrintNumber dig.digit[j] -> ");
      //Serial.println(dig.digit[j]);
      delay(5);
    }
  }
}

bool Countdown(int n, int del){
  for (int q=n; q>0; q--){ // for donde disminuye el valor del conteo (Timer)
    Serial.print("countdown -> "); Serial.println(q);
    PrintNumber(q,del); // se muestra el valor en el display
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
  struct struct_digits dig, dig2;
  Serial.print("reset countdown_time -> "); Serial.println(countdown_time);

  dig = IntToDigits(countdown_time); // conviente el tiempo de conteo (124 default) en un digito
  dig2 = IntToDigits(rest_time);

  while (digitalRead(button1)==HIGH) { // BOTON 1 -> empezar timer
    // RESET FUNCION ---------------------------\*
    delay(2000);
    for (int j=0; j<4; j++) { // SE RESETEAN LOS VALORES
      SwitchDigit(j);
      lightNumber(dig.digit[j]);
      delay(5);
    }
    delay(2000);
    for (int j=0; j<4; j++) { // SE RESETEAN LOS VALORES
      SwitchDigit(j);
      lightNumber(dig2.digit[j]);
      delay(5);
    }
    // FIN RESET FUNCION ----------------------/*
    // INCIO DEL ESPACIO DEL DIMMER
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
    // FIN DEL ESPACIO DEL DIMMER
    if (digitalRead(button3)==HIGH) { // BOTON 3 -> INCREMENTAR
      pressed3=0;
    }
    if (digitalRead(button4)==HIGH) { // BOTON 4 -> DECREMENTAR
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
 