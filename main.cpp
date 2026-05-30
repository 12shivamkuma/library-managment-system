/*
 * ============================================================
 *   LIBRARY MANAGEMENT SYSTEM
 *   Using Queue (Book Issue Requests) and Linear Search
 * ------------------------------------------------------------
 *   B.Tech Mini Project | Data Structures & Algorithms
 *   Language : C++ (STL Allowed)
 *   Author   : [Your Name]
 *   Date     : 2024
 * ============================================================
 *
 * DATA STRUCTURES USED:
 *  1. Queue (STL queue<>) - for Book Issue Requests
 *     - FIFO: First student to request a book gets it first
 *     - Operations: push() to add, front() to peek, pop() to remove
 *
 *  2. Linear Search - to find books by ID or Name
 *     - Traverse the entire books vector one by one
 *     - Time Complexity: O(n) — checks each element until found
 *
 *  3. Vector (STL vector<>) - to store all book records
 *     - Dynamic array that grows automatically
 *     - Easy to iterate, add, and update records
 */

#include <iostream>   // for cin, cout
#include <vector>     // for vector<> — dynamic array to store books
#include <queue>      // for queue<> — FIFO structure for issue requests
#include <string>     // for string data type
#include <iomanip>    // for setw() — formatting table output
#include <algorithm>  // for transform() — used in string comparison

using namespace std;

// ============================================================
//   STRUCT: Book
//   Represents a single book record in the library
// ============================================================
struct Book {
    int    bookID;           // Unique identifier for the book
    string bookName;         // Title of the book
    string authorName;       // Name of the author
    string category;         // e.g., Science, Fiction, Math
    int    quantity;         // Total copies available
    bool   isAvailable;      // true = available, false = all copies issued

    // Constructor: sets default values when a Book object is created
    Book(int id, string name, string author, string cat, int qty)
        : bookID(id), bookName(name), authorName(author),
          category(cat), quantity(qty), isAvailable(qty > 0) {}
};

// ============================================================
//   STRUCT: IssueRequest
//   Stores a single book issue request in the queue
// ============================================================
struct IssueRequest {
    string studentName;  // Name of the student requesting the book
    int    bookID;       // ID of the book being requested
    string bookName;     // Name of the book (for display purposes)
};

// ============================================================
//   GLOBAL DATA CONTAINERS
// ============================================================
vector<Book>         libraryBooks;    // Stores all book records
queue<IssueRequest>  issueQueue;      // Queue of pending issue requests (FIFO)
int                  totalBooks = 0;  // Counter: total unique book titles added

// ============================================================
//   UTILITY FUNCTIONS
// ============================================================

// Prints a horizontal separator line for clean UI
void printSeparator(char ch = '=', int width = 60) {
    cout << string(width, ch) << endl;
}

// Prints a centered title inside separators
void printTitle(string title) {
    printSeparator();
    int padding = (60 - title.length()) / 2;
    cout << string(padding, ' ') << title << endl;
    printSeparator();
}

// Converts a string to lowercase (used in case-insensitive search)
string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// Waits for user to press Enter before continuing
void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// ============================================================
//   FUNCTION: displayMenu
//   Shows the main menu options to the user
// ============================================================
void displayMenu() {
    printTitle("  LIBRARY MANAGEMENT SYSTEM  ");
    cout << "  1. Add New Book" << endl;
    cout << "  2. Search Book (by ID or Name)" << endl;
    cout << "  3. Issue Book to Student" << endl;
    cout << "  4. Return Book" << endl;
    cout << "  5. Display All Books" << endl;
    cout << "  6. Display Issue Queue" << endl;
    cout << "  7. Total Books Counter" << endl;
    cout << "  8. Exit System" << endl;
    printSeparator('-');
    cout << "  Enter your choice (1-8): ";
}

