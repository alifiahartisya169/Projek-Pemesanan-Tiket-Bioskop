#include <iostream>
#include <conio.h>
#include <fstream>     
#include <queue>
#include <stack>
#include <string>
#include <cstring>
#include <string.h>
#include <vector>
#include <sstream>
#include <limits>
#include <iomanip>
#include <cctype>
#include <limits>
#include <cstdlib>
#include <algorithm>
#include <dirent.h>
using namespace std;

struct Akun {
    string nama_lengkap;
    string no_telepon;
    string email;
    string username;
    string password;
};

struct Akunadmin {
    string nama_lengkap;
    string no_telepon;
    string email;
    string username;
    string password;
};

struct Film {
    char judul[100];
    char sinopsis[1000];
    char waktu[30];
    char durasi[50];
    char genre[50];
    int harga;
    char studio;
};

struct Studio {
    char nama[20];
    Film jadwal[10];
    int jumlahFilm;
};

struct Pemesanan {
    string namaPemesan;
    string studio;
    string judulFilm;
    string waktu;
    string durasi;
    string genre;
    string jenisTiket;
    int harga;
    int jumlahTiket;
    int totalHarga;
    vector<string> kursi;
    string metodePembayaran;
    bool sudahDibayar = false;
};

vector<Akun> bacaAkun() {
    vector<Akun> daftar;
    ifstream file("akun.txt");
    Akun a;

    while (getline(file, a.nama_lengkap)) {
        getline(file, a.no_telepon);
        getline(file, a.email);
        getline(file, a.username);
        getline(file, a.password);
        daftar.push_back(a);
    }
    file.close();
    return daftar;
}

vector<Akunadmin> bacaAkunadmin() {
    vector<Akunadmin> daftar;
    ifstream file("akunadmin.txt");
    Akunadmin a;

    while (getline(file, a.nama_lengkap)) {
        getline(file, a.no_telepon);
        getline(file, a.email);
        getline(file, a.username);
        getline(file, a.password);
        daftar.push_back(a);
    }
    file.close();
    return daftar;
}

void simpanAkun(const vector<Akun>& daftar) {
    ofstream file("akun.txt");
    for (size_t i = 0; i < daftar.size(); ++i) {
        file << daftar[i].nama_lengkap << "\n"
             << daftar[i].no_telepon << "\n"
             << daftar[i].email << "\n"
             << daftar[i].username << "\n"
             << daftar[i].password << "\n";
    }
    file.close();
}

void simpanAkunadmin(const vector<Akunadmin>& daftar) {
    ofstream file("akunadmin.txt");
    for (size_t i = 0; i < daftar.size(); ++i) {
        file << daftar[i].nama_lengkap << "\n"
             << daftar[i].no_telepon << "\n"
             << daftar[i].email << "\n"
             << daftar[i].username << "\n"
             << daftar[i].password << "\n";
    }
    file.close();
}

void registrasi() {
    system("CLS");
    Akun baru;
    cout << "============ Registrasi Akun Baru ============\n\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Nama lengkap : "; getline(cin, baru.nama_lengkap);
    cout << "Nomor telepon: "; getline(cin, baru.no_telepon);
    cout << "Email        : "; getline(cin, baru.email);
    cout << "Username     : "; getline(cin, baru.username);
    cout << "Password     : "; getline(cin, baru.password);

    vector<Akun> daftar = bacaAkun();

    for (size_t i = 0; i < daftar.size(); ++i) {
        if (daftar[i].username == baru.username) {
            cout << "\nUsername sudah digunakan.\n\n";
            system("pause");
            return;
        }
    }

    daftar.push_back(baru);
    simpanAkun(daftar);
    cout << "\nRegistrasi berhasil.\n\n";
    system("pause");
}

enum JenisLogin { TIDAK_LOGIN = -1, LOGIN_USER = 0, LOGIN_ADMIN = 1 };

int login(JenisLogin &tipeLogin) {
    system("CLS");
    string uname, pass;
    cout << "============ Login ============\n\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Username: "; getline(cin, uname);
    cout << "Password: "; getline(cin, pass);

    vector<Akun> daftar = bacaAkun();
    for (size_t i = 0; i < daftar.size(); ++i) {
        if (daftar[i].username == uname && daftar[i].password == pass) {
            cout << "\nLogin sebagai User berhasil. Selamat datang, " << daftar[i].nama_lengkap << "!\n\n";
            tipeLogin = LOGIN_USER;
            system("pause");
            return (int)i;
        }
    }

    vector<Akunadmin> daftarAdmin = bacaAkunadmin();
    for (size_t i = 0; i < daftarAdmin.size(); ++i) {
        if (daftarAdmin[i].username == uname && daftarAdmin[i].password == pass) {
            cout << "\nLogin sebagai Admin berhasil. Selamat datang, " << daftarAdmin[i].nama_lengkap << "!\n\n";
            tipeLogin = LOGIN_ADMIN;
            system("pause");
            return (int)i;
        }
    }

    cout << "\nUsername atau password salah.\n\n";
    tipeLogin = TIDAK_LOGIN;
    system("pause");
    return -1;
}


