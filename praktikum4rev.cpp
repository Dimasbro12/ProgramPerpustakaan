#include <iostream>
#include <string>
using namespace std;

// Hash Table Login
struct hashTabel
{
  string username, password;
} dataAkun[10000];

// Binary Tree Buku
// Structure to store book metadata
struct Book {
    int id;
    string title;
    string author;
    int year;
    bool isBorrowed;
};

// Node structure for BST
struct TreeNode {
    Book book;
    TreeNode* left;
    TreeNode* right;
};

// Struct Transaksi
struct Transaksi {
    Book* book; // Use a pointer to the actual book object
    int id; // ID of the transaction
    string tanggalPinjam;
    string tanggalKembali;
    Transaksi *next;
};

// Hash Table untuk Transaksi
struct HashTableNode {
    Transaksi transaksi;
    HashTableNode* next;
};

// Array untuk tabel hash
HashTableNode* hashTable[10000] = {nullptr};

// Tampilkan lokasi rak buku
void tampilkanLokasiRakBuku(int jumlah_simpul, int matrix[10][10]) {
    cout << "Lokasi rak buku dalam perpustakaan berdasarkan graf konektivitas:" << endl;
    for (int i = 1; i <= jumlah_simpul; ++i) {
        cout << "Rak buku " << i << " terhubung ke rak buku: ";
        for (int j = 1; j <= jumlah_simpul; ++j) {
            if (matrix[i][j] == 1) {
                cout << j << " ";
            }
        }
        cout << endl;
    }
}


// Fungsi Hash untuk ID Buku
int HashID(int id)
{
  return id % 10000;
}

// Function to create a new tree node
TreeNode* createNode(Book book) {
    TreeNode* newNode = new TreeNode();
    newNode->book = book;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

// Function to insert a book into the BST
TreeNode* insert(TreeNode* root, Book book) {
    if (root == nullptr) {
        root = createNode(book);
    } else if (book.id < root->book.id) {
        root->left = insert(root->left, book);
    } else if (book.id > root->book.id) {
        root->right = insert(root->right, book);
    }
    return root;
}

// Function to search for a book by ID
TreeNode* search(TreeNode* root, int id) {
    if (root == nullptr || root->book.id == id) {
        return root;
    }
    if (id < root->book.id) {
        return search(root->left, id);
    } else {
        return search(root->right, id);
    }
}

// Function to display book metadata (in-order traversal)
void inorderDisplay(TreeNode* root) {
    if (root != nullptr) {
        inorderDisplay(root->left);
        cout << "ID: " << root->book.id << ", Title: " << root->book.title
             << ", Author: " << root->book.author << ", Year: " << root->book.year << endl;
        inorderDisplay(root->right);
    }
}

// Function to input book metadata
Book inputBook() {
    Book book;
    cout << "Enter book ID: ";
    cin >> book.id;
    cin.ignore(); // To ignore the newline character after ID input
    cout << "Enter book title: ";
    getline(cin, book.title);
    cout << "Enter book author: ";
    getline(cin, book.author);
    cout << "Enter publication year: ";
    cin >> book.year;
    book.isBorrowed = false;
    return book;
}
// Function to display transactions
void DisplayTransaksi() {
    Transaksi* transaksiArray[10000];
    int transaksiCount = 0;

    // Extract all transactions from the hash table
    for (int i = 0; i < 10000; ++i) {
        HashTableNode* node = hashTable[i];
        while (node != nullptr) {
            transaksiArray[transaksiCount++] = &node->transaksi;
            node = node->next;
        }
    }

    // Sort transactions using selection sort based on transaction ID
    for (int i = 0; i < transaksiCount - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < transaksiCount; ++j) {
            if (transaksiArray[j]->id < transaksiArray[minIndex]->id) {
                minIndex = j;
            }
        }
        // Swap
        Transaksi* temp = transaksiArray[i];
        transaksiArray[i] = transaksiArray[minIndex];
        transaksiArray[minIndex] = temp;
    }

    // Display sorted transactions
    for (int i = 0; i < transaksiCount; ++i) {
        cout << "Transaction ID: " << transaksiArray[i]->id << "\n";
        cout << "Book ID: " << transaksiArray[i]->book->id << "\n";
        cout << "Book Title: " << transaksiArray[i]->book->title << "\n";
        cout << "Tanggal Pinjam: " << transaksiArray[i]->tanggalPinjam << "\n";
        cout << "Tanggal Kembali: " << transaksiArray[i]->tanggalKembali << "\n";
        cout << "-------------------------------------\n";
    }
}

