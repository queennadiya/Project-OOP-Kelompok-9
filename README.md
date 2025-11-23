# Sistem Pengelolaan Nilai Sederhana (C++)
Program ini merupakan simulasi sederhana sistem penilaian di sekolah. Data guru, murid, dan nilai tugas dikelola menggunakan konsep **Object-Oriented Programming (OOP)** dan array statis.
## Fitur
- Menyimpan data guru dan murid  
- Input nilai tugas dengan validasi  
- Batas kapasitas:
  - `MAX_STUDENTS = 10`
  - `MAX_TASKS = 5`
  - `MAX_TEACHERS = 5`
- Perhitungan rata-rata nilai  
- Menampilkan laporan nilai murid
## Struktur Kelas
- **Person** — menyimpan nama & umur  
- **Teacher : Person** -> data guru  
- **Student : Person** -> data murid, nilai tugas, dan rata-rata  
## Fungsionalitas Program
- Melihat daftar guru & memilih guru aktif  
- Menambahkan data murid saat pertama kali diberi nilai  
- Input nilai tugas (1–99, nilai 100 ditolak)  
- Mencetak daftar nilai seluruh murid  
## Tujuan Proyek
Menyediakan contoh program C++ yang menerapkan OOP, array statis, dan validasi input untuk pengelolaan data pendidikan secara sederhana.
