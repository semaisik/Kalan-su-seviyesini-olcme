# Kalan Su Seviyesini Ölçen Proje
Su Seviyesi / Yağmur Sensörü adında su seviyesini ölçen sensör mevcut. Fakat ben yağmur sensörünü kullanmadan farklı materyaller kullanarak kalan su seviyesini ölçen proje gerçekleştirdim.

# Projenin Çalışma Mantığı
Birinci HC-SR04 Ultrasonik Mesafe Sensörü ile kabın zeminden yüksekliği hesaplandı. İkinci ultrasonik mesafe sensörü ile kabın içindeki suyu algıladığı yerden itibaren yüksekliği hesaplandı. Elde edilen bu iki sonucu birinci sensörden ikinci sensörü çıkararak arada kalan yani kalan su seviyesini hesaplamış olduk.
Ayrıca ortamın sıcaklığını DTH11 Sıcaklık ve Nem Sensörü ile ölçümünü yaptık.
Bulunan değerleri öncelikle seri port ekranında birinci sensörün, ikinci sensörün uzaklığı ve bu uzaklıklardan elde edilen kalan mesafeyi ve sıcaklık değerini yazdırdık.
Daha sonra ortam sıcaklığını, kalan su seviyesi yarının üzerinde ise 16x2’lik lcd ekranda örneğin;
“Sicaklik: 14.00
 Su seviyesi:7 cm” şeklinde yazı yazacak. 
Eğer kalan su seviyesi yarının altında ise buzzer ötecek ve 16x2’lik lcd ekranda örneğin;
“Sicaklik: 14.00
 Su ekle! 3 cm kaldi” şeklinde yazı yazacak.
Potansiyometre ise lcd ekranın parlaklığını ayarlamak için kullanıldı.

# NOT1
Projede su bardağı kullandım. Su bardağının yüksekliği 10 cm idi.  Siz kullanacağınız ürüne göre programdaki 10 cm olan yerleri ürününüzün yüksekliği ile değiştirebilirsiniz.
# NOT2 
Programdaki kodların ne işe yaradığını yorum satırları ile yanlarına ekledim. Çok rahat bir şekilde program kodlarını anlayabilirsiniz.

# Gerekli Malzemeler
    2x HC-SR04 Ultrasonik Mesafe Sensörü
    1x 16x2 LCD Ekran
    1x Buzzer
    1x 1K Potansiyometre
    1x DTH11 Sıcaklık ve Nem Sensörü
    1x 10K Direnç
    1x Arduino Uno
    40x Jumper Kablo
    2x Breadboard
