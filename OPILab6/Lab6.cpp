#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// ��������� ������
struct Product {
    string name;
    double price;
    int stock;
};

// ��������� �������� ����
struct SaleItem {
    string name;
    double price;
    int quantity;
};

// ��������� �볺���
struct Customer {
    string name;
    string phone;
};

    // Debug function to display products
    void displayProducts(const vector<Product>& products) {
    cout << "\n displayProducts() called\n";
    cout << "products.size() = " << products.size() << "\n";

    // 👉 Перевірка порожнього списку
    if (products.empty()) {
        cout << "\n=== Available products ===\n";
        cout << "Список товарів порожній!\n";
        return;  // нічого більше не виводимо
    }

    cout << "\n=== Available products ===\n";
    cout << left << setw(15) << "Name"
         << setw(8) << "Price"
         << setw(8) << "Stock" << endl;
    cout << "----------------------------\n";

    int index = 0;
    for (const auto& prod : products) {
        cout << "Product #" << index << "\n";
        cout << "name  = \"" << prod.name << "\"\n";
        cout << "price = " << prod.price << "\n";
        cout << "stock = " << prod.stock << "\n";

        if (prod.stock < 0) {
            cout << "Error: Negative stock for product " << prod.name << "!\n";
        }
        if (prod.stock == 0) {
            cout << "Warning: Out of stock for product " << prod.name << "!\n";
        }

        cout << left << setw(15) << prod.name
             << setw(8) << fixed << setprecision(2) << prod.price
             << setw(8) << prod.stock << endl;

        index++;
    }
}
// ������������� �볺���
Customer identifyCustomer(vector<Customer>& customers) {
    string phone;
    cout << "Enter customer phone number: ";
    cin >> ws;
    getline(cin, phone);

    for (auto& c : customers) {
        if (c.phone == phone) {
            cout << "Welcome, " << c.name << "!\n";
            return c;
        }
    }

    string name;
    cout << "New customer. Enter name: ";
    getline(cin, name);

    Customer newCustomer = { name, phone };
    customers.push_back(newCustomer);
    cout << "Customer registered.\n";
    return newCustomer;
}

// �������� ������ � ���
void inputSale(vector<Product>& products, vector<SaleItem>& sale) {
    string itemName;
    int quantity;
    char cont;

    do {
        displayProducts(products);

        cout << "Enter product name to buy: ";
        cin >> ws;
        getline(cin, itemName);

        bool found = false;
        for (auto& prod : products) {
            if (prod.name == itemName) {
                found = true;
                cout << "Enter quantity: ";
                cin >> quantity;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (quantity <= prod.stock) {
                    sale.push_back({ prod.name, prod.price, quantity });
                    prod.stock -= quantity;
                    cout << "Product added to sale.\n";
                }
                else {
                    cout << "Not enough stock. Available: " << prod.stock << endl;
                }
                break;
            }
        }

        if (!found) cout << "Product not found!\n";

        cout << "Add another product? (y/n): ";
        cin >> cont;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (cont == 'y' || cont == 'Y');
}

// ���������� �������
double calculateTotal(const vector<SaleItem>& sale) {
    double total = 0;
    for (const auto& item : sale) {
        total += item.price * item.quantity;
    }
    return total * 1.2; // VAT 20%
}

// ���� ������� ������
string selectPaymentMethod() {
    int choice;
    cout << "Select payment method:\n";
    cout << "1. Cash\n2. Card\nEnter choice: ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return (choice == 1) ? "Cash" : "Card";
}

// ���� ����
void printReceipt(const vector<SaleItem>& sale, const Customer& customer) {
    cout << "\n===== Sale Receipt =====\n";
    cout << "Customer: " << customer.name << endl;
    cout << left << setw(15) << "Name"
        << setw(8) << "Price"
        << setw(8) << "Qty"
        << setw(10) << "Total" << endl;
    cout << "----------------------------\n";

    double subtotal = 0;
    for (const auto& item : sale) {
        double sum = item.price * item.quantity;
        subtotal += sum;
        cout << left << setw(15) << item.name
            << setw(8) << fixed << setprecision(2) << item.price
            << setw(8) << item.quantity
            << setw(10) << sum << endl;
    }

    double total = subtotal * 1.2;
    cout << "----------------------------\n";
    cout << "Subtotal: " << subtotal << endl;
    cout << "VAT (20%): " << subtotal * 0.2 << endl;
    cout << "Total to pay: " << total << endl;

    string payment = selectPaymentMethod();
    cout << "Payment method: " << payment << endl;
    cout << "============================\n";
}

int main() {
    vector<Product> products = {
        {"Paracetamol", 25.0, 50},
        {"Ibuprofen", 30.0, 40},
        {"Vitamin C", 15.0, 100},
        {"Bandage", 10.0, 200}
    };

    vector<Customer> customers = {
        {"Ivanenko Ivan", "0671234567"},
        {"Petrenko Petro", "0997654321"}
    };

    vector<SaleItem> sale;

    cout << "=== Sales Module ===\n";

    Customer currentCustomer = identifyCustomer(customers);

    inputSale(products, sale);

    printReceipt(sale, currentCustomer);

    return 0;
}
