#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

// --------------------------------------------------
// Product Class
// --------------------------------------------------

class Product {
private:
    int id;
    string name;
    string category;
    double price;
    int quantity;

public:

    Product(int productId,
            string productName,
            string productCategory,
            double productPrice,
            int productQuantity) {

        id = productId;
        name = productName;
        category = productCategory;
        price = productPrice;
        quantity = productQuantity;
    }

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    string getCategory() const {
        return category;
    }

    double getPrice() const {
        return price;
    }

    int getQuantity() const {
        return quantity;
    }

    void setPrice(double newPrice) {
        price = newPrice;
    }

    void setQuantity(int newQuantity) {
        quantity = newQuantity;
    }

    void display() const {

        cout << "----------------------------------------\n";
        cout << "Product ID : " << id << endl;
        cout << "Name       : " << name << endl;
        cout << "Category   : " << category << endl;
        cout << "Price      : $" << fixed
             << setprecision(2) << price << endl;
        cout << "Quantity   : " << quantity << endl;
    }
};


// --------------------------------------------------
// Inventory Class
// --------------------------------------------------

class Inventory {
private:
    vector<Product> products;
    int nextId;

public:

    Inventory() {
        nextId = 1;
    }

    // Find product by ID
    Product* findProduct(int id) {

        for (auto &product : products) {

            if (product.getId() == id) {
                return &product;
            }
        }

        return nullptr;
    }

    // Add product
    void addProduct() {

        string name;
        string category;
        double price;
        int quantity;

        cin.ignore();

        cout << "\nEnter product name: ";
        getline(cin, name);

        cout << "Enter category: ";
        getline(cin, category);

        cout << "Enter price: ";
        cin >> price;

        cout << "Enter quantity: ";
        cin >> quantity;

        if (price < 0 || quantity < 0) {

            cout << "Invalid price or quantity.\n";
            return;
        }

        Product product(
            nextId,
            name,
            category,
            price,
            quantity
        );

        products.push_back(product);

        cout << "\nProduct added successfully.\n";
        cout << "Product ID: " << nextId << endl;

        nextId++;
    }

    // Display all products
    void displayProducts() const {

        if (products.empty()) {

            cout << "\nNo products available.\n";
            return;
        }

        cout << "\n========== PRODUCT LIST ==========\n";

        for (const auto &product : products) {
            product.display();
        }
    }

    // Search product
    void searchProduct() {

        int id;

        cout << "\nEnter product ID: ";
        cin >> id;

        Product *product = findProduct(id);

        if (product == nullptr) {

            cout << "Product not found.\n";
            return;
        }

        product->display();
    }

    // Update product price
    void updatePrice() {

        int id;
        double price;

        cout << "\nEnter product ID: ";
        cin >> id;

        Product *product = findProduct(id);

        if (product == nullptr) {

            cout << "Product not found.\n";
            return;
        }

        cout << "Current price: $"
             << product->getPrice() << endl;

        cout << "Enter new price: ";
        cin >> price;

        if (price < 0) {

            cout << "Price cannot be negative.\n";
            return;
        }

        product->setPrice(price);

        cout << "Price updated successfully.\n";
    }

    // Add stock
    void addStock() {

        int id;
        int quantity;

        cout << "\nEnter product ID: ";
        cin >> id;

        Product *product = findProduct(id);

        if (product == nullptr) {

            cout << "Product not found.\n";
            return;
        }

        cout << "Current quantity: "
             << product->getQuantity() << endl;

        cout << "Enter quantity to add: ";
        cin >> quantity;

        if (quantity <= 0) {

            cout << "Quantity must be positive.\n";
            return;
        }

        int newQuantity =
            product->getQuantity() + quantity;

        product->setQuantity(newQuantity);

        cout << "Stock added successfully.\n";
        cout << "New quantity: "
             << newQuantity << endl;
    }

    // Remove stock
    void removeStock() {

        int id;
        int quantity;

        cout << "\nEnter product ID: ";
        cin >> id;

        Product *product = findProduct(id);

        if (product == nullptr) {

            cout << "Product not found.\n";
            return;
        }

        cout << "Available quantity: "
             << product->getQuantity() << endl;

        cout << "Enter quantity to remove: ";
        cin >> quantity;

        if (quantity <= 0) {

            cout << "Quantity must be positive.\n";
            return;
        }

        if (quantity > product->getQuantity()) {

            cout << "Not enough stock available.\n";
            return;
        }

        int newQuantity =
            product->getQuantity() - quantity;

        product->setQuantity(newQuantity);

        cout << "Stock removed successfully.\n";
    }