void hapusAkun() {
    system("CLS");
    string uname, pass;
    char konfirmasi;
    cout << "============ Hapus Akun ============\n\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Username: "; getline(cin, uname);
    cout << "Password: "; getline(cin, pass);

    vector<Akun> daftar = bacaAkun();
    bool ditemukan = false;

    for (size_t i = 0; i < daftar.size(); ++i) {
        if (daftar[i].username == uname && daftar[i].password == pass) {
            cout << "\nYakin ingin menghapus akun ini? (y/n): ";
            cin >> konfirmasi;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (konfirmasi == 'y' || konfirmasi == 'Y') {
                daftar.erase(daftar.begin() + i);
                simpanAkun(daftar);
                cout << "\nAkun berhasil dihapus.\n";
                system("pause");
            } else if(konfirmasi == 'n' || konfirmasi == 'N'){
                cout << "\nPenghapusan dibatalkan.\n";
                system("pause");
            } else {
                cout << "\nInput Invalid!. Penghapusan dibatalkan.\n";
                system("pause");
            }
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "\nAkun tidak ditemukan atau password salah.\n";
        system("pause");
    }
}

void menu_before_login() {
    system("CLS");
    cout << "============ MENU LOGIN ============\n\n";
    cout << "[1] Registrasi Akun\n";
    cout << "[2] Login\n";
    cout << "[3] Hapus Akun\n";
    cout << "[0] Keluar\n";
    cout << "\nPilih (1-3) : ";
}

void menu_after_login() {
    cout << "\n";
    cout << "============ MENU UTAMA ============\n\n";
    cout << "[1] Lihat Data Diri\n";
    cout << "[2] Lihat Jadwal Tayangan\n";
    cout << "[3] Pesan Tiket\n";
    cout << "[4] Buka File Pesanan\n";
    cout << "[5] Edit Tiket\n";
    cout << "[6] Edit Pesan Kursi\n";
	cout << "[7] Logout\n";
	cout << "[0] Keluar\n";
    cout << "\nPilih (1-7) : ";
}

void menu_admin() {
	system("CLS");
    cout << "============ MENU ADMIN ============\n\n";
    cout << "[1] Tampilkan Daftar Film\n";
    cout << "[2] Pesan Tiket" << endl;
    cout << "[3] Buka File Pesanan" << endl;
	cout << "[4] Edit Pesanan" << endl;
	cout << "[5] Edit Pesan Kursi" << endl;
	cout << "[6] Statistik Kursi Terisi\n";
	cout << "[7] Logout" << endl;
    cout << "[0] Keluar" << endl;
    cout << "\nPilih (1-7) : ";
}

void lihatDataDiri(const Akun& user){
    system("CLS");
    cout << "============ Data Diri ============\n\n";
    cout << "Username      : " << user.username << "\n";
    cout << "Nama lengkap  : " << user.nama_lengkap << "\n";
    cout << "Nomer Telepon : " << user.no_telepon << "\n";
    cout << "Alamat Email  : " << user.email << "\n\n";
	system("pause");  
}

void tampilkan_logo_bioskop(){
	system("CLS");
	cout << "\t  ____ ___ _    _ _____ __  __  _____   __    ____    __ ___    ______ __  __ ____ ___ ____  _____\n";
	cout << "\t / ___|_ _| \\  | | ____|  \\/  |/  __ \\  \\ \\  / /\\ \\  / /|_ _|  |  ____|  \\/  |    \\_ _|    \\| ____|\n";
	cout << "\t| |    | ||  \\ | | |__ | |\\/| ||  || |   \\ \\/ /  \\ \\/ /  | |   | |__  | |\\/| | |> || || |> || |__\n";
	cout << "\t| |    | ||   \\| |  __|| |  | ||  __ |    >  <    >  <   | |   |  __| | |  | |  __/| ||   _/|  __|\n";
	cout << "\t| |___ | || |\\   | |___| |  | || / | |   / /\\ \\  / /\\ \\  | |   | |___ | |  | | |   | || | \\ | |___\n";
	cout << "\t \\____|___|_| \\__|_____|_|  |_||_| |_|  /_/  \\_\\/_/  \\_\\|___|  |______|_|  |_|_|  |___|_|\\_\\|_____|\n";
}

void tampilfilm(){
	string back;
	system("cls");
	cout<<"|=========================================================================================================================|\n";
	cout<<"|                                                         DAFTAR FILM                                                     |\n";
	cout<<"+------+--------------------------------------------+-----------------+----------------------------+----------------------+\n";
	cout<<"|  NO  |                  Judul Film                |      Harga      |         Waktu Tayang       |          Genre       |\n";
	cout<<"+------+--------------------------------------------+-----------------+----------------------------+----------------------+\n";
	cout<<"|=========================================================================================================================|\n";
	cout<<"|                                                           STUDIO 1                                                      |\n";
	cout<<"+------+--------------------------------------------+-----------------+----------------------------+----------------------+\n";
	cout<<"|  1.  |                   BALLERINA                |   Rp 35.000     |    12:00:00 - 14:04:00     |   Action, Thriller   |\n";
	cout<<"|  2.  |       FINAL DESTINATION: BLOODLINES        |   Rp 45.000     |    14:20:00 - 15:50:00     |         Action       |\n";
	cout<<"|  3.  |                    GUNDIK                  |   Rp 45.000     |    16:15:00 - 18:07:00     |         Action       |\n";
	cout<<"|  4.  |                WAKTU MAGHRIB 2             |   Rp 40.000     |    12:00:00 - 14:04:00     |         Horor        |\n";
	cout<<"|  5.  |             KARATE KID: LEGENDS            |   Rp 45.000     |    20:50:00 - 22:20:00     |         Action       |\n";
	cout<<"|  6.  |            GOWOK KAMASUTRA JAWA            |   Rp 35.000     |    22:30:00 - 00:35:00     |         Drama        |\n";
	cout<<"|=========================================================================================================================|\n";
	cout<<"|                                                           STUDIO 2                                                      |\n";
	cout<<"+------+--------------------------------------------+-----------------+----------------------------+----------------------+\n";
	cout<<"|  1.  |                    GUNDIK                  |   Rp 45.000     |    12:05:00 - 13:57:00     |         Action       |\n";
	cout<<"|  2.  |                   BALLERINA                |   Rp 35.000     |    14:20:00 - 16:24:00     |   Action, Thriller   |\n";
	cout<<"|  3.  |                   BALLERINA                |   Rp 35.000     |    16:40:00 - 18:44:00     |   Action, Thriller   |\n";
	cout<<"|  4.  |            GOWOK KAMASUTRA JAWA            |   Rp 35.000     |    17:00:00 - 19:05:00     |         Drama        |\n";
	cout<<"|  5.  |  MISSION:IMPOSSIBLE - THE FINAL RECKONING  |   Rp 45.000     |    20:15:00 - 23:04:00     |         Action       |\n";
	cout<<"|  6.  |                WAKTU MAGHRIB 2             |   Rp 40.000     |    23:14:00 - 01:01:00     |         Horor        |\n";
	cout<<"|=========================================================================================================================|\n";
	cout<<"|                                                           STUDIO 3                                                      |\n";
	cout<<"+------+--------------------------------------------+-----------------+----------------------------+----------------------+\n";
	cout<<"|  1.  |       FINAL DESTINATION: BLOODLINES        |   Rp 45.000     |    12:15:00 - 13:45:00     |         Action       \n";
	cout<<"|  2.  |                 LILO & STITCH              |   Rp 40.000     |    14:30:00 - 16:18:00     |   Adventure, Fantasy |\n";
	cout<<"|  3.  |       FINAL DESTINATION: BLOODLINES        |   Rp 45.000     |    16:25:00 - 17:55:00     |         Action       |\n";
	cout<<"|  4.  |       FINAL DESTINATION: BLOODLINES        |   Rp 45.000     |    18:00:00 - 19:30:00     |         Action       |\n";
	cout<<"|  5.  |       FINAL DESTINATION: BLOODLINES        |   Rp 45.000     |    20:25:00 - 21:55:00     |         Action       |\n";
	cout<<"|  6.  |                WAKTU MAGHRIB 2             |   Rp 40.000     |    22:05:00 - 23:52:00     |         Horor        |\n";
	cout<<"|=========================================================================================================================|\n";
	cout<<"|                                                           STUDIO 4                                                      |\n";
	cout<<"+------+--------------------------------------------+-----------------+----------------------------+----------------------+\n";
	cout<<"|  1.  |                WAKTU MAGHRIB 2             |   Rp 40.000     |    12:35:00 - 14:22:00     |         Horor        |\n";
	cout<<"|  2.  |                WAKTU MAGHRIB 2             |   Rp 40.000     |    14:40:00 - 16:27:00     |         Horor        |\n";
	cout<<"|  3.  |                   BALLERINA                |   Rp 35.000     |    16:40:00 - 18:44:00     |   Action, Thriller   |\n";
	cout<<"|  4.  |                   BALLERINA                |   Rp 35.000     |    19:00:00 - 21:04:00     |   Action, Thriller   |\n";
	cout<<"|  5.  |                   BALLERINA                |   Rp 35.000     |    21:20:00 - 23:24:00     |   Action, Thriller   |\n";
	cout<<"|=========================================================================================================================|\n";
	cout<<"|                                                           STUDIO 5                                                      |\n";
	cout<<"+------+--------------------------------------------+-----------------+----------------------------+----------------------+\n";
	cout<<"|  1.  |  MISSION:IMPOSSIBLE - THE FINAL RECKONING  |   Rp 45.000     |    13:00:00 - 15:49:00     |         Action       |\n";
	cout<<"|  2.  |             KARATE KID: LEGENDS            |   Rp 45.000     |    17:10:00 - 18:40:00     |         Action       |\n";
	cout<<"|  3.  |             KARATE KID: LEGENDS            |   Rp 45.000     |    19:00:00 - 20:30:00     |         Action       |\n";
	cout<<"|  4.  |  MISSION:IMPOSSIBLE - THE FINAL RECKONING  |   Rp 45.000     |    20:45:00 - 23:34:00     |         Action       |\n";
	cout<<"|  5.  |                 LILO & STITCH              |   Rp 40.000     |    23:45:00 - 01:33:00     |   Adventure, Fantasy |\n";
	cout<<"|=========================================================================================================================|\n";
	cout<<"|                                                           STUDIO 6                                                      |\n";
	cout<<"+------+--------------------------------------------+-----------------+----------------------------+----------------------+\n";
	cout<<"|  1.  |             KARATE KID: LEGENDS            |   Rp 45.000     |    13:30:00 - 15:00:00     |         Action       |\n";
	cout<<"|  2.  |            GOWOK KAMASUTRA JAWA            |   Rp 35.000     |    15:30:00 - 17:35:00     |         Drama        |\n";
	cout<<"|  3.  |                 LILO & STITCH              |   Rp 40.000     |    18:00:00 - 19:48:00     |   Adventure, Fantasy |\n";
	cout<<"|  4.  |            GOWOK KAMASUTRA JAWA            |   Rp 35.000     |    20:30:00 - 22:35:00     |         Drama        |\n";
	cout<<"|  5.  |                    GUNDIK                  |   Rp 45.000     |    22:50:00 - 00:42:00     |         Action       |\n";
	cout<<"|=========================================================================================================================|\n";
	cout<<"|                                                      STUDIO 7 (PREMIER)                                                 |\n";
	cout<<"+------+--------------------------------------------+-----------------+----------------------------+----------------------+\n";
	cout<<"|  1.  |                 LILO & STITCH              |   Rp 80.000     |    11:00:00 - 12:48:00     |   Adventure, Fantasy |\n";
	cout<<"|  2.  |            GOWOK KAMASUTRA JAWA            |   Rp 85.000     |    13:10:00 - 15:15:00     |         Drama        |\n";
	cout<<"|  3.  |             KARATE KID: LEGENDS            |   Rp 90.000     |    15:20:00 - 16:50:00     |         Action       |\n";
	cout<<"|  4.  |  MISSION:IMPOSSIBLE - THE FINAL RECKONING  |   Rp 100.000    |    17:40:00 - 20:29:00     |         Action       |\n";
	cout<<"|  5.  |         GOWOK KAMASUTRA JAWA UNCUT         |   Rp 85.000     |    20:50:00 - 23:02:00     |         Drama        |\n";
	cout<<"|  6.  |  MISSION:IMPOSSIBLE - THE FINAL RECKONING  |   Rp 100.000    |    23:10:00 - 01:59:00     |         Action       |\n";
	cout<<"|=========================================================================================================================|\n";
	cout << " "; system("pause");
	
}


Studio bioskop[7] = {
    {"STUDIO 1", {
        {"BALLERINA","Eve (Ana de Armas) seorang pembunuh yang terlatih dalam tradisi organisasi Ruska Roma berangkat untuk membalas dendam setelah kematian ayahnya.",
		 "12:00:00 - 14:04:00", "2 jam 4 menit", "Action, Thriller", 35000},
        {"FINAL DESTINATION: BLOODLINES","Film horor terbaru dari waralaba New Line Cinema ini mengikuti Stefanie, seorang mahasiswi yang diteror mimpi buruk berulang. Ia kembali ke kampung halamannya untuk mencari orang yang bisa mematahkan kutukan dan menyelamatkan keluarganya dari kematian tragis yang tak terelakkan.",
		 "14:20:00 - 15:50:00", "1 jam 30 menit", "Action", 45000},
        {"GUNDIK","Osman, mantan tentara, merencanakan perampokan bersama timnya, termasuk menantunya, Baim. Namun, mereka terjebak mimpi buruk saat mengetahui target mereka adalah siluman sakti penguasa Pantai Selatan.",
		 "16:15:00 - 18:07:00", "1 jam 52 menit", "Action", 45000},
        {"WAKTU MAGHRIB 2","Dua puluh tahun setelah kejadian di Jatijajar, Jin Ummu Sibyan kembali meneror, kini di desa Giritirto. Usai keributan saat pertandingan bola, sekelompok anak menyumpahi tim lawan dalam perjalanan pulang saat maghrib. Tanpa sadar, mereka membangkitkan kembali teror lama. Kali ini, Ummu Sibyan merasuki salah satu dari mereka dan mulai memburu nyawa anak-anak dengan lebih mencekam.",
		 "18:50:00 - 20:37:00", "1 jam 47 menit", "Horor", 40000},
        {"KARATE KID: LEGENDS","Setelah pindah ke New York, Li Fong berusaha menyesuaikan diri di sekolah barunya. Saat mengikuti kompetisi karate demi membantu temannya, ia menyadari keterampilannya belum cukup. Dengan bimbingan Tn. Han dan Daniel LaRusso, Li belajar menggabungkan dua gaya bela diri untuk menghadapi pertarungan penting.", 
		"20:50:00 - 22:20:00", "1 jam 30 menit", "Action", 45000},
        {"GOWOK KAMASUTRA JAWA","Ratri, anak seorang pelacur yang diasuh oleh Nyai Santi, tumbuh menjadi gadis cantik dan pewaris ilmu gowokan. Ia jatuh cinta pada Kamanjaya, namun dikhianati setelah mereka bercinta. Dua puluh tahun kemudian, mereka bertemu lagi saat putra Kamanjaya, Bagas, datang belajar pada Nyai Santi dan jatuh cinta pada Ratri, tanpa mengetahui masa lalu orang tua mereka. Ratri pun melihat kesempatan untuk membalas dendam.",
		 "22:30:00 - 00:35:00", "2 jam 5 menit", "Drama", 35000},
    }, 6},
    {"STUDIO 2", {
        {"GUNDIK","Osman, mantan tentara, merencanakan perampokan bersama timnya, termasuk menantunya, Baim. Namun, mereka terjebak mimpi buruk saat mengetahui target mereka adalah siluman sakti penguasa Pantai Selatan.",
		 "12:05:00 - 13:57:00", "1 jam 52 menit", "Action", 45000},
        {"BALLERINA","Eve (Ana de Armas) seorang pembunuh yang terlatih dalam tradisi organisasi Ruska Roma berangkat untuk membalas dendam setelah kematian ayahnya.",
		 "14:20:00 - 16:24:00","2 jam 4 menit", "Action, Thriller", 35000},
        {"GOWOK KAMASUTRA JAWA","Ratri, anak seorang pelacur yang diasuh oleh Nyai Santi, tumbuh menjadi gadis cantik dan pewaris ilmu gowokan. Ia jatuh cinta pada Kamanjaya, namun dikhianati setelah mereka bercinta. Dua puluh tahun kemudian, mereka bertemu lagi saat putra Kamanjaya, Bagas, datang belajar pada Nyai Santi dan jatuh cinta pada Ratri, tanpa mengetahui masa lalu orang tua mereka. Ratri pun melihat kesempatan untuk membalas dendam.",
		 "17:00:00 - 19:05:00", "2 jam 5 menit", "Drama", 35000},
        {"MISSION:IMPOSSIBLE - THE FINAL RECKONING","Melanjutkan kisah dari film sebelumnya, Mission: Impossible - Dead Reckoning Part One. Ethan Hunt (Tom Cruise) akan kembali meneruskan misi untuk menghancurkan musuh lama dan musuh baru yang lebih berbahaya.",
		 "20:15:00 - 23:04:00", "2 jam 49 menit", "Action", 45000},
        {"WAKTU MAGHRIB 2","Dua puluh tahun setelah kejadian di Jatijajar, Jin Ummu Sibyan kembali meneror, kini di desa Giritirto. Usai keributan saat pertandingan bola, sekelompok anak menyumpahi tim lawan dalam perjalanan pulang saat maghrib. Tanpa sadar, mereka membangkitkan kembali teror lama. Kali ini, Ummu Sibyan merasuki salah satu dari mereka dan mulai memburu nyawa anak-anak dengan lebih mencekam.",
		 "23:14:00 - 01:01:00", "1 jam 47 menit", "Horor", 45000},
    }, 5},
    {"STUDIO 3", {
        {"FINAL DESTINATION: BLOODLINES","Film horor terbaru dari waralaba New Line Cinema ini mengikuti Stefanie, seorang mahasiswi yang diteror mimpi buruk berulang. Ia kembali ke kampung halamannya untuk mencari orang yang bisa mematahkan kutukan dan menyelamatkan keluarganya dari kematian tragis yang tak terelakkan.",
		 "12:15:00 - 13:45:00", "Action", 45000},
        {"LILO & STITCH", "Lilo (Maia Kealoha) seorang anak kecil dari Hawaii yang kesepian bertemu dengan Stitch (Chris Sanders), seorang alien yang melarikan diri dari planet asalnya. Keduanya kini berteman dan mencoba memperbaiki kondisi keluarga yang terpecah belah.",
		 "14:30:00 - 16:18:00", "1 jam 48 menit", "Adventure, Fantasy", 40000},
        {"FINAL DESTINATION: BLOODLINES","Film horor terbaru dari waralaba New Line Cinema ini mengikuti Stefanie, seorang mahasiswi yang diteror mimpi buruk berulang. Ia kembali ke kampung halamannya untuk mencari orang yang bisa mematahkan kutukan dan menyelamatkan keluarganya dari kematian tragis yang tak terelakkan.",
		 "16:25:00 - 17:55:00", "1 jam 30 menit", "Action", 45000},
        {"FINAL DESTINATION: BLOODLINES","Film horor terbaru dari waralaba New Line Cinema ini mengikuti Stefanie, seorang mahasiswi yang diteror mimpi buruk berulang. Ia kembali ke kampung halamannya untuk mencari orang yang bisa mematahkan kutukan dan menyelamatkan keluarganya dari kematian tragis yang tak terelakkan.",
		 "18:00:00 - 19:30:00", "1 jam 30 menit", "Action", 45000},
        {"FINAL DESTINATION: BLOODLINES","Film horor terbaru dari waralaba New Line Cinema ini mengikuti Stefanie, seorang mahasiswi yang diteror mimpi buruk berulang. Ia kembali ke kampung halamannya untuk mencari orang yang bisa mematahkan kutukan dan menyelamatkan keluarganya dari kematian tragis yang tak terelakkan.",
		 "19:45:00 - 21:15:00", "1 jam 30 menit", "Action", 45000},
        {"WAKTU MAGHRIB 2","Dua puluh tahun setelah kejadian di Jatijajar, Jin Ummu Sibyan kembali meneror, kini di desa Giritirto. Usai keributan saat pertandingan bola, sekelompok anak menyumpahi tim lawan dalam perjalanan pulang saat maghrib. Tanpa sadar, mereka membangkitkan kembali teror lama. Kali ini, Ummu Sibyan merasuki salah satu dari mereka dan mulai memburu nyawa anak-anak dengan lebih mencekam.",
		 "23:14:00 - 01:01:00", "1 jam 47 menit", "Horor", 40000},
    }, 6},
    {"STUDIO 4", {
        {"WAKTU MAGHRIB 2","Dua puluh tahun setelah kejadian di Jatijajar, Jin Ummu Sibyan kembali meneror, kini di desa Giritirto. Usai keributan saat pertandingan bola, sekelompok anak menyumpahi tim lawan dalam perjalanan pulang saat maghrib. Tanpa sadar, mereka membangkitkan kembali teror lama. Kali ini, Ummu Sibyan merasuki salah satu dari mereka dan mulai memburu nyawa anak-anak dengan lebih mencekam.",
		 "12:35:00 - 14:22:00", "1 jam 47 menit", "Horor", 40000},
        {"WAKTU MAGHRIB 2","Dua puluh tahun setelah kejadian di Jatijajar, Jin Ummu Sibyan kembali meneror, kini di desa Giritirto. Usai keributan saat pertandingan bola, sekelompok anak menyumpahi tim lawan dalam perjalanan pulang saat maghrib. Tanpa sadar, mereka membangkitkan kembali teror lama. Kali ini, Ummu Sibyan merasuki salah satu dari mereka dan mulai memburu nyawa anak-anak dengan lebih mencekam.",
		 "14:40:00 - 16:27:00", "1 jam 47 menit", "Horor", 40000},
        {"BALLERINA","Eve (Ana de Armas) seorang pembunuh yang terlatih dalam tradisi organisasi Ruska Roma berangkat untuk membalas dendam setelah kematian ayahnya.",
		 "16:40:00 - 18:44:00", "2 jam 4 menit", "Action, Thriller", 35000},
        {"BALLERINA","Eve (Ana de Armas) seorang pembunuh yang terlatih dalam tradisi organisasi Ruska Roma berangkat untuk membalas dendam setelah kematian ayahnya.",
		 "19:00:00 - 21:04:00", "2 jam 4 menit", "Action, Thriller", 35000},
        {"BALLERINA","Eve (Ana de Armas) seorang pembunuh yang terlatih dalam tradisi organisasi Ruska Roma berangkat untuk membalas dendam setelah kematian ayahnya.",
		 "21:30:00 - 23:34:00", "2 jam 4 menit", "Action, Thriller", 35000},
    }, 5},
    {"STUDIO 5", {
        {"MISSION:IMPOSSIBLE - THE FINAL RECKONING","Melanjutkan kisah dari film sebelumnya, Mission: Impossible - Dead Reckoning Part One. Ethan Hunt (Tom Cruise) akan kembali meneruskan misi untuk menghancurkan musuh lama dan musuh baru yang lebih berbahaya.",
		 "13:00:00 - 15:49:00", "2 jam 49 menit", "Action", 45000},
        {"KARATE KID: LEGENDS","Setelah pindah ke New York, Li Fong berusaha menyesuaikan diri di sekolah barunya. Saat mengikuti kompetisi karate demi membantu temannya, ia menyadari keterampilannya belum cukup. Dengan bimbingan Tn. Han dan Daniel LaRusso, Li belajar menggabungkan dua gaya bela diri untuk menghadapi pertarungan penting.",
		 "17:10:00 - 18:40:00", "1 jam 30 menit", "Action", 45000},
        {"KARATE KID: LEGENDS","Setelah pindah ke New York, Li Fong berusaha menyesuaikan diri di sekolah barunya. Saat mengikuti kompetisi karate demi membantu temannya, ia menyadari keterampilannya belum cukup. Dengan bimbingan Tn. Han dan Daniel LaRusso, Li belajar menggabungkan dua gaya bela diri untuk menghadapi pertarungan penting.",
		 "19:00:00 - 20:30:00", "1 jam 30 menit", "Action", 45000},
        {"MISSION:IMPOSSIBLE - THE FINAL RECKONING","Melanjutkan kisah dari film sebelumnya, Mission: Impossible - Dead Reckoning Part One. Ethan Hunt (Tom Cruise) akan kembali meneruskan misi untuk menghancurkan musuh lama dan musuh baru yang lebih berbahaya.",
		 "20:45:00 - 23:34:00", "2 jam 49 menit", "Action", 45000},
        {"LILO & STITCH","Lilo (Maia Kealoha) seorang anak kecil dari Hawaii yang kesepian bertemu dengan Stitch (Chris Sanders), seorang alien yang melarikan diri dari planet asalnya. Keduanya kini berteman dan mencoba memperbaiki kondisi keluarga yang terpecah belah.",
		 "23:45:00 - 01:33:00", "1 jam 48 menit", "Adventure, Fantasy", 40000},
    }, 5},
    {"STUDIO 6", {
        {"KARATE KID: LEGENDS","Setelah pindah ke New York, Li Fong berusaha menyesuaikan diri di sekolah barunya. Saat mengikuti kompetisi karate demi membantu temannya, ia menyadari keterampilannya belum cukup. Dengan bimbingan Tn. Han dan Daniel LaRusso, Li belajar menggabungkan dua gaya bela diri untuk menghadapi pertarungan penting.",
		 "13:30:00 - 15:00:00", "1 jam 30 menit", "Action", 45000},
        {"GOWOK KAMASUTRA JAWA","Ratri, anak seorang pelacur yang diasuh oleh Nyai Santi, tumbuh menjadi gadis cantik dan pewaris ilmu gowokan. Ia jatuh cinta pada Kamanjaya, namun dikhianati setelah mereka bercinta. Dua puluh tahun kemudian, mereka bertemu lagi saat putra Kamanjaya, Bagas, datang belajar pada Nyai Santi dan jatuh cinta pada Ratri, tanpa mengetahui masa lalu orang tua mereka. Ratri pun melihat kesempatan untuk membalas dendam.",
		 "15:30:00 - 17:35:00", "2 jam 5 menit", "Drama", 35000},
        {"LILO & STITCH","Lilo (Maia Kealoha) seorang anak kecil dari Hawaii yang kesepian bertemu dengan Stitch (Chris Sanders), seorang alien yang melarikan diri dari planet asalnya. Keduanya kini berteman dan mencoba memperbaiki kondisi keluarga yang terpecah belah.",
		 "18:00:00 - 19:48:00", "1 jam 48 menit", "Adventure, Fantasy", 40000},
        {"GOWOK KAMASUTRA JAWA","Ratri, anak seorang pelacur yang diasuh oleh Nyai Santi, tumbuh menjadi gadis cantik dan pewaris ilmu gowokan. Ia jatuh cinta pada Kamanjaya, namun dikhianati setelah mereka bercinta. Dua puluh tahun kemudian, mereka bertemu lagi saat putra Kamanjaya, Bagas, datang belajar pada Nyai Santi dan jatuh cinta pada Ratri, tanpa mengetahui masa lalu orang tua mereka. Ratri pun melihat kesempatan untuk membalas dendam.",
		 "20:30:00 - 22:35:00", "2 jam 5 menit", "Drama", 35000},
        {"GUNDIK","Osman, mantan tentara, merencanakan perampokan bersama timnya, termasuk menantunya, Baim. Namun, mereka terjebak mimpi buruk saat mengetahui target mereka adalah siluman sakti penguasa Pantai Selatan.",
		 "22:50:00 - 00:42:00", "1 jam 52 menit", "Action", 45000},
    }, 5},
    {"STUDIO 7", {
        {"LILO & STITCH","Lilo (Maia Kealoha) seorang anak kecil dari Hawaii yang kesepian bertemu dengan Stitch (Chris Sanders), seorang alien yang melarikan diri dari planet asalnya. Keduanya kini berteman dan mencoba memperbaiki kondisi keluarga yang terpecah belah.",
		 "11:00:00 - 12:48:00", "1 jam 48 menit", "Adventure, Fantasy", 40000},
        {"GOWOK KAMASUTRA JAWA","Ratri, anak seorang pelacur yang diasuh oleh Nyai Santi, tumbuh menjadi gadis cantik dan pewaris ilmu gowokan. Ia jatuh cinta pada Kamanjaya, namun dikhianati setelah mereka bercinta. Dua puluh tahun kemudian, mereka bertemu lagi saat putra Kamanjaya, Bagas, datang belajar pada Nyai Santi dan jatuh cinta pada Ratri, tanpa mengetahui masa lalu orang tua mereka. Ratri pun melihat kesempatan untuk membalas dendam.",
		 "13:10:00 - 15:15:00", "2 jam 5 menit", "Drama", 45000},
        {"KARATE KID: LEGENDS","Setelah pindah ke New York, Li Fong berusaha menyesuaikan diri di sekolah barunya. Saat mengikuti kompetisi karate demi membantu temannya, ia menyadari keterampilannya belum cukup. Dengan bimbingan Tn. Han dan Daniel LaRusso, Li belajar menggabungkan dua gaya bela diri untuk menghadapi pertarungan penting.",
		 "15:20:00 - 16:50:00", "1 jam 30 menit", "Action", 45000},
        {"MISSION:IMPOSSIBLE - THE FINAL RECKONING","Melanjutkan kisah dari film sebelumnya, Mission: Impossible - Dead Reckoning Part One. Ethan Hunt (Tom Cruise) akan kembali meneruskan misi untuk menghancurkan musuh lama dan musuh baru yang lebih berbahaya.",
		 "17:40:00 - 20:29:00", "2 jam 49 menit", "Action", 45000},
        {"GOWOK KAMASUTRA JAWA UNCUT","Ratri (Alika Jantinia) merupakan anak dari seorang pelacur, tanpa mengetahui siapa ayahnya. Sejak bayi, ia diasuh oleh Nyai Santi (Lola Amaria), seorang gowok yang bijaksana dan disegani.",
		 "20:50:00 - 23:02:00", "2 jam 12 menit", "Drama", 45000},
		{"MISSION:IMPOSSIBLE - THE FINAL RECKONING","Melanjutkan kisah dari film sebelumnya, Mission: Impossible - Dead Reckoning Part One. Ethan Hunt (Tom Cruise) akan kembali meneruskan misi untuk menghancurkan musuh lama dan musuh baru yang lebih berbahaya.",
		 "23:10:00 - 01:59:00", "2 jam 49 menit", "Action", 45000},
    }, 6},
};

void jadwal() {
    struct JadwalGabungan {
    	int jenisTiket[2];
        char judul[100];
        char studio[20][20];
        char waktu[20][30];
        char durasi[20][50];
		char genre[50];
    	int harga;  
        int jumlahTayang;
        char sinopsis[1000];
    };

    JadwalGabungan daftarFilm[50];
    int jumlahJudul = 0;

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < bioskop[i].jumlahFilm; j++) {
            bool ditemukan = false;
            for (int k = 0; k < jumlahJudul; k++) {
                if (strcmp(daftarFilm[k].judul, bioskop[i].jadwal[j].judul) == 0) {
                    strcpy(daftarFilm[k].studio[daftarFilm[k].jumlahTayang], bioskop[i].nama);
                    strcpy(daftarFilm[k].waktu[daftarFilm[k].jumlahTayang], bioskop[i].jadwal[j].waktu);
                    strcpy(daftarFilm[k].durasi[daftarFilm[k].jumlahTayang], bioskop[i].jadwal[j].durasi);
                    strcpy(daftarFilm[k].genre, bioskop[i].jadwal[j].genre);
                    daftarFilm[k].harga = bioskop[i].jadwal[j].harga;
                    daftarFilm[k].jumlahTayang++;
                    ditemukan = true;
                    break;
                }
            }

            if (!ditemukan) {
                strcpy(daftarFilm[jumlahJudul].judul, bioskop[i].jadwal[j].judul);
                strcpy(daftarFilm[jumlahJudul].studio[0], bioskop[i].nama);
                strcpy(daftarFilm[jumlahJudul].waktu[0], bioskop[i].jadwal[j].waktu);
                strcpy(daftarFilm[jumlahJudul].durasi[0], bioskop[i].jadwal[j].durasi);
                strcpy(daftarFilm[jumlahJudul].sinopsis, bioskop[i].jadwal[j].sinopsis);
                strcpy(daftarFilm[jumlahJudul].genre, bioskop[i].jadwal[j].genre);
                daftarFilm[jumlahJudul].harga = bioskop[i].jadwal[j].harga;
                daftarFilm[jumlahJudul].jumlahTayang = 1;
                jumlahJudul++;
            }
        }
    }

	system("cls");
    cout<<"============================================================================================================================================================\n";
	cout<<"\t\t\t\t\t\t\t\t\t  DAFTAR FILM\n";
	cout<<"------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < jumlahJudul; i++) {
        cout << "\nFilm         : " << daftarFilm[i].judul;
        cout << "\nSinopsis     : " << daftarFilm[i].sinopsis;
        cout << "\nGenre        : " << daftarFilm[i].genre;
        cout << "\nHarga        : " << daftarFilm[i].harga;
        cout << "\nJadwal Tayang:\n";
        for (int j = 0; j < daftarFilm[i].jumlahTayang; j++) {
            cout << daftarFilm[i].waktu[j] 
                 << endl;
        }
        cout<<"\n------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    }
    system("pause");
}

