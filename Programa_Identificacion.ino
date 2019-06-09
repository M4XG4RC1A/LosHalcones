

//2 juego 1
//3 juego 2
//4 juego 3
//6 End

#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

#define RST_PIN         5      
#define SS_PIN          53

MFRC522 mfrc522(SS_PIN, RST_PIN); 

byte LecturaUID[4];
byte Usuario1[4]= {0xDE, 0x83, 0x97, 0x59};  //Tarjeta
byte Usuario2[4]= {0x3D, 0x83, 0x4C, 0x79};  //Llavero 1
byte Usuario3[4]= {0x07, 0xF7, 0x4F, 0x13};  //Llavero 2

String Usuario[] = {" ", "Max", "Jorge", "Chava"};

int Puntaje[] = {0,0,0};
int U = 0;
int PuntosG = 0;

boolean State = true;

const int pinecho = 22;
const int pintrigger = 23;
const int pinecho1 = 24;
const int pintrigger1 = 25;
const int pinecho2 = 26;
const int pintrigger2 = 27;
 
unsigned int tiempo;
double distancia;
double distancia1;
double distancia2;

int PuntajeJ2[5] = {0,40,10,10,20};
int PuntajeJ2P1 = 40;
int PuntajeJ2P2 = 10;
int PuntajeJ2P3 = 10;
int PuntajeJ2P4 = 20;
int Repeticiones = 0;
int Juego2 = random(1,4);
int PuntJ2 = 0;
int C = 0;

const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Listo");
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(6,INPUT);
  pinMode(28, OUTPUT);
  pinMode(29, OUTPUT);
  pinMode(30, OUTPUT);
  pinMode(31, OUTPUT);
  pinMode(pinecho, INPUT);
  pinMode(pintrigger, OUTPUT);
  pinMode(pinecho1, INPUT);
  pinMode(pintrigger1, OUTPUT);
  pinMode(pinecho2, INPUT);
  pinMode(pintrigger2, OUTPUT);
  lcd.setCursor(0, 0);
  lcd.print("    Hexaware    ");
  lcd.setCursor(0, 1);
  lcd.print("  Technologies  ");
}

void loop() {
  if(millis()%4000 == 0){
    lcd.setCursor(0, 0);
    lcd.print("    Hexaware    ");
    lcd.setCursor(0, 1);
    lcd.print("  Technologies  ");
  }else if(millis()%2000 == 0){
    lcd.setCursor(0, 0);
    lcd.print("     Visit:     ");
    lcd.setCursor(0, 1);
    lcd.print("  hexaware.com  ");
  }
  if ( ! mfrc522.PICC_IsNewCardPresent()){
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()){
    return;
  }
    Serial.print("UID: ");
    for(byte i = 0; i < mfrc522.uid.size; i++){  //No se pone 4 de 4 bytes que siempre hay ya que hay unos que tienen 7 bytes
      if (mfrc522.uid.uidByte[i] < 0x10){ // es para leer en bytes osea en hexadecimal, ya que si es >0x10 osea 09 no se muestra 09 se muestra 9 que hara incomodo leer
        Serial.print(" 0");
        }
        else{
          Serial.print(" ");
        }
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        LecturaUID[i]=mfrc522.uid.uidByte[i];
      }

      Serial.print("\t");

      if(comparaUID(LecturaUID, Usuario1)){
        Serial.println("Bienvenido Usuario 1");
        U = 1;
      }else
      if(comparaUID(LecturaUID, Usuario2)){
        Serial.println("Bienvenido Usuario 2");
        U = 2;
      }else
      if(comparaUID(LecturaUID, Usuario3)){
        Serial.println("Bienvenido Usuario 3");
        U = 3;
      }else{
        Serial.println("No Reconocido");
        U = 0;
      }
      
      mfrc522.PICC_HaltA(); //Halt=detener

      if(U != 0){
        Serial.println("Hola "+ Usuario[U] +", ¿que juego quieres jugar?");
        Serial.println("Tu puntaje es "+ Puntaje[U]);
        Serial.println("Selecciona un juego");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("      Hola      ");
        lcd.setCursor(2, 1);
        lcd.print(Usuario[U]);
        delay(4000);
        lcd.setCursor(0, 0);
        lcd.print("   Selecciona   ");
        lcd.setCursor(0, 1);
        lcd.print("      Juego     ");
        char juego = ' ';
        while(juego == ' '){
          juego = Serial.read();
        }
        Serial.println("Elegiste Juego ");
        Serial.println(juego);
        switch(juego){
          case 'a':
          while(State){
            lcd.setCursor(0, 0);
            lcd.print("    Jugando    ");
            lcd.setCursor(0, 1);
            lcd.print("               ");
          digitalWrite(pintrigger, LOW);
          delayMicroseconds(2);
          digitalWrite(pintrigger, HIGH);
          delayMicroseconds(10);
          digitalWrite(pintrigger, LOW);
          tiempo = pulseIn(pinecho, HIGH);
          distancia = tiempo / 58;
          Serial.print(distancia);
          Serial.println(" cm");
          if(distancia < 7){
            Serial.println("Caso 1");
            PuntosG = 50;
            Serial.println(PuntosG);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("    Ganaste    ");
            lcd.setCursor(0, 1);
            lcd.print("       50       ");
            delay(1000);
          }else if(distancia < 14){
            Serial.println("Caso 2");
            PuntosG = 100;
            Serial.println(PuntosG);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("    Ganaste    ");
            lcd.setCursor(0, 1);
            lcd.print("       100      ");
            delay(1000);
          }else if(distancia < 17.95){
            Serial.println("Caso 3");
            PuntosG = 0;
            Serial.println(PuntosG);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("    Ganaste    ");
            lcd.setCursor(0, 1);
            lcd.print("        0       ");
            delay(1000);
          }
          delay(100);
          Puntaje[U] = Puntaje[U] + PuntosG;
          PuntosG = 0;
          if(Serial.read() == 's'){
            State = false;
          }
          }
          State = true;
          Serial.println("Gracias por jugar");
          delay(2000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("    Tienes     ");
          lcd.setCursor(4, 1);
          lcd.print(Puntaje[U]);
          Serial.println("Puntos Actuales "+ Puntaje[U]);
          break;


          case 'b':
          
          while(State){
            lcd.setCursor(0, 0);
            lcd.print("    Jugando    ");
            lcd.setCursor(0, 1);
            lcd.print("               ");
          if(PuntJ2 != 0 || C%3000 == 0){
    Juego2 = random(1,4);
    C = 0;
    Puntaje[U] = Puntaje[U] + PuntJ2;
    PuntJ2 = 0;
    digitalWrite(28,LOW);
    digitalWrite(29,LOW);
    digitalWrite(30,LOW);
    digitalWrite(31,LOW);
    delay(500);
    
  }  
  boolean Estado = true;
  digitalWrite(pintrigger1, LOW);
  delayMicroseconds(2);
  digitalWrite(pintrigger1, HIGH);
  delayMicroseconds(10);
  digitalWrite(pintrigger1, LOW);
  tiempo = pulseIn(pinecho1, HIGH);
  distancia1 = tiempo / 58;
  Serial.print(distancia1);
  Serial.println(" cm");
  delay(25);
  digitalWrite(pintrigger2, LOW);
  delayMicroseconds(2);
  digitalWrite(pintrigger2, HIGH);
  delayMicroseconds(10);
  digitalWrite(pintrigger2, LOW);
  tiempo = pulseIn(pinecho2, HIGH);
  distancia2 = tiempo / 58;
  Serial.print(distancia2);
  Serial.println(" cm");
  delay(25);
  PuntJ2 = Comparar(Juego2, distancia1, distancia2);
  C = C+50;  
  if(Serial.read() == 's'){
            State = false;
          }
}
State = true;
digitalWrite(28,LOW);
    digitalWrite(29,LOW);
    digitalWrite(30,LOW);
    digitalWrite(31,LOW);
          Serial.println("Gracias por jugar");
          delay(2000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("    Tienes     ");
          lcd.setCursor(4, 1);
          lcd.print(Puntaje[U]);
          Serial.println("Puntos Actuales "+ Puntaje[U]);
          break;

          
          default:
          Serial.println("No se encontro el juego :(");
          break;
        }
        }
      }

  boolean comparaUID(byte lectura[], byte usuario[]){
    for (byte i=0; i < mfrc522.uid.size; i++){
      if(lectura[i] != usuario[i]){
        return(false);
      }
      return(true);
    }
  }

  int Comparar(char Ram,int R1, int R2){
  switch(Ram){
    case 1:
    digitalWrite(28,HIGH);
    if(R1 > 10 && R1 < 16){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    Ganaste    ");
      lcd.setCursor(7, 1);
      lcd.print(PuntajeJ2[1]);
      return PuntajeJ2[1];
    }
    break;
    case 2:
    digitalWrite(29,HIGH);
    if(R1 > 0 && R1 < 9){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    Ganaste    ");
      lcd.setCursor(7, 1);
      lcd.print(PuntajeJ2[2]);
      return PuntajeJ2[2];
    }
    break;
    case 3:
    digitalWrite(30,HIGH);
    if(R2 > 10 && R2 < 16){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    Ganaste    ");
      lcd.setCursor(7, 1);
      lcd.print(PuntajeJ2[3]);
      return PuntajeJ2[3];
    }
    break;
    case 4:
    digitalWrite(31,HIGH);
    if(R2 > 0 && R2 < 9){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    Ganaste    ");
      lcd.setCursor(7, 1);
      lcd.print(PuntajeJ2[4]);
      return PuntajeJ2[4];
    }
    break;
    default:
    
    break;
  }
  return 0;
}
