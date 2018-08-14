#include <Wire.h>   //libreria comunicacion
#include <I2Cdev.h> //libreria comunicacion
#include <MPU6050.h>//Libreria acelerometro
#include <Mouse.h>  //libreria Mouse
MPU6050 mpu;        //declaramos el sensor
int ClicIzquierdo = 7;
int ClicDerecho = 3;
int botonIzquierdo = 0; 
int botonDerecho = 0; 
int16_t ax, ay, az, gx, gy, gz; //variables del sensor

void setup() 
{
  Serial.begin(9600); //iniciamos comunicacion serial
  Wire.begin();
  pinMode(ClicIzquierdo, INPUT);
  pinMode(ClicDerecho, INPUT);
  mpu.initialize();   //Iniciamos acelerometro
  if (!mpu.testConnection()) { while (1); }
}

void loop() {
 mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); //obtenemos variables del sensor
 
 ax=-(ax/1000);    //ariba - abajo mapear monitor
 ay=(ay/1000);    //izquierda - derecha mapear monitor
 Serial.print(ax); 
 Serial.print(",");
 Serial.println(ay);    
 Mouse.move(ay, ax); //Enviamos coordenadas

  botonIzquierdo = digitalRead(ClicIzquierdo);
  botonDerecho = digitalRead(ClicDerecho);
  
 if (botonIzquierdo == HIGH) 
 {
    Mouse.press(MOUSE_LEFT);
    delay(100);
    Mouse.release(MOUSE_LEFT);
    delay(200);
    } 
  delay(1);
}