void buatLayoutKursi(string fileKursi) {
    ofstream f(fileKursi.c_str());
    for (char baris = 'A'; baris <= 'J'; ++baris) {
        for (int kolom = 1; kolom <= 17; ++kolom) {
            f << baris << kolom << " 0\n";
        }
    }
    f.close();
}

void initLayout() {
    ofstream f("layoutkursi.txt");
    if (!f) {
        cout << "Gagal membuat file kursi.\n";
        return;
    }

    for (char baris = 'A'; baris <= 'J'; ++baris) {
        for (int kolom = 1; kolom <= 17; ++kolom) {
            f << baris << kolom << " 0" << endl;
        }
    }

    f.close();
    cout << "[?] layoutkursi.txt dibuat ulang.\n";
}

void tampilLayoutKursi(string fileKursi) {
    ifstream f(fileKursi.c_str());
    if (!f) {
        cout << "Layout belum tersedia. Membuat baru...\n";
        buatLayoutKursi(fileKursi);
        f.open(fileKursi.c_str());
    }

    string kode;
    int status;
    int count = 0;
    while (f >> kode >> status) {
        if (status == 0) cout << "[" << kode << "] ";
        else cout << "[XX] ";
        count++;
        if (count % 17 == 0) cout << endl;
    }
    f.close();
}

