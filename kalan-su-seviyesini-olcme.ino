#include <dht11.h> //dth11 ve lcd ekranın kütüphanelerini ekliyoruz.
#include <LiquidCrystal.h>

#define trig1Pin 10 //Hc-sr04 ultrasonik mesafe sönsürlerinin pinlerini tanımlıyoruz.
#define echo1Pin 12
#define trig2Pin 11
#define echo2Pin 13
#define buzzerPin 3 //buzzer'ın pinini tanımlıyoruz.
#define dht11Pin 2 //dth11 sıcaklık ve nem sensörü pinini tanımlıyoruz.
dht11 sicaklik; //dth11 kütüphanesinden nesne oluşturuyoruz.
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); //lcd ekranın pinini tanımlıyoruz.

long sure1, uzaklik1, sure2, uzaklik2, sonuc , sensor1, sensor2; //mesafe sönsüründe kullanılacak değişkenleri tanımlıyoruz.
int deger; //sıcaklık ölçme de kullanılacak değişkeni tanımlıyoruz.

void setup() {
  Serial.begin(9600); //seri port ekranında da yazmasını istediğimiz için seri port ekranını başlatıyoruz.
  lcd.begin(16, 2); //lcd mizin 16x2 lcd olduğunu belirtiyoruz.
  pinMode(trig1Pin, OUTPUT); //mesafe sönsörlerin trig pinlerini çıkış,
  pinMode(echo1Pin, INPUT); //echo pinlerini giriş olarak ayarlıyoruz.
  pinMode(trig2Pin, OUTPUT);
  pinMode(echo2Pin, INPUT);
  pinMode(buzzerPin, OUTPUT); //buzzer pinini çıkış,
  pinMode(dht11Pin, INPUT);   //sıcaklık nem sensörünün pinini giriş olarak ayarlıyoruz.
}

void loop() {
  Sensor1Hesapla(trig1Pin, echo1Pin); //Sensor1Hesapla() fonksiyonuna trig ve echo pinlerini gönderiyoruz ve uzaklık hesaplama orada yapılıyor.
  sensor1 = uzaklik1; //sensor1 değişkenine hesaplanan uzaklık1 değerini atıyoruz.
  Sensor2Hesapla(trig2Pin, echo2Pin); //Sensor2Hesapla() fonksiyonuna trig ve echo pinlerini gönderiyoruz ve uzaklık hesaplama orada yapılıyor.
  sensor2 = uzaklik2; //sensor2 değişkenine hesaplanan uzaklık2 değerini atıyoruz.

  //Burada su bardağını baz alarak zeminden yüksekliği 10 cm olduğundan 10 değerini kullandık. Siz burada kullanacağınız ürünün yüksekliğini yazabilirsiniz.
  if (sensor1 > 10) { //Eğer hesaplamada çıkan sonuc 10 cm ve üzeri bütün uzaklıklar ise 10 cm olarak yazacak.
    sensor1 = 10;
  }
  if (sensor2 > 10) { //Aynı şekilde sensor2 içinde aynı işlemleri uyguladık.
    sensor2 = 10;
  }
  sonuc = sensor1 - sensor2;  //birinci sensörün değerinden ikinci sensörün değerini çıkarttığımızda bize kalan su seviyesini verecek ve
                              //çıkan sonucu, sonuc değişkenine atayacağız.

  Serial.print("uzaklik1:"); //mesafe sensörlerinin uzaklıklarını ve kalan mesafe sonucunu seri port ekranında yazdırıyoruz.
  Serial.println(sensor1);
  Serial.print("uzaklik2:");
  Serial.println(sensor2);
  Serial.print("sonuc:");
  Serial.println(sonuc);

  BuzzerCalis(sonuc); //çıkan uzaklığa yani sonuca göre BuzzerCalis() fonksiyonuna değeri gönderiyoruz ve orada işlemleri yaptırıyoruz.
  SicaklikHesapla(); //SicaklikHesapla() fonksiyonunu çağırıyoruz.
  LcdYaz(sonuc); //çıkan uzaklığa yani sonuca göre LcdYaz() fonksiyonuna değeri gönderiyoruz ve orada işlemleri yaptırıyoruz.
  delay(1500); //bu işlemler 1.5 sn'de bir tekrarlanacak.
}

