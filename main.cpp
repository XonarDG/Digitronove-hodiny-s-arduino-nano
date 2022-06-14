#include <Arduino.h>
#include <SPI.h>
#include "RTClib.h"
#include <Wire.h>

//desetihodinový digitron
#define A1 2
#define B1 5
#define C1 2
#define D1 4

//hodinový digitron
#define A2 9
#define B2 8
#define C2 7
#define D2 6

//desetiminutový digitron
#define A3 10
#define B3 12
#define C3 13
#define D3 11

//minutový digitron
#define A4 14
#define B4 16
#define C4 17
#define D4 15

//blikajicí dvojtečka mezi dvojčíslím WIP
#define dvojtecka 20

char A[4] = {A1, A2, A3, A4};
char B[4] = {B1, B2, B3, B4};
char C[4] = {C1, C2, C3, C4};
char D[4] = {D1, D2, D3, D4};

//deklarace zkratky rtc
RTC_DS3231 rtc;

int pocitadlo = 0;

//pravdivostní tabulka pro MH74141 IC
void NapisCislo(int a, int b) {
  switch (b) {
    case 0:
      digitalWrite(A[a], LOW);
      digitalWrite(B[a], LOW);
      digitalWrite(C[a], LOW);
      digitalWrite(D[a], LOW);
      break;
    case 9:
      digitalWrite(A[a], HIGH);
      digitalWrite(B[a], LOW);
      digitalWrite(C[a], LOW);
      digitalWrite(D[a], HIGH);
      break;
    case 8:
      digitalWrite(A[a], LOW);
      digitalWrite(B[a], LOW);
      digitalWrite(C[a], LOW);
      digitalWrite(D[a], HIGH);
      break;
    case 7:
      digitalWrite(A[a], HIGH);
      digitalWrite(B[a], HIGH);
      digitalWrite(C[a], HIGH);
      digitalWrite(D[a], LOW);
      break;
    case 6:
      digitalWrite(A[a], LOW);
      digitalWrite(B[a], HIGH);
      digitalWrite(C[a], HIGH);
      digitalWrite(D[a], LOW);
      break;
    case 5:
      digitalWrite(A[a], HIGH);
      digitalWrite(B[a], LOW);
      digitalWrite(C[a], HIGH);
      digitalWrite(D[a], LOW);
      break;
    case 4:
      digitalWrite(A[a], LOW);
      digitalWrite(B[a], LOW);
      digitalWrite(C[a], HIGH);
      digitalWrite(D[a], LOW);
      break;
    case 3:
      digitalWrite(A[a], HIGH);
      digitalWrite(B[a], HIGH);
      digitalWrite(C[a], LOW);
      digitalWrite(D[a], LOW);
      break;
    case 2:
      digitalWrite(A[a], LOW);
      digitalWrite(B[a], HIGH);
      digitalWrite(C[a], LOW);
      digitalWrite(D[a], LOW);
      break;
    case 1:
      digitalWrite(A[a], HIGH);
      digitalWrite(B[a], LOW);
      digitalWrite(C[a], LOW);
      digitalWrite(D[a], LOW);
      break;
  }
}
void VypisJednaAzDevet(){
  for (size_t i = 0; i < 2; i++)
  {  
  for (size_t i = 0; i < 10; i++)
  {
    NapisCislo(0, i);
    NapisCislo(1, i);
    NapisCislo(2, i);
    NapisCislo(3, i);
    delay(75);
  }
  }

}

void OchranaKatod(int des_sec, int sec){

if (des_sec + sec == 0)
{
  VypisJednaAzDevet();
}

}

/*void OchranaKatodJinak(){

  if (pocitadlo == 120)
  {
    VypisJednaAzDevet();
    pocitadlo = 0;
  }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
} */

void setup() {
  Serial.begin(9600);

//přízak pro zahájení komunikace s RTC modulem
  rtc.begin();

//testovací kód pro RTC modul
/*#ifndef ESP8266
  while (!Serial);
#endif

 if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  } */
  //rtc.adjust(DateTime(2022, 1, 17, 11, 0, 0));

  //kód pro nastavení času RTC(nastaví se čas ve kterém se kód zkopiloval)
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  

//nastavení výstupů
pinMode(A1, OUTPUT);
pinMode(B1, OUTPUT);
pinMode(C1, OUTPUT);
pinMode(D1, OUTPUT);
pinMode(A2, OUTPUT);
pinMode(B2, OUTPUT);
pinMode(C2, OUTPUT);
pinMode(D2, OUTPUT);
pinMode(A3, OUTPUT);
pinMode(B3, OUTPUT);
pinMode(C3, OUTPUT);
pinMode(D3, OUTPUT);
pinMode(A4, OUTPUT);
pinMode(B4, OUTPUT);
pinMode(C4, OUTPUT);
pinMode(D4, OUTPUT);
pinMode(dvojtecka, OUTPUT);

                                                  //nastavení všech výstupů na pozici 0 (důležité protože nepopsané vstupy můžou poškodit BCD dekódery)
  for (char i = 0; i < 4; i++) {
    digitalWrite(A[i], LOW);
    digitalWrite(B[i], LOW);
    digitalWrite(C[i], LOW);
    digitalWrite(D[i], LOW);
  } 
}

void loop() {
DateTime cas = rtc.now();

int desitkova_hodina = 0;
int hodina = 0;
int desitkova_minuta = 0;
int minuta = 0;
int desitkova_sekunda = 0;                       //odkomentovat v případě použití sekudnových číslic
int sekunda = 0;                                 //odkomentovat v případě použití sekudnových číslic

if (sekunda < 10)                                //odkomentovat v případě použití sekudnových číslic
{
  desitkova_sekunda = sekunda + 0;
}

//převod času z DS3231 na jednotlivé číslice
desitkova_hodina = (cas.hour() / 10) % 10;         
hodina = (cas.hour() % 10);
desitkova_minuta = (cas.minute() / 10) % 10;
minuta = (cas.minute() % 10);
desitkova_sekunda = (cas.second() / 10) % 10;     //odkomentovat v případě použití sekudnových číslic
sekunda = (cas.second());                         //odkomentovat v případě použití sekudnových číslic

//Serial feedback
Serial.print(desitkova_hodina, DEC);
Serial.print("/");
Serial.print(hodina, DEC);
Serial.print(":");
Serial.print(desitkova_minuta, DEC);
Serial.print("/");
Serial.print(minuta, DEC);
Serial.print(":");                                //odkomentovat v případě použití sekudnových číslic
if (sekunda < 10)
{
  Serial.print(desitkova_sekunda, DEC);
}
Serial.print("/");
Serial.print(sekunda, DEC);                       //odkomentovat v případě použití sekudnových číslic

Serial.println();


OchranaKatod(desitkova_sekunda, sekunda);
//OchranaKatodJinak();

//výpis čísel pomocí metody NapisCislo(pořadí, zobrazované číslo)
NapisCislo(0, desitkova_hodina);
NapisCislo(1, hodina);
NapisCislo(2, desitkova_minuta);
NapisCislo(3, minuta);

delay(1000);
pocitadlo = pocitadlo +1;
}

void off(int a) {
  digitalWrite(A[a], HIGH);
  digitalWrite(B[a], LOW);
  digitalWrite(C[a], LOW);
  digitalWrite(D[a], LOW);
}