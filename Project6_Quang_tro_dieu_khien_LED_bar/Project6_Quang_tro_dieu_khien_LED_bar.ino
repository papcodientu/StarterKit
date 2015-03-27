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
- 27/03/2015 Rev. 1.1 - Thêm 3 đèn LED
- 03/01/2015 Rev. 1.0
Website: http://papcodientu.com/
*/

//khai báo cổng đèn LED
int denDo1 = 13;
int denDo2 = 12;
int denVang1 = 11;
int denVang2 = 10;
int denXanh1 = 9;
int denXanh2 = 8;

// khai báo biến trở
int quangTro = A0;

// gia tri doc duoc tu bien tro 0-1023
int giatriquangTro = 0;

void setup() {                
  // cài đặt cổng led là cổng output
  pinMode(denXanh1, OUTPUT);
  pinMode(denXanh2, OUTPUT);
  pinMode(denVang1, OUTPUT);
  pinMode(denVang2, OUTPUT);
  pinMode(denDo1, OUTPUT);
  pinMode(denDo2, OUTPUT);
}

void loop() {
  // đọc giá trị từ quang trở
  giatriquangTro = analogRead(quangTro);
  if (giatriquangTro <= 170) {
    digitalWrite(denXanh1, HIGH);
    digitalWrite(denXanh2, LOW);
    digitalWrite(denVang1, LOW);
    digitalWrite(denVang2, LOW);
    digitalWrite(denDo1, LOW);
    digitalWrite(denDo2, LOW);
  } else if (giatriquangTro > 170 && giatriquangTro <= 341) {
    digitalWrite(denXanh1, HIGH);
    digitalWrite(denXanh2, HIGH);
    digitalWrite(denVang1, LOW);
    digitalWrite(denVang2, LOW);
    digitalWrite(denDo1, LOW);
    digitalWrite(denDo2, LOW);
  } else if (giatriquangTro > 314 && giatriquangTro <= 512) {
    digitalWrite(denXanh1, HIGH);
    digitalWrite(denXanh2, HIGH);
    digitalWrite(denVang1, HIGH);
    digitalWrite(denVang2, LOW);
    digitalWrite(denDo1, LOW);
    digitalWrite(denDo2, LOW);
  } else if (giatriquangTro > 512 && giatriquangTro <= 682) {
    digitalWrite(denXanh1, HIGH);
    digitalWrite(denXanh2, HIGH);
    digitalWrite(denVang1, HIGH);
    digitalWrite(denVang2, HIGH);
    digitalWrite(denDo1, LOW);
    digitalWrite(denDo2, LOW);
  } else if (giatriquangTro > 682 && giatriquangTro <= 853) {
    digitalWrite(denXanh1, HIGH);
    digitalWrite(denXanh2, HIGH);
    digitalWrite(denVang1, HIGH);
    digitalWrite(denVang2, HIGH);
    digitalWrite(denDo1, HIGH);
    digitalWrite(denDo2, LOW);
  } else {
    digitalWrite(denXanh1, HIGH);
    digitalWrite(denXanh2, HIGH);
    digitalWrite(denVang1, HIGH);
    digitalWrite(denVang2, HIGH);
    digitalWrite(denDo1, HIGH);
    digitalWrite(denDo2, HIGH);
  }
}

