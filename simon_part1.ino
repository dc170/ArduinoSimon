


#include <SPI.h>

// Definicions dels pins
const int green = 10;
const int blue = 9;
const int red = 5;

const int interval = 1000; // led interval


int c = 0;
const int MAX = 20; //Aqui podem configurar la llargada maxima de la secuencia
int joc[MAX];

int ran;

void setup() {                
  //Configurar la placa amb entrades i sortides
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(A4,INPUT);
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  //Configurar por serie per si cal fer alguna comprovacio
  Serial.begin(9600);
  randomSeed(analogRead(0));//seed del random, el pin 0 no esta conectat, el "soroll" que hi haura doncs, permetra un random bo
}

bool top() {
  digitalWrite(A0, LOW);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  return analogRead(A4)==LOW;//actiu a nivell baix

}

bool down() {
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  return analogRead(A4) ==LOW;
}

bool left() {
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  return analogRead(A4) ==LOW;
}

bool right() {
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  return analogRead(A4) ==LOW;
}

void vermell() {
  digitalWrite(red, HIGH);
  delay(1000);
  digitalWrite(red, LOW);
  
}

void verd() {
  digitalWrite(green, HIGH);
  delay(1000);
  digitalWrite(green, LOW);
  
}

void blau() {
  digitalWrite(blue, HIGH);
  delay(1000);
  digitalWrite(blue, LOW);
  
}

void groc() {
  digitalWrite(green, HIGH);
  digitalWrite(red, HIGH);
  delay(1000);
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
}

void mostrarSecuencia(int limit){
  //Mostrem la secuencia guardada fins el moment
  delay(500);
  for(int i=0;i<=limit;i++){
    if(joc[i]==0){
      verd();
      delay(500); // hi ha un petit delay per poder visualitzar be la secuencia
    }
    else if(joc[i]==1){
      blau();
      delay(500);
    }
    else if(joc[i]==2){
      vermell();
      delay(500);
    }
    else if(joc[i]==3){
      groc();
      delay(500);
    }
  }
  
}

void resetJoc(){
  //Fem un reset del joc, el comptador queda a zero i mostrem una secuencia de leds vermells
  c = 0;
  vermell();
  delay(500);
  vermell();
  delay(500);
  vermell();
  delay(500);
}

void victoriaFinal(){
  //Mostrem secuencia de 3 leds verds amb poc delay per indicar clarament que s'ha guanyat
  verd();
  delay(250);
  verd();
  delay(250);
  verd();
  delay(250);
}
//0 VERD, 1 BLAU, 2 VERRMELL, 3 GROC
void loop(){
  //randomSeed(millis()); seria una altre manera de fer random 
  ran = random(4); //random de 0 a 3
  joc[c]=ran; //afegim la jugada
  mostrarSecuencia(c); //mostrem la secuencia fins al moment
  
  int i = 0;
  boolean encert = true; //partim de que s'ha encertat
  while(i <= c && encert){ //Es un esquema de cerca! Se surt quan es falla
    int jugada = 4; //inicialitzem a 4 ja que per exemple a 4 no hi tenim cap color
    while(jugada==4){
      if(top()){
        while(top()){//mentre es premi el boto es mostrara el color aixi l'usuari "te temps per jugar"
          verd();
        }
        jugada = 0;
      }
      else if(left()){
        while(left()){
          blau();
        }
        jugada = 1;
      }
      else if(right()){
        while(right()){
          vermell();
        }
        jugada = 2;
      }
      else if(down()){
        while(down()){
          groc();
        }
        jugada = 3;
      }
    }
    if(joc[i]!=jugada){//si no coincideix encert pasa a fals i se surt de la "partida"
      encert = false;
    }
    else{//si s'ha encertat, seguim comprovant el seguent
      i++;
    }
  }
  
  if(!encert){//Si s'ha fallat o hem arribat al maxim reiniciem el joc
    resetJoc();
  }
  else if(c==MAX){
    victoriaFinal();
    resetJoc();
  }
  else{//Si s'ha encertat la secuencia afegim un element mes!
    c++;
  }
  
  
}

