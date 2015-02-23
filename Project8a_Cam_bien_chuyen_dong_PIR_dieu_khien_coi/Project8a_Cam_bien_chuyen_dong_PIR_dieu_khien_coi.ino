/*
Mạch điều khiển đèn còi bằng cảm biến PIR

Linh kiện:
- Cảm biến PIR
- Còi
- Arduino Uno

Cách lắp mạch:
- Xem hình

Tác giả: Nhân Nguyễn
Ngày: 03/01/2015
Lịch sử thay đổi
- 03/01/2015 Rev. 1.0
Website: http://papcodientu.com/
*/

// khai báo cổng đèn LED
int coi = 9;

// khai báo cảm biến PIR
int cambienPIR = 2;

void setup() {                
  // cài đặt cổng led là cổng output
  pinMode(coi, OUTPUT);
  
  // cài đặt cổng cảm biến PIR là đầu vào
  pinMode(cambienPIR, INPUT);
}

void loop() {
  // đọc giá trị từ cảm biến PIR
  if (digitalRead(cambienPIR) == HIGH) {
    analogWrite(coi, 200);
    delay(200);
    analogWrite(coi, 0);
    delay(200);
  } else {
    digitalWrite(coi, LOW);
  }
}

