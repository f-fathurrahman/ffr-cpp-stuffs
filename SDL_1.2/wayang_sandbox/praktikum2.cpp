void data_types()
{
  printf("%-14s %4s %20s %20s\n", "type", "size", "min", "max");
  printf("%-16s %2d %20d %20d\n", "char", sizeof(char), CHAR_MIN, CHAR_MAX);
  printf("%-16s %2d %20d %20d\n", "short", sizeof(short), SHRT_MIN, SHRT_MAX);
  printf("%-16s %2d %20d %20d\n", "int", sizeof(int), INT_MIN, INT_MAX);
  printf("%-16s %2d %20u %20u\n", "unsigned char", sizeof(unsigned char), 0, UCHAR_MAX);
  printf("%-16s %2d %20u %20u\n", "unsigned short", sizeof(unsigned short), 0, USHRT_MAX);
  printf("%-16s %2d %20u %20u\n", "unsigned int", sizeof(unsigned int), 0, UINT_MAX);
  printf("%-16s %2d %20e %20e\n", "float", sizeof(float), FLT_MIN, FLT_MAX);
  printf("%-16s %2d %20le %20le\n", "double", sizeof(double), DBL_MIN, DBL_MAX);
  printf("%-16s %2d %20lle %20lle\n", "long double", sizeof(long double), LDBL_MIN, LDBL_MAX);
}


/*** LATIHAN 2.1 GEOMETRI ***/

// Variabel global, wayang
hWayang nakula, sadewa;

/* Subrutin lat2_1
 * Mengambar rumah dengan koordinat kartesian dan polar
 */
void lat2_1() {

  // konstanta
  const int sisi = 100;     // panjang dinding

  // buat judul
  kSetCaption("Praktikum 2.1");

  // buat aktor nakula dan sadewa
  nakula = wCreate(1, "images/wayang/Nakula.png");
  sadewa = wCreate(1, "images/wayang/Sadewa.png");

  // gambar rumah, sudut D pada posisi (100, -200)
  // pakai koordinat kartesian relatif
  wJumpTo(sadewa, 200, -100);  // pindah ke sudut D
  wShow(sadewa);
  
  // bilang: Membuat rumah kartesian
  wSay(sadewa, sans16, 5000, "Ngedamel griya kartesian");

  // hitung koordinat pucuk rumah, pakai fungsi sin dan cos
  int sudut = 60.0 / 180.0 * M_PI;   // konversi ke radian
  int x = (sisi * cos(sudut));       // hitung posisi x
  int y = (sisi * sin(sudut));       // hitung posisi y

  // hidupkan jejak, ukuran 4, warna merah
  wSetTrail(sadewa, 4);
  wSetTrailColor(sadewa, RED);

  // mulai menggambar dengan wMove agar tampak jejaknya
  // tiap langkah didelay sedikit agar nampak bergeraknya
  wMove(sadewa, x, y);        // pindah ke A
  dDelay(500);
  wMove(sadewa, x,-y);        // pindah ke C
  dDelay(500);
  wMove(sadewa, 0, -sisi);    // pindah ke E
  dDelay(500);
  wMove(sadewa, -sisi, 0);    // pindah ke D
  dDelay(500);
  wMove(sadewa, 0, 100);     // pindah ke B
  dDelay(500);
  wMove(sadewa, 100, 0);     // pindah ke C


  // Gambar rumah, sudut D di posisi (0,-200)
  wJumpTo(nakula, 0, -100);   // pindah ke B
  wShow(nakula);
  wSay(nakula, sans16, 5000, "Ngedamel griya polar");

  // hidupkan jejak (trail) agar bisa menggambar
  wSetTrail(nakula, 4);
  wSetTrailColor(nakula, BLUE);

  // mulai menggambar pakai gerakan polar
  // wTurn: berputar menghadap sudut tertentu
  // wMoveForward: maju sejauh tertentu pada arah hadapan
  wTurn(nakula, 60);
  wMoveForward(nakula, sisi);  // pindah ke A
  dDelay(500);
  wTurn(nakula, -120);
  wMoveForward(nakula, sisi);  // ke C
  dDelay(500);
  wTurn(nakula, -30);
  wMoveForward(nakula, sisi);  // ke E
  dDelay(500);
  wTurn(nakula, -90);
  wMoveForward(nakula, sisi);  // ke D
  dDelay(500);
  wTurn(nakula, -90);
  wMoveForward(nakula, sisi);  // ke B
  dDelay(500);
  wTurn(nakula, -90);
  wMoveForward(nakula, sisi);  // ke C*/
}