void Sensor1Hesapla(int trigPin, int echoPin) { //Sensor1Hesapla() fonksiyonunda sensor1'in uzaklığı hesaplanıyor.
  digitalWrite(trigPin, LOW); //trip pinini durumunu LOW olarak başlatıyoruz.
  delayMicroseconds(5); //5 mikrosaniye(saniyenin milyonda biri) beklemesini belirtiyoruz.
  digitalWrite(trigPin, HIGH); //Daha sonra pinimizin ses dalgası göndermesi için açıyoruz yani HIGH yapıyoruz.
  delayMicroseconds(10); //10 mikrosaniye(saniyenin milyonda biri) beklemesini belirtiyoruz.
  digitalWrite(trigPin, LOW); //yeni ses dalgası üretebilmesi için trig pinimizi pasif durumuna yani LOW durumuna getiriyoruz.

  sure1 = pulseIn(echoPin, HIGH); //gönderilen ses dalgasının geri dönmesindeki süre ölçülüyor.
  uzaklik1 = sure1 / 29.1 / 2; //ölçütüğümüz süre uzaklığa çevriliyor ve değeri uzaklik1 değişkenine atıyoruz.
}

void Sensor2Hesapla(int trigPin2, int echoPin2) { //Sensor2Hesapla() fonksiyonunda sensor2'in uzaklığı hesaplanıyor.
  digitalWrite(trigPin2, LOW); //Sensor1Hesapla() fonksiyonundaki açıklamaların aynısı burada da geçerlidir.
  delayMicroseconds(5);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  sure2 = pulseIn(echoPin2, HIGH);
  uzaklik2 = sure2 / 29.1 / 2;
}

void BuzzerCalis(int sonuc) { //mesafe 5 cm den küçük ise yani su seviyesi yarımdan az ise buzzer 1 sn ötecek ve 1 sn susacak.
  if (sonuc < 5) {
    digitalWrite(buzzerPin, HIGH);
    delay(1000);
    digitalWrite(buzzerPin, LOW);
    delay(1000);
  }
}

void SicaklikHesapla() { //ortamın sıcaklığı ölçülüyor ve ölçülen sıcaklığı seri port ekranına yazdırıyoruz.
  deger = sicaklik.read(dht11Pin);
  Serial.print("Sicaklik (Celcius): ");
  Serial.println((float)sicaklik.temperature, 2);
}

void LcdYaz(int sonuc) { //eğer mesafe yarımdan az ise lcd ekranına 
  if (sonuc < 5) {
    lcd.setCursor(0, 0); //setCursor ile 0.satır - 0.sutundan yazmaya başla yapıyoruz.
    lcd.print("Sicaklik:"); //Sicaklik: yazacak.
    lcd.setCursor(9, 0); //0.satır - 9.sutundan yazmaya devam edecek.
    lcd.print((float)sicaklik.temperature, 2); //ölçülen sıcaklık değerini örn; 12.00 şeklinde yazacak.
    lcd.setCursor(0, 1); //1.satır - 0.sutundan yazmaya başlayacak.
    lcd.print("Su ekle!"); //Su ekle! yazacak.
    lcd.setCursor(8, 1); //1.satır - 8.sutundan yazmaya başlayacak.
    lcd.print(sonuc); //kalan mesafeyi yani sonucu yazacak.
    lcd.setCursor(9, 1); //1.satır - 9.sutundan yazmaya başlayacak.
    lcd.print("cm kldi"); //cm kaldi yazacak.
    delay(3000); //bu işlemi 3 sn'de bir tekrarlayacak.
    lcd.clear(); //her seferinde lcd ekranı temizleyecek ve yeniden yazacak.
  }
  else { //eğer mesafe normal seviyede ise lcd ekrana if'de yaptığımız gibi mesaj niteliğinde kalan mesafeyi ve ortam sıcaklığını yazacak.
    lcd.setCursor(0, 0);
    lcd.print("Sicaklik:");
    lcd.setCursor(9, 0);
    lcd.print((float)sicaklik.temperature, 2);
    lcd.setCursor(0, 1);
    lcd.print("Su seviyesi:");
    lcd.setCursor(12, 1);
    lcd.print(sonuc);
    lcd.setCursor(14, 1);
    lcd.print("cm");
    delay(3000);
    lcd.clear();
  }
}
