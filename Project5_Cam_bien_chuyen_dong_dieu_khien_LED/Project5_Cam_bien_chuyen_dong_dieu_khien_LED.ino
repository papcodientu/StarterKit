/*
Mạch điều khiển đèn LED bằng cảm biến PIR

Linh kiện:
- Cảm biến PIR
- Đèn LED
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
int denLED = 11;

// khai báo cảm biến PIR
int cambienPIR = 2;

void setup() {                
  // cài đặt cổng led là cổng output
  pinMode(denLED, OUTPUT);
  
  // cài đặt cổng cảm biến PIR là đầu vào
  pinMode(cambienPIR, INPUT);
}

void loop() {
  // đọc giá trị từ cảm biến PIR
  if (digitalRead(cambienPIR) == HIGH) {
    digitalWrite(denLED, HIGH); 
  } else {
    digitalWrite(denLED, LOW);
  }
}

