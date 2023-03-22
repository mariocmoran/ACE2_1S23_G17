#include <math.h>

int digit_pin[] = {6, 9, 10, 11}; // PWM Display digit pins from left to right
int speakerPin = 15; // PIN DEL BUZZER

#define DIGIT_ON  LOW
#define DIGIT_OFF  HIGH

// CANCION DE FINALIZACION --------------------------------------------------------------
int tempo = 180;
#define NOTE_B0  31
  #define NOTE_C1  33
  #define NOTE_CS1 35
  #define NOTE_D1  37
  #define NOTE_DS1 39
  #define NOTE_E1  41
  #define NOTE_F1  44
  #define NOTE_FS1 46
  #define NOTE_G1  49
  #define NOTE_GS1 52
  #define NOTE_A1  55
  #define NOTE_AS1 58
  #define NOTE_B1  62
  #define NOTE_C2  65
  #define NOTE_CS2 69
  #define NOTE_D2  73
  #define NOTE_DS2 78
  #define NOTE_E2  82
  #define NOTE_F2  87
  #define NOTE_FS2 93
  #define NOTE_G2  98
  #define NOTE_GS2 104
  #define NOTE_A2  110
  #define NOTE_AS2 117
  #define NOTE_B2  123
  #define NOTE_C3  131
  #define NOTE_CS3 139
  #define NOTE_D3  147
  #define NOTE_DS3 156
  #define NOTE_E3  165
  #define NOTE_F3  175
  #define NOTE_FS3 185
  #define NOTE_G3  196
  #define NOTE_GS3 208
  #define NOTE_A3  220
  #define NOTE_AS3 233
  #define NOTE_B3  247
  #define NOTE_C4  262
  #define NOTE_CS4 277
  #define NOTE_D4  294
  #define NOTE_DS4 311
  #define NOTE_E4  330
  #define NOTE_F4  349
  #define NOTE_FS4 370
  #define NOTE_G4  392
  #define NOTE_GS4 415
  #define NOTE_A4  440
  #define NOTE_AS4 466
  #define NOTE_B4  494
  #define NOTE_C5  523
  #define NOTE_CS5 554
  #define NOTE_D5  587
  #define NOTE_DS5 622
  #define NOTE_E5  659
  #define NOTE_F5  698
  #define NOTE_FS5 740
  #define NOTE_G5  784
  #define NOTE_GS5 831
  #define NOTE_A5  880
  #define NOTE_AS5 932
  #define NOTE_B5  988
  #define NOTE_C6  1047
  #define NOTE_CS6 1109
  #define NOTE_D6  1175
  #define NOTE_DS6 1245
  #define NOTE_E6  1319
  #define NOTE_F6  1397
  #define NOTE_FS6 1480
  #define NOTE_G6  1568
  #define NOTE_GS6 1661
  #define NOTE_A6  1760
  #define NOTE_AS6 1865
  #define NOTE_B6  1976
  #define NOTE_C7  2093
  #define NOTE_CS7 2217
  #define NOTE_D7  2349
  #define NOTE_DS7 2489
  #define NOTE_E7  2637
  #define NOTE_F7  2794
  #define NOTE_FS7 2960
  #define NOTE_G7  3136
  #define NOTE_GS7 3322
  #define NOTE_A7  3520
  #define NOTE_AS7 3729
  #define NOTE_B7  3951
  #define NOTE_C8  4186
  #define NOTE_CS8 4435
  #define NOTE_D8  4699
  #define NOTE_DS8 4978
  #define REST      0

int melody[] = {
  NOTE_E5, 8, NOTE_D5, 8, NOTE_FS4, 4, NOTE_GS4, 4, 
  NOTE_CS5, 8, NOTE_B4, 8, NOTE_D4, 4, NOTE_E4, 4, 
  NOTE_B4, 8, NOTE_A4, 8, NOTE_CS4, 4, NOTE_E4, 4,
  NOTE_A4, 2, 
};
int notes = sizeof(melody) / sizeof(melody[0]) / 2;
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;

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
int button1=13; // INICIAR EL DISPLAY
int button2=12; // RESETEAR EL DISPLAY
int button3=16; // DURACION TOTAL POMODORO
int button4=17;
//----------------------------------------------------------------------------------------
const int buzzer = 24;// ALARMA BUZZER
int dimmer = A1; // LECTURA DEL DIMMER
bool working = false;
//----------------------------------------------------------------------------------------
int countdown_time = 45; // TIEMPO DE TRABAJO DEFAULT
int rest_time = 15; // TIEMPO DE DESCANSO DEFAULT
int total_time = 1; // TIEMPO TOTAL DEL POMODORO EN MINUTOS
//----------------------------------------------------------------------------------------
struct struct_digits { // STRUCT DONDE SE DEFINEN LOS DIGITOS
  int digit[4] = {0,0,0,0};
};

