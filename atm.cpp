#define finePerDay 1;
#define maxBorrowDays 10;
class Book {
private:
    string id;         
    string title;      
    string author;     
    string category;   
    string publicationDate;

public:
    // Constructor
    Book(string id, string title,string author,
         string category, string publicationDate): id(id), title(title), author(author), category(category), publicationDate(publicationDate) {}

    // Getters
    string getId()  { return id; }
    string getTitle()  { return title; }
    string getAuthor()  { return author; }
    string getCategory()  { return category; }
    string getPublicationDate(){ return publicationDate; }
};


class BookItem {
private:
    string barcode;        
    string rackNumber;    
    bool isAvailable;          
    int borrowDate;             
     

public:
   
    BookItem(string barcode, string rackNumber): barcode(barcode), rackNumber(rackNumber), isAvailable(true), borrowDate(0) {}

    // Getters
    string getBarcode()  { return barcode; }
    string getRackNumber()  { return rackNumber; }
    bool getAvailability()  { return isAvailable; }

    // Borrow 
    bool checkoutBook(int currentDate, string errorMsg) {
        if (!isAvailable) {
            errorMsg = "Book already checked out.";
            return false;
        }
        isAvailable = false;
        borrowDate = currentDate;  // Store the borrow date
        return true;
    }

    // Return the book and calculate fine
    int returnBook(int returnDate, string errorMsg) {
        if (isAvailable) {
            errorMsg = "Book is not currently checked out.";
            return -1;  
        }
        isAvailable = true;

        int daysBorrowed = returnDate - borrowDate;
        borrowDate = 0;  // Reset borrow date

        if (daysBorrowed > maxBorrowDays) {
            return (daysBorrowed - maxBorrowDays) * finePerDay;
        }
        return 0;
    }
};



class Member {
private:
    string memberId;            
    string name;                
    vector<std::string> borrowedBooks;  
     int maxBooks = 5;   

public:
    
    Member(string memberId, string name)
        : memberId(memberId), name(name) {}

    // Getters
    string getMemberId()  { return memberId; }
    string getName()  { return name; }

    // Borrow a book
    bool borrowBook(string barcode, string errorMsg) {
        if (borrowedBooks.size() >= maxBooks) {
            errorMsg = "limit reached.";
            return false;
        }
        borrowedBooks.push_back(barcode);
        return true;
    }

    // Return a book
    void returnBook(string& barcode) {
        auto it = find(borrowedBooks.begin(), borrowedBooks.end(), barcode);
        if (it != borrowedBooks.end()) {
            borrowedBooks.erase(it);
        }
    }

    // Get the list of borrowed books
    vector<string>& getBorrowedBooks()  {
        return borrowedBooks;
    }
};


class Library {
private:
    map<string, Book> books;
    map<string, BookItem> bookItems;
    :map<string, Member> members;

public:
    // Add new book
    void addBook(Book book) {
        books[book.getId()] = book;
    }

    // Add new book item (copy)
    void addBookItem( BookItem bookItem) {
        bookItems[bookItem.getBarcode()] = bookItem;
    }

    // Register new member
    void registerMember(const Member& member) {
        members[member.getMemberId()] = member;
    }

    // Search k by title
    void searchBookByTitle(string title)  {
        for ( auto [id, book] : books) {
            if (book.getTitle() == title) {
                cout << book.getTitle() << "author name" << book.getAuthor() ;
            }
        }
    }

    // Checkout book
    bool checkoutBook(string& barcode, string& memberId, int currentDate) {// defined again but method overloading is done 
        string errorMsg;
        if (bookItems.find(barcode) == bookItems.end()) {
            cout << "BookItem doesnt exist";//book ke liye
            return false;
        }
        if (members.find(memberId) == members.end()) {//member ke liye
            cout << "Member doesnt exist.";
            return false;
        }

        bool success = bookItems[barcode].checkoutBook(currentDate, errorMsg);
        if (!success) {
        cout << errorMsg << "\n";//if ye false hoga toh ye msg dedega joh error string me save ha and it has to be passed by reference every where
            return false;
        }

        members[memberId].borrowBook(barcode, errorMsg);
        return true;
    }

    // Return a book
    void returnBook(string& barcode,string& memberId, int returnDate) {
        std::string errorMsg;
        if (bookItems.find(barcode) == bookItems.end()) {
            cout << "BookItem not found.\n";
            return;
        }
        if (members.find(memberId) == members.end()) {
            cout << "Member not found.\n";
            return;
        }

        int fine = bookItems[barcode].returnBook(returnDate, errorMsg);
        if (fine == -1) {
            cout << errorMsg << "\n";
            return;
        }

        members[memberId].returnBook(barcode);

        if (fine > 0) {
            cout << "Fine for late return: ";
        } else {
            cout << "Book returned on time. No fine.";
        }
    }
};

// ======================= Main Function ========================
int main() {
   

        // Add a book
        Book book1("1", "1984", "George Orwell", "Dystopian", "1949");
        library.addBook(b1);

        // Add book items
        BookItem bookItem1("bc1", "r1");
        library.addBookItem(bookItem1);

        // Register a member
        Member member1("m1", "Aman");
        library.registerMember(member1);

        // Search for a book
        library.searchBookByTitle("1984");

        
        if (library.checkoutBook("bc1", "m1", 10)) {
            std::cout << "Book checked out successfully";
        }

       
        library.returnBook("bc1", "m1", 15);
    } 
    return 0;
