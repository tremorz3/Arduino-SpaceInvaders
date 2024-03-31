#include<Arduino.h>
#include<U8g2lib.h>
#include<Wire.h>

int xship = 64;
const int yship = 60;

int xshot;
int yshot;
bool FIRING = false;

int xalien;
int yalien;
bool ALIEN = false;

bool COLLISION = false;

unsigned long int t1,dt;

int points = 0;
char pts[5];
char gameover[9];

const int pinBuzzer = 8;  //pin del buzzer

const int frequenzaSparo = 1000;  //frequenza del suono dello sparo
const int durataSparo = 100;  //durata del suono dello sparo

const int frequenzaEsplosione = 250;  //frequenza del suono dell'esplosione
const int durataEsplosione = 50;  //durata del suono dell'esplosione

bool REVERSE = false;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);

void setup(){
  pinMode(pinBuzzer, OUTPUT);
  pinMode(6,INPUT);
  Serial.begin(9600);

  u8g2.begin();
  randomSeed(analogRead(A0));
  u8g2.setFont(u8g2_font_unifont_t_symbols);
}

void loop(){
  int statoPulsante = digitalRead(6);

  u8g2.clearBuffer();

  int valoreX = analogRead(A0);
  xship = map(valoreX,0,1024,5,123);

  //sparo
  if(statoPulsante && !FIRING){
    FIRING = true;
    xshot = xship;
    yshot = yship - 5;
    riproduciSparo();
  }

  //astronave         punto a sx           punto a dx       punta della nave
  u8g2.drawTriangle(xship - 5,yship,    xship + 5,yship,    xship,yship - 5);

  //missile
  if(FIRING){     //coordinate di inizio      coordinate di fine    dello sparo
    u8g2.drawLine(  xshot,yshot,                xshot,yshot - 5);
    yshot -= 5;
    if(yshot <= 5)FIRING = false;
  }

  //alieno
  if(!ALIEN){
    ALIEN = true;
    xalien = random(0,123);
    yalien = 10;
  }
  
  //movimento e gestione alieno 
  if(ALIEN){
    u8g2.drawGlyph(xalien,yalien,0x2606);
    if(!COLLISION && yalien < yship){
      if(!REVERSE){
        xalien += 4;
      }

      if(REVERSE){
        xalien -= 4;
      }

      if(!COLLISION && xalien >= 120){
        REVERSE = true;
      }

      if(!COLLISION && xalien < 5){
        REVERSE = false;
      }

      if(random(3) == 1){yalien += 1;}
    }

    //gameover
    if(!COLLISION && yalien >= yship){
      ALIEN = false;
      points = 0;
    }
    
  }

  //collisione
  if(FIRING && ALIEN && 
    (xshot >= xalien) && (xshot <= xalien + 8) &&
    (yshot - 5 <= yalien + 8) && (yshot - 5 >= yalien)){
      //ALIEN = false;
      COLLISION = true;
      FIRING = false;
      t1 = millis(); 
  }

  //esplosione
  if(COLLISION){
    u8g2.drawCircle(xalien + 4,yalien - 4,5,U8G2_DRAW_ALL);
    u8g2.drawCircle(xalien + 4,yalien - 4,8,U8G2_DRAW_ALL);
    dt = millis() - t1;
    if(dt >= 250){
      ALIEN = false;
      COLLISION = false;
      points++;
    }
    riproduciEsplosione();
  }

  //punteggio
  sprintf(pts,"%3d",points);
  u8g2.drawStr(1,10,pts);

  u8g2.sendBuffer();
  delay(50);
}

void riproduciSparo() {
  tone(pinBuzzer, frequenzaSparo, durataSparo);  //genera il suono

  int t = millis();
  if(millis() - t >= durataSparo) //tempo di durata del suono
    noTone(pinBuzzer); //interrompe il suono
}

void riproduciEsplosione() {
  tone(pinBuzzer, frequenzaEsplosione, durataEsplosione);

  int t = millis();
  if(millis() - t >= durataEsplosione)
    noTone(pinBuzzer);
}