// Menu Perpustakaan
void MenuPerpustakaan() {
    TreeNode* root = nullptr;
    int pilihan;
    bool ketemu, nolsemua;
    int matrix[10][10];
    int i, j, jumlah_simpul, jumlah_sisi, asal, tujuan;
    loop:
    while (true) {
        cout << "\t==== Selamat Datang di Program Perpustakaan ===\t" << "\n";
        cout << "1. Menu Lokasi Rak Buku" << "\n";
        cout << "2. Menu Manajemen Buku" << "\n";
        cout << "3. Menu Transaksi Peminjaman" << "\n";
        cout << "4. Keluar" << "\n";
        cout << "Masukkan Pilihan: [1-4]= ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            cout << "\t=== Selamat Datang di Menu Lokasi ===\t" << "\n";
            cout << "1. Edit dan tampilkan denah perpustakaan" << "\n";
            cout << "2. Menu utama" << "\n";
            cout << "Masukkan pilihan [1-2]= ";
            cin >> pilihan;
            if (pilihan == 1) {
                 cout << "Jumlah simpul: ";
    cin >> jumlah_simpul;
    cout << "Jumlah sisi: ";
    cin >> jumlah_sisi;

    // Inisialisasi matriks dengan 0
    for (i = 1; i <= jumlah_simpul; i++) {
        for (j = 1; j <= jumlah_simpul; j++) {  // Mengubah jumlah_sisi ke jumlah_simpul untuk inisialisasi yang benar
            matrix[i][j] = 0;
        }
    }

    // Memasukkan sisi ke dalam matriks
    for (int i = 0; i < jumlah_sisi; i++) {  // Mengubah <= menjadi < untuk perulangan yang benar
        cout << "Simpul asal: ";
        cin >> asal;
        cout << "Simpul tujuan: ";
        cin >> tujuan;
        matrix[asal][tujuan] = 1;
        matrix[tujuan][asal] = 1;
    }

    // Menampilkan lokasi rak buku
    tampilkanLokasiRakBuku(jumlah_simpul, matrix);

    // Memeriksa apakah graf terhubung
    i = 1;
    nolsemua = false;
    while (i <= jumlah_simpul && nolsemua == false) {
        j = 1;
        ketemu = false;
        while (j <= jumlah_simpul && ketemu == false) {
            if (matrix[i][j] == 1) {
                ketemu = true;
            } else {
                j++;
            }
        }
        if (ketemu == false) {
            nolsemua = true;
        } else {
            i++;
        }
    }

    if (nolsemua == true) {
        cout << "Graf tidak terhubung" << endl;
    } else {
        cout << "Graf terhubung" << endl;
    }
            }
            else {
              goto loop;
            }
            break;

        case 2: {
            int pilihanBuku;
            do {
                cout << "\nMenu:\n";
                cout << "1. Add Book\n";
                cout << "2. Search Book by ID\n";
                cout << "3. Display All Books\n";
                cout << "4. Exit\n";
                cout << "Enter your choice: ";
                cin >> pilihanBuku;

                switch (pilihanBuku) {
                case 1: {
                    Book book = inputBook();
                    root = insert(root, book);
                    break;
                }
                case 2: {
                    int id;
                    cout << "Enter book ID to search: ";
                    cin >> id;
                    TreeNode* result = search(root, id);
                    if (result != nullptr) {
                        cout << "Book found: \n";
                        cout << "ID: " << result->book.id << ", Title: " << result->book.title
                             << ", Author: " << result->book.author << ", Year: " << result->book.year << endl;
                    } else {
                        cout << "Book not found.\n";
                    }
                    break;
                }
                case 3:
                    cout << "Books in the library:\n";
                    inorderDisplay(root);
                    break;
                case 4:
                    goto loop;
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                }
            } while (pilihanBuku != 4);
            break;
        }

        case 3: {
            int pilihanTransaksi;
            do {
                cout << "\t == Menu Transaksi ==" << endl;
                cout << "1. Pinjam Buku" << endl;
                cout << "2. Tampilkan Transaksi" << endl;
                cout << "3. Kembalikan Buku" << "\n";
                cout << "4. Quit" << "\n";
                cout << "Masukkan pilihan " << endl;
                cin >> pilihanTransaksi;

                switch (pilihanTransaksi) {
                case 1: {
                    int ID;
                    string TanggalPinjam;
                    cout << "Masukkan ID Buku yang dipinjam: ";
                    cin >> ID;
                    cin.ignore();
                    cout << "Masukkan tanggal pinjam (cth:12 Februari 2021): ";
                    getline(cin, TanggalPinjam);

                    TreeNode* result = search(root, ID);
                    if (result != nullptr && !result->book.isBorrowed) {
                        int index = HashID(ID);
                        HashTableNode* newNode = new HashTableNode;
                        newNode->transaksi.book = &result->book;
                        newNode->transaksi.id = ID;
                        newNode->transaksi.tanggalPinjam = TanggalPinjam;
                        newNode->next = nullptr;

                        if (hashTable[index] == nullptr) {
                            hashTable[index] = newNode;
                        } else {
                            HashTableNode* temp = hashTable[index];
                            while (temp->next != nullptr) {
                                temp = temp->next;
                            }
                            temp->next = newNode;
                        }

                        result->book.isBorrowed = true;
                        cout << "Transaksi berhasil diproses\n";
                    } else {
                        cout << "Book not found or already borrowed.\n";
                    }
                    break;
                }

                case 2:
                    DisplayTransaksi();
                    break;

                case 3: {
                    int ID;
                    cout << "Masukkan ID Buku yang dikembalikan: ";
                    cin >> ID;

                    TreeNode* result = search(root, ID);
                    if (result != nullptr && result->book.isBorrowed) {
                        result->book.isBorrowed = false;
                        cout << "Buku berhasil dikembalikan\n";
                    } else {
                        cout << "Buku tidak ditemukan atau belum dipinjam\n";
                    }
                    break;
                }

                case 4:
                    goto loop;
                    break;

                default:
                    cout << "Invalid choice. Please try again.\n";
                }
            } while (pilihanTransaksi != 4);
            break;
        }

        case 4:
            return;
        break;
        default:
            cout << "Invalid choice. Please try again.\n";
        break;
        }
    }
}

