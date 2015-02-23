/*
Cổng tuần tự (Serial) điều khiển đèn LED đa màu RGB

Linh kiện:
- Đèn LED RGB 4 chân
- Điện trở 220 Ohm
- Arduino Uno

Cách lắp mạch:
- Xem hình

Tác giả: Phi-Anh Phan
Ngày: 07/01/2015
Lịch sử thay đổi
- 07/01/2015 Rev. 1.0
Website: http://papcodientu.com/
*/

const int denxanhDaTroi = 9;
const int denxanhLaCay = 10;
const int denDo = 11;

void setup() {
  Serial.begin(9600);  // khai bao cong tuan tu o toc do 9600 baud rate
  
  // Khai báo các cổng trên board Arduino
  pinMode(denxanhDaTroi, OUTPUT);  // Đèn LED là thiết bị đầu ra (output)
  pinMode(denxanhLaCay, OUTPUT);  // Đèn LED là thiết bị đầu ra (output)
  pinMode(denDo, OUTPUT);  // Đèn LED là thiết bị đầu ra (output)
}

void loop() {
  // nếu có thông tin từ cổng tuần tự thì đọc thông tin đó
  while (Serial.available() > 0) {

    // giá trị đầu tiên đọc từ cổng tuần tự là thông số màu đỏ
    int giatriDo = Serial.parseInt(); 
    // giá trị thứ hai đọc từ cổng tuần tự là thông số màu xanh lá cây
    int giatrixanhLaCay = Serial.parseInt(); 
    // giá trị thứ ba đọc từ cổng tuần tự là thông số màu da trời
    int giatrixanhDaTroi = Serial.parseInt(); 

    // nếu phím Enter được nhấn thì kết thúc đọc giá trị
    if (Serial.read() == '\n') {
      giatriDo = 255 - constrain(giatriDo, 0, 255);
      giatrixanhLaCay = 255 - constrain(giatrixanhLaCay, 0, 255);
      giatrixanhDaTroi = 255 - constrain(giatrixanhDaTroi
      , 0, 255);

      // xuất giá trị đỏ, xanh lá cây, xanh da trời ra đèn LED
      analogWrite(denDo, giatriDo);
      analogWrite(denxanhLaCay, giatrixanhLaCay);
      analogWrite(denxanhDaTroi, giatrixanhDaTroi);

      // hiển thị giá trị đèn đỏ, xanh lá cây, xanh da trời ở dạng mã HEX
      Serial.print(giatriDo, HEX);
      Serial.print(giatrixanhLaCay, HEX);
      Serial.println(giatrixanhDaTroi, HEX);
    }
  }
}