// ============================================================
//   FUNCTION: addBook
//   Allows librarian to add a new book to the library
// ============================================================
void addBook() {
    printTitle("        ADD NEW BOOK        ");

    Book newBook(0, "", "", "", 0); // Create empty book object

    // ----- Input: Book ID -----
    cout << "  Enter Book ID     : ";
    cin  >> newBook.bookID;

    // Check if Book ID already exists (using linear search)
    for (int i = 0; i < libraryBooks.size(); i++) {
        if (libraryBooks[i].bookID == newBook.bookID) {
            cout << "\n  [ERROR] Book ID " << newBook.bookID
                 << " already exists!\n";
            pauseScreen();
            return;
        }
    }

    cin.ignore(); // Clear newline from input buffer

    // ----- Input: Book Name -----
    cout << "  Enter Book Name   : ";
    getline(cin, newBook.bookName);

    // ----- Input: Author Name -----
    cout << "  Enter Author Name : ";
    getline(cin, newBook.authorName);

    // ----- Input: Category -----
    cout << "  Enter Category    : ";
    getline(cin, newBook.category);

    // ----- Input: Quantity -----
    cout << "  Enter Quantity    : ";
    cin  >> newBook.quantity;

    // Validate quantity
    if (newBook.quantity <= 0) {
        cout << "\n  [ERROR] Quantity must be greater than 0!\n";
        pauseScreen();
        return;
    }

    // Set availability based on quantity
    newBook.isAvailable = (newBook.quantity > 0);

    // Add to vector and increment counter
    libraryBooks.push_back(newBook);
    totalBooks++;  // Increment total books counter

    cout << "\n  [SUCCESS] Book added successfully!\n";
    cout << "  Total Books in Library: " << totalBooks << endl;
    pauseScreen();
}

// ============================================================
//   FUNCTION: linearSearchByID
//   LINEAR SEARCH: Finds a book by its unique Book ID
//   Time Complexity: O(n) — checks each element one by one
//   Returns: index in vector, or -1 if not found
// ============================================================
int linearSearchByID(int searchID) {
    // Start from index 0 and go through every book
    for (int i = 0; i < libraryBooks.size(); i++) {
        if (libraryBooks[i].bookID == searchID) {
            return i;  // Found! Return the index
        }
    }
    return -1;  // Not found
}

// ============================================================
//   FUNCTION: linearSearchByName
//   LINEAR SEARCH: Finds a book by its name (case-insensitive)
//   Time Complexity: O(n) — checks each element one by one
//   Returns: index in vector, or -1 if not found
// ============================================================
int linearSearchByName(string searchName) {
    string lowerSearch = toLower(searchName); // Convert search input to lowercase

    // Start from index 0 and go through every book
    for (int i = 0; i < libraryBooks.size(); i++) {
        // Convert stored name to lowercase for comparison
        if (toLower(libraryBooks[i].bookName) == lowerSearch) {
            return i;  // Found! Return the index
        }
    }
    return -1;  // Not found
}

// ============================================================
//   FUNCTION: printBookDetails
//   Displays all details of a single book in a formatted way
// ============================================================
void printBookDetails(int index) {
    Book& b = libraryBooks[index]; // Reference to avoid copying
    printSeparator('-');
    cout << "  Book ID       : " << b.bookID        << endl;
    cout << "  Book Name     : " << b.bookName      << endl;
    cout << "  Author        : " << b.authorName    << endl;
    cout << "  Category      : " << b.category      << endl;
    cout << "  Quantity      : " << b.quantity      << endl;
    cout << "  Availability  : " << (b.isAvailable ? "Available" : "Not Available") << endl;
    printSeparator('-');
}

// ============================================================
//   FUNCTION: searchBook
//   Menu for searching a book by ID or Name
// ============================================================
void searchBook() {
    printTitle("        SEARCH BOOK         ");

    int choice;
    cout << "  Search by:\n";
    cout << "  1. Book ID\n";
    cout << "  2. Book Name\n";
    cout << "  Enter choice: ";
    cin  >> choice;

    if (choice == 1) {
        // ---- Search by Book ID ----
        int searchID;
        cout << "  Enter Book ID to search: ";
        cin  >> searchID;

        cout << "\n  [Performing Linear Search by ID...]\n";

        int index = linearSearchByID(searchID);  // Call linear search

        if (index == -1) {
            cout << "  [NOT FOUND] No book found with ID " << searchID << endl;
        } else {
            cout << "  [FOUND] Book details:\n";
            printBookDetails(index);
        }

    } else if (choice == 2) {
        // ---- Search by Book Name ----
        cin.ignore();
        string searchName;
        cout << "  Enter Book Name to search: ";
        getline(cin, searchName);

        cout << "\n  [Performing Linear Search by Name...]\n";

        int index = linearSearchByName(searchName);  // Call linear search

        if (index == -1) {
            cout << "  [NOT FOUND] No book found with name: " << searchName << endl;
        } else {
            cout << "  [FOUND] Book details:\n";
            printBookDetails(index);
        }

    } else {
        cout << "  [ERROR] Invalid choice!\n";
    }

    pauseScreen();
}

