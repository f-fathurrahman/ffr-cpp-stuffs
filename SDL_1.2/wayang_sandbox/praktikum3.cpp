// fungsi menggambar bintang
// posisi sudut A di (x,y), panjang segment s

void drawStar( hWayang w, int x, int y, int s )
{
  // menggambar bintang, gerakan polar
  wJumpTo(w, x, y);   // ke titik A

  // inisialisasi variabel kondisi
  int sudut = 0;

  // ulang, pakai pemeriksaan akhir saja
  // karena blok pasti dieksekusi minimal sekali
  do {
    // perintah blok
    wTurnTo(w, sudut);
    wMoveForward(w, s);

    // update kondisi
    sudut = sudut - 144;
  } while (sudut >= -576);   // kondisi berhenti
}

// tokoh wayang yang bisa terbang ...
hWayang gatotkaca;

void lat3_1() {
  // definisi warna bintang oranye
  const Uint32 STAR_COLOR = 0xFF0000;
  kSetCaption("Praktikum 3.1");
  gatotkaca = wCreate(1, "images/wayang/Gatotkaca.png");
  wJumpTo(gatotkaca,-200,-200);
  wShow(gatotkaca);
  wSay(gatotkaca, sans16, 5000, "Aku satrio pringondani");
  wSay(gatotkaca, sans16, 5000, "Saged mabur nabur bintang ...");
  wSetTrail(gatotkaca, 2);
  wSetTrailOpaque(gatotkaca, 255);
  wSetTrailColor(gatotkaca, STAR_COLOR);

  // manual, tidak pakai loop
  wJumpTo(gatotkaca, 0, 250);
  wTurnTo(gatotkaca, 0);

  // gambar pakai wTurnTo relatif
  wMoveForward(gatotkaca, 50);
  wTurn(gatotkaca, -144);
  wMoveForward(gatotkaca, 50);  // ke titik E
  wTurnTo(gatotkaca, -288);
  wMoveForward(gatotkaca, 50);  // ke B
  wTurnTo(gatotkaca, -432);
  wMoveForward(gatotkaca, 50);  // ke D
  wTurnTo(gatotkaca, -576);
  wMoveForward(gatotkaca, 50);  // ke A

  // gambar banyak bintang pakai prosedur
  // loop posisi x pada 50, 100, ..., 200
  for (int x = 50; x <= 200; x = x + 50) {
    drawStar(gatotkaca, x, randInt(230, 50), randInt(20, 30));
  }

  wSetTrail(gatotkaca, 0);
  wStepTo(gatotkaca, -200, 50, 500);
}
