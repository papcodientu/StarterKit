/*
Mạch điều khiển LED bar bằng quang trở

Linh kiện:
- Quang trở
- Đèn LED xanh, vàng, đỏ
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

//khai báo cổng đèn LED
int denXanh = 13;
int denVang = 12;
int denDo = 11;

// khai báo biến trở
int quangTro = A0;

// gia tri doc duoc tu bien tro 0-1023
int giatriquangTro = 0;

void setup() {                
  // cài đặt cổng led là cổng output
  pinMode(denXanh, OUTPUT);
  pinMode(denVang, OUTPUT);
  pinMode(denDo, OUTPUT);
}

void loop() {
  // đọc giá trị từ quang trở
  giatriquangTro = analogRead(quangTro);
  if (giatriquangTro <= 150) {
    digitalWrite(denXanh, LOW);
    digitalWrite(denVang, LOW);
    digitalWrite(denDo, LOW);
  } else if (giatriquangTro > 150 && giatriquangTro <= 300) {
    digitalWrite(denXanh, HIGH);
    digitalWrite(denVang, LOW);
    digitalWrite(denDo, LOW);
  } else if (giatriquangTro > 300 && giatriquangTro <= 600) {
    digitalWrite(denXanh, HIGH);
    digitalWrite(denVang, HIGH);
    digitalWrite(denDo, LOW);
  } else {
    digitalWrite(denXanh, HIGH);
    digitalWrite(denVang, HIGH);
    digitalWrite(denDo, HIGH);
  }
}