// ============================================================
//   FUNCTION: issueBook
//   Issues a book to a student using QUEUE (FIFO)
//   Each issue request is pushed into the queue
// ============================================================
void issueBook() {
    printTitle("        ISSUE BOOK          ");

    if (libraryBooks.empty()) {
        cout << "  [ERROR] No books available in library!\n";
        pauseScreen();
        return;
    }

    cin.ignore();

    // ----- Input: Student Name -----
    string studentName;
    cout << "  Enter Student Name: ";
    getline(cin, studentName);

    // ----- Input: Book ID -----
    int bookID;
    cout << "  Enter Book ID     : ";
    cin  >> bookID;

    // Search for the book using Linear Search
    int index = linearSearchByID(bookID);

    if (index == -1) {
        cout << "\n  [ERROR] Book ID " << bookID << " not found!\n";
        pauseScreen();
        return;
    }

    if (!libraryBooks[index].isAvailable || libraryBooks[index].quantity <= 0) {
        cout << "\n  [ERROR] Book \"" << libraryBooks[index].bookName
             << "\" is currently NOT available!\n";
        pauseScreen();
        return;
    }

    // ---- Add to Queue (FIFO) ----
    // Queue stores the issue request; requests processed in order received
    IssueRequest request;
    request.studentName = studentName;
    request.bookID      = bookID;
    request.bookName    = libraryBooks[index].bookName;

    issueQueue.push(request);  // ENQUEUE: push request to back of queue

    // Update book availability
    libraryBooks[index].quantity--;
    if (libraryBooks[index].quantity == 0) {
        libraryBooks[index].isAvailable = false;
    }

    // Display confirmation
    printSeparator('-');
    cout << "  [SUCCESS] Issue Request Queued (FIFO)!\n";
    cout << "  Student Name  : " << studentName << endl;
    cout << "  Book Name     : " << libraryBooks[index].bookName << endl;
    cout << "  Book ID       : " << bookID << endl;
    cout << "  Queue Position: " << issueQueue.size() << endl;
    cout << "  Remaining Qty : " << libraryBooks[index].quantity << endl;
    printSeparator('-');

    pauseScreen();
}

// ============================================================
//   FUNCTION: returnBook
//   Processes a book return and updates availability
// ============================================================
void returnBook() {
    printTitle("        RETURN BOOK         ");

    int bookID;
    cout << "  Enter Book ID to return: ";
    cin  >> bookID;

    // Use Linear Search to find the book
    int index = linearSearchByID(bookID);

    if (index == -1) {
        cout << "\n  [ERROR] Book ID " << bookID << " not found in library!\n";
        pauseScreen();
        return;
    }

    // Update availability
    libraryBooks[index].quantity++;
    libraryBooks[index].isAvailable = true;

    cout << "\n  [SUCCESS] Book returned successfully!\n";
    cout << "  Book Name     : " << libraryBooks[index].bookName << endl;
    cout << "  New Quantity  : " << libraryBooks[index].quantity << endl;
    cout << "  Availability  : Available\n";

    pauseScreen();
}

// ============================================================
//   FUNCTION: displayAllBooks
//   Displays all books in a formatted table
// ============================================================
void displayAllBooks() {
    printTitle("        ALL BOOKS           ");

    if (libraryBooks.empty()) {
        cout << "  [INFO] No books in the library yet.\n";
        pauseScreen();
        return;
    }

    // Table Header
    cout << left
         << setw(6)  << "ID"
         << setw(25) << "Book Name"
         << setw(18) << "Author"
         << setw(12) << "Category"
         << setw(5)  << "Qty"
         << setw(12) << "Status"
         << endl;
    printSeparator('-');

    // Table Rows — iterate through all books (Linear traversal)
    for (int i = 0; i < libraryBooks.size(); i++) {
        Book& b = libraryBooks[i];
        cout << left
             << setw(6)  << b.bookID
             << setw(25) << b.bookName.substr(0, 23)   // Truncate long names
             << setw(18) << b.authorName.substr(0, 16)
             << setw(12) << b.category.substr(0, 10)
             << setw(5)  << b.quantity
             << setw(12) << (b.isAvailable ? "Available" : "Issued")
             << endl;
    }

    printSeparator('-');
    cout << "  Total Titles: " << libraryBooks.size() << endl;
    pauseScreen();
}

