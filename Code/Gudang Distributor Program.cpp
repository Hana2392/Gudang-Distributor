#include <iostream>
#include <string>
#include <iomanip>
#include <unistd.h>

using namespace std;
const int MAX = 100;

// Menentukan lebar kolom
const int noWidth = 3;
const int namaBarangWidth = 25;   // Lebar kolom untuk nama barang
const int stokWidth = 10;         // Lebar kolom untuk stok
const int tanggalMasukWidth = 15; // Lebar kolom untuk tanggal masuk

// struct
struct Barang
{
    string nama;
    int nomor;
    int stok;
    string tanggalMasuk;
};

// struct
struct GudangDistributor
{
    // Array
    Barang antrian[MAX];
    int awal, akhir;

    bool full()
    {
        return (akhir + 1) % MAX == awal;
    }

    bool empty()
    {
        return awal == -1;
    }

    void inQueue(const Barang &item) // Masukkan Barang ke Gudang
    {
        if (full())
        {
            cout << "Antrian penuh. Tidak dapat menambahkan barang." << endl;
            return;
        }

        if (empty())
        {
            awal = akhir = 0;
        }
        else
        {
            akhir = (akhir + 1) % MAX;
        }

        antrian[akhir] = item;
        for (int i = 0; i < 4; ++i)
        {
            cout << "....";
            sleep(1);
        }
        cout << endl;
        cout << "Barang dengan nama '" << item.nama << "' telah dimasukkan ke dalam antrian." << endl;
    }

    void deQueue() // Keluarkan Barang dari Gudang
    {
        if (empty())
        {
            cout << "Antrian kosong. Tidak dapat mengeluarkan barang." << endl;
            return;
        }

        Barang item = antrian[awal];

        if (awal == akhir)
        {
            awal = akhir = -1;
        }
        else
        {
            awal = (awal + 1) % MAX;
        }

        cout << "Nomor Barang : " << item.nomor << "\nNama Barang : " << item.nama << endl;

        // Tambahkan ke stack riwayat keluar
        if (topStack < MAX - 1)
        {
            riwayatKeluar[++topStack] = item;
        }
        else
        {
            cout << "Stack riwayat keluar penuh. Data tidak dapat ditambahkan." << endl;
        }
    }

    void lihatJumlahAntrian() // List Barang dalam Gudang
    {
        if (empty())
        {
            cout << "Antrian kosong." << endl;
        }
        else
        {
            system("cls");
            // Sorting Bubble Sort secara ascending berdasarkan nama barang
            for (int i = awal; i <= akhir; ++i)
            {
                for (int j = awal; j <= akhir - 1; ++j)
                {
                    if (antrian[j].nama > antrian[j + 1].nama)
                    {
                        Barang temp = antrian[j];
                        antrian[j] = antrian[j + 1];
                        antrian[j + 1] = temp;
                    }
                }
            }

            // Tampilkan header
            cout << "List Barang (asc):" << endl;
            cout << string(noWidth + 1 + namaBarangWidth + 1 + stokWidth + 1 + tanggalMasukWidth + 1, '=') << endl;
            cout << "| " << left << setw(noWidth) << "NO"
                 << "| " << left << setw(namaBarangWidth) << "Nama Barang"
                 << "| " << left << setw(stokWidth) << "Stok"
                 << "| " << left << setw(tanggalMasukWidth) << "Tanggal Masuk"
                 << "|" << endl;

            // Tampilkan data barang
            for (int i = awal; i <= akhir; ++i)
            {
                cout << "| " << left << setw(noWidth) << i + 1 << "| " << left << setw(namaBarangWidth) << antrian[i].nama << "| " << left << setw(stokWidth) << antrian[i].stok << "| " << left << setw(tanggalMasukWidth) << antrian[i].tanggalMasuk << "|" << endl;
            }

            // Tampilkan footer
            cout << string(noWidth + 1 + namaBarangWidth + 1 + stokWidth + 1 + tanggalMasukWidth + 1, '=') << endl;
        }
    }

    // Searching menggunakan metode Sentinel Search
    // Membuat Function searching
    int sentinelSearch(const string &key)
    {
        int i = awal;
        antrian[akhir + 1].nama = key; // Menetapkan sentinel sebagai kunci pencarian

        while (antrian[i].nama != key)
        {
            ++i;
        }

        if (i <= akhir)
        {
            return i;
        }

        return -1;
    }

    void caribarang()
    {
        if (empty())
        {
            lihatJumlahAntrian();
        }
        else
        {
            string ulang;
            do
            {
                lihatJumlahAntrian();

                // Metode Sentinel Searching
                string keyword;
                cout << "Masukkan Nama Barang yang dicari: ";
                cin >> keyword;

                int index = sentinelSearch(keyword); // memanggil function searching

                if (index != -1)
                {
                    cout << "Barang ditemukan pada posisi: " << index + 1 << endl;
                    cout << "Apakah ingin mengulang pencarian? (y/t) :";
                    cin >> ulang;
                }
                else
                {
                    cout << "Barang tidak ditemukan." << endl;
                    cout << "Apakah ingin mengulang pencarian? (y/t) :";
                    cin >> ulang;
                }
            } while (ulang == "y");
        }
    }

    // Penggunaan Stack
    Barang riwayatKeluar[MAX]; // Penambahan stack untuk riwayat barang keluar
    int topStack;