// Function Hash
int hashFunction(string key)
{
  return tolower(key[0]) - 97;
}

// cekDaftar
bool cekDaftar(string username, string password)
{
  int index = hashFunction(password);
  // cek index masih kosong atau sudah ditempati
  if (dataAkun[index].username != "" && dataAkun[index].password != "") {
    // kalo sel index hash tidak table kosong
    cout << "User sudah ada!!" << endl;
    return false;
  } else {
    // kalo sel index di hash table kosong
    dataAkun[index].username = username;
    dataAkun[index].password = password;
    return true;
  }
}

// cekLogin
bool cekLogin(string username, string password)
{
  // hashing dulu
  int index = hashFunction(password);

  // cek username & password bener gak
  if (dataAkun[index].username == username && dataAkun[index].password == password) {
    // kalo bener
    return true;
  } else {
    return false;
  }
}

// cekHapusAkun
bool cekHapusAkun(int index)
{
  // cek apakah sel index di hash table kosong atau tidak
  if (dataAkun[index].username == "" && dataAkun[index].password == "") {
    // kalo selnya kosong
    cout << "\nData akun tidak ada!!" << endl;
    return false;
  } else {
    // kalo ada datanya
    dataAkun[index].username = "";
    dataAkun[index].password = "";
    return true;
  }
}

