/*
Mạch điều khiển đèn LED sáng tối bằng biến trở


Linh kiện:
- Quang trở
- Đèn LED
- Điện trở 220 Ohm, 10 Kilo Ohm
- Arduino Uno

Cách lắp mạch:
- Xem hình

Tác giả: Khang Nguyễn
Ngày: 03/01/2015
Lịch sử thay đổi
- 12/03/2015 Rev. 1.1 - Map giá trị quang trở và giá trị xuất ra LED
- 03/01/2015 Rev. 1.0
Website: http://papcodientu.com/
*/

//khai báo cổng đèn LED
int denLED = 11;

// khai báo biến trở
int quangTro = A0;

// gia tri doc duoc tu bien tro 0-1023
int giatriquangTro = 0;
int giatridenLED = 0;

void setup() {                
  // cài đặt cổng led là cổng output
  pinMode(denLED, OUTPUT);
}

void loop() {
  // đọc giá trị từ quang trở
  giatriquangTro = analogRead(quangTro);
  
  // map giá trị quang trở với giá trị xuất ra LED
  giatridenLED = map(giatriquangTro, 0, 1023, 0, 255);
  
  // hiển thị độ sáng đèn LED theo giá trị quang trở
  analogWrite(denLED, giatridenLED/2);
  
  // độ trễ 100 mili giây để ổn định giá trị quang trở
  delay(100);
}

