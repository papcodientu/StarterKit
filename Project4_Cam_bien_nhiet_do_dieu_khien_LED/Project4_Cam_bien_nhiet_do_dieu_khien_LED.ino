/*
Mạch điều khiển đèn LED bar dùng cảm biến nhiệt độ và độ ẩm DHT11

Linh kiện:
- Cảm biến nhiệt độ và độ ẩm DHT11
- Đèn LED màu xanh lá cây, màu vàng và màu đỏ
- Điện trở 220 Ohm, 10 Kilo Ohm
- Arduino Uno

Cách lắp mạch:
- Xem hình

Tác giả: Nhân Nguyễn
Ngày: 03/01/2015
Lịch sử thay đổi
- 03/01/2015 Rev. 1.0
Website: http://papcodientu.com/
*/

// thư viện DHT - https://github.com/RobTillaart/Arduino
#include <dht.h>

// khai báo biến DHT
dht DHT;

// khai báo cổng cảm biến
int cambienDHT11 = 2;

//khai báo cổng đèn LED
int denXanh = 13;
int denVang = 12;
int denDo = 11;

// khai báo các giá trị ngưỡng
int nguongXanh = 28;
int nguongVang = 30;

void setup() {
  // thiết lập cổng serial ở tốc độ 57600 baudrate
  Serial.begin(57600);
  
  // cài đặt cổng led là cổng output
  pinMode(denXanh, OUTPUT);
  pinMode(denVang, OUTPUT);
  pinMode(denDo, OUTPUT);
}

void loop() {
  // thiết lập cảm biến DHT11
  DHT.read11(cambienDHT11);
  
  // đọc nhiệt độ từ cảm biến
  int nhietdo = (int)DHT.temperature;
  
  Serial.print("Nhiet do hien tai: ");
  Serial.println(nhietdo);
  
  if (nhietdo <= nguongXanh) {
    // nếu nhiệt độ nhỏ hoặc bằng nguongXanh thì bật đèn xanh
    digitalWrite(denXanh, HIGH);
    digitalWrite(denVang, LOW);
    digitalWrite(denDo, LOW);
  } else if (nhietdo > nguongXanh && nhietdo <= nguongVang) {
     // nếu nhiệt độ lớn hơn nguongXanh và nhỏ hơn hoặc bằng nguongVang thì bật đèn vàng
    digitalWrite(denXanh, LOW);
    digitalWrite(denVang, HIGH);
    digitalWrite(denDo, LOW);
  } else {
    // nếu nhiệt độ lớn hơn nguongVang thì bật đèn đỏ
    digitalWrite(denXanh, LOW);
    digitalWrite(denVang, LOW);
    digitalWrite(denDo, HIGH);
  }
  
  // delay 2s
  delay(2000);
}

