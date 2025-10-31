#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <map>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace std;

// Utility functions
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void divider() {
    cout << "\n===========================================\n";
}

// ------------------- USER CLASS -------------------
class User {
public:
    string username;
    string password;
    string role; // buyer or seller
    string mobileNumber;

    User() {}

    User(string username, string password, string role, string mobileNumber) {
        this->username = username;
        this->password = password;
        this->role = role;
        this->mobileNumber = mobileNumber;
    }
};

// ------------------- DOG CLASS -------------------
class Dog {
public:
    static int idCounter;
    int id;
    string name;
    string breed;
    int age;
    float price;
    string listedBy;

    Dog(string name, string breed, int age, float price, string listedBy) {
        this->id = idCounter++;
        this->name = name;
        this->breed = breed;
        this->age = age;
        this->price = price;
        this->listedBy = listedBy;
    }

    void displayDog(const map<string, User>& users) const {
        cout << "Dog ID     : " << id << endl;
        cout << "Name       : " << name << endl;
        cout << "Breed      : " << breed << endl;
        cout << "Age        : " << age << " years" << endl;
        cout << "Price      : " << fixed << setprecision(2) << price << endl;
        cout << "Listed By  : " << listedBy;
        auto it = users.find(listedBy);
        if (it != users.end()) {
            cout << " (Mobile: " << it->second.mobileNumber << ")";
        }
        cout << endl;
        divider();
    }
};

int Dog::idCounter = 1;

class Portal {
private:
    vector<Dog> dogs;
    vector<string> adoptionHistory;
    map<string, User> users;

public:
    Portal() {
        loadUsers();
        loadDogs();
        loadTransactions();
    }

    void saveUsers() {
        ofstream file("users.txt");
        for (auto& pair : users) {
            file << pair.second.username << "," << pair.second.password << "," << pair.second.role << "," << pair.second.mobileNumber << endl;
        }
        file.close();
    }

    void loadUsers() {
        ifstream file("users.txt");
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string uname, pass, role, mobile;
            getline(ss, uname, ',');
            getline(ss, pass, ',');
            getline(ss, role, ',');
            getline(ss, mobile);

            // Skip invalid lines (empty username, password, role, or mobile)
            if (uname.empty() || pass.empty() || role.empty() || mobile.empty()) {
                cout << "Skipped invalid user entry in file: " << line << endl;
                continue;
            }

            users[uname] = User(uname, pass, role, mobile);
        }
        file.close();
    }

    void saveDogs() {
        ofstream file("dogs.txt");
        for (Dog& dog : dogs) {
            file << dog.id << "," << dog.name << "," << dog.breed << "," << dog.age << "," << dog.price << "," << dog.listedBy << endl;
        }
        file.close();
    }

    void loadDogs() {
        ifstream file("dogs.txt");
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, breed, listedBy;
            int id, age;
            float price;
            char comma;
            ss >> id >> comma;
            getline(ss, name, ',');
            getline(ss, breed, ',');
            ss >> age >> comma >> price >> comma;
            getline(ss, listedBy);

            Dog::idCounter = max(Dog::idCounter, id + 1);
            dogs.push_back(Dog(name, breed, age, price, listedBy));
            dogs.back().id = id;
        }
        file.close();
    }

    void saveTransactions() {
        ofstream file("transactions.txt");
        for (const string& record : adoptionHistory) {
            file << record << endl;
        }
        file.close();
    }

    void loadTransactions() {
        ifstream file("transactions.txt");
        string line;
        while (getline(file, line)) {
            adoptionHistory.push_back(line);
        }
        file.close();
    }

    bool registerUser(const string& username, const string& password, const string& role, const string& mobileNumber) {
        if (username.empty() || password.empty() || role.empty() || mobileNumber.empty()) {
            cout << "All fields are required. Registration failed.\n";
            return false;
        }

        if (users.find(username) != users.end()) {
            cout << "Username already exists.\n";
            return false;
        }

        users[username] = User(username, password, role, mobileNumber);
        saveUsers();
        cout << "Registration successful!\n";
        return true;
    }

    User* loginUser(const string& username, const string& password) {
        auto it = users.find(username);
        if (it != users.end() && it->second.password == password) {
            cout << "Login successful! Welcome, " << username << ".\n";
            return &(it->second);
        }
        cout << "Invalid credentials.\n";
        return nullptr;
    }

    void listDog(const string& name, const string& breed, int age, float price, const string& listedBy) {
        dogs.push_back(Dog(name, breed, age, price, listedBy));
        saveDogs();
        cout << "Dog listed successfully by " << listedBy << "!\n";
    }

    void viewDogs() {
        if (dogs.empty()) {
            cout << "No dogs currently listed.\n";
            return;
        }
        for (const Dog& dog : dogs) {
            dog.displayDog(users);
        }
    }

    void searchDogsByBreed(const string& breed) {
        bool found = false;
        for (const Dog& dog : dogs) {
            if (dog.breed == breed) {
                dog.displayDog(users);
                found = true;
            }
        }
        if (!found)
            cout << "No dogs of breed " << breed << " found.\n";
    }

    void searchDogsByPrice(float maxPrice) {
        bool found = false;
        for (const Dog& dog : dogs) {
            if (dog.price <= maxPrice) {
                dog.displayDog(users);
                found = true;
            }
        }
        if (!found)
            cout << "No dogs under " << maxPrice << " found.\n";
    }

    void buyDog(int id, const string& buyer) {
        for (auto it = dogs.begin(); it != dogs.end(); ++it) {
            if (it->id == id) {
                cout << "You have successfully adopted " << it->name << "!\n";
                adoptionHistory.push_back(buyer + " adopted " + it->name + " (ID: " + to_string(id) + ")");
                dogs.erase(it);
                saveTransactions();
                saveDogs();
                return;
            }
        }
        cout << "Dog ID not found.\n";
    }

    void showAdoptionHistory() {
        if (adoptionHistory.empty()) {
            cout << "No adoptions yet.\n";
            return;
        }
        cout << "\n--- Adoption History ---\n";
        for (const string& record : adoptionHistory) {
            cout << record << endl;
        }
    }
};