    GudangDistributor()
    {
        awal = akhir = -1;
        topStack = -1;
    }
    void lihatRiwayatKeluar() // Riwayat Barang Keluar
    {
        if (topStack >= 0)
        {
            system("cls");
            cout << "Riwayat Barang Keluar:" << endl;
            cout << string(noWidth + 1 + namaBarangWidth + 1 + stokWidth + 1, '=') << endl;
            cout << "| " << left << setw(noWidth) << "NO"
                 << "| " << left << setw(namaBarangWidth) << "Nama Barang"
                 << "| " << left << setw(stokWidth) << "Stok"
                 << "|" << endl;

            // Menggunakan pointer untuk mengakses elemen-elemen array
            Barang *pointer = riwayatKeluar;
            for (int i = 0; i <= topStack; ++i)
            {
                cout << "| " << left << setw(noWidth) << i + 1 << "| " << left << setw(namaBarangWidth) << pointer->nama << "| " << left << setw(stokWidth) << pointer->stok << "|" << endl;
                ++pointer;
            }

            cout << string(noWidth + 1 + namaBarangWidth + 1 + stokWidth + 1, '=') << endl;
        }
        else
        {
            cout << "Riwayat barang keluar kosong." << endl;
        }
    }

    void clear() // Tutup Antrian
    {
        string pilihtutup;
        cout << "Apakah anda ingin menutup antrian? (y/t) :";
        cin >> pilihtutup;
        if (pilihtutup == "t" || "T")
        {
            cout << "Batal menutup antrian" << endl;
        }
        else
        {
            awal = akhir = -1;
            cout << "Antrian berhasil ditutup." << endl;
        }
    }
};

int main()
{
    GudangDistributor antrianGudang;

    int pilihan, nomorAntrian = 1;
    char kembali;
menu:
    do
    {
        system("cls");
        cout << "================ Gudang Distributor ================\n"
             << endl;
        cout << "Pilihan:" << endl;
        cout << "1. Masukkan Barang ke Gudang" << endl;
        cout << "2. Keluarkan Barang dari Gudang" << endl;
        cout << "3. List Barang dalam Gudang" << endl;
        cout << "4. Pencarian Barang" << endl;
        cout << "5. Riwayat Barang Keluar" << endl; // Menambahkan opsi untuk melihat riwayat barang keluar
        cout << "6. Tutup Antrian" << endl;
        cout << "7. Keluar dari Program" << endl; // Menambahkan opsi untuk keluar dari program
        cout << endl;
        cout << "Silahkan Pilih: ";
        cin >> pilihan;
        Barang item;

        switch (pilihan)
        {
        case 1:
            for (int i = 0; i < 4; ++i)
            {
                cout << "....";
                sleep(1);
            }
            system("cls");
            cout << "================ Masukkan Barang ke Gudang ================ \n"
                 << endl;
            cout << "Masukkan Nama: ";
            cin >> item.nama;
            cout << "Masukkan Stok: ";
            cin >> item.stok;
            cout << "Masukkan Tanggal Masuk (format: DD/MM/YYYY): ";
            cin >> item.tanggalMasuk;
            item.nomor = nomorAntrian++;
            antrianGudang.inQueue(item);
            cout << endl;
            cout << "Kembali ke menu? (y) :";
            cin >> kembali;
            goto menu;
            break;
        case 2:
            for (int i = 0; i < 4; ++i)
            {
                cout << "....";
                sleep(1);
            }
            cout << endl;
            system("cls");
            cout << "================ Keluarkan Barang dari Gudang ================ \n"
                 << endl;
            antrianGudang.deQueue();
            cout << "Kembali ke menu? (y) :";
            cin >> kembali;
            goto menu;
            break;
        case 3:
            for (int i = 0; i < 4; ++i)
            {
                cout << "....";
                sleep(1);
            }
            cout << endl;
            system("cls");
            cout << "================ List Barang dalam Gudang ================ \n"
                 << endl;
            antrianGudang.lihatJumlahAntrian();
            cout << endl;
            cout << "Kembali ke menu? (y) :";
            cin >> kembali;
            goto menu;
            break;
        case 4:
            for (int i = 0; i < 4; ++i)
            {
                cout << "....";
                sleep(1);
            }
            cout << endl;
            system("cls");
            cout << "================ Pencarian Barang ================ \n"
                 << endl;
            antrianGudang.caribarang();
            goto menu;
            break;
        case 5:
            for (int i = 0; i < 4; ++i)
            {
                cout << "....";
                sleep(1);
            }
            cout << endl;
            system("cls");
            cout << "================ Riwayat Barang Keluar ================ \n"
                 << endl;
            antrianGudang.lihatRiwayatKeluar();
            cout << "Kembali ke menu? (y) :";
            cin >> kembali;
            goto menu;
            break;
        case 6:
            for (int i = 0; i < 4; ++i)
            {
                cout << "....";
                sleep(1);
            }
            system("cls");
            cout << "================ Tutup Antrian ================ \n"
                 << endl;
            antrianGudang.clear();
            cout << endl;
            cout << "Kembali ke menu? (y) :";
            cin >> kembali;
            goto menu;
            break;
        case 7:
            cout << "Keluar dari Program." << endl;
            cout << "================ TERIMA KASIH ================" << endl;
            sleep(1);
            break;
        default:
            cout << "Pilihan tidak valid" << endl;
            sleep(2.8);
            goto menu;
        }
    } while (pilihan != 7);

    return 0;
}

