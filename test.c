// #include <stdio.h>

// // Struktur data untuk menyimpan pemasukan dan pengeluaran per minggu
// typedef struct {
//     double pemasukan;
//     double pengeluaran;
// } DataMingguan;

// int main() {
//     // Mengatur jumlah minggu dalam satu bulan (asumsi 4 minggu)
//     const int JUMLAH_MINGGU = 4;
//     DataMingguan data[JUMLAH_MINGGU];

//     double total_pemasukan_bulanan = 0.0;
//     double total_pengeluaran_bulanan = 0.0;
//     double total_tabungan_bulanan = 0.0;
//     double rasio_menabung = 0.0;

//     printf("--- Sistem Input Laporan Keuangan ---\n");
//     printf("Silakan masukkan data keuangan untuk %d minggu terakhir.\n\n", JUMLAH_MINGGU);

//     // --- PROSES INPUT DATA PER MINGGU ---
//     for (int i = 0; i < JUMLAH_MINGGU; i++) {
//         printf("===== Data Minggu ke-%d =====\n", i + 1);
//         printf("Masukkan total Pemasukan : Rp. ");
//         scanf("%lf", &data[i].pemasukan);
//         printf("Masukkan total Pengeluaran: Rp. ");
//         scanf("%lf", &data[i].pengeluaran);
//         printf("\n");
//     }

//     // --- PROSES PERHITUNGAN ---
//     // 1. Menghitung total pemasukan dan pengeluaran bulanan
//     for (int i = 0; i < JUMLAH_MINGGU; i++) {
//         total_pemasukan_bulanan += data[i].pemasukan;
//         total_pengeluaran_bulanan += data[i].pengeluaran;
//     }

//     // 2. Menghitung total tabungan (Asumsi: Tabungan = Pemasukan - Pengeluaran)
//     // Bagian ini sesuai dengan logika umum, di mana tabungan adalah sisa dari pendapatan.
//     total_tabungan_bulanan = total_pemasukan_bulanan - total_pengeluaran_bulanan;

//     // 3. Menghitung Rasio Menabung
//     // Cek untuk menghindari pembagian dengan nol jika tidak ada pemasukan
//     if (total_pemasukan_bulanan > 0) {
//         rasio_menabung = (total_tabungan_bulanan / total_pemasukan_bulanan) * 100.0;
//     } else {
//         rasio_menabung = 0;
//     }

//     // --- MENAMPILKAN LAPORAN FINAL ---
//     printf("\n========================================\n");
//     printf("===   LAPORAN KEUANGAN FINAL BULANAN  ===\n");
//     printf("========================================\n");
//     printf("Total Pemasukan Bulanan  : Rp. %.2f\n", total_pemasukan_bulanan);
//     printf("Total Pengeluaran Bulanan : Rp. %.2f\n", total_pengeluaran_bulanan);
//     printf("----------------------------------------\n");
//     printf("Total Tabungan Bulanan    : Rp. %.2f\n", total_tabungan_bulanan);
//     printf("----------------------------------------\n");
//     printf("Rasio Menabung            : %.2f%%\n", rasio_menabung);
//     printf("========================================\n\n");

//     // --- ANALISIS KESEHATAN KEUANGAN ---
//     printf("--- ANALISIS KESEHATAN KEUANGAN ANDA ---\n");
//     if (rasio_menabung > 20) {
//         printf("Status: IDEAL (> 20%%)\n");
//         printf("Selamat! Kekayaan Anda akan tumbuh dengan cepat. Pertahankan disiplin ini!\n");
//     } else if (rasio_menabung >= 10) {
//         printf("Status: MINIMAL (10%% - 20%%)\n");
//         printf("Ini adalah batas terendah agar keuangan tidak stagnan. Pertimbangkan untuk menaikkannya.\n");
//     } else if (rasio_menabung >= 0) {
//         printf("Status: KURANG SEHAT (< 10%%)\n");
//         printf("Anda mungkin terlalu boros atau penghasilan perlu ditingkatkan. Segera evaluasi pengeluaran Anda.\n");
//     } else {
//         printf("Status: WASPADA (Pengeluaran > Pemasukan)\n");
//         printf("Keuangan Anda defisit! Segera lakukan perubahan drastis pada pengeluaran atau cari sumber pemasukan tambahan.\n");
//     }
//     printf("------------------------------------------\n");

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>  // Untuk input keyboard (_kbhit, _getch)
#include <windows.h> // Untuk fungsi Sleep dan kontrol kursor
#include <time.h>   // Untuk angka acak

// Konfigurasi Area Game
#define WIDTH 20
#define HEIGHT 20

int playerX;
int score;
int coinX, coinY;
int gameOver;

// Fungsi untuk menyembunyikan kursor agar tampilan lebih bersih
void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

// Fungsi untuk memindahkan posisi kursor (menghindari flickering dibanding system("cls"))
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setup() {
    gameOver = 0;
    score = 0;
    playerX = WIDTH / 2; // Pemain mulai di tengah
    
    // Posisi awal koin
    srand(time(0));
    coinX = rand() % (WIDTH - 2) + 1;
    coinY = 0;
    
    hideCursor();
}

void draw() {
    // Kembali ke titik 0,0 daripada menghapus layar (mengurangi kedip)
    gotoxy(0, 0);

    // Gambar batas atas
    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");

    // Gambar area permainan
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0) printf("#"); // Dinding kiri

            if (i == coinY && j == coinX) {
                printf("$"); // Gambar Koin
            }
            else if (i == HEIGHT - 1 && j == playerX) {
                printf("U"); // Gambar Pemain (Keranjang)
            }
            else {
                printf(" "); // Ruang kosong
            }

            if (j == WIDTH - 1) printf("#"); // Dinding kanan
        }
        printf("\n");
    }

    // Gambar batas bawah
    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");

    // Tampilkan Skor & Kontrol
    printf("Skor: %d\n", score);
    printf("Kontrol: 'a' (Kiri) | 'd' (Kanan) | 'x' (Keluar)\n");
}

void input() {
    if (_kbhit()) { // Mengecek apakah ada tombol yang ditekan
        char current = _getch();
        switch (current) {
            case 'a': // Gerak Kiri
                if (playerX > 0) playerX--;
                break;
            case 'd': // Gerak Kanan
                if (playerX < WIDTH - 1) playerX++;
                break;
            case 'x': // Keluar game
                gameOver = 1;
                break;
        }
    }
}

void logic() {
    // Gerakkan koin ke bawah
    coinY++;

    // Cek apakah koin tertangkap
    if (coinY == HEIGHT - 1) {
        if (coinX == playerX) {
            score += 10; // Tambah skor
            // Reset koin ke atas di posisi acak baru
            coinX = rand() % (WIDTH - 2) + 1;
            coinY = 0;
        }
    }

    // Cek jika koin menyentuh tanah (melewati pemain)
    if (coinY >= HEIGHT) {
        // Game Over jika koin jatuh (opsional, bisa diubah jadi kurangi nyawa)
        gameOver = 1; 
    }
}

int main() {
    setup();

    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(100); // Mengatur kecepatan game (makin kecil makin cepat)
    }

    // Pesan Game Over
    gotoxy(0, HEIGHT + 4);
    printf("\n=== GAME OVER ===\n");
    printf("Skor Akhir Anda: %d\n", score);
    printf("Tekan apa saja untuk keluar...");
    _getch();

    return 0;
}