/* fungsi lat2_2
 * membuat gambar pelangi warna-warni
 */
void lat2_2() {

  const int CENTER_X = -160;
  const int CENTER_Y = 60;
  const int RADIUS = 100;
  const int ANGLE_1 = 30;
  const int ANGLE_2 = 220;

  // variabel untuk menyimpan warna
  Uint8 red, green, blue;   // 8 bit warna dasar
  Uint32 color;             // 32 bit warna komplit

  kSetCaption("Praktikum 2.2");
  printf("Membuat pelangi\n");

  red   = 0xFF;  // warna dasar penuh
  green = 0xFF;  // hexadesimal
  blue  = 0xFF;  // desimal

  // siapkan pena Kelir 
  kSetThickness(20);  // tebal 20 pixel
  kSetOpaque(51);  // transparansi 20% dari 255
  
  // buat lengkungan pertama warna merah
  color = red;
  
  // cetak teks ke layar, pakai format hexa
  printf("Merah = %06lX\n", color);
  
  // ubah warna pena kelir
  kSetColor(color);
  
  // buat lengkungan pelangi
  kArc(CENTER_X, CENTER_Y, RADIUS, ANGLE_1, ANGLE_2);
  dDelay(500);

  // buat lengkungan warna kuning (merah campur hijau)
  color = (green << 8) | red;
  printf("Kuning = %06lX = %d\n", color);
  kSetColor(color);
  kArc(CENTER_X, CENTER_Y, RADIUS+15, ANGLE_1, ANGLE_2);
  dDelay(500);

  // buat lengkungan warna hijau
  color = green << 8;
  printf("Hijau = %06lX = %d\n", color);
  kSetColor(color);
  kArc(CENTER_X, CENTER_Y, RADIUS+30, ANGLE_1, ANGLE_2);
  dDelay(500);

  // buat lengkungan warna cyan (hijau campur biru)
  color = (green << 8) | (blue << 16) ;
  printf("Cyan = %06lX\n", color);
  kSetColor(color);
  kArc(CENTER_X, CENTER_Y, RADIUS+45, ANGLE_1, ANGLE_2);
  dDelay(500);

  // buat lengkungan warna biru
  color = ( blue << 16 );
  printf("Biru = %06lX\n", color);
  kSetColor(color);
  kArc(CENTER_X, CENTER_Y, RADIUS+60, ANGLE_1, ANGLE_2);
  dDelay(500);

  // buat lengkungan warna violet (biru campur merah)
  color = (blue << 16) | red;
  printf("Jingga = %06lX\n", color);
  kSetColor(color);
  kArc(CENTER_X, CENTER_Y, RADIUS+75, ANGLE_1, ANGLE_2);
  dDelay(500);

  // Sadewa dan nakula balik badan, melihat pelangi
  wFlipX(sadewa);
  wFlipX(nakula);
  wSay(sadewa, sans16, 3000, "Eh, ono kluwung ...");
  dDelay(1000);
}

// LATIHAN C. KINEMATIKA

/* Latihan 2.3
 * Nakula dan sadewa berjalan secara real-time
 * Waktu bisa diukur, dan berlaku rumus s = v * t
 */
