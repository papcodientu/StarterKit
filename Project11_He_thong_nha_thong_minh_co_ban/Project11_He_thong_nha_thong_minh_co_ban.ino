/*
Hệ thống nhà thông minh cơ bản dùng Arduino

Linh kiện:
- Nút bấm 4 chân
- Đèn LED RGB
- Điện trở 220 Ohm, 10K Ohm
- Quang trở
- Còi
- Cảm biến nhiệt độ
- Cảm biến chuyển động
- Arduino Uno

Chế đô:
0 - Tắt hệ thống
1 - Nhà thông minh
2 - Báo động
3 - Cảm biết nhiệt độ

Cách lắp mạch:
- Xem hình

Tác giả: Nhân Nguyễn
Ngày: 13/01/2015
Lịch sử thay đổi
- 13/01/2015 Rev. 1.1 Upgraded
- 04/11/2014 Rev. 1.0 Added button debounce
- 06/09/2014 Rev. 0.1 Draft, no button debounce
Website: http://papcodientu.com/
*/

// thư viện DHT - https://github.com/RobTillaart/Arduino
#include <dht.h>

// khai báo biến DHT
dht DHT;

// Các thiết bị đầu vào
const int nutBam = 2;    // nut bam noi vao pin 2 cua Arduino
const int denledDo1 = 5;  // đèn LED điều khiển bởi nút bấm
const int denledXanhLaCay1 = 3;

const int quangTro = A5;  // Quang trở cảm biến ánh sáng
const int giatringuongQuangTro = 600; // gia tri nguong tu 0 ~ 1024

const int cambienDHT11 = 7;  // Cảm biến nhiệt độ và độ ẩm DHT11
const int cambienPIR= 8;  // Cảm biến chuyển động PIR
int trangthaiPIR = LOW;
  
// Các thiết bị đầu ra
const int coi = 6;
const int denledDo2 = 11;
const int denledXanhLaCay2 = 10;
const int denledXanhNuocBien2 = 9;

// khai báo các giá trị ngưỡng
int nguongXanh = 26;
int nguongVang = 28;

int chedodenLED = 0;  // tùy chế độ mà hiển thị màu đèn LED tương ứng
int trangthaiNutBam;    // trang thai nut bam hien tai
int trangthainutbamTruoc = HIGH;   // trang thai nut bam truoc do

long thoidiemDebounceTruoc = 0;  // thoi diem nut bam chuyen doi trang thai
long dotreDebounce = 50;   // do tre cua moi lan debounce

void setup() {
  Serial.begin(57600);
  // khai báo các cổng vào & ra trên board Arduino
  // cổng vào
  pinMode(nutBam, INPUT);  // nút bấm
  pinMode(cambienDHT11, INPUT); // cảm biến nhiệt độ DHT11
  pinMode(cambienPIR, INPUT); // cảm biến chuyển động PIR
  
  // cổng ra
  pinMode(denledDo1, OUTPUT);   // đèn led đỏ 1
  pinMode(denledXanhLaCay1, OUTPUT);   // đèn led xanh lá cây 1
  pinMode(coi, OUTPUT);  // còi
  pinMode(denledDo2, OUTPUT);  // đèn led đỏ 2
  pinMode(denledXanhLaCay2, OUTPUT);  // đèn led xanh lá cây 2
  pinMode(denledXanhNuocBien2, OUTPUT);  // đèn led nước biển 2
  
  digitalWrite(denledDo1, HIGH);
  digitalWrite(denledXanhLaCay1, HIGH);
  digitalWrite(denledDo2, HIGH);
  digitalWrite(denledXanhLaCay2, HIGH);
  digitalWrite(denledXanhNuocBien2, HIGH);
}

