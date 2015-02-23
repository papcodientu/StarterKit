/*
Mạch bật tất đèn LED bằng nút bấm dùng Arduino

Linh kiện:
- Nút bấm 4 chân
- Đèn LED
- Điện trở 220 Ohm, 10K Ohm
- Arduino Uno

Cách lắp mạch:
- Xem hình

Tác giả: Nhân Nguyễn
Ngày: 06/09/2014
Lịch sử thay đổi
- 04/11/2014 Rev. 1.0 Added button debounce
- 06/09/2014 Rev. 0.1 Draft, no button debounce
Website: http://papcodientu.com/
*/

const int nutBam = 2;    // nut bam noi vao pin 2 cua Arduino
const int denLED = 13;  // den LED noi vao pin 13 cua Arduino

int trangthaidenLED = LOW;  // trang thai den LED hien tai
int trangthaiNutBam;    // trang thai nut bam hien tai
int trangthainutbamTruoc = HIGH;   // trang thai nut bam truoc do
int tocdonhaydenLED = 1000;

long thoidiemDebounceTruoc = 0;  // thoi diem nut bam chuyen doi trang thai
long dotreDebounce = 50;   // do tre cua moi lan debounce

void setup() {
  // Khai báo các cổng trên board Arduino
  pinMode(denLED, OUTPUT);  // Đèn LED là thiết bị đầu ra (output)
  pinMode(nutBam, INPUT);   // Nút bấm là thiết bị đầu vào (input)
  
  // Thiet lap trang thai ban dau led va nut bam
  digitalWrite(denLED, trangthaidenLED);
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
        trangthaidenLED = !trangthaidenLED;  
      }
    }
  }
  
  if (trangthaidenLED == HIGH) {
    digitalWrite(denLED, HIGH);
    delay(tocdonhaydenLED);
    digitalWrite(denLED, LOW);  
    delay(tocdonhaydenLED);
  } else {
    digitalWrite(denLED, LOW); 
  }  
  
  // ghi lai gia tri nut bam
  trangthainutbamTruoc = giatriNutBam;
}