bool pesanKursiDi(string fileKursi, string kodeKursi) {
    ifstream in(fileKursi.c_str());
    ofstream temp("tempkursi.txt");
    string kode;
    int status;
    bool tersedia = false;

    while (in >> kode >> status) {
        if (kode == kodeKursi && status == 0) {
            temp << kode << " 1\n";
            tersedia = true;
        } else {
            temp << kode << " " << status << "\n";
        }
    }

    in.close();
    temp.close();

    remove(fileKursi.c_str());
    rename("tempkursi.txt", fileKursi.c_str());

    return tersedia;
}

void batalkanKursiDi(string fileKursi, string kodeKursi) {
    ifstream in(fileKursi.c_str());
    ofstream temp("tempkursi.txt");
    string kode;
    int status;

    while (in >> kode >> status) {
        if (kode == kodeKursi) {
            temp << kode << " 0\n";
        } else {
            temp << kode << " " << status << "\n";
        }
    }

    in.close();
    temp.close();

    remove(fileKursi.c_str());
    rename("tempkursi.txt", fileKursi.c_str());
}

void statistikKursiTerisi() {
	system("cls");
    cout << "\n============ Statistik Kursi Terisi ============\n\n";

    DIR *dir;
    struct dirent *ent;
    dir = opendir(".");

    if (dir != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            string filename = ent->d_name;
            if (filename.find("kursi_") == 0 && filename.find(".txt") != string::npos) {
                ifstream f(filename.c_str());
                int total = 0, terisi = 0;
                string kode;
                int status;
                while (f >> kode >> status) {
                    total++;
                    if (status == 1) terisi++;
                }
                f.close();
                cout << filename << " => " << terisi << "/" << total << " kursi terisi\n";
            }
        }
        closedir(dir);
    } else {
        cout << "Gagal membaca direktori.\n";
    }

    system("pause");
}


