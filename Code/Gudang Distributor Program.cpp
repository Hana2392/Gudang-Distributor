#include <iostream>
#include <string>
using namespace std;

const int MAX = 100;

struct Barang {
    string nama;
    int nomor;
};

// struct
struct GudangDistributor {
	// Array
    Barang antrian[MAX];
    int awal, akhir;
    
    // stack
    Barang riwayatKeluar[MAX];  // Penambahan stack untuk riwayat barang keluar
    int topStack;

    GudangDistributor() {
        awal = akhir = -1;
        topStack = -1;
    }

    bool full() {
        return (akhir + 1) % MAX == awal;
    }

    bool empty() {
        return awal == -1;
    }

	// pointer
    void inQueue(const Barang& item) {
        if (full()) {
            cout << "Antrian penuh. Tidak dapat menambahkan barang." << endl;
            return;
        }

        if (empty()) {
            awal = akhir = 0;
        } else {
            akhir = (akhir + 1) % MAX;
        }

        antrian[akhir] = item;
        cout << "Barang dengan nama '" << item.nama << "' telah dimasukkan ke dalam antrian." << endl;
    }

    void deQueue() {
        if (empty()) {
            cout << "Antrian kosong. Tidak dapat mengeluarkan barang." << endl;
            return;
        }

        Barang item = antrian[awal];

        if (awal == akhir) {
            awal = akhir = -1;
        } else {
            awal = (awal + 1) % MAX;
        }

        cout << "Panggilan Nomor: " << item.nomor << "\nAtas nama: " << item.nama << endl;

        // Tambahkan ke stack riwayat keluar
        if (topStack < MAX - 1) {
            riwayatKeluar[++topStack] = item;
        } else {
            cout << "Stack riwayat keluar penuh. Data tidak dapat ditambahkan." << endl;
        }
    }

    void clear() {
        awal = akhir = -1;
        cout << "Antrian berhasil ditutup." << endl;
    }

    void lihatJumlahAntrian() {
        if (empty()) {
            cout << "Antrian kosong." << endl;
        } else {
            int jumlah = (akhir - awal + MAX) % MAX + 1;
            cout << "Jumlah barang dalam antrian: " << jumlah << endl;

            // Sorting Bubble Sort secara ascending berdasarkan nama barang
            for (int i = awal; i <= akhir; ++i) {
                for (int j = awal; j <= akhir - 1; ++j) {
                    if (antrian[j].nama > antrian[j + 1].nama) {
                        Barang temp = antrian[j];
                        antrian[j] = antrian[j + 1];
                        antrian[j + 1] = temp;
                    }
                }
            }

            cout << "List Barang (asc):" << endl;
            for (int i = awal; i <= akhir; ++i) {
                cout << i + 1 << ". " << antrian[i].nama << endl;
            }
        }
    }

    void lihatRiwayatKeluar() {
        if (topStack >= 0) {
            cout << "Riwayat Barang Keluar:" << endl;
            for (int i = topStack; i >= 0; --i) {
                cout << "(" << riwayatKeluar[i].nama << ")" << endl;
            }
        } else {
            cout << "Riwayat barang keluar kosong." << endl;
        }
    }
};

int main() {
    GudangDistributor antrianGudang;

    int pilihan, nomorAntrian = 1;
    do {
        cout << "Antrian Gudang Distributor" << endl;
        cout << "Pilihan:" << endl;
        cout << "1. Masukkan Barang ke Antrian" << endl;
        cout << "2. Keluarkan Barang dari Antrian" << endl;
        cout << "3. List Jumlah Barang dalam Antrian" << endl;
        cout << "4. Riwayat Barang Keluar" << endl;  // Menambahkan opsi untuk melihat riwayat barang keluar
        cout << "5. Tutup Antrian" << endl;
        cout << "6. Keluar dari Program" << endl;  // Menambahkan opsi untuk keluar dari program
        cout << "Silahkan Pilih: ";
        cin >> pilihan;

        Barang item;

        switch (pilihan) {
            case 1:
                cout << "Masukkan Nama: ";
                cin >> item.nama;
                item.nomor = nomorAntrian++;
                antrianGudang.inQueue(item);
                cout << endl;
                break;
            case 2:
                antrianGudang.deQueue();
                cout << endl;
                break;
            case 3:
                antrianGudang.lihatJumlahAntrian();
                cout << endl;
                break;
            case 4:
                antrianGudang.lihatRiwayatKeluar();
                cout << endl;
                break;
            case 5:
                antrianGudang.clear();
                cout << endl;
                break;
            case 6:
                cout << "Keluar dari Program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid" << endl;
        }
    } while (pilihan != 6);

    return 0;
}

