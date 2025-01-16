#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>
#include <string>
using namespace std;

// Struct untuk data KTP
struct KTP {
    string nomorKTP;
    string nama;
    string alamat;
};

// Struct untuk data item barang
struct Item {
    string kodeItem;
    string tanggalMasuk;
};

// Fungsi untuk menyimpan data KTP ke file
void simpanDataKTP(const KTP& ktp) {
    ofstream file("data_ktp.txt", ios::app);
    if (file.is_open()) {
        file << ktp.nomorKTP << "," << ktp.nama << "," << ktp.alamat << endl;
        file.close();
    } else {
        cerr << "Error: Tidak dapat membuka file untuk menyimpan data KTP!" << endl;
    }
}

// Fungsi untuk mencetak daftar barang
void cetakDaftarBarang(const stack<Item>& lifo) {
    cout << "\nDaftar Barang (LIFO - Last In First Out):\n";
    stack<Item> tempLifo = lifo;
    while (!tempLifo.empty()) {
        Item item = tempLifo.top();
        tempLifo.pop();
        cout << "Kode: " << item.kodeItem << ", Tanggal Masuk: " << item.tanggalMasuk << endl;
    }
}

int main() {
    stack<Item> lifoGudang; // Penyimpanan LIFO
    vector<KTP> pembeli;

    int pilihan;
    string nomorKTP, nama, alamat;
    string kodeItem, tanggalMasuk;

    do {
        cout << "\nMenu:\n";
        cout << "1. Admin Sign In\n";
        cout << "2. Entri Item Barang\n";
        cout << "3. Jual Item Barang\n";
        cout << "4. Cetak Daftar Barang\n";
        cout << "5. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "Masukkan nomor KTP: ";
                cin >> nomorKTP;
                cout << "Masukkan nama: ";
                cin.ignore();
                getline(cin, nama);
                cout << "Masukkan alamat: ";
                getline(cin, alamat);

                pembeli.push_back({nomorKTP, nama, alamat});
                simpanDataKTP({nomorKTP, nama, alamat});
                cout << "Admin berhasil masuk dan data KTP disimpan.\n";
                break;

            case 2:
                cout << "Masukkan kode item: ";
                cin >> kodeItem;
                cout << "Masukkan tanggal masuk (YYYY-MM-DD): ";
                cin >> tanggalMasuk;

                lifoGudang.push({kodeItem, tanggalMasuk});
                cout << "Item berhasil ditambahkan ke gudang.\n";
                break;

            case 3:
                if (!lifoGudang.empty()) {
                    Item itemLIFO = lifoGudang.top();
                    lifoGudang.pop();
                    cout << "Barang dengan kode " << itemLIFO.kodeItem << " telah dijual.\n";
                } else {
                    cout << "Error: Gudang kosong, tidak ada barang yang bisa dijual.\n";
                }
                break;

            case 4:
                cetakDaftarBarang(lifoGudang);
                break;

            case 5:
                cout << "Keluar dari program.\n";
                break;

            default:
                cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 5);

    return 0;
}