void tampilLayout() {
	system("cls");
    ifstream f("layoutkursi.txt");
    if (!f) {
        cout << "Gagal membuka layoutkursi.txt\n";
        return;
    }

    string kode;
    int status;
    int count = 0;

    cout << "\n============ Layout Kursi ============\n\n";
    while (f >> kode >> status) {
        if (status == 0)
            cout << "[" << kode << "] ";
        else
            cout << "[XX] ";

        count++;
        if (count % 17 == 0) cout << endl;
    }

    f.close();
}

void pesanKursi(string inputKode) {
    ifstream in("layoutkursi.txt");
    ofstream temp("temp.txt");

    if (!in || !temp) {
        cout << "Gagal membuka file.\n";
        return;
    }

    string kode;
    int status;
    bool ditemukan = false;
    bool sudahDipesan = false;

    while (in >> kode >> status) {
        if (kode == inputKode) {
            if (status == 1) {
                sudahDipesan = true;
            } else {
                temp << kode << " 1\n";
                ditemukan = true;
            }
        } else {
            temp << kode << " " << status << "\n";
        }
    }

    in.close();
    temp.close();

    remove("layoutkursi.txt");
    rename("temp.txt", "layoutkursi.txt");

    if (sudahDipesan) {
        cout << " Kursi sudah dipesan!\n";
    } else if (ditemukan) {
        ofstream log("datapemesanankursi.txt", ios::app);
        log << "Kursi " << inputKode << " berhasil dipesan.\n";
        log.close();
        cout << " Pemesanan berhasil.\n";
    } else {
        cout << " Kursi tidak ditemukan.\n";
    }
    system("pause");
}

vector<Pemesanan> daftarPemesanan;

    vector<Film*> pilihanFilm;
	vector<int> asalStudio;

int stringToInt(const char* str) {
    int result = 0;
    int i = 0;

    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return result;
}

void batalkanKursi(string kodeKursi) {
    fstream file("layoutkursi.txt", ios::in | ios::out);
    if (!file) {
        cout << "Gagal membuka file layoutkursi.txt\n";
        return;
    }

    char baris = kodeKursi[0];
    int kolom = atoi(kodeKursi.substr(1).c_str());
    int pos = (baris - 'A') * 20 + (kolom - 1);

    file.seekp(pos);
    file.put('0');
    file.close();
}

