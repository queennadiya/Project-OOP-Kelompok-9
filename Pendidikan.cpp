/*
JOSE IMANUEL STANLEY WIJAYA/255150300111040
QUEEN NADIYA AILSA DIKLA/25515030111029
MUHAMMAD HANIF FADHILAH/25515030111026
*/
/*SISTEM PENGELOLAAN MURID, GURU DAN PENILAIAN TUGAS*/

#include <iostream>
#include <string>
using namespace std;

// banyak murid maksimal, banyak tugas per murid, banyak guru
const int MAX_STUDENTS = 10;
const int MAX_TASKS = 5;
const int MAX_TEACHERS = 5;

// Class Person 
// menyimpan nama dan umur (dipakai untuk guru & murid)
class Person {
protected:
    string nama; // nama: menyimpan nama orang (guru atau murid)
    int umur;    // umur: menyimpan umur orang dalam tahun
public:
    Person(): nama(""), umur(0) {}
    void setData(const string& n, int u) { nama = n; umur = u; }
    string getNama() const { return nama; }
    int getUmur() const { return umur; }
};

// Class Student
// menyimpan nilai tugas (array tetap) dan menghitung rata-rata
class Student : public Person {
    int tugas[MAX_TASKS]; // tugas: array menyimpan nilai tugas, indeks 0..MAX_TASKS-1
    int nTugas;           // nTugas: jumlah tugas yang sudah diisi untuk murid ini
public:
    Student(): nTugas(0) { for (int i = 0; i < MAX_TASKS; ++i) tugas[i] = 0; }
    void init(const string& n, int u) { setData(n, u); nTugas = 0; }
    int submit(int nilai) { // kembalikan 1 jika berhasil, 0 jika penuh
        if (nTugas >= MAX_TASKS) return 0;
        tugas[nTugas++] = nilai;
        return 1;
    }
    double rata() const {
        if (nTugas == 0) return 0.0;
        int s = 0;
        for (int i = 0; i < nTugas; ++i) s += tugas[i];
        return double(s) / nTugas;
    }
    int jumlahTugas() const { return nTugas; }
    int nilaiAt(int i) const { return (i >= 0 && i < nTugas) ? tugas[i] : 0; }
};

// Class teacher
// (menggunakan Person: nama & umur)
class Teacher : public Person {
public:
    Teacher(): Person() {}
    void set(const string& n, int u) { setData(n, u); }
};
 