void stopWorkingAlarm(){
  tone(buzzer,2000,500); //tone(pin,frequency,duration)
  delay(900);
  tone(buzzer,2000,500); //tone(pin,frequency,duration)
  delay(900);
  tone(buzzer,2000,500); //tone(pin,frequency,duration)
  delay(900);
  tone(buzzer,2000,500); //tone(pin,frequency,duration)
  delay(900);
  tone(buzzer,2000,500); //tone(pin,frequency,duration)
}

void startWorkingAlarm(){
  tone(buzzer,1500,2000); //tone(pin,frequency,duration)
  delay(2000);
  tone(buzzer,1500,2000); //tone(pin,frequency,duration)
}

void finishAlarm(){
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }
    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration * 0.9);
    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
}

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
  //PIN ENTRADA ANALOGICA DEL DIMMER

  // PINES DE ENTARDA PARA LOS BOTONES
  pinMode(button1,INPUT_PULLUP);
  pinMode(button2,INPUT_PULLUP);
  pinMode(button3,INPUT_PULLUP);
  pinMode(button4,INPUT_PULLUP);
}

// ENCENDER LOS SEGMENTOS DEL DISPLAY
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
      String n1 = minutos_s.substring(0,1);
      String n2 = minutos_s.substring(1,2);
      /*
      Serial.print("string segundos n1 n2 -> ");
      Serial.print(n1);
      Serial.print(" ");
      Serial.print(n2);*/
      dig.digit[0] = n1.toInt();
      dig.digit[1] = n2.toInt();
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
 
// TEMPORIZADOR
bool Countdown(int n, int del){
  for (int q=n; q>0; q--){ // for donde disminuye el valor del conteo (Timer)
    Serial.print("countdown -> "); Serial.println(q);
    PrintNumber(q,del); // se muestra el valor en el display
    Serial.print("button 2 respones -> "); Serial.println(digitalRead(button2));
    if (digitalRead(button2)==LOW) { // BOTON 2 de reset
      return false;
    }
  }
  return true;
}

// CONVERSION SEÑAL DIMMER -> MINUTOS
void setTotalTime(int dimmer_val) {
  if (dimmer_val == 0) {
    total_time = 1;  
  } else {
    total_time = ceil(((float)dimmer_val/1023)*45);  
  }
}

// FUNCION DE RESET
void reset() {
  int m, zeros, d, pressed3 = 0, pressed4 = 0; // valores de 
  m=countdown_time;
  struct struct_digits dig, dig2;
  Serial.print("reset countdown_time -> "); Serial.println(countdown_time);

  dig = IntToDigits(countdown_time); // conviente el tiempo de conteo (124 default) en un digito
  dig2 = IntToDigits(rest_time);

  bool ajuste_duracion = false;

  while (digitalRead(button1)==HIGH) { // BOTON 1 -> empezar timer
    // RESET FUNCION ---------------------------\*
    PrintNumber(countdown_time, 1000);
    PrintNumber(rest_time, 1000);
    // FIN RESET FUNCION ----------------------/*
    // INCIO DEL ESPACIO DEL DIMMER
    if (digitalRead(button3)==LOW) {
      ajuste_duracion = true;
      delay(2000);
    }
    while (ajuste_duracion) {
      int duracion_total_s = total_time*60;
      PrintNumber(duracion_total_s, 500);
      int value = analogRead(dimmer);
      setTotalTime(value);
      if (digitalRead(button3)==LOW) {
        ajuste_duracion = false;
      }
    }
    // FIN DEL ESPACIO DEL DIMMER
  }
}

void loop(){
  //SwitchDigit(0);
  //lightNumber(2);
  inicio:
    reset();
    //PRIMER POMODORO
    startWorkingAlarm();
    while (!Countdown(countdown_time,962)) {
      reset();
    }
    stopWorkingAlarm();
    while (!Countdown(rest_time,962)) {
      goto inicio;
    }
    //SEGUNDO POMODORO
    startWorkingAlarm();
    while (!Countdown(countdown_time,962)) {
      goto inicio;
    }
    stopWorkingAlarm();
    while (!Countdown(rest_time,962)) {
      goto inicio;
    }
    //TERCER POMODORO
    startWorkingAlarm();
    while (!Countdown(countdown_time,962)) {
      goto inicio;
    }
    stopWorkingAlarm();
    while (!Countdown(rest_time,962)) {
      goto inicio;
    }
    //CUARTO POMODORO
    startWorkingAlarm();
    while (!Countdown(countdown_time,962)) {
      goto inicio;
    }
    finishAlarm();
    while (digitalRead(button2)==1){};
}

/*
  BOTON 1  -> START
  BOTON 2  -> RESET
  BOTON 3  -> AJUSTE TIEMPO TOTAL
  BOTON 4  -> 
*/
 