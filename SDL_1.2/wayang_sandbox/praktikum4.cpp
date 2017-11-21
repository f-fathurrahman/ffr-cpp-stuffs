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

s 
