
char* AUTHOR_NAME = "Fadjar Fathurrahman";
int   AUTHOR_NIM  = 13306023;
 
void about()
{
  printf("Oleh : %s\n", AUTHOR_NAME);
  printf("NIM  : %d\n", AUTHOR_NIM);
}


void lat1_2()
{
  kSetCaption("Praktikum 1.2");

  kSetColor(YELLOW);
  kFillArc(0, 210, 50, -60, 240);
  kSetOpaque(40);
  kFillCircle(0, 210, 100);

  kSetOpaque(150);
  kFillRectangle(-400, -260, 800, 120);

  kSetColor(WHITE);
  kSetOpaque(50);
  kSetThickness(10);
  kRectangle(-380, -240, 760, 80);
}


// global variables for Ukoro
hUkoro sans16;
hUkoro sans16a;
hUkoro jawa40;

void lat1_3()
{
  kSetCaption("Praktikum 1.3");
 
  // Menampilkan tulisan di kelir
  // harus memuat ukoro (teks) dulu, lalu panggil uPrint
  jawa40 = uCreate("fonts/truetype/jawa-latin.ttf", 40);
  uSetColor(jawa40, BLACK);
  uPrintC(jawa40, 0, -210, "Wayang Cyber");
 
  // Ukoro juga bisa tampil terus di atas kelir
  // Untuk itu harus dibuat obyek sendiri-sendiri
  // dan diletakkan pada tempat yang semestinya
  sans16= uCreate("fonts/truetype/freefont/FreeSans.ttf", 16);
  uSetColor(sans16, BLACK);
  uSetText(sans16, "Oleh : %s", AUTHOR_NAME);
  uJumpTo(sans16, -380, -285);
  uSetMode(sans16, MODE_LEFT + MODE_SHOW);
 
  // tulisan kedua dengan huruf sama
  // Klone dari ukoro lain
  sans16a= uClone(sans16);
  uSetText(sans16a, "NIM  : %d", AUTHOR_NIM);
  uJumpTo(sans16a, 380, -285);
  uSetMode(sans16a, MODE_RIGHT + MODE_SHOW);
}

/* Subrutin lat1_4
 * Memakai wayang 
 */
hWayang batu;
hWayang matahari;
hWayang awan;
 
void lat1_4() {
  kSetCaption("Praktikum 1.4");
 
  // Ganti gambar latar belakag
  kSetImage("images/alam/kelir_01.jpg");
 
  // Wayang
  batu = wCreate(1, "images/alam/bebatuan.png");
  awan = wCreate(1, "images/alam/awan.png");
  // Wayang dengan 2 gambar, agar bisa blink
  matahari = wCreate(2, "images/alam/matahari_01.png",
       "images/alam/matahari_02.png");
 
  // wayang batu loncat ke posisi tertentu,
  // lalu menggambar diri (tetap)
  wJumpTo(batu, -200, -200);
  wStamp(batu);
  wJumpTo(batu, -50, -230);
  wStamp(batu);
  wJumpTo(batu, -120, -235);
  wStamp(batu);
 
  const int SPEED = 300;

  // wayang, loncat ke posisi awal dan bergerak
  wJumpTo(matahari, -500, 250);
  wShow(matahari);
  wStepTo(matahari, -250, 250, SPEED);
 
  // wayang, bergerak meninggalkan jejak samar
  wJumpTo(awan, 350, 320);
  wShow(awan);
  wSetTrail(awan, 40);
  wSetTrailColor(awan, WHITE);
  wSetTrailOpaque(awan, 10);
  wStepTo(awan, -210, 230, SPEED);
 
  // wayang berubah bentuk 6 kali dengan periode 300 ms
  wBlink(matahari, 6, 300);
}
