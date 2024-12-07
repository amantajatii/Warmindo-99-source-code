#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int MAX_USERS = 99;
const int MAX_MENU_ITEMS = 10;
const int MAX_ORDERS = 13;
const int MAX_ITEMS_PER_ORDER = 5;

class User {
private:
    string username;
    string password;
    string phoneNumber;

public:
    User() : username(""), password(""), phoneNumber("") {}

    void setUser(const string& uname, const string& pword, const string& phone) {
        username = uname;
        password = pword;
        phoneNumber = phone;
    }

    string getUsername() const { return username; }
    bool authenticate(const string& inputPassword) const { return password == inputPassword; }
};

class MenuItem {
private:
    string name;
    double price;

public:
    MenuItem() : name(""), price(0) {}

    void setMenuItem(const string& itemName, double itemPrice) {
        name = itemName;
        price = itemPrice;
    }

    string getName() const { return name; }
    double getPrice() const { return price; }
};

class Order {
private:
    string customerName;
    MenuItem items[MAX_ITEMS_PER_ORDER];
    int itemCount;
    double totalPrice;

public:
    Order() : customerName(""), itemCount(0), totalPrice(0) {}

    void setCustomerName(const string& name) {
        customerName = name;
    }

    string getCustomerName() const { return customerName; }

    bool addItem(const MenuItem& item) {
        if (itemCount < MAX_ITEMS_PER_ORDER) {
            items[itemCount] = item;
            totalPrice += item.getPrice();
            itemCount++;
            return true;
        }
        return false;
    }

    double getTotalPrice() const { return totalPrice; }

    void displayOrderDetails() const {
        cout << "Nama: " << customerName
             << "\n   Total Harga: Rp" << fixed << setprecision(0) << totalPrice << endl;
        cout << "   Detail Pesanan:" << endl;
        for (int j = 0; j < itemCount; ++j) {
            cout << "     - " << items[j].getName() << " (Rp" << items[j].getPrice() << ")" << endl;
        }
    }
};

class WarmindoApp {
private:
    User users[MAX_USERS];
    MenuItem menu[MAX_MENU_ITEMS];
    Order orders[MAX_ORDERS];

    int userCount = 0;
    int menuSize = 0;
    int orderCount = 0;

    const string pewe = "bukansembarangwarmindo";

public:
    WarmindoApp() {
        addMenuItem("Indomie Goreng", 7000);
        addMenuItem("Indomie Rebus", 8000);
        addMenuItem("Indomie Goreng Telur", 10000);
        addMenuItem("Indomie Rebus Telur", 11000);
    }

    void displayMenu() {
        cout << "\n--- Menu Warmindo 99 ---" << endl;
        for (int i = 0; i < menuSize; ++i) {
            cout << i + 1 << ". " << menu[i].getName() << " - Rp" << fixed << setprecision(0) << menu[i].getPrice() << endl;
        }
    }

    void registerUser() {
        if (userCount >= MAX_USERS) {
            cout << "Maaf, membership udah penuh." << endl;
            return;
        }
        string username, password, phoneNumber;
        cout << "Masukin username baru: ";
        cin.ignore();
        getline(cin, username);
        cout << "Masukin password: ";
        getline(cin, password);
        cout << "Masukin nomor telepon: ";
        getline(cin, phoneNumber);

        users[userCount].setUser(username, password, phoneNumber);
        userCount++;

        cout << "Registrasi membership berhasil! jangan lupa login yak kalo mau lanjut." << endl;
    }

    bool loginUser(string& loggedInUser) {
        string username, password;
        cout << "Masukin usernamemu: ";
        cin.ignore();
        getline(cin, username);
        cout << "Masukin passwordmu: ";
        getline(cin, password);

        for (int i = 0; i < userCount; ++i) {
            if (users[i].getUsername() == username && users[i].authenticate(password)) {
                loggedInUser = username;
                cout << "Login berhasil! Selamat pesan, " << username << "." << endl;
                return true;
            }
        }
        cout << "Login gagal. Username atau passwordmu salah bro, atau ngga register dulu." << endl;
        return false;
    }

