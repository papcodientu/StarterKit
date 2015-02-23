/*
Nút bấm điều khiển đèn LED đa màu RGB

Linh kiện:
- Nút bấm 4 chân
- Đèn LED RGB 4 chân
- Điện trở 220 Ohm, 10K Ohm
- Arduino Uno

Cách lắp mạch:
- Xem hình

Tác giả: Tùng Nguyễn
Ngày: 06/09/2014
Lịch sử thay đổi
- 04/11/2014 Rev. 1.0 Added button debounce
- 06/09/2014 Rev. 0.1 Draft, no button debounce
Website: http://papcodientu.com/
*/

const int nutBam = 2;    // nut bam noi vao pin 2 cua Arduino
const int denxanhDaTroi = 9;  // chân đèn xanh da trời kết nối vào cổng 9
const int denxanhLaCay = 10;  // chân đèn xanh lá cây kết nối vào cổng 10s
const int denDo = 11;         // chân đèn đỏ kết nối vào cổng 11

int hienthidenLED = 0;  // trang thai den LED hien tai
int trangthaiNutBam;    // trang thai nut bam hien tai
int trangthainutbamTruoc = HIGH;   // trang thai nut bam truoc do

long thoidiemDebounceTruoc = 0;  // thoi diem nut bam chuyen doi trang thai
long dotreDebounce = 50;   // do tre cua moi lan debounce

void setup() {
  // Khai báo các cổng trên board Arduino
  pinMode(denxanhDaTroi, OUTPUT);  // Đèn LED là thiết bị đầu ra (output)
  pinMode(denxanhLaCay, OUTPUT);  // Đèn LED là thiết bị đầu ra (output)
  pinMode(denDo, OUTPUT);  // Đèn LED là thiết bị đầu ra (output)
  pinMode(nutBam, INPUT);   // Nút bấm là thiết bị đầu vào (input)
}

void loop() {
  int giatriNutBam = digitalRead(nutBam);  // doc gia tri cua nut bam
  
  // Neu trang thai nut bam thay doi, do viec bi nhieu hoac duoc nhan
  if (giatriNutBam != trangthainutbamTruoc) {
    // reset thoi diem debounce
    thoidiemDebounceTruoc = millis(); 
  }
  
  // nut bam duoc giu lau hon dotreDebounce, nut bam that su duoc nhan
  if ((millis() - thoidiemDebounceTruoc) > dotreDebounce) {
    // trang thai nut bam da thay doi
    if (giatriNutBam != trangthaiNutBam) {
      // thay doi trang thai nut bam bang gia tri hien tai
      trangthaiNutBam = giatriNutBam;
     
      // nut bam da duoc nhan
      if (trangthaiNutBam == LOW) {
        // thay doi trang thai den LED
        hienthidenLED += 1;  // mỗi lần nút nhấn giá trị tăng lên 1
      }
    }
  }
  
  // kiểm tra giá trị của biến hienthidenLED
  switch(hienthidenLED) {
    case 0:
      thietlapmaudenLED(255,0,0);    // màu đỏ
      break;
    case 1:
      thietlapmaudenLED(0,255,0);    // màu xanh lá cây
      break;
    case 2:
      thietlapmaudenLED(0,0,255);    // màu xanh da trời
      break;
    case 3:
      thietlapmaudenLED(255,0,255);    // màu vàng
      break;
    case 4:
      thietlapmaudenLED(255,255,0);    // màu tím
      break;
    case 5:
      thietlapmaudenLED(255,255,255);  // màu trắng
      break;
    default:
      hienthidenLED = 0;     // gán giá trị 0 cho biến
      break;
  }
  
  // ghi lai gia tri nut bam
  trangthainutbamTruoc = giatriNutBam;
}

void thietlapmaudenLED(int giatriDo, int giatrixanhDaTroi, int giatrixanhLaCay) {
  digitalWrite(denDo, 255 - giatriDo);  // thiết lập giá trị màu cho đèn đỏ
  digitalWrite(denxanhDaTroi, 255 - giatrixanhDaTroi);  // thiết lập giá trị màu cho đèn xanh da trời
  digitalWrite(denxanhLaCay, 255 - giatrixanhLaCay);  // thiết lập giá trị màu cho đèn xanh lá cây
}
