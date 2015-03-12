/*
Mạch điều khiển đèn LED sáng tối bằng biến trở


Linh kiện:
- Biến trở 10K
- Đèn LED
- Điện trở 220 Ohm
- Arduino Uno

Cách lắp mạch:
- Xem hình

Tác giả: Tùng Nguyễn
Ngày: 03/01/2015
Lịch sử thay đổi
- 03/01/2015 Rev. 1.0
Website: http://papcodientu.com/
*/

//khai báo cổng đèn LED
int denLED = 11;

// khai báo biến trở
int bienTro = A0;

// gia tri doc duoc tu bien tro 0-1023
int giatribienTro = 0;

// gia tri xuat ra den LED 0-255
int giatridenLED = 0;

void setup() {                
  // cài đặt cổng led là cổng output
  pinMode(denLED, OUTPUT);
}

void loop() {
  // đọc giá trị từ biến trở
  giatribienTro = analogRead(bienTro);
  
  // map giá trị biến trở với giá trị xuất ra LED
  giatridenLED = map(giatribienTro, 0, 1023, 0, 255);
  
  // hiển thị độ sáng đèn LED theo giá trị biến trở
  analogWrite(denLED, giatridenLED);
  
  // độ trễ 100 mili giây để ổn định giá trị biến trở
  delay(100);
}

