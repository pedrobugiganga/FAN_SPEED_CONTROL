#include <MicroLCD.h>
#define buttonA 2
#define buttonB 4
#define pwm 10
int sinal = 0;
#define entrada_sensor A0
//LCD_SH1106 lcd; /* para módulo controlado pelo CI SH1106 OLED */ 
LCD_SSD1306 lcd; /* para módulo contralado pelo CI SSD1306 OLED */

float temp;
int sensor_temp;
char manual;
const unsigned char logo2 [] PROGMEM = {
0x00, 0x00, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0x00, 0xE0, 0xE0, 0xE0, 0xE0,
0x00, 0x00, 0xE0, 0xE0, 0xE0, 0x00, 0xC0, 0xE0, 0xE0, 0xF0, 0xF0, 0x70, 0xF0, 0xE0, 0xE0, 0x00,
0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xC7, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0xC7, 0xC7, 0xC7, 0x00,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x1F, 0x00, 0x1F, 0x3F, 0x3F, 0x7F,
0x70, 0x70, 0x7F, 0x3F, 0x1F, 0x00, 0x1F, 0x3F, 0x7F, 0x7F, 0x7F, 0x71, 0x3F, 0x3F, 0x3F, 0x00,
0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xF8, 0xFC, 0xFC, 0x0C, 0x08, 0xFC, 0xFC, 0x00, 0x00, 0x78, 0x78, 0x7C, 0x9C, 0x8C,
0xFC, 0xFC, 0xF8, 0x00, 0xFC, 0xFC, 0xFC, 0xFC, 0x0C, 0xFC, 0xFC, 0xFC, 0xF8, 0x00, 0xFC, 0xFE,
0xFE, 0x06, 0x04, 0xFE, 0xFE, 0x00, 0x78, 0x78, 0x7C, 0xDC, 0x8C, 0xFC, 0xFC, 0xF8, 0x00, 0x00,
0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x80, 0x80, 0xFF, 0xFF, 0x00, 0x00, 0xFE, 0xFE, 0xFF, 0x87, 0x83,
0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x7F, 0x7F,
0x7F, 0x40, 0x40, 0xFF, 0xFF, 0x00, 0xFE, 0xFE, 0xFF, 0x87, 0x83, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
0x00, 0x00, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03,
0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void setup() {
  lcd.begin();


  lcd.setCursor(40, 1);
  lcd.draw(logo2,48,48);
  delay(4000);

  lcd.clear();

  lcd.setFontSize(FONT_SIZE_SMALL);
 lcd.println("FAN CONTROL AUTOMATIC");
    lcd.setFontSize(FONT_SIZE_MEDIUM);
  lcd.setCursor(1, 2);
  lcd.println("FAN:");
    lcd.setCursor(1, 6);
  lcd.println("TEMP:");
      lcd.setCursor(67, 6);
  lcd.println("'C");
  
  Serial.begin (9600);
  pinMode(buttonA,INPUT);
  pinMode(buttonB,INPUT);
  pinMode(entrada_sensor, INPUT);
  pinMode(pwm, OUTPUT); 
  
}

void loop() {



//////////////////////////////////////////////////////////           CONTROLE AUTOMATICO

  float tempM[500]; // medição média
  int j=0 ;
  for(j =0; j<500; j++){
  sensor_temp = analogRead(entrada_sensor);
  tempM [j] = (sensor_temp * (5.0/1023.0))*100;
  temp =temp+tempM[j];
  }

    int temp_result = temp / 500;
    temp = 0;

lcd.setCursor(50, 6);
lcd.println(temp_result);
delay(120);
  
int sinal_100 = ((sinal*100)/255);
  

if(sinal_100== 100){ // AJUSTE DISPLAY
    lcd.setCursor(40, 2);
  }
if(sinal_100< 100){ 
    lcd.setCursor(40, 2);
    lcd.printLong(0);
    lcd.setCursor(56, 2);
  }
if(sinal_100< 10){ 
    lcd.setCursor(56, 2);
    lcd.printLong(0);
    lcd.setCursor(72, 2);  
  }                         // FIM AJUSTE DISPLAY
  
  lcd.setFontSize(FONT_SIZE_XLARGE);
  lcd.printLong(sinal_100);
  lcd.setCursor(95, 2);
  lcd.println("%");
 
int estado_buttonA = digitalRead(buttonA);
int estado_buttonB = digitalRead(buttonB);



if (temp_result< 35 && estado_buttonA == HIGH && estado_buttonB == HIGH ) {
  sinal = 0;
}

if (temp_result>= 36 && temp_result<= 40 && estado_buttonA == HIGH && estado_buttonB == HIGH) {
  sinal = 50;
}

if (temp_result>= 41 && temp_result<= 47 && estado_buttonA == HIGH && estado_buttonB == HIGH) {
  sinal = 100;
}

if (temp_result> 48 && estado_buttonA == HIGH && estado_buttonB == HIGH) {
  sinal = 255;
}

analogWrite(pwm,sinal);

//////////////////////////////////////////////////////////           CONTROLE MANUAL

if(estado_buttonB == 0){
int menu = 1;
lcd.clear();

 lcd.setFontSize(FONT_SIZE_SMALL);
 lcd.setCursor(0, 0);
  lcd.println(" FAN CONTROL MANUAL");
    lcd.setFontSize(FONT_SIZE_MEDIUM);
  lcd.setCursor(1, 2);
  lcd.println("FAN:");
    lcd.setCursor(1, 6);
  lcd.println("TEMP:");
      lcd.setCursor(67, 6);
  lcd.println("'C");
estado_buttonA = digitalRead(buttonA);
estado_buttonB = digitalRead(buttonB);
//delay(100);
while(menu == 1){


 float tempM[500]; // medição média
  int j=0 ;
  for(j =0; j<500; j++){
  sensor_temp = analogRead(entrada_sensor);
  tempM [j] = (sensor_temp * (5.0/1023.0))*100;
  temp =temp+tempM[j];
  }

    int temp_result = temp / 500;
    temp = 0;

lcd.setCursor(50, 6);
lcd.println(temp_result);
delay(120);
  
int sinal_100 = ((sinal*100)/255);
  

if(sinal_100== 100){ // AJUSTE DISPLAY
    lcd.setCursor(40, 2);
  }
if(sinal_100< 100){ 
    lcd.setCursor(40, 2);
    lcd.printLong(0);
    lcd.setCursor(56, 2);
  }
if(sinal_100< 10){ 
    lcd.setCursor(56, 2);
    lcd.printLong(0);
    lcd.setCursor(72, 2);  
  }                         // FIM AJUSTE DISPLAY
  
  lcd.setFontSize(FONT_SIZE_XLARGE);
  lcd.printLong(sinal_100);
  lcd.setCursor(95, 2);
  lcd.println("%");
 
int estado_buttonA = digitalRead(buttonA);
int estado_buttonB = digitalRead(buttonB);

 if (estado_buttonA == LOW) { 
    sinal = sinal - 8;
    delay(150);
    if(sinal_100<=0){sinal=0;}
    analogWrite(pwm,sinal);
}
 if (estado_buttonB == LOW) {
  sinal = sinal + 8;
  delay(150);
  if(sinal>=255){sinal=255;}
 analogWrite(pwm,sinal);
}




estado_buttonA = digitalRead(buttonA);
estado_buttonB = digitalRead(buttonB);
if(estado_buttonA == 0 && estado_buttonB == 0 ) { menu = 0;}

  }
  lcd.clear();

  lcd.setFontSize(FONT_SIZE_SMALL);
 lcd.println("FAN CONTROL AUTOMATIC");
    lcd.setFontSize(FONT_SIZE_MEDIUM);
  lcd.setCursor(1, 2);
  lcd.println("FAN:");
    lcd.setCursor(1, 6);
  lcd.println("TEMP:");
      lcd.setCursor(67, 6);
  lcd.println("'C");
}
}
