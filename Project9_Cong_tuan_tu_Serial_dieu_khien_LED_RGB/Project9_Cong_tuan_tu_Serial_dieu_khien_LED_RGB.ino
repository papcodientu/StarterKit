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

// Bảng mã màu
#define mauDo 0xFF0000  // màu đỏ
#define mauVang 0xFFCD00  // màu vàng
#define mauXanhLaCay 0x009F6B // màu xanh lá cây
#define mauXanhLam 0x0000FF  // màu xanh lam
#define mauXanhDaTroi 0x007FFF  // màu xanh da trời
#define mauHong 0xFF0099  // màu hồng
#define mauTrang 0xFFFFFF  // màu trắng

const int denxanhDaTroi = 9;
const int denxanhLaCay = 10;
const int denDo = 11;

void setup() {
  Serial.begin(9600);  // khai bao cong tuan tu o toc do 9600 baud rate

  // Khai báo các cổng trên board Arduino
  pinMode(denxanhDaTroi, OUTPUT);  // Đèn LED là thiết bị đầu ra (output)
  pinMode(denxanhLaCay, OUTPUT);  // Đèn LED là thiết bị đầu ra (output)
  pinMode(denDo, OUTPUT);  // Đèn LED là thiết bị đầu ra (output)
  
  // Mặc định đèn tắt
  digitalWrite(denxanhDaTroi, HIGH);
  digitalWrite(denxanhLaCay, HIGH);
  digitalWrite(denDo, HIGH);
}

void loop() {
  char maudenLED;
  // nếu có thông tin từ cổng tuần tự thì đọc thông tin đó
  while (Serial.available() > 0) {
    maudenLED = Serial.read();
    // đổi màu đèn LED theo giá trị nhập vào
    doimaudenLED(maudenLED);
  }
}

// Hàm chuyển đổi mã màu
void doimaudenLED(char maudenLED) {
  switch(maudenLED) {  // chuyển đổi chữ cái mã màu
    case 'r':  // r màu đỏ
      thietlapmaudenLED(mauDo);
      break;
    case 'y':  // y màu vàng
      thietlapmaudenLED(mauVang);
      break;
    case 'g':  // g màu xanh lá cây
      thietlapmaudenLED(mauXanhLaCay);
      break;
    case 'c':  // c màu xanh lam
      thietlapmaudenLED(mauXanhLam);
      break;
    case 'b': // b màu xanh da trời
      thietlapmaudenLED(mauXanhDaTroi);
      break;
    case 'p': // p màu hồng
      thietlapmaudenLED(mauHong);
      break;
    case 'w': // w màu trắng
      thietlapmaudenLED(mauTrang);
      break;  
    default:
      Serial.println("Sai ma mau");
      break;
  } 
}

// Hàm thiết lập màu đèn LED
void thietlapmaudenLED(long giatridenLED) {
  analogWrite(denDo, 255 - ((giatridenLED & 0xFF0000) >> 16));  // Giá trị màu đỏ là 8 bits đầu tiên [23:16]
  analogWrite(denxanhLaCay, 255 - ((giatridenLED & 0x00FF00) >> 8)); // Giá trị màu xanh lá cây là 8 bits tiếp theo [15:8]
  analogWrite(denxanhDaTroi, 255 - (giatridenLED & 0x0000FF)); // Giá trị màu xanh da trời là 8 bits cuối [7:0]
}
