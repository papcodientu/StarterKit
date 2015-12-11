#include <DHT.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

#define LOAIDHT DHT11
#define DEBUG

const int nutBam = 2;
int trangthaiNutBam;
int trangthaiNutBamCuoi = LOW;
long thoigianBamCuoi = 0;
long dotreNutBam = 50;

const int cambienNhietDo = 4;
DHT dht(cambienNhietDo, LOAIDHT);
float doAm;
float nhietDo;

const int ledMauDo = 3;
const int ledMauXanhLaCay = 5;
const int ledMauXanhDaTroi = 6;
const int cambienPIR = 7;
const int coi = 9;

int cheDo = 0;

void setup() {
  Serial.begin(9600);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.clearDisplay();
  
  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Co Dien Tu PAP");
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("SmartHome");
  display.display();
  delay(2000);

  pinMode(nutBam, INPUT);
  pinMode(cambienNhietDo, INPUT);
  pinMode(cambienPIR, INPUT);
  pinMode(ledMauDo, OUTPUT);
  pinMode(ledMauXanhLaCay, OUTPUT);
  pinMode(ledMauXanhDaTroi, OUTPUT);
  pinMode(coi, OUTPUT);

  analogWrite(ledMauDo, 255);
  analogWrite(ledMauXanhLaCay, 255);
  analogWrite(ledMauXanhDaTroi, 255);
  analogWrite(coi, 0);

  dht.begin();
}

void loop() {
  int trangthai = digitalRead(nutBam);

  if(trangthai != trangthaiNutBamCuoi) {
    thoigianBamCuoi = millis();
  }

  if((millis() - thoigianBamCuoi) > dotreNutBam) {
    Serial.println(trangthai);
    if(trangthai != trangthaiNutBam) {
      trangthaiNutBam = trangthai;

      if(trangthaiNutBam == HIGH) {
        cheDo = !cheDo;
        Serial.println(cheDo);
      }
    }
  }

  switch(cheDo) {
    case 0:
      thietlapMauBaoDong();
      chedoBaoDong();
      if(docgiatriPIR()) {
        batCoi();
        manhinhAlarm();
      }
      delay(100);
      tatCoi();
      delay(100);
      break;
      
    case 1:
      thietlapMauDoNhietDo();
      docgiatriDHT();
      chedoThongMinh();
      break;
      
    default:
      break;
  }
  
  trangthaiNutBamCuoi = trangthai;
}

void thietlapMauBaoDong() {
  analogWrite(ledMauDo, 0);
  analogWrite(ledMauXanhLaCay, 255);
  analogWrite(ledMauXanhDaTroi, 255);
}

void thietlapMauDoNhietDo() {
  analogWrite(ledMauDo, 255);
  analogWrite(ledMauXanhLaCay, 0);
  analogWrite(ledMauXanhDaTroi, 255);
}

int docgiatriPIR() {
  return digitalRead(cambienPIR);
}

void batCoi() {
  analogWrite(coi, 255);
}

void tatCoi() {
  analogWrite(coi, 0);
}

void docgiatriDHT() {
  doAm = dht.readHumidity();
  nhietDo = dht.readTemperature();

  Serial.print(doAm);
  Serial.print("\t");
  Serial.println(nhietDo);

  if(isnan(doAm) || isnan(nhietDo)) {
    Serial.println("Khong the doc gia tri tu cam bien DHT.");
  }
}

void chedoBaoDong() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("Che Do Bao Dong");
  display.display();
}

void manhinhAlarm() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("Che Do Bao Dong");
  display.setTextSize(2);
  display.setCursor(30,10);
  display.println("ALARM");
  display.display();
}

void chedoThongMinh() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("Che Do Thong Minh");
  display.print("Do Am: ");
  display.println(doAm);
  display.print("Nhiet Do: ");
  display.println(nhietDo);
  display.display();
}