// print Data Akun
void printDataAkun()
{
  cout << "\nData Akun : " << endl;
  cout << "| Index\t - Username - Password |" << endl;
  for (int i = 0; i < 26; i++) {
    cout << "| " << i << "\t - ";
    if (dataAkun[i].username == "") {
      cout << "(kosong) - ";
    } else {
      cout << dataAkun[i].username << " - ";
    }
    if (dataAkun[i].password == "") {
      cout << "(kosong) |" << endl;
    } else {
      cout << dataAkun[i].password << " |" << endl;
    }
  }
}

// view Tambah Akun
void viewTambahAkun()
{
  string username, password;
  cout << "\n== MENU TAMBAH AKUN ==" << endl;
  cout << "Masukkan username & password" << endl;
  cout << "Isi Username akun : ";
  cin >> username;
  cout << "Isi Password akun : ";
  cin >> password;

  if (cekDaftar(username, password)) {
    cout << "Akun berhasil terdaftar!!" << endl;
  } else {
    cout << "Akun gagal terdaftar!!" << endl;
  }

  return;
}

// viewHapusAkun
void viewHapusAkun()
{
  int index;
  cout << "\n== MENU HAPUS AKUN ==" << endl;
  cout << "Isi index : ";
  cin >> index;

  if (cekHapusAkun(index)) {
    cout << "Data akun berhasil dihapus!!" << endl;
  } else {
    cout << "Data akun gagal dihapus!!" << endl;
  }
}

// view Menu Login
void viewMenuLogin()
{
  while (true) {
    string pilihan;
    cout << "\n== MENU ADMIN ==" << endl;
    cout << "Menu Pilihan :" << endl;
    cout << "1. Tambah Akun" << endl;
    cout << "2. Hapus Akun" << endl;
    cout << "3. Lihat Data Akun" << endl;
    cout << "4. Logout" << endl;
    cout << "Pilih menu [1/2/3] : ";
    cin >> pilihan;
    if (pilihan == "1") {
      viewTambahAkun();
    } else if (pilihan == "2") {
      viewHapusAkun();
    } else if (pilihan == "3") {
      printDataAkun();
    } else if (pilihan == "4") {
      cout << "Anda berhasil logout" << endl;
      break;
    } else {
      cout << "Pilihan tidak tersedia!!" << endl;
    }
  }
}

int main()
{
  while (true) {
    int PilihLogin;
    cout << "=== Selamat Datang Di Program Perpustakaan ===\n";
    cout << "1. Daftar (Jika Masih Belum Mempunyai Akun)" << "\n";
    cout << "2. Login (Jika sudah punya akun)" << "\n";
    cout << "3. Admin " << "\n";
    cout << "4. Keluar" << "\n";
    cout << "Masukkan pilihan anda: ";
    cin >> PilihLogin;
    string username, password;

    switch (PilihLogin) {
    case 1:
        cout << "\n== MENU DAFTAR ==" << endl;
        cout << "Masukkan username & password" << endl;
        cout << "Isi Username anda : ";
        cin >> username;
        cout << "Isi Password anda : ";
        cin >> password;

        if (cekDaftar(username, password)) {
            cout << "Akun berhasil terdaftar!!" << endl;
        } else {
            cout << "Akun gagal terdaftar!!" << endl;
        }
        break;

    case 2:
        cout << "== VIEW LOGIN ==" << endl;
        cout << "Masukkan username & password" << endl;
        cout << "Isi username anda : ";
        cin >> username;
        cout << "Isi password anda : ";
        cin >> password;

        if (cekLogin(username, password)) {
            cout << "\nLogin berhasil!!" << endl;
            MenuPerpustakaan();
        } else {
            cout << "\nLogin Gagal!!" << endl;
        }
        break;

    case 3:
        viewMenuLogin();
        break;

    case 4:
        cout << "\nTerimakasih sudah menggunakan aplikasi perpustakaan." << endl;
        return 0;

    default:
        cout << "Pilihan tidak tersedia!!" << endl;
    }
  }
}