void lat2_3() {
  Uint32 tstart, tfinish;
  int distance, dx, dy;
  int seconds, mseconds;
  float fseconds, fspeed, fdistance;

  kSetCaption("Praktikum 2.3");

  // Nakula akan berjalan ke kaki pelangi
  // pakai gerakan polar, dengan jarak tertentu
  // selama gerak waktunya diukur
  // sehingga kecepatan bisa dihitung

  // siap-siap jalan ke kaki pelangi
  wSay(nakula, sans16, 3000, "Ayo ngolek emas");
  wSetTrailOpaque(nakula, 20);   // samarkan trail
  wTurnTo(nakula, -10);
  distance = 320;

  // catat waktu mulai, dalam mili detik
  tstart = dGetTicks();
  // proses berjalan
  wStepForward(nakula, distance, 100);
  // catat waktu selesai, dalam mili detik
  tfinish = dGetTicks();

  // hitung selang waktu dalam detik dan mili detik (bulat)
  seconds = (tfinish - tstart) / 1000;  // hitung detik
  mseconds = tfinish - tstart; // hitung mili detik

  // menghitung kecepatan pixel / detik dalam pecahan
  // ini salah lho, betulkan !
  fseconds = (double)(tfinish - tstart)/1000.0;
    
  // hitung kecepatan sesuai rumus GLB
  fspeed = distance/fseconds;

  // tampilkan hasil perhitungan
  wTurnTo(nakula,0);
  wFlipX(nakula);
  wSay(nakula, sans16, 5000, "Kulo mlampah %d pixel", distance);
  wSay(nakula, sans16, 5000, "Suwene %d detik, %d mili detik", seconds, mseconds);
  wSay(nakula, sans16, 5000, "Ngebut %6.2f pixel/detik", fspeed);

  // kali ini sadewa yang jalan, pakai gerakan kartesian
  // dengan kecepatan sama dengan sadewa
  // sehingga kita akan tahu jaraknya
  wSetTrailOpaque(sadewa, 20);   // samarkan trail
  // delta perpindahan dalam sumbu x dan y
  dx = -125;
  dy = 125;

  tstart = dGetTicks();   // catat waktu mulai
  wStepTo(sadewa, dx, dy, fspeed); // operasi
  tfinish = dGetTicks();  // catat waktu selesai

  // hitung waktu dalam detik, jadi pecahan
  // ini salah lho, betulkan
  fseconds = (double)(tfinish - tstart) / 1000.0; 

  // hitung jarak, dibulatkan
  // ini terkena kesalahan pembulatan, betulkan
  distance = fspeed * fseconds; 

  // tampilkan hasil perhitungan
  wFlipX(sadewa);
  wSay(sadewa, sans16, 5000, "Kulo ngebut %7.2f pixel/detik", fspeed);
  wSay(sadewa, sans16, 5000, "Suwene %7.2f detik", fseconds);
  wSay(sadewa, sans16, 5000, "Adohe %d pixel", distance);

  // tampilkan jarak yang benar menurut pythagoras
  fdistance = sqrt(dx*dx + dy*dy);
  wSay(sadewa, sans16, 5000, "Kudune %7.2f pixel", fdistance);
}

// LATIHAN D. STATISTIKA

hWayang pohon;  // aktor yang mau ditanam

/* fungsi random integer 
 * kembali angka acak antara min - min+range
 */
int randInt(int min, int range) {
    // Ini kena rounding error, hasilnya min terus
    return min + (rand() / RAND_MAX * range); 

    // ini bisa overflow
    //return min + (range * rand() / RAND_MAX); 

    // yang paling efektif adalah pake modulo. Kok bisa ?
    // return min + (rand() % range);
}

/* fungsi random float
 * kembali angka acak antara min - min+range, pecahan
 */
float randFloat(float min, float range) {
    // pakai modulo seperti integer ?
    // float tak bisa, ini salah berat
    //return min + (rand() % range);
    
    // ini masih salah, kena rounding error
    //return min + (rand() / RAND_MAX * range);

    // yang benar adalah
    return min + ((float) rand() / RAND_MAX * range);

    // ini juga bisa
    // return min + (range / RAND_MAX * rand());
}

/* prosedur meletakkan pohon pada rentang tertentu
 * pakai prosedur / fungsi void
 */
void stampRandom(hWayang w, int x0, int y0) {
    // acak jenis pohon, sesuai banyak state
    wSetState(w, randInt(0, wGetStateNum(w))); 
  
    // acak posisi 20 pixel dari yang diminta
    wJumpTo(w, randInt(x0,20), randInt(y0,20));

    // skalakan tinggi antara 0.5 - 1.5
    wScaleTo(w, randFloat(0.5, 1.0));   

    // gambar pohon
    wStamp(w);

    // cetak ke konsole
    printf("Posisi=(%3d,%3d) Tinggi=%d\n", 
        wGetX(w), wGetY(w), wGetH(w));
}

/* Subrutin lat2_4
 * Mengambar pohon dengan tinggi dan posisi Y random
 */
void lat2_4() {
  kSetCaption("Praktikum 2.4");

  pohon = wCreate(4, "images/alam/pohon_01.png",
                     "images/alam/pohon_02.png",
                     "images/alam/pohon_03.png",
                     "images/alam/pohon_04.png");

  wSay(sadewa, sans16, 2000, "Tak nandur alas roban");

  // inisialisasi random
  srand(clock());

  // gambar 10 pohon pakai prosedur
  stampRandom(pohon, 280, 140);
  stampRandom(pohon, 260, 130);
  stampRandom(pohon, 380, 140);
  stampRandom(pohon, -280, 160);
  // silahkan, salin tempel terus sampai 10 pohon 
  // lebih banyak juga boleh ;)
  
  wSay(nakula, sans16, 2000, "Cape deh");
  wHide(nakula);
  wHide(sadewa);
}


