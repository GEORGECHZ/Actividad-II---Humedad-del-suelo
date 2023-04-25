// Librería Wire.h para la comunicación I2C
#include <Wire.h>
//Librería para controlar el display LCD
#include <LiquidCrystal_I2C.h>


//Se define la direccion I2C, 16 columnas, 2 filas
LiquidCrystal_I2C lcd(0x27,16,2);


//Se definen los pines de los LEDs que se utilizaran
//para indicar el nivel de humedad
#define ledV 2
#define ledAz 3
#define ledB 4
#define ledAm 5
#define ledR 6


//Se define un arreglo de bytes que contiene un carácter
//personalizado para ser mostrado en el display
byte customChar[] = {
  B00000,
  B00100,
  B01100,
  B11110,
  B11101,
  B11111,
  B01110,
  B00000
};


void setup()
{
  //Se inicializa comunicación serial a 9600 baudios
  Serial.begin(9600);
  
  //Se inicializa el display 
  lcd.init();
  //Se enciende la iluminación del display
  lcd.backlight();
  //Crea un carácter personalizado en el display
  lcd.createChar(0, customChar);
  //Se posiciona el cursor del display en la segundo fila
  lcd.setCursor(0, 1);
  //Se escribe el carácter 8 veces seguida de un espacio
  for (int i=0;i<8;i++){
    lcd.write(0);
    lcd.print(" ");
  }
 
  //Configuración de pines como salidas
  pinMode(ledV, OUTPUT);
  pinMode(ledAz, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(ledAm, OUTPUT);
  pinMode(ledR, OUTPUT);
}


//Función para controlar el encendido de los LEDs en base al
//valor de humedad recibido en la variable “h”.
//Se utiliza digitalWrite() para encender y apagar los LEDs
void luces(float h){
  if (h == 100){
    digitalWrite(ledV, HIGH);
  digitalWrite(ledAz, LOW);
    digitalWrite(ledB, LOW);
    digitalWrite(ledAm, LOW);
    digitalWrite(ledR, LOW);
  } else if (h < 100 && h > 74){
    digitalWrite(ledAz, HIGH);
    digitalWrite(ledV, LOW);
    digitalWrite(ledB, LOW);
    digitalWrite(ledAm, LOW);
    digitalWrite(ledR, LOW);
  } else if (h < 75 && h > 49){
    digitalWrite(ledB, HIGH);
    digitalWrite(ledAz, LOW);
    digitalWrite(ledV, LOW);
    digitalWrite(ledAm, LOW);
    digitalWrite(ledR, LOW);
  } else if (h < 50 && h > 24){
    digitalWrite(ledAm, HIGH);
    digitalWrite(ledAz, LOW);
    digitalWrite(ledV, LOW);
    digitalWrite(ledB, LOW);
    digitalWrite(ledR, LOW);
  } else {
    digitalWrite(ledR, HIGH);
    digitalWrite(ledAz, LOW);
    digitalWrite(ledV, LOW);
    digitalWrite(ledB, LOW);
    digitalWrite(ledAm, LOW);
  }
}


void loop()
{
  //Leer el valor analógico del sensor de humedad y utilizar la
  //función map() para convertir los valores en porcentaje y 
  //almacenarlo en la variable “sensorH”
  float sensorH = map(analogRead(A0),1015,15,0,100);
  //Llamar a la función luces para controlar los LEDs
  luces(sensorH);
  //Posición del cursor en la primera fila
  lcd.setCursor(1, 0);
  //Imprimir “Humedad” en el display
  lcd.print("Humedad");
  //Posición del cursor en la novena fila
  lcd.setCursor(9, 0);
  //Imprimir el porcentaje de humedad seguido de unos espacios
  lcd.print(sensorH);
  lcd.print("   ");
  //Retardo de 1 segundo
  delay(1000);
}