void pesan_tiket() {
    system("cls");
    struct JadwalGabungan {
        char judul[100];
        char studio[20][20];
        char waktu[20][30];
        char durasi[20][50];
        int jumlahTayang;
        char sinopsis[1000];
        char genre[50];
        int harga;
    };

    JadwalGabungan daftarFilm[50];
    int jumlahJudul = 0;
    int jenisTiket;
    bool isMemberBaru = false;

    cout << "\n============ Pilih Jenis Tiket ============\n";
    cout << "[1] Reguler (STUDIO 1 - 6)\n";
    cout << "[2] Premier (STUDIO 7 saja)\n";
    cout << "\nPilihan Anda (1-2) : ";
    cin >> jenisTiket;

    if (jenisTiket != 1 && jenisTiket != 2) {
        cout << "Jenis tiket tidak valid.\n";
        return;
    }

    if (jenisTiket == 2) {
        cout << "Anda memilih tiket Premier. Hanya film di STUDIO 7 yang tersedia.\n";
    }

    int startStudio = 0, endStudio = 7;
    if (jenisTiket == 2) {
        startStudio = 6;
        endStudio = 7;
    }

    for (int i = startStudio; i < endStudio; i++) {
        for (int j = 0; j < bioskop[i].jumlahFilm; j++) {
            bool ditemukan = false;
            for (int k = 0; k < jumlahJudul; k++) {
                if (strcmp(daftarFilm[k].judul, bioskop[i].jadwal[j].judul) == 0) {
                    strcpy(daftarFilm[k].studio[daftarFilm[k].jumlahTayang], bioskop[i].nama);
                    strcpy(daftarFilm[k].waktu[daftarFilm[k].jumlahTayang], bioskop[i].jadwal[j].waktu);
                    strcpy(daftarFilm[k].durasi[daftarFilm[k].jumlahTayang], bioskop[i].jadwal[j].durasi);
                    daftarFilm[k].jumlahTayang++;
                    ditemukan = true;
                    break;
                }
            }

            if (!ditemukan) {
                strcpy(daftarFilm[jumlahJudul].judul, bioskop[i].jadwal[j].judul);
                strcpy(daftarFilm[jumlahJudul].studio[0], bioskop[i].nama);
                strcpy(daftarFilm[jumlahJudul].waktu[0], bioskop[i].jadwal[j].waktu);
                strcpy(daftarFilm[jumlahJudul].durasi[0], bioskop[i].jadwal[j].durasi);
                strcpy(daftarFilm[jumlahJudul].sinopsis, bioskop[i].jadwal[j].sinopsis);
                strcpy(daftarFilm[jumlahJudul].genre, bioskop[i].jadwal[j].genre);
                daftarFilm[jumlahJudul].harga = bioskop[i].jadwal[j].harga;
                daftarFilm[jumlahJudul].jumlahTayang = 1;
                jumlahJudul++;
            }
        }
    }

    cout << "\n============ PILIH FILM ============\n";
    for (int i = 0; i < jumlahJudul; i++) {
        cout << "[" << i + 1 << "] " << daftarFilm[i].judul << endl;
    }

    int pilihanJudul;
    cout << "\nMasukkan nomor film : ";
    cin >> pilihanJudul;
    pilihanJudul--;

    if (pilihanJudul < 0 || pilihanJudul >= jumlahJudul) {
        cout << "Pilihan tidak valid!\n";
        return;
    }

    cout << "\nSINOPSIS : " << daftarFilm[pilihanJudul].sinopsis << "\n\n";

    vector<Film*> pilihanFilm;
    vector<int> asalStudio;

    cout << "============ JAM TAYANG UNTUK '" << daftarFilm[pilihanJudul].judul << "' ============\n";
    for (int i = 0; i < daftarFilm[pilihanJudul].jumlahTayang; i++) {
        cout << "[" << i + 1 << "] " << daftarFilm[pilihanJudul].waktu[i]
             << " di " << daftarFilm[pilihanJudul].studio[i] << endl;
    }

    int pilihanJam;
    cout << "\nMasukkan nomor jam tayang: ";
    cin >> pilihanJam;
    pilihanJam--;

    if (pilihanJam < 0 || pilihanJam >= daftarFilm[pilihanJudul].jumlahTayang) {
        cout << "Pilihan tidak valid!\n";
        return;
    }

    int jumlahTiket;
    cout << "Jumlah tiket: ";
    cin >> jumlahTiket;
    if (jumlahTiket < 1) {
        cout << "Jumlah tiket tidak valid.\n";
        return;
    }

    // Tanya member baru
    char jawabanMember;
    cout << "Apakah Anda member baru? (y/n): ";
    cin >> jawabanMember;
    if (jawabanMember == 'y' || jawabanMember == 'Y') {
        isMemberBaru = true;
    }

    string studio = daftarFilm[pilihanJudul].studio[pilihanJam];
    bool isStudio7 = (studio.find("STUDIO 7") != string::npos);

    if ((jenisTiket == 1 && isStudio7) || (jenisTiket == 2 && !isStudio7)) {
        cout << "Studio tidak sesuai dengan jenis tiket yang dipilih.\n";
        return;
    }

    int hargaAsli = daftarFilm[pilihanJudul].harga;
    int hargaFinal = hargaAsli + (jenisTiket == 2 ? 40000 : 0);
    int total = hargaFinal * jumlahTiket;

    if (isMemberBaru) {
        int diskon = total * 0.10;
        cout << "Diskon member baru: Rp" << diskon << endl;
        total -= diskon;
    }

    cout << "\n============ TIKET ANDA ============\n";
    cout << "Jenis Tiket   : " << (jenisTiket == 1 ? "Reguler" : "Premier") << endl;
    cout << "Studio        : " << studio << endl;
    cout << "Film          : " << daftarFilm[pilihanJudul].judul << endl;
    cout << "Genre         : " << daftarFilm[pilihanJudul].genre << endl;
    cout << "Jam Tayang    : " << daftarFilm[pilihanJudul].waktu[pilihanJam] << endl;
    cout << "Durasi Film   : " << daftarFilm[pilihanJudul].durasi[pilihanJam] << endl;
    cout << "Harga         : " << hargaFinal << endl;
    cout << "Jumlah Tiket  : " << jumlahTiket << endl;
    if (isMemberBaru) {
        cout << "Status Member : Member Baru (Diskon 10%)" << endl;
    }

    Pemesanan pesanan;
    vector<string> kursiDipilih;

    cout << "\n============ PILIH KURSI ============\n";
    string judul = daftarFilm[pilihanJudul].judul;
    string waktu = daftarFilm[pilihanJudul].waktu[pilihanJam];

    string fileKursi = "kursi_" + studio + "_" + judul + "_" + waktu + ".txt";
    replace(fileKursi.begin(), fileKursi.end(), ' ', '_');
    replace(fileKursi.begin(), fileKursi.end(), ':', '_');
    replace(fileKursi.begin(), fileKursi.end(), '-', '_');

    cout << "\nLayout Kursi untuk Sesi Ini:\n";
    tampilLayoutKursi(fileKursi);
    cin.ignore();

    for (int i = 0; i < jumlahTiket; ++i) {
        string kodeKursi;
        cout << "\nMasukkan kode kursi ke-" << i + 1 << ": ";
        getline(cin, kodeKursi);

        if (!pesanKursiDi(fileKursi, kodeKursi)) {
            cout << " Kursi sudah dipesan atau tidak valid. Ulangi!\n";
            --i;
        } else {
            kursiDipilih.push_back(kodeKursi);
            pesanan.kursi.push_back(kodeKursi);
        }
    }

    cout << "TOTAL        : Rp" << total << endl;
    cout << "==================================\n";

    pesanan.namaPemesan = "User";
    pesanan.studio = studio;
    pesanan.judulFilm = daftarFilm[pilihanJudul].judul;
    pesanan.waktu = daftarFilm[pilihanJudul].waktu[pilihanJam];
    pesanan.durasi = daftarFilm[pilihanJudul].durasi[pilihanJam];
    pesanan.genre = daftarFilm[pilihanJudul].genre;
    pesanan.jenisTiket = (jenisTiket == 1) ? "Reguler" : "Premier";
    pesanan.harga = hargaFinal;
    pesanan.jumlahTiket = jumlahTiket;
    pesanan.totalHarga = total;

    daftarPemesanan.push_back(pesanan);

    ofstream file("daftar_pesanan.txt", ios::app);
    if (file.is_open()) {
        file << "\n============ PESANAN BARU MASUK ============\n";
        file << pesanan.namaPemesan << endl << endl;
        file << "Studio              : " << pesanan.studio << endl;
        file << "Judul Film          : " << pesanan.judulFilm << endl;
        file << "Waktu               : " << pesanan.waktu << endl;
        file << "Durasi              : " << pesanan.durasi << endl;
        file << "Genre               : " << pesanan.genre << endl;
        file << "Jenis Tiket         : " << pesanan.jenisTiket << endl;
        file << "Harga               : " << pesanan.harga << endl;
        file << "Jumlah Tiket        : " << pesanan.jumlahTiket << endl;
        file << "Kursi yang dipilih  : ";
        for (int i = 0; i < pesanan.kursi.size(); ++i) {
            file << pesanan.kursi[i] << " ";
        }
        file << endl;
        if (isMemberBaru) {
            file << "Status Member       : Member Baru (Diskon 10%)" << endl;
        }
        file << "Total Harga         : " << pesanan.totalHarga << endl;
    } else {
        cout << "Gagal menyimpan ke file.\n";
    }

    cout << "\n===== PEMBAYARAN =====\n";
    cout << "Pilih metode pembayaran:\n";
    cout << "1. Tunai\n2. Non-Tunai\nPilihan: ";
    int pilihBayar;
    cin >> pilihBayar;

    if (pilihBayar == 1) {
        pesanan.metodePembayaran = "Tunai";
    } else if (pilihBayar == 2) {
        pesanan.metodePembayaran = "Non-Tunai";
    } else {
        cout << "Pilihan tidak valid. Dibatalkan.\n";
        return;
    }

    pesanan.sudahDibayar = true;
    file << "Metode Pembayaran   : " << pesanan.metodePembayaran << endl;
    file << "Status Pembayaran   : " << (pesanan.sudahDibayar ? "Sudah Dibayar" : "Belum Dibayar") << endl;
    file.close();

    if (pesanan.sudahDibayar) {
        cout << "\nPesanan ini sudah dibayar dan tidak bisa diubah.\n";
    }
}

