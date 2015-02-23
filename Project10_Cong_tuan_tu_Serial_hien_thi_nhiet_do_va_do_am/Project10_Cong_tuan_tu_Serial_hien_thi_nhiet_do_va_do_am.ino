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

void setup() {
  // thiết lập cổng serial ở tốc độ 57600 baudrate
  Serial.begin(9600);
  Serial.println("Nhiet do (oC), Do am (%)");
}

void loop() {
  // thiết lập cảm biến DHT11
  DHT.read11(cambienDHT11);
  
  Serial.print(DHT.temperature);
  Serial.print("\t\t");
  Serial.println(DHT.humidity); 
  
  // delay 2s
  delay(2000);
}