    // Delete product
    void deleteProduct() {

        int id;

        cout << "\nEnter product ID: ";
        cin >> id;

        for (auto it = products.begin();
             it != products.end();
             ++it) {

            if (it->getId() == id) {

                products.erase(it);

                cout << "Product deleted successfully.\n";
                return;
            }
        }

        cout << "Product not found.\n";
    }

    // Search by category
    void searchByCategory() {

        string category;

        cin.ignore();

        cout << "\nEnter category: ";
        getline(cin, category);

        bool found = false;

        for (const auto &product : products) {

            if (product.getCategory() == category) {

                product.display();
                found = true;
            }
        }

        if (!found) {

            cout << "No products found in this category.\n";
        }
    }

    // Low stock report
    void lowStockReport() {

        int threshold;

        cout << "\nEnter stock threshold: ";
        cin >> threshold;

        bool found = false;

        cout << "\n========== LOW STOCK REPORT ==========\n";

        for (const auto &product : products) {

            if (product.getQuantity() <= threshold) {

                product.display();
                found = true;
            }
        }

        if (!found) {

            cout << "No products have low stock.\n";
        }
    }

    // Calculate inventory value
    void inventoryValue() const {

        double total = 0;

        for (const auto &product : products) {

            total +=
                product.getPrice()
                * product.getQuantity();
        }

        cout << "\nTotal Inventory Value: $"
             << fixed
             << setprecision(2)
             << total
             << endl;
    }

    // Statistics
    void statistics() const {

        if (products.empty()) {

            cout << "\nNo products available.\n";
            return;
        }

        int totalProducts = products.size();

        int totalQuantity = 0;

        double totalValue = 0;

        const Product *mostExpensive =
            &products[0];

        for (const auto &product : products) {

            totalQuantity += product.getQuantity();

            totalValue +=
                product.getPrice()
                * product.getQuantity();

            if (product.getPrice()
                > mostExpensive->getPrice()) {

                mostExpensive = &product;
            }
        }

        cout << "\n========== INVENTORY STATISTICS ==========\n";

        cout << "Total Products : "
             << totalProducts << endl;

        cout << "Total Items    : "
             << totalQuantity << endl;

        cout << "Inventory Value: $"
             << fixed
             << setprecision(2)
             << totalValue
             << endl;

        cout << "Most Expensive : "
             << mostExpensive->getName()
             << endl;

        cout << "Highest Price  : $"
             << mostExpensive->getPrice()
             << endl;
    }

    // Display menu
    void menu() const {

        cout << "\n====================================\n";
        cout << "      INVENTORY MANAGEMENT SYSTEM\n";
        cout << "====================================\n";
        cout << "1.  Add Product\n";
        cout << "2.  Display Products\n";
        cout << "3.  Search Product\n";
        cout << "4.  Update Price\n";
        cout << "5.  Add Stock\n";
        cout << "6.  Remove Stock\n";
        cout << "7.  Delete Product\n";
        cout << "8.  Search by Category\n";
        cout << "9.  Low Stock Report\n";
        cout << "10. Inventory Value\n";
        cout << "11. Statistics\n";
        cout << "12. Exit\n";
        cout << "====================================\n";
    }
};


// --------------------------------------------------
// Main Function
// --------------------------------------------------

int main() {

    Inventory inventory;

    // Add some initial products
    // for demonstration purposes

    cout << "Initializing inventory...\n";

    int choice;

    while (true) {

        inventory.menu();

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                inventory.addProduct();
                break;

            case 2:
                inventory.displayProducts();
                break;

            case 3:
                inventory.searchProduct();
                break;

            case 4:
                inventory.updatePrice();
                break;

            case 5:
                inventory.addStock();
                break;

            case 6:
                inventory.removeStock();
                break;

            case 7:
                inventory.deleteProduct();
                break;

            case 8:
                inventory.searchByCategory();
                break;

            case 9:
                inventory.lowStockReport();
                break;

            case 10:
                inventory.inventoryValue();
                break;

            case 11:
                inventory.statistics();
                break;

            case 12:

                cout << "\nThank you for using "
                     << "the Inventory Management System.\n";

                return 0;

            default:

                cout << "\nInvalid choice.\n";
                cout << "Please enter a number "
                     << "between 1 and 12.\n";
        }
    }

    return 0;
}