void loop() {
  int giatriNutBam = digitalRead(nutBam);  // doc gia tri cua nut bam
  
  // Neu trang thai nut bam thay doi, do viec bi nhieu hoac duoc nhan
  if (giatriNutBam != trangthainutbamTruoc) {
    // reset thoi diem debounce
    thoidiemDebounceTruoc = millis(); 
  }
  
  // nut bam duoc giu lau hon dotreDebounce, nut bam that su duoc nhan
  if ((millis() - thoidiemDebounceTruoc) > dotreDebounce) {
    // trang thai nut bam da thay doi
    if (giatriNutBam != trangthaiNutBam) {
      // thay doi trang thai nut bam bang gia tri hien tai
      trangthaiNutBam = giatriNutBam;
     
      // nut bam da duoc nhan
      if (trangthaiNutBam == LOW) {
        // thay doi trang thai den LED
        chedodenLED += 1;
      }
    }
  }

  switch(chedodenLED) {
    case 1:
      // đèn LED 1 hiển thị màu xanh lá cây
      analogWrite(denledDo1, 255);
      analogWrite(denledXanhLaCay1, 0);
      chedoNhaThongMinh();
      break;
    case 2:
      // đèn LED 1 hiển thị màu đỏ
      analogWrite(denledDo1, 0);
      analogWrite(denledXanhLaCay1, 255);
      chedoBaoDong();
      break;
    case 3:
      // đèn LED 1 hiển thị màu vàng
      analogWrite(denledDo1, 150);
      analogWrite(denledXanhLaCay1, 0);
      chedocambienNhietDo();
      break;
    default:
      analogWrite(denledDo1, 255);
      analogWrite(denledXanhLaCay1, 255);
      analogWrite(denledDo2, 255);
      analogWrite(denledXanhLaCay2, 255);
      analogWrite(denledXanhNuocBien2, 255);
      chedodenLED = 0;
      break;
  }
  
  // ghi lai gia tri nut bam
  trangthainutbamTruoc = giatriNutBam;
}

void chedoNhaThongMinh() {
  Serial.println("Che do nha thong minh.");
  
  int giatriQuangTro = analogRead(quangTro);
  Serial.print("Gia tri quang tro: ");
  Serial.println(giatriQuangTro);
  
  // giá trị quang trở nhỏ hơn giá trị ngưỡng => trời tối
  if (giatriQuangTro < giatringuongQuangTro) {
    // đọc trang thái cảm biến PIR
    if (digitalRead(cambienPIR) == HIGH) {
      trangthaiPIR = !trangthaiPIR; 
    }
    Serial.println(trangthaiPIR);
    if (trangthaiPIR == HIGH) {
      // cảm biến chuyển động được kích hoạt => bật sáng đèn
      digitalWrite(denledDo2, 100);
      digitalWrite(denledXanhLaCay2, 0);
      digitalWrite(denledXanhNuocBien2, 0);
    } else {
      // cảm biến chuyển động được kích hoạt => bật sáng đèn
      digitalWrite(denledDo2, 255);
      digitalWrite(denledXanhLaCay2, 255);
      digitalWrite(denledXanhNuocBien2, 255);
    }
  } else {
    // giá trị quang trở lớn hơn ngưỡng => trời sáng, luôn tắt đèn
      digitalWrite(denledDo2, 255);
      digitalWrite(denledXanhLaCay2, 255);
      digitalWrite(denledXanhNuocBien2, 255);
  }
  
  // delay 1s
  delay(2000);
}

void chedoBaoDong() {
  Serial.println("Che do bao dong.");
  
  if (digitalRead(cambienPIR) == HIGH) {
    trangthaiPIR = HIGH; 
  }
  
  //
  while (trangthaiPIR == HIGH) {
    analogWrite(denledDo2, 0);
    delay(100);
    analogWrite(denledDo2, 255);
    delay(100);
    analogWrite(coi, 200);
    delay(100);
    analogWrite(coi, 0);
    delay(100);
  }
}

void chedocambienNhietDo() {
  Serial.println("Che do cam bien nhiet do.");
  
  // thiết lập cảm biến DHT11
  DHT.read11(cambienDHT11);
  
  // đọc nhiệt độ từ cảm biến
  int nhietdo = (int)DHT.temperature;
  Serial.print("Nhiet do: ");
  Serial.println(nhietdo);
  
  if (nhietdo <= nguongXanh) {
    // nếu nhiệt độ nhỏ hoặc bằng nguongXanh thì bật đèn xanh
    analogWrite(denledXanhLaCay2, 0);
    analogWrite(denledXanhNuocBien2, 255);
    analogWrite(denledDo2, 255);
  } else if (nhietdo > nguongXanh && nhietdo <= nguongVang) {
     // nếu nhiệt độ lớn hơn nguongXanh và nhỏ hơn hoặc bằng nguongVang thì bật đèn vàng
    analogWrite(denledXanhLaCay2, 0);
    analogWrite(denledXanhNuocBien2, 255);
    analogWrite(denledDo2, 150);
  } else {
    // nếu nhiệt độ lớn hơn nguongVang thì bật đèn đỏ
    analogWrite(denledXanhLaCay2, 255);
    analogWrite(denledXanhNuocBien2, 255);
    analogWrite(denledDo2, 0);
  }
  
  // delay 2s
  delay(2000);
}