    void customerMode(const string& loggedInUser) {
        if (orderCount >= MAX_ORDERS) {
            cout << "\nAntrian penuh, coba 1 jam lagi yak." << endl;
            return;
        }

        cout << "\n--- Mode Member ---" << endl;
        Order newOrder;
        newOrder.setCustomerName(loggedInUser);

        char moreItems;
        do {
            displayMenu();
            int choice;
            cout << "Pilih menu: ";
            cin >> choice;

            if (choice > 0 && choice <= menuSize) {
                if (newOrder.addItem(menu[choice - 1])) {
                    cout << menu[choice - 1].getName() << " Pesenan udah ditambahin yak." << endl;
                } else {
                    cout << "Kenyang, bang. Cukup segini aja pesennya" << endl;
                    break;
                }
            } else {
                cout << "Pilihan ngga valid. Coba lagi dong yang bener." << endl;
            }

            cout << "Tambah item lagi ga bang? (y/n): ";
            cin >> moreItems;

        } while (tolower(moreItems) == 'y');

        cout << "\nTotal Harganya: Rp" << newOrder.getTotalPrice() << endl;
        char pay;
        cout << "Mau lanjutin bayar ga? (y/n): ";
        cin >> pay;

        if (tolower(pay) == 'y') {
            cout << "Pembayaran berhasil! Pesenanmu udah diterima admin." << endl;
            orders[orderCount] = newOrder;
            orderCount++;
        } else {
            cout << "Pesenan gaberhasil, kalo mau berhasil harus bayar." << endl;
        }
    }

    void adminMode() {
        string password;
        bool authenticated = false;

        while (true) {
            cout << "Masukin password admin: ";
            cin.ignore();
            getline(cin, password);

            if (password != pewe) {
                cout << "Password salah. Masukin yang bener bang, aksesmu ditolak." << endl;
                return;
            }

            authenticated = true;

            while (authenticated) {
                cout << "\n--- Mode Admin ---" << endl;
                cout << "1. Tampilkan Daftar Pesenan" << endl;
                cout << "2. Tambah Menu Baru" << endl;
                cout << "3. Kembali ke Menu Utama" << endl;
                cout << "Pilih opsi: ";
                int choice;
                cin >> choice;

                switch (choice) {
                case 1:
                    if (orderCount == 0) {
                        cout << "\nBelum ada pesenan bang, semangat yak." << endl;
                    } else {
                        cout << "\n--- Daftar Pesenan ---" << endl;
                        for (int i = 0; i < orderCount; ++i) {
                            orders[i].displayOrderDetails();
                        }
                    }
                    break;

                case 2:
                    if (menuSize < MAX_MENU_ITEMS) {
                        string newName;
                        double newPrice;
                        cout << "Masukin nama menu baru: ";
                        cin.ignore();
                        getline(cin, newName);
                        cout << "Masukin harga menu baru: ";
                        cin >> newPrice;

                        addMenuItem(newName, newPrice);
                        cout << "Menu baru berhasil ditambahin." << endl;
                    } else {
                        cout << "Menu udah maksimal, gabisa nambah lagi." << endl;
                    }
                    break;

                case 3:
                    authenticated = false;
                    break;

                default:
                    cout << "Pilihan ga valid." << endl;
                }

                if (!authenticated) break;
            }

            break;
        }
    }

    void addMenuItem(const string& name, double price) {
        if (menuSize < MAX_MENU_ITEMS) {
            menu[menuSize].setMenuItem(name, price);
            menuSize++;
        }
    }

    void run() {
        string loggedInUser = "";
        while (true) {
            cout << "\n--- Aplikasi Warmindo ---" << endl;
            cout << "---MEMBERSHIP ONLY!!! ---" << endl;
            cout << "1. Register" << endl;
            cout << "2. Login" << endl;
            cout << "3. Mode Pelanggan" << endl;
            cout << "4. Mode Admin" << endl;
            cout << "5. Keluar" << endl;
            cout << "Pilih opsi: ";
            int mode;
            cin >> mode;

            switch (mode) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser(loggedInUser)) {
                    cout << "Pilih Mode Pelanggan yak kalo mau lanjut." << endl;
                }
                break;
            case 3:
                if (!loggedInUser.empty()) {
                    customerMode(loggedInUser);
                } else {
                    cout << "Harus login dulu bang." << endl;
                }
                break;
            case 4:
                adminMode();
                break;
            case 5:
                cout << "Makasih udah pake aplikasinya yak! Jangan lupa diambil pesenannya" << endl;
                return;

            default:
                cout << "Pilihan ngga valid. Coba lagi." << endl;
            }
        }
    }
};

int main() {
    WarmindoApp app;
    app.run();
}