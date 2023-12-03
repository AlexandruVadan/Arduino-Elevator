#include<Stepper.h>

int stepIN1Pin = 8;
int stepIN2Pin = 9;
int stepIN3Pin = 10;
int stepIN4Pin = 11;
int rotatii=2048;

int buton1Pin=2;
int buton2Pin=3;
int buton3Pin=4;
int trig=5;
int echo=6;
int var;
int distanta;
int a=A1;
int b=A0;
int c=A3;
int d=A4;
int e=A5;
int g=A2;
Stepper myStepper(rotatii, stepIN1Pin, stepIN3Pin, stepIN2Pin, stepIN4Pin);

void urcaNivel(){//functie urca de la 1->2 si 2->3
        myStepper.step(rotatii/1);
  }
  
void urcaNivel2(){//functie urca 1->3
      urcaNivel();
      urcaNivel();
  }

void coboaraNivel(){//functie coboara 2->1,3->2
  myStepper.step(-rotatii/1);
  }
  
void coboaraNivel2(){//functie coboara 3->1
  coboaraNivel();
  coboaraNivel();
  }

void aprinde1(){
   stergereD();
  analogWrite(b,255);
  analogWrite(c,255);
  }
  
void aprinde2(){
   stergereD();
  analogWrite(a,255);
  analogWrite(b,255);
  analogWrite(g,255);
  analogWrite(e,255);
  analogWrite(d,255);
 
  }
void aprinde3(){
  stergereD();
  analogWrite(a,255);
  analogWrite(b,255);
  analogWrite(g,255);
  analogWrite(c,255);
  analogWrite(d,255);
 
  }
void stergereD(){
   analogWrite(a,0);
  analogWrite(b,0);
  analogWrite(g,0);
  analogWrite(c,0);
  analogWrite(d,0);
  analogWrite(e,0);
  }


void setup() {
pinMode(buton1Pin, INPUT);
  pinMode(buton2Pin, INPUT);
  pinMode(buton3Pin, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(a,OUTPUT);
  pinMode(b,OUTPUT);
  pinMode(c,OUTPUT);
  pinMode(d,OUTPUT);
  pinMode(e,OUTPUT);
  pinMode(g,OUTPUT);
  
  Serial.begin(9600);

  myStepper.setSpeed(15);
}

void loop() {
  int buton1Stare, buton2Stare, buton3Stare;
  buton1Stare=digitalRead(buton1Pin);
  buton2Stare=digitalRead(buton2Pin);
  buton3Stare=digitalRead(buton3Pin);

  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

    var = pulseIn(echo, HIGH);
  distanta = var * 0.034 / 2;
  Serial.println(distanta);


  //1->2
  if(buton2Stare==HIGH&&(distanta>=0)&&(distanta<=5)){
    aprinde2();
    urcaNivel();
     aprinde2();
    }

    
   

    
    //1->3
    else if(buton3Stare==HIGH&&(distanta>=0)&&(distanta<=5)){
      aprinde3();
     urcaNivel2();
      aprinde3();
      }

//2->3
        else if(buton3Stare==HIGH&&distanta>=6&&distanta<=10){
    aprinde3();
    myStepper.step(1024);
    }


      //3->1
      else if(buton1Stare==HIGH&&distanta>=10){
        aprinde1(); 
        coboaraNivel2(); 
        aprinde1();
        }


        //3->2
        else if(buton2Stare==HIGH&&(distanta>=10)){
          aprinde2();
        coboaraNivel();
         aprinde2();
          }


          //2->1
          else if(buton1Stare==HIGH&&(distanta>=5)&&(distanta<10)){
            aprinde1();
       coboaraNivel();
        aprinde1();
            }
            delay(50);
}