void sellerMenu(Portal& portal, const string& username) {
    int choice;
    do {
        divider();
        cout << "--- Seller Dashboard ---\n";
        cout << "1. List a Dog\n";
        cout << "2. View All Dogs\n";
        cout << "3. Logout\n";
        divider();
        cout << "Enter your choice: ";
        cin >> choice;
        clearInput();

        if (choice == 1) {
            string name, breed;
            int age;
            float price;
            cout << "Enter dog's name: "; getline(cin, name);
            cout << "Enter breed: "; getline(cin, breed);
            cout << "Enter age: "; cin >> age;
            cout << "Enter price: "; cin >> price;
            clearInput();
            portal.listDog(name, breed, age, price, username);
        } else if (choice == 2) {
            portal.viewDogs();
        }
    } while (choice != 3);
}

void buyerMenu(Portal& portal, const string& username) {
    int choice;
    do {
        divider();
        cout << "--- Buyer Dashboard ---\n";
        cout << "1. View Dogs\n";
        cout << "2. Buy Dog\n";
        cout << "3. Search Dog by Breed\n";
        cout << "4. Search Dog by Price\n";
        cout << "5. View Adoption History\n";
        cout << "6. Logout\n";
        divider();
        cout << "Enter your choice: ";
        cin >> choice;
        clearInput();

        if (choice == 1) {
            portal.viewDogs();
        } else if (choice == 2) {
            int dogID;
            cout << "Enter Dog ID to adopt: ";
            cin >> dogID;
            clearInput();
            portal.buyDog(dogID, username);
        } else if (choice == 3) {
            string breed;
            cout << "Enter breed to search: ";
            getline(cin, breed);
            portal.searchDogsByBreed(breed);
        } else if (choice == 4) {
            float price;
            cout << "Enter maximum price: ";
            cin >> price;
            portal.searchDogsByPrice(price);
        } else if (choice == 5) {
            portal.showAdoptionHistory();
        }
    } while (choice != 6);
}

int main() {
    Portal portal;
    int choice;

    while (true) {
        divider();
        cout << "=== Welcome to Dog Adoption Portal ===\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        divider();
        cout << "Choose option: ";
        cin >> choice;
        clearInput();

        if (choice == 1) {
            string uname, pass, role, mobile;
            cout << "Enter username: "; getline(cin, uname);
            cout << "Enter password: "; getline(cin, pass);
            cout << "Are you a buyer or seller? "; getline(cin, role);
            cout << "Enter mobile number: "; getline(cin, mobile);
            portal.registerUser(uname, pass, role, mobile);
        } else if (choice == 2) {
            string uname, pass;
            cout << "Enter username: "; getline(cin, uname);
            cout << "Enter password: "; getline(cin, pass);
            User* user = portal.loginUser(uname, pass);
            if (user != nullptr) {
                if (user->role == "buyer")
                    buyerMenu(portal, user->username);
                else if (user->role == "seller")
                    sellerMenu(portal, user->username);
                else
                    cout << "Unknown role.\n";
            }
        } else if (choice == 3) {
            cout << "Thanks for visiting the Dog Adoption Portal!\n";
            break;
        } else {
            cout << "Invalid option.\n";
        }
    }

    return 0;
}