int main() {
    // 5 slot guru sudah ditetapkan dari awal (bisa diubah di kode)
    Teacher teachers[MAX_TEACHERS];
    teachers[0].set("Pak Heru", 40);
    teachers[1].set("Pak Arief", 38);
    teachers[2].set("Ibu Anes", 35);
    teachers[3].set("Pak Ai", 42);
    teachers[4].set("Bu Hanif", 30);

    Student siswa[MAX_STUDENTS]; // array murid, slot 0..9
    int currentTeacher = 0; // index guru aktif (default 0)

    // Penjelasan variabel :
    // teachers         : array untuk menyimpan data 5 guru (nama & umur)
    // siswa            : array untuk menyimpan data murid (slot 0..9), tiap murid punya daftar tugas
    // currentTeacher   : nomor/index guru yang dipilih sebagai guru aktif saat ini

    // loop menu sederhana
    while (true) {
        cout << "\n--- Sistem Penilaian Sederhana ---\n";
        cout << "1. Lihat daftar guru\n";
        cout << "2. Pilih guru aktif (0..4)\n";
        cout << "3. Submit nilai (isi data murid jika belum ada)\n";
        cout << "4. Cetak nilai akhir (untuk guru aktif)\n";
        cout << "5. Keluar\n";
        cout << "Pilih: ";

        int pilihan;
        cin >> pilihan; // baris pengecekan kompleks dihapus seperti minta kamu

        if (pilihan == 1) {
            // tampilkan semua guru dan umur mereka
            cout << "\nDaftar guru (slot 0.." << (MAX_TEACHERS - 1) << "):\n";
            for (int i = 0; i < MAX_TEACHERS; ++i) {
                cout << i << ". " << teachers[i].getNama() << " (umur " << teachers[i].getUmur() << ")\n";
            }
        } else if (pilihan == 2) {
            // pilih guru aktif berdasarkan index yang terlihat di menu 1
            cout << "Pilih nomor guru aktif (0.." << (MAX_TEACHERS - 1) << "): ";
            int no; cin >> no;
            if (no < 0 || no >= MAX_TEACHERS) {
                cout << "Nomor guru tidak valid.\n";
                continue;
            }
            currentTeacher = no;
            cout << "Guru aktif sekarang: " << teachers[currentTeacher].getNama() << "\n";
        } else if (pilihan == 3) {
            // tambah nilai untuk murid di slot tertentu; jika murid belum terisi, masukkan data murid
            cout << "Masukkan nomor murid (0 sampai " << (MAX_STUDENTS - 1) << "): ";
            int nomor; cin >> nomor;
            if (nomor < 0 || nomor >= MAX_STUDENTS) {
                cout << "Nomor tidak valid.\n";
                continue;
            }
            // jika nama murid masih kosong (belum diisi), minta nama & umur
            if (siswa[nomor].getNama().size() == 0) {
                cout << "Data murid belum ada, isi data baru.\n";
                string nama; int umur;
                cout << "Nama murid: "; cin >> ws; getline(cin, nama);
                cout << "Umur murid: "; cin >> umur;
                siswa[nomor].init(nama, umur);
                cout << "Murid tersimpan di slot " << nomor << ".\n";
            } else {
                cout << "Murid terpilih: " << siswa[nomor].getNama() << "\n";
            }
            // submit nilai tugas dengan aturan baru:
            // - nilai tidak boleh 100 (jika 100 tampilkan pesan dan minta lagi)
            // - nilai yang valid adalah 1..99
            int nilai;
            while (true) {
                cout << "Masukkan nilai tugas (1-99): ";
                cin >> nilai;
                if (nilai == 100) {
                    cout << "kesempurnaan hanya milik tuhan\n";
                    // ulangi input
                    continue;
                }
                if (nilai < 1 || nilai > 99) {
                    cout << "Nilai tidak valid. Masukkan nilai antara 1 sampai 99.\n";
                    continue;
                }
                // valid
                break;
            }
            int hasil = siswa[nomor].submit(nilai);
            if (hasil == 1) cout << "Nilai tersimpan untuk " << siswa[nomor].getNama() << ".\n";
            else cout << "Sudah penuh tugas untuk murid ini.\n";
        } else if (pilihan == 4) {
            // cetak semua murid beserta nilai & rata-rata; guru aktif hanya ditampilkan sebagai info
            cout << "\n-- Data Guru & Murid (Guru aktif: " << teachers[currentTeacher].getNama() << ") --\n";
            int jumlahDitemukan = 0;
            for (int i = 0; i < MAX_STUDENTS; ++i) {
                if (siswa[i].getNama().size() == 0) {
                    // kosong, lewati
                } else {
                    jumlahDitemukan = jumlahDitemukan + 1;
                    cout << i << ". " << siswa[i].getNama() << " | Tugas: " << siswa[i].jumlahTugas() << " | Nilai: ";
                    for (int t = 0; t < siswa[i].jumlahTugas(); ++t) {
                        cout << siswa[i].nilaiAt(t);
                        if (t < siswa[i].jumlahTugas() - 1) cout << ", ";
                    }
                    cout << " | Rata-rata: " << siswa[i].rata() << "\n";
                }
            }
            if (jumlahDitemukan == 0) cout << "Belum ada murid yang terdaftar.\n";
        } else if (pilihan == 5) {
            cout << "Keluar.\n";
            break;
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    }

    return 0;
}