void bukaFilePesanan() {
    system("cls");
    ifstream file("daftar_pesanan.txt");

    if (!file.is_open()) {
        cout << "File daftar_pesanan.txt tidak ditemukan atau gagal dibuka.\n";
        system("pause");
        return;
    }

    cout << "\n============ DAFTAR PESANAN DARI FILE ============\n\n";

    string baris;
    while (getline(file, baris)) {
        cout << baris << endl;
    }

    file.close();
    system("pause");
}

void editPemesanan() {
    if (daftarPemesanan.empty()) {
        cout << "Belum ada pemesanan.\n";
        return;
    }

    cout << "\n============ DAFTAR PEMESANAN ============\n\n";
    for (int i = 0; i < daftarPemesanan.size(); i++) {
        cout << i + 1 << "  .   " << daftarPemesanan[i].judulFilm << "   |   "
             << daftarPemesanan[i].studio << "   | Jumlah Tiket:   "
             << daftarPemesanan[i].jumlahTiket << endl;
    }

    int pilih;
    cout << "Pilih nomor pesanan yang ingin diedit: ";
    cin >> pilih;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (pilih < 1 || pilih > daftarPemesanan.size()) {
        cout << "Pilihan tidak valid.\n";
        return;
    }

    Pemesanan &pesanan = daftarPemesanan[pilih - 1];

    int jenisTiket;
    cout << "\n============ Jenis Tiket ============\n\n";
    cout << "1. Reguler (STUDIO 16)\n";
    cout << "2. Premier (STUDIO 7)\n";
    cout << "Pilihan Anda: ";
    cin >> jenisTiket;

    if (jenisTiket != 1 && jenisTiket != 2) {
        cout << "Jenis tiket tidak valid.\n";
        return;
    }

    cout << "\n============ Pilih Judul Film ============\n\n";
    vector<Film*> pilihanFilm;
    vector<int> asalStudio;
    for (int i = 0; i < 7; i++) {
        if ((jenisTiket == 1 && i < 6) || (jenisTiket == 2 && i == 6)) {
            for (int j = 0; j < bioskop[i].jumlahFilm; j++) {
                cout << pilihanFilm.size() + 1 << ". " << bioskop[i].jadwal[j].judul << endl;
                pilihanFilm.push_back(&bioskop[i].jadwal[j]);
                asalStudio.push_back(i);
            }
        }
    }

    int pilihFilm;
    cout << "Pilihan film: ";
    cin >> pilihFilm;
    if (pilihFilm < 1 || pilihFilm > pilihanFilm.size()) {
        cout << "Pilihan film tidak valid.\n";
        return;
    }

    Film* film = pilihanFilm[pilihFilm - 1];
    int studioIndex = asalStudio[pilihFilm - 1];

    int jumlahTiket;
    cout << "Jumlah tiket: ";
    cin >> jumlahTiket;
    if (jumlahTiket < 1) {
        cout << "Jumlah tidak valid.\n";
        return;
    }

    pesanan.namaPemesan = "User";
    pesanan.studio = bioskop[studioIndex].nama;
    pesanan.judulFilm = film->judul;
    pesanan.waktu = film->waktu;
    pesanan.durasi = film->durasi;
    pesanan.genre = film->genre;
    pesanan.harga = film->harga + (jenisTiket == 2 ? 40000 : 0);
    pesanan.jenisTiket = (jenisTiket == 1) ? "Reguler" : "Premier";
    pesanan.jumlahTiket = jumlahTiket;
    pesanan.totalHarga = pesanan.harga * jumlahTiket;
    
	for (int i = 0; i < pesanan.kursi.size(); ++i) {
	    batalkanKursi(pesanan.kursi[i]);
	}
	pesanan.kursi.clear();
    
    vector<string> kursiDipilih;
	cout << "\n============ PILIH KURSI BARU ============\n\n";
	tampilLayout();
	cin.ignore();
	
	for (int i = 0; i < jumlahTiket; ++i) {
	    string kodeKursi;
	    cout << "Masukkan kode kursi ke-" << i + 1 << ": ";
	    getline(cin, kodeKursi);
	    pesanKursi(kodeKursi);
	    kursiDipilih.push_back(kodeKursi);
	    pesanan.kursi.push_back(kodeKursi);
	}

    ofstream file("daftar_pesanan.txt");
    if (file.is_open()) {
        for (int i = 0; i < daftarPemesanan.size(); i++) {
            Pemesanan &q = daftarPemesanan[i];
            file << "============ PESANAN YANG DIUBAH ============\n" << endl;
            file << q.namaPemesan << endl <<endl;
			file << "Studio 		    :" << q.studio <<endl;
			file << "Judul Film 	    :" << q.judulFilm <<endl;
			file << "Waktu 			    :" << q.waktu <<endl;
			file << "Durasi 	     	:" << q.durasi <<endl;
			file << "Genre 			    :" << q.genre <<endl;
			file << "Jenis Tiket 	    :" << q.jenisTiket <<endl;
			file << "Harga 			    :" << q.harga <<endl;
			file << "Jumlah Tiket 	    :" << q.jumlahTiket <<endl;
			file << "Kursi yang dipilih : ";
			for (int j = 0; j < q.kursi.size(); ++j) {
			    file << q.kursi[j] << " ";
			}
			file << endl;
			file << "Total Harga 	:" << q.totalHarga << endl;
        }
        file.close();
        cout << "\nPerubahan pesanan berhasil disimpan ke file.\n";
    } else {
        cout << "Gagal menyimpan ke file.\n";
    }
}

void editPemesananUser() {
    struct JadwalGabungan {
        char judul[100];
        char studio[20][20];
        char waktu[20][30];
        char durasi[20][50];
        char genre[50];
        int harga;
        int jumlahTayang;
        char sinopsis[1000];
    };

    JadwalGabungan daftarFilm[50];
    int jumlahJudul = 0;

    if (daftarPemesanan.empty()) {
        cout << "Belum ada pemesanan.\n";
        return;
    }

    cout << "\n============ DAFTAR PEMESANAN ============\n\n";
    for (int i = 0; i < daftarPemesanan.size(); i++) {
        cout << i + 1 << ". " << daftarPemesanan[i].judulFilm
             << " | Studio      : " << daftarPemesanan[i].studio
             << " | Jumlah Tiket: " << daftarPemesanan[i].jumlahTiket << "\n";
    }

    int pilih;
    cout << "\nPilih nomor pesanan yang ingin diedit: ";
    cin >> pilih;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (pilih < 1 || pilih > daftarPemesanan.size()) {
        cout << "Pilihan tidak valid.\n";
        return;
    }

    Pemesanan& pesanan = daftarPemesanan[pilih - 1];
    if (pesanan.sudahDibayar) {
        cout << "\nPesanan ini sudah dibayar dan tidak bisa diubah.\n";
        return;
    }

    daftarPemesanan.erase(daftarPemesanan.begin() + (pilih - 1));

    // (lanjutkan proses pemesanan ulang seperti sebelumnya)
    // kode pemesanan ulang dari fungsi pesan_tiket bisa digunakan di sini
    cout << "\nSilakan ulangi proses pemesanan baru...\n";
    pesan_tiket();
}

