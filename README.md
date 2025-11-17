# 🐶 Dog Adoption Portal (C++ Project)

## 📖 Overview
The Dog Adoption Portal is a console-based C++ application designed to connect dog sellers and buyers on a single platform.  
It allows sellers to list dogs for adoption and buyers to browse, search, and adopt them easily — all with persistent data storage using text files.

This project demonstrates core OOP concepts such as:
- Encapsulation  
- File handling  
- Class interaction  
- Data persistence  
- Menu-driven logic  

---

## 🚀 Features

### 👤 User Management
- Register as **Buyer** or **Seller**
- Secure login authentication
- Stores user details persistently in `users.txt`
- Fields stored: username, password, role, mobile number

### 🐕 Dog Management (Seller)
- Add new dog listings (name, breed, age, price)
- Auto-generates a unique **Dog ID**
- View all listed dogs
- All data saved in `dogs.txt`

### 🛒 Adoption System (Buyer)
- View all listed dogs with seller details
- Search dogs by:
  - Breed  
  - Price range  
- Adopt (buy) a dog using its ID
- Adoption details stored in `transactions.txt`

### 📁 File Persistence
Data is saved across sessions using:
- `users.txt` → Registered users  
- `dogs.txt` → Dogs listed for adoption  
- `transactions.txt` → Adoption history  

---

## 🧩 Object-Oriented Design
Classes used:
- **User**
- **Dog**
- **Portal**

Concepts demonstrated:
- Structured modular design (inheritance-free)
- Encapsulation
- File handling (`fstream`)
- STL: `vector`, `map`, `stringstream`

---

## 🧮 Tech Stack
- **Language:** C++
- **Concepts Used:**
  - Classes & Objects  
  - File Handling (Read/Write)  
  - STL (vector, map, string)  
  - Encapsulation & Data Management  

---

## 📊 How It Works
1. **User Registration/Login**
   - Creates or verifies user from `users.txt`.

2. **Role-based Menu**
   - **Seller:** Add or view dogs  
   - **Buyer:** View, search, or adopt dogs  

3. **Data Persistence**
   - All actions automatically recorded into respective text files

---

## 🧠 Key Learning Outcomes
- Understanding file handling in real-world applications  
- Applying OOP principles  
- Building menu-driven console applications  
- Managing persistent data without databases  

---

## 🔮 Future Improvements
- Add an admin dashboard for moderation  
- Encrypt passwords for security  
- Replace file storage with a MySQL/SQLite database  
- Build a GUI using Qt or Python backend  

---

## 👨‍💻 Author
**Chirag Gupta**

