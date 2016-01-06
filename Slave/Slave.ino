#include <SPI.h>
#include<Servo.h>
volatile boolean ricevuto;
volatile byte val_pot1, val_pot2;
Servo servo2;
void setup() {
  servo2.attach(3);
  servo2.write(20);
  pinMode(MISO,OUTPUT);//forzo la slave mode
  SPCR |=_BV(SPE);
  ricevuto= false;
  SPI.attachInterrupt();
}
ISR (SPI_STC_vect){
  val_pot1 = (int)SPDR;//accedo ai dati in ricezione
  ricevuto=true;
}
void loop() {
  
  if(ricevuto){
    if (val_pot1>20&&val_pot1<160){
    servo2.write(val_pot1);
    }
    val_pot2=analogRead(0);
    map(val_pot2,0,1024,20,160);
    val_pot2=(byte)val_pot2;
    SPDR=val_pot2;
    
    ricevuto=false;
  }
}
