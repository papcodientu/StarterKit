/*
Nút bấm điều khiển đèn LED đa màu RGB

Linh kiện:
- Biến trở 10k
- Đèn LED RGB 4 chân
- Điện trở 220 Ohm
- Arduino Uno

Cách lắp mạch:
- Xem hình

Tác giả: Nhân Nguyễn
Ngày: 06/09/2014
Lịch sử thay đổi
- 04/11/2014 Rev. 1.0 Update code
- 06/09/2014 Rev. 0.1 Dràft
Website: http://papcodientu.com/
*/

const int bienTro = A0;    // nut bam noi vao pin 2 cua Arduino
const int denxanhDaTroi = 9;  // chân đèn xanh da trời kết nối vào cổng 9
const int denxanhLaCay = 10;  // chân đèn xanh lá cây kết nối vào cổng 10s
const int denDo = 11;         // chân đèn đỏ kết nối vào cổng 11

void setup() {
  Serial.begin(57600);
  // Khai báo các cổng trên board Arduino
  pinMode(bienTro, INPUT);   // Nút bấm là thiết bị đầu vào (input)
  pinMode(denxanhDaTroi, OUTPUT);  // Đèn LED là thiết bị đầu ra (output)
  pinMode(denxanhLaCay, OUTPUT);  // Đèn LED là thiết bị đầu ra (output)
  pinMode(denDo, OUTPUT);  // Đèn LED là thiết bị đầu ra (output)
  
  // Mặc định đèn tắt, LED RGB cực dương chung
  digitalWrite(denxanhDaTroi, HIGH);
  digitalWrite(denxanhLaCay, HIGH);
  digitalWrite(denDo, HIGH);
}

void loop() {
  int giatribienTro, giatridenLED;
  
  // đọc giá trị từ biến trở
  giatribienTro = analogRead(bienTro);
  
  // map giá trị biến trở với giá trị xuất ra LED
  giatridenLED = map(giatribienTro, 0, 1023, 0, 255);
  Serial.println(giatridenLED);
  
  // hiển thị độ sáng đèn LED theo giá trị biến trở
  thietlapmaudenLED(giatridenLED);
  
  // độ trễ 100 mili giây để ổn định giá trị biến trở
  delay(100);
}

void thietlapmaudenLED(int giatridenLED) {
  analogWrite(denDo, 50 - giatridenLED);  // thiết lập giá trị màu cho đèn đỏ
  analogWrite(denxanhDaTroi, 100 - giatridenLED);  // thiết lập giá trị màu cho đèn xanh da trời
  analogWrite(denxanhLaCay, 150 - giatridenLED);  // thiết lập giá trị màu cho đèn xanh lá cây
}
