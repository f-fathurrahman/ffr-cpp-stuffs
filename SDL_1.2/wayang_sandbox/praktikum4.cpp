// Latihan 4.1
// Koordinat 2D sistem kartesian bisa didefinisikan jadi struktur
// berupa tipe data baru dengan nama "Cartesian"
typedef struct {
   int x;   // field koordinat sumbu x
   int y;   // field koordinat sumbu y
} Cartesian;
 
// Koordinat 2D sistem polar
typedef struct {
   float r;    // field radius
   float a;    // field angle (sudut)
} Polar;
 
// Setelah didefinisikan, struct berlaku sebagai tipe data baru
// bisa dipakai untuk argumen fungsi
float radiusC(Cartesian c1, Cartesian c2);
 
// maupun untuk kembalian fungsi
Polar toPolar(Cartesian c);
Cartesian toCartesian(Polar p);

// LATIHAN A. GEOMETRI
 
// Contoh struct
// Guna 1: bisa untuk mempersingkat / menyatukan argumen
// Tanpa struct, semua variabel argumen dikirim terpisah
// Lihat contoh fungsi radius di latihan3, bandingkan dengan ini
 
/* menghitung radius antara dua koordinat cartesian
 */
float radiusC(Cartesian c1, Cartesian c2) {
   int dx = c1.x - c2.x;
   int dy = c1.y - c2.y;
   return sqrt(dx*dx + dy*dy); 
}
 
// Guna 2: untuk kembalian banyak data
 
/* Fungsi konversi dari koordinat cartesian ke polar
 * Mengembalikan struct Polar, radius dan angle bersatu
 */
Polar toPolar(Cartesian c) {
    Polar p;
    p.r = sqrt((c.x* c.x) + (c.y * c.y)); // radius pythagoras
    p.a = atan2(c.y, c.x) / M_PI * 180;   // angle dalam degree
    return p;
}
 
// Tanpa struct, kita harus menulis banyak fungsi terpisah-pisah
// dengan kembalian tipe dasar (ini contoh kurang baik)
int toPolarRadius(int x, int y) {
   return sqrt(x * x + y * y);
}
 
float toPolarAngle(int x, int y) {
   return atan2(y, x);
}

// lanjutan latihan 4.1
 
// banyak item array, sangat dianjurkan dibuatkan konstanta
#define NPOLY 6
 
// memesan variabel polygon bernama cpoly
// berupa array struktur Cartesian sebanyak NPOLY.
// Variabel cpoly langsung diinisialisasi ke-6 itemnya
// Perhatikan bahwa nilai tiap item sesuai dengan posisi field
// di struct cartesian, dalam hal ini {x,y}
Cartesian cpoly[NPOLY] = {
  {12,0}, {0,80}, {-12,-16}, {-12,16}, {0,-80}, {12,0}
};
 
 
// memesan variabel bernama ppoly
// berupa array struktur Polar sebanyak NPOLY, tidak diinisialisasi
Polar ppoly[NPOLY];
 
// array bisa dijadikan argumen ke fungsi
// namun jumlah itemnya tak perlu didefinisikan.
// Dengan demikian, harus ada argumen terpisah yang
// menyatakan jumlah item (dalam hal ini n).
// Di dalam fungsi, akses array dengan indeks
// antara 0 hingga (n-1).
 
/* fungsi konversi polygon cartesian ke polygon polar
*/
void toPolars(int n, Cartesian c[], Polar p[]) {
  int i;
  float last_a = 0; // sudut awal
 
  for (i=0; i<n; i++) {
    p[i] = toPolar(c[i]); // pakai fungsi sebelumnya
    p[i].a = p[i].a - last_a; // sudut dibuat relatif
    last_a = last_a + p[i].a;
  }
}


// lanjutan latihan 4.1
 
/* fungsi menggambar polygon, koordinat cartesian
 */
void movePolygon(hWayang w, int n, Cartesian c[]) {
    // ulang untuk semua item array
    for (int i=0; i<n; i++) {
        // wayang pindah sesuai koordinat cartesian item
        wMove(w, c[i].x, c[i].y);
    }
}

/* fungsi menggambar polygon, koordinat polar
 */
void movePolarPolygon(hWayang w, int n, Polar p[]) {
    // ulang untuk semua item array p
    for (int i=0; i < n; i++) {
        // wayang turn lalu move forward sesuai item p
        wTurn(w, p[i].a);
        wMoveForward(w, p[i].r);
    }
}


// tokoh wayang episode ini
hWayang krisna, cakra;
 
/* krisna menggambar 8 polygon cartesian di bumi 
 * dan 8 polygon polar di langit
 */
void lat4_1() {
    // siapkan panggung
    kSetCaption("Praktikum 4.1");
    kSetImage("images/wayang/keraton_01.jpg");
 
    hUkoro sans16;
    sans16= uCreate("fonts/truetype/freefont/FreeSans.ttf", 16);

    // siapkan aktor
    cakra  = wCreate(2, "images/wayang/Cakra_01.png", "images/wayang/Cakra_02.png");
    krisna = wCreate(1, "images/wayang/Krisna.png");

    wJumpTo(krisna, -250, 140);
    wJumpTo(cakra,  -250, 140);
    wShow(krisna);
    wShow(cakra);
 
    wSay(krisna, sans16, 3000, "Cakra ning bumi");
    wStepTo(cakra, 0, -270, 1000);
    dPause(4000);
 
    // siapkan trail cakra ukuran 5, warna kuning, transparan 20%
    wSetTrail(cakra, 5);
    wSetTrailColor(cakra, YELLOW);
    wSetTrailOpaque(cakra, 20);
 
    // gambar 8 polygon berjejer, pakai cartesian
    // pengulangan 8 kali
    for (int i=0; i<8; i++) {
        // gambar polygon cartesian
        movePolygon(cakra, NPOLY, cpoly);
        // geser sedikit
        wJump(cakra, 40, 0);
    }
    dPause(2000);

    // lanjuk ke gambar kedua
    wSay(krisna, sans16, 3000, "Cakra ning langit");
    wJumpTo(cakra, 300, 160);
 
    // konversi polygon cartesian ke polygon polar
    toPolars(NPOLY, cpoly, ppoly);

    // gambar 9 polygon, pakai polar
    // ulang 9 kali
    for (int i=0; i<9; i++) {
        // gambar polygon polar
        movePolarPolygon(cakra, NPOLY, ppoly);
        // putar arah cakra 45 derajat
        wTurnTo(cakra, 40*(i+1));
    }
 
    // Krisna terbang ke tempat cakra, lalu berbalik
    wStepTo(krisna, 300, 160, 600);
    wFlipX(krisna);
}


