#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// Include pustaka proyek sendiri
#include "sprig/sprig.h"
#include "wayang/wayang.h"

// variabel elemen game
#define BUTO_MAX 8
hWayang buto[BUTO_MAX];      // pesan beberapa buto
hUkoro textR, textL, textC;  // pesan 3 ukoro untuk tampilan
 
// parameter game
int butoSpeed;               // kecepatan buto
int butoInterval;            // interval kemunculan buto
long butoTime;               // waktu buto boleh muncul
int butoNext;                // indeks buto yang akan muncul
int butoNum, butoWon;        // cacahan banyak buto
 
/* membuat 8 buah buto (raksasa)
 * dan 3 teks untuk menampilkan status buto
 */
void butoCreateAll() {
    // membuat 8 buah buto
    buto[0] = wCreate(1,"images/buto/buto_01.png");
    buto[1] = wCreate(1,"images/buto/buto_02.png");
    buto[2] = wCreate(1,"images/buto/buto_03.png");
    buto[3] = wCreate(1,"images/buto/buto_04.png");
    buto[4] = wCreate(1,"images/buto/buto_05.png");
    buto[5] = wCreate(1,"images/buto/buto_06.png");
    buto[6] = wCreate(1,"images/buto/buto_07.png");
    buto[7] = wCreate(1,"images/buto/buto_08.png");
 
    textL = uCreate("fonts/truetype/freefont/FreeSans.ttf", 20);
    uSetMode(textL, MODE_LEFT + MODE_SHOW);
    uJumpTo(textL, -380, 285);
    uSetColor(textL, YELLOW);
 
    textC = uClone(textL);
    uSetMode(textC, MODE_CENTER + MODE_SHOW);
    uJumpTo(textC, 0, 285);
 
    textR = uClone(textL);
    uSetMode(textR, MODE_RIGHT + MODE_SHOW);
    uJumpTo(textR, 380, 285);
}
 
/* Start seluruh buto ke kondisi awal
 */
void butoStartAll() {
    int i;
    srand(clock());
    for (i=0; i<BUTO_MAX; i++) {
        wHide(buto[i]);
    }
    butoSpeed = 5;
    butoInterval = 100;
    butoTime = 0;
    butoNext = rand() % BUTO_MAX;
    butoNum = 0;
    butoWon = 0;
}

/* guard mendeteksi apakah buto bisa hidup.
 * sekaligus menentukan kondisi berikutnya
 */
int butoCanAlive(int i) {
    int j;
    if ((butoNext == i) && (butoTime < dGetTicks())) {
        // tentukan waktu hidup berikutnya
        butoTime += (10 + rand() % 50) * butoInterval;
        // tentukan indeks buto yang akan hidup berikutnya
        butoNext = i = (i + 1 + (rand() % 5)) % BUTO_MAX;
        while(!wIsHidden(buto[butoNext])) {
            butoNext = (butoNext+1) % BUTO_MAX;
            if (butoNext == i) break;
        }
        return true;
    }
    return false;
}
 
/* guard mendeteksi apakah buto sudah finish
 */
int butoCanFinish(int i) {
    return (wGetX(buto[i]) >= kMaxX()+20);
}

/* action buto menjadi hidup
*/
void butoAlive(int i) {
    wJumpTo(buto[i], kMinX() - 20, 100 + rand() % 160);
    wShow(buto[i]);
    butoNum++;
    uSetText(textL, "Buto:%d", butoNum);
}
 
/* action buto selesai
*/
void butoFinish(int i) {
    wHide(buto[i]);
    butoWon++;
    uSetText(textR, "Lolos:%d", butoWon);
}
 
/* action buto bergerak
*/
void butoMove(int i) {
    wJump(buto[i], butoSpeed, 0);
}


/* Action buto atas event IsTime
 */
void butoRespondTime(int i) {
    // periksa state dulu
    if (wIsHidden(buto[i])) {
        // state = HIDDEN
        // periksa guard
        if (butoCanAlive(i)) {
            butoAlive(i);   // jalankan aksi
        }
    }
    else {
        // state = SHOWN
        butoMove(i); // jalankan aksi
        if (butoCanFinish(i)) {
            butoFinish(i); // jalankan aksi
        }
    }
}

void lat5_1 () {
    int i;
    // siapkan layar
    kSetCaption("Praktikum 5.1");
    kSetImage("images/wayang/keraton_02.jpg");
 
    // siapkan wayang
    butoCreateAll();
    butoStartAll();
 
    // loop utama dalang
    dStart(50);
    do {
        if (dIsTime()) {
            for (i=0; i<BUTO_MAX; i++) butoRespondTime(i);
        }
        if (dIsKey()) dBreak();
    } while (dNext());
    dFinish();
}


int main()
{
  kOpen(800, 600, "images/layar/infantis_246.jpg");
  lat5_1();
  kClose();
  return 0;
}