void lihatPemesanan() {
    ifstream file("datapemesanankursi.txt");
    if (!file) {
        cout << "Belum ada pemesanan.\n";
        system("pause");
        return;
    }

    string line;
    cout << "\n============ Riwayat Pemesanan ============\n\n";
    while (getline(file, line)) {
        cout << line << endl;
        system("pause");
    }
	system("pause");
    file.close();
}

void editKursi(string kodeLama, string kodeBaru) {
    ifstream in("layoutkursi.txt");
    ofstream temp("temp.txt");

    if (!in || !temp) {
        cout << "Gagal membuka file.\n";
        return;
    }

    string kode;
    int status;
    bool ditemukanLama = false, ditemukanBaru = false;
    bool kursiBaruTersedia = false;

    while (in >> kode >> status) {
        if (kode == kodeLama) {
            temp << kode << " 0\n";
            ditemukanLama = true;
        } else if (kode == kodeBaru) {
            ditemukanBaru = true;
            if (status == 0) {
                temp << kode << " 1\n";
                kursiBaruTersedia = true;
            } else {
                temp << kode << " " << status << "\n";
            }
        } else {
            temp << kode << " " << status << "\n";
        }
    }

    in.close();
    temp.close();

    remove("layoutkursi.txt");
    rename("temp.txt", "layoutkursi.txt");

    if (!ditemukanLama) {
        cout << " Kursi lama tidak ditemukan.\n";
    } else if (!ditemukanBaru) {
        cout << " Kursi baru tidak ditemukan.\n";
    } else if (!kursiBaruTersedia) {
        cout << " Kursi baru sudah dipesan.\n";
    } else {
        ofstream log("datapemesanankursi.txt", ios::app);
        log << " Kursi " << kodeLama << " diubah ke " << kodeBaru << ".\n";
        log.close();
        cout << " Kursi berhasil diubah.\n";
    }
}

int main() {
    system("color 2");
    ifstream cek("layoutkursi.txt");
    if (!cek || cek.peek() == ifstream::traits_type::eof()) {
        initLayout();
    }
    cek.close();

    int pilihan;
	int index_login = -1;
	JenisLogin tipe_login = TIDAK_LOGIN;

	do {
    	if (index_login == -1) {
        	menu_before_login();
        	cin >> pilihan;
        	switch (pilihan) {
            	case 1: registrasi(); break;
            	case 2: index_login = login(tipe_login); break;
            	case 3: hapusAkun(); break;
            	case 0: cout << "Keluar dari program.\n"; break;
            	default: cout << "Pilihan tidak valid.\n"; system("pause"); break;
        	}
    	} else {
        	if (tipe_login == LOGIN_USER) {
        		tampilkan_logo_bioskop();
            	menu_after_login();
            	cin >> pilihan;
            	switch (pilihan) {
                	case 1: lihatDataDiri(bacaAkun()[index_login]); break;
                	case 2: jadwal(); break;
                	case 3: pesan_tiket(); break;
                	case 4: bukaFilePesanan(); break;
                	case 5: editPemesananUser(); break;
                	case 6: {
                		system("cls");
	                		int jumlahKursi;
	                		 
	                		vector<pair<string, string> > daftarKursiBaru;
	                		 
						    cout << "Masukkan jumlah kursi yang ingin diubah: ";
						    cin >> jumlahKursi;
						    cin.ignore(); // flush newline
						
						    for (int i = 0; i < jumlahKursi; ++i) {
						        string kodeLama, kodeBaru;
						        cout << "\nKursi ke-" << i+1 << endl;
						        cout << "Masukkan kode kursi lama : ";
						        getline(cin, kodeLama);
						        cout << "Masukkan kode kursi baru : ";
						        getline(cin, kodeBaru);
						        editKursi(kodeLama, kodeBaru);
						        daftarKursiBaru.push_back(make_pair(kodeLama, kodeBaru));
						    }
						    
						     for (int j = 0; j < daftarPemesanan.size(); ++j) {
							    vector<string>& kursiList = daftarPemesanan[j].kursi;
							    for (int k = 0; k < kursiList.size(); ++k) {
							        for (int l = 0; l < daftarKursiBaru.size(); ++l) {
							            if (kursiList[k] == daftarKursiBaru[l].first) {
							                kursiList[k] = daftarKursiBaru[l].second;
							            }
							        }
							    }
							}
						    
						    ofstream file("daftar_pesanan.txt");
						    for (int i = 0; i < daftarPemesanan.size(); ++i) {
						        Pemesanan &q = daftarPemesanan[i];
						        file << "============ PESANAN ============\n" << endl;
						        file << q.namaPemesan << endl << endl;
						        file << "Studio            : " << q.studio << endl;
						        file << "Judul Film        : " << q.judulFilm << endl;
						        file << "Waktu             : " << q.waktu << endl;
						        file << "Durasi            : " << q.durasi << endl;
						        file << "Genre             : " << q.genre << endl;
						        file << "Jenis Tiket       : " << q.jenisTiket << endl;
						        file << "Harga             : " << q.harga << endl;
						        file << "Jumlah Tiket      : " << q.jumlahTiket << endl;
						        file << "Total Harga       : " << q.totalHarga << endl;
						        file << "Kursi yang dipilih: ";
						        for (int k = 0; k < q.kursi.size(); ++k) {
						            file << q.kursi[k] << " ";
						        }
						        file << endl;
						    }
						    file.close();
						    cout << "Data kursi berhasil diperbarui dan disimpan.\n";
						
						    system("pause");
							break;
					}
					case 7:
    					index_login = -1; 
						break;
                	case 0: cout << "Keluar dari program.\n"; break;
                	default: cout << "Pilihan tidak valid.\n"; break;
            	}
        	} else if (tipe_login == LOGIN_ADMIN) {
        		string kode;
            	menu_admin();
            	cin >> pilihan;
            	switch (pilihan) {
                	case 1: tampilfilm(); break;
                	case 2: pesan_tiket(); break;
                	case 3: bukaFilePesanan(); break;
                	case 4: editPemesanan(); break;
                	case 5: {
                		 int jumlahKursi;
                		 
                		vector<pair<string, string> > daftarKursiBaru;
                		 
					    cout << "Masukkan jumlah kursi yang ingin diubah: ";
					    cin >> jumlahKursi;
					    cin.ignore(); // flush newline
					
					    for (int i = 0; i < jumlahKursi; ++i) {
					        string kodeLama, kodeBaru;
					        cout << "\nKursi ke-" << i+1 << endl;
					        cout << "Masukkan kode kursi lama: ";
					        getline(cin, kodeLama);
					        cout << "Masukkan kode kursi baru: ";
					        getline(cin, kodeBaru);
					        editKursi(kodeLama, kodeBaru);
					        daftarKursiBaru.push_back(make_pair(kodeLama, kodeBaru));
					    }
					    
					     for (int j = 0; j < daftarPemesanan.size(); ++j) {
						    vector<string>& kursiList = daftarPemesanan[j].kursi;
						    for (int k = 0; k < kursiList.size(); ++k) {
						        for (int l = 0; l < daftarKursiBaru.size(); ++l) {
						            if (kursiList[k] == daftarKursiBaru[l].first) {
						                kursiList[k] = daftarKursiBaru[l].second;
						            }
						        }
						    }
						}
					    
					    ofstream file("daftar_pesanan.txt");
					    for (int i = 0; i < daftarPemesanan.size(); ++i) {
					        Pemesanan &q = daftarPemesanan[i];
					        file << "============ PESANAN ============\n" << endl;
					        file << q.namaPemesan << endl << endl;
					        file << "Studio            : " << q.studio << endl;
					        file << "Judul Film        : " << q.judulFilm << endl;
					        file << "Waktu             : " << q.waktu << endl;
					        file << "Durasi            : " << q.durasi << endl;
					        file << "Genre             : " << q.genre << endl;
					        file << "Jenis Tiket       : " << q.jenisTiket << endl;
					        file << "Harga             : " << q.harga << endl;
					        file << "Jumlah Tiket      : " << q.jumlahTiket << endl;
					        file << "Total Harga       : " << q.totalHarga << endl;
					        file << "Kursi yang dipilih: ";
					        for (int k = 0; k < q.kursi.size(); ++k) {
					            file << q.kursi[k] << " ";
					        }
					        file << endl;
					    }
					    file.close();
					    cout << "Data kursi berhasil diperbarui dan disimpan.\n";
					
					    system("pause");
					    break;
					}
					case 6: statistikKursiTerisi(); break;
                	case 7: index_login = -1; tipe_login = TIDAK_LOGIN; break;
                	case 0: cout << "Keluar dari program.\n"; break;
                	default: cout << "Pilihan tidak valid.\n"; break;
            	}
        	}
    	}
	} while (pilihan != 0);

    return 0;
}
