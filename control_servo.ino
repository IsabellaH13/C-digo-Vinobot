#include<Servo.h>
#include <Stepper.h>

// salida de rotación 
const int stepsPerRevolution = 200;
// entradas del integrado
const int motorPin1 = 11;
const int motorPin2 = 10;
const int motorPin3 = 13;
const int motorPin4 = 12;

int previo=0;
int sum;

// Crear una instancia de la clase Stepper
Stepper myStepper(stepsPerRevolution, motorPin1, motorPin2, motorPin3, motorPin4);

Servo base1;
Servo base2;
Servo arti1;
Servo arti2;
Servo efec;
String palabra;
String Art;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  base1.attach(7);
  base2.attach(9);
  arti1.attach(8);
  efec.attach(5);
  arti2.attach(6);
  myStepper.setSpeed(60); // 60 RPM
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1);
  if(Serial.available()){
    palabra=Serial.readString(); //se lee lo que se declaro en palabra, readString lee la palabra completa 
    int M = palabra.indexOf('M');//buscan en palabra el caracter m y si lo encuentra guarda la posición del caracter 
    int F = palabra.indexOf('F');
    //cuando indexOF no encuentra el caracter en la palabra imprime un -1
    Serial.println(palabra);

    if ((M!=-1) && (F!=-1) && (F>M)){//asegura que haya encontrado el caracter en la palabra 
      String motor = palabra.substring(M+1,M+2);//substring segmenta la palabra segun la posición que se le ingrese 
      String ang = palabra.substring(M+2,F);

      int Mot = motor.toInt();
      int Angulo = ang.toInt();

      switch (Mot){
        case 1://la cantidad de casos corresponde a la cantidad de motores que tengo 
          base1.write(Angulo);
          base2.write(-Angulo+180);
          Art = "bases: "+ ang;//agrega el ang anterior que es un string a la palabra base 
          break;
        case 2:
          arti1.write(Angulo);
          Art = "Primera Articulacion: "+ ang;
          break;
        case 3://la cantidad de casos corresponde a la cantidad de motores que tengo 
          arti2.write(Angulo);
          Art = "Segunda Articulación: "+ ang;//agrega el ang anterior que es un string a la palabra base 
          break;
        case 4:
          efec.write(Angulo);
          Art = "Efector final: "+ ang;
          break;
        case 5:
          sum=Angulo-previo;
          Serial.println(sum);
          if ( sum> 0) {
            myStepper.step(sum);
            Art = "Motor paso a paso hacia adelante: " + ang;
          } else if (sum < 0) {
            myStepper.step(sum);
            Art = "Motor paso a paso hacia atrás: " + ang;
          }
          previo=Angulo;
          break;

      }

      Serial.print(Art);
      Serial.println("grados");

    }
  }

}
