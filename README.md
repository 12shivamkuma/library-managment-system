# 📚 Library Management System
### Using Queue and Linear Search | C++ Mini Project

---

## 📋 Project Overview

This is a **B.Tech Mini Project** that demonstrates the use of core **Data Structures and Algorithms (DSA)** concepts through a real-world application — a Library Management System.

The system is built using **C++ with STL** and runs entirely on the console. It allows a librarian to manage books, handle issue requests using a Queue, and search books efficiently using Linear Search.

---

## ✨ Features

| # | Feature | Description |
|---|---------|-------------|
| 1 | **Add New Book** | Add a book with ID, Name, Author, Category, Quantity |
| 2 | **Search Book** | Search by Book ID or Book Name using Linear Search |
| 3 | **Issue Book** | Raise an issue request; stored in Queue (FIFO order) |
| 4 | **Return Book** | Return a book; updates availability automatically |
| 5 | **Display All Books** | View all books in a formatted table |
| 6 | **Display Issue Queue** | View pending issue requests in FIFO order |
| 7 | **Total Books Counter** | Count of unique book titles in the system |
| 8 | **Exit System** | Clean exit from the program |

---

## 🗂️ Data Structures Used

### 1. Queue (`std::queue<>`) — Book Issue Requests
- Used to store book issue requests from students
- **FIFO (First In, First Out):** The first student to request a book is processed first
- Operations used: `push()`, `front()`, `pop()`, `empty()`, `size()`

```
Queue State Example:
[Alice - Book 101] ← [Bob - Book 103] ← [Carol - Book 102]
 FRONT (served 1st)                        REAR (added last)
```

### 2. Linear Search — Book Lookup
- Used to search books by **Book ID** and **Book Name**
- Traverses the books vector from index 0 to n-1
- **Time Complexity:** O(n) — checks each element until a match is found

```
Linear Search Example (searching ID = 103):
[101] → [102] → [103] ✓ FOUND at index 2
```

### 3. Vector (`std::vector<>`) — Book Storage
- Dynamic array that stores all book records
- Supports easy iteration, insertion, and random access

---

## 📁 Project Structure

```
LibraryManagementSystem/
│
├── main.cpp            ← Complete C++ source code
├── README.md           ← Project overview (this file)
├── Report.docx         ← Full project report documentation
├── Presentation.pptx   ← 8-slide PowerPoint presentation
└── VivaQA.md           ← 20 Viva Questions and Answers
```

---

## 🚀 How to Compile and Run

### On Mac / Linux (Terminal)

**Compile:**
```bash
g++ -std=c++17 -o LibrarySystem main.cpp
```

**Run:**
```bash
./LibrarySystem
```

**Single command (compile + run):**
```bash
g++ -std=c++17 -o LibrarySystem main.cpp && ./LibrarySystem
```

### On Windows (Command Prompt / MinGW)

**Compile:**
```cmd
g++ -std=c++17 -o LibrarySystem.exe main.cpp
```

**Run:**
```cmd
LibrarySystem.exe
```

> **Note:** Change `system("clear")` to `system("cls")` inside `main.cpp` for Windows.

---

## 📸 Sample Output

### Main Menu
```
============================================================
             LIBRARY MANAGEMENT SYSTEM
============================================================
  1. Add New Book
  2. Search Book (by ID or Name)
  3. Issue Book to Student
  4. Return Book
  5. Display All Books
  6. Display Issue Queue
  7. Total Books Counter
  8. Exit System
------------------------------------------------------------
  Enter your choice (1-8):
```

### Display All Books
```
ID    Book Name                Author            Category    Qty  Status
------------------------------------------------------------
101   Data Structures in C++  Mark Allen Weiss  Computer    3    Available
102   Let Us C                Yashavant Kanetk  Computer    5    Available
103   Physics Volume 1        H.C. Verma        Science     2    Available
104   Engineering Mathematics B.S. Grewal       Math        4    Available
105   Object Oriented C++     Robert Lafore     Computer    1    Available
------------------------------------------------------------
  Total Titles: 5
```

### Issue Queue
```
Pos   Student Name         Book ID  Book Name
------------------------------------------------------------
1     Alice Johnson        101      Data Structures in C++
2     Bob Sharma           103      Physics Volume 1
------------------------------------------------------------
  Total Pending Requests: 2
```

---

## 👨‍💻 Technologies Used

- **Language:** C++ (C++17 Standard)
- **Libraries:** `<iostream>`, `<vector>`, `<queue>`, `<string>`, `<iomanip>`, `<algorithm>`
- **Paradigm:** Procedural Programming
- **IDE:** Any (VS Code, Code::Blocks, Dev-C++, Terminal)

---

## 📝 Notes for Students

- This project uses **beginner-friendly code** with detailed comments
- Every function is documented explaining its purpose and DSA concept
- The Queue is implemented using STL `queue<>` container
- Linear Search is implemented manually (not using STL `find()`) to demonstrate the algorithm

---

*B.Tech Mini Project | Data Structures and Algorithms | [Your College Name]*
