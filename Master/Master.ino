//Il programma prevede una comunicazione fra due Arduino, in modo che il potenziometro
//collegato al master muova il motore collegato allo slave e viceversa
#include <SPI.h>
#include <Servo.h>
Servo servo1;
byte val_pot1,val_pot2;//inizializzo delle variabile byte in modo da poterle inviare
void setup() {
  digitalWrite (SS,HIGH);//in modo che non vi sia ancora comunicazione con lo slave
  SPI.begin();//inizializzo coi valori di default la comunicazione spi
  SPI.setClockDivider(SPI_CLOCK_DIV8);//rallento il clock a piacere
  servo1.attach(4);
  servo1.write(20);
}

void loop() {
  digitalWrite(SS,LOW);//permetto la comunicazione con lo slave
  val_pot1= analogRead(0);
  map(val_pot1,0,1024,20,160);
  val_pot1=(byte)val_pot1;
  val_pot2=(int)SPI.transfer(val_pot1);//(non so se si può fare m ho seguito un tutorial)
                                       //prima di inviare l'altro valore salvo il mio.
  if (val_pot2>20&&val_pot2<160){
    servo1.write(val_pot2);
  }
  delay(200);
  digitalWrite(SS,HIGH);
  delay(1000);

}