// ============================================================
//   FUNCTION: displayIssueQueue
//   Displays all pending book issue requests in the Queue
//   NOTE: We use a copy of the queue to avoid destroying original
// ============================================================
void displayIssueQueue() {
    printTitle("     BOOK ISSUE QUEUE       ");

    if (issueQueue.empty()) {
        cout << "  [INFO] Issue queue is empty. No pending requests.\n";
        pauseScreen();
        return;
    }

    // Make a COPY of the queue so we don't destroy the original
    // (queue doesn't support iteration, only front/pop)
    queue<IssueRequest> tempQueue = issueQueue;

    int position = 1;
    cout << left
         << setw(6)  << "Pos"
         << setw(20) << "Student Name"
         << setw(8)  << "Book ID"
         << setw(25) << "Book Name"
         << endl;
    printSeparator('-');

    // Process the copy using FIFO order
    while (!tempQueue.empty()) {
        IssueRequest& req = tempQueue.front(); // Peek at front (FIFO)
        cout << left
             << setw(6)  << position
             << setw(20) << req.studentName.substr(0, 18)
             << setw(8)  << req.bookID
             << setw(25) << req.bookName.substr(0, 23)
             << endl;
        tempQueue.pop(); // Remove from front (FIFO)
        position++;
    }

    printSeparator('-');
    cout << "  Total Pending Requests: " << issueQueue.size() << endl;
    pauseScreen();
}

// ============================================================
//   FUNCTION: showTotalBooks
//   Displays the total count of book titles in the library
// ============================================================
void showTotalBooks() {
    printTitle("     TOTAL BOOKS COUNTER    ");
    cout << "  Total Book Titles Added    : " << totalBooks       << endl;
    cout << "  Currently In System        : " << libraryBooks.size() << endl;
    cout << "  Pending Issue Requests     : " << issueQueue.size() << endl;
    printSeparator('-');
    pauseScreen();
}

// ============================================================
//   FUNCTION: preloadSampleData
//   Adds sample books so the system isn't empty on startup
// ============================================================
void preloadSampleData() {
    libraryBooks.push_back(Book(101, "Data Structures in C++", "Mark Allen Weiss",   "Computer",  3));
    libraryBooks.push_back(Book(102, "Let Us C",               "Yashavant Kanetkar", "Computer",  5));
    libraryBooks.push_back(Book(103, "Physics Volume 1",       "H.C. Verma",         "Science",   2));
    libraryBooks.push_back(Book(104, "Engineering Mathematics", "B.S. Grewal",       "Math",      4));
    libraryBooks.push_back(Book(105, "Object Oriented C++",    "Robert Lafore",      "Computer",  1));
    totalBooks = libraryBooks.size();
}

// ============================================================
//   MAIN FUNCTION
//   Entry point — runs the menu-driven interface
// ============================================================
int main() {
    // Load some sample data for demonstration
    preloadSampleData();

    int choice = 0;

    cout << "\n  Welcome to the Library Management System!\n";
    cout << "  Sample data has been preloaded.\n";
    pauseScreen();

    // ---- Main Program Loop ----
    do {
        system("clear"); // Clear screen for clean UI (use "cls" on Windows)

        displayMenu();   // Show the menu
        cin >> choice;   // Get user's choice

        // ---- Switch-Case Menu Handler ----
        switch (choice) {
            case 1:
                system("clear");
                addBook();          // Add a new book
                break;

            case 2:
                system("clear");
                searchBook();       // Search by ID or Name (Linear Search)
                break;

            case 3:
                system("clear");
                issueBook();        // Issue a book (adds to Queue)
                break;

            case 4:
                system("clear");
                returnBook();       // Return a book
                break;

            case 5:
                system("clear");
                displayAllBooks();  // Show all books
                break;

            case 6:
                system("clear");
                displayIssueQueue(); // Show Queue contents (FIFO)
                break;

            case 7:
                system("clear");
                showTotalBooks();   // Total books counter
                break;

            case 8:
                // Exit the system
                printTitle("    THANK YOU! GOODBYE!     ");
                cout << "  Library System closed.\n";
                printSeparator();
                break;

            default:
                // Invalid option entered
                cout << "\n  [ERROR] Invalid choice! Please enter 1-8.\n";
                pauseScreen();
                break;
        }

    } while (choice != 8); // Loop until user chooses Exit

    return 0;
}
