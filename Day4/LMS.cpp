#include <bits/stdc++.h>
using namespace std;

enum class BookFormat {
    HARDCOVER = 1,
    PAPERBACK,
    AUDIO_BOOK,
    EBOOK,
    NEWSPAPER,
    MAGAZINE,
    JOURNAL
};

enum class BookStatus {
    AVAILABLE = 1,
    RESERVED,
    LOANED,
    LOST
};

enum class ReservationStatus {
    WAITING = 1,
    PENDING,
    CANCELED,
    NONE
};

enum class AccountStatus {
    ACTIVE = 1,
    CLOSED,
    CANCELED,
    BLACKLISTED,
    NONE
};

class Address {
private:
    string streetAddress;
    string city;
    string state;
    string zipCode;
    string country;

public:
    Address(const string &street, const string &city, const string &state, 
            const string &zipCode, const string &country)
        : streetAddress(street), city(city), state(state), zipCode(zipCode), country(country) {}
};

class Person {
private:
    string name;
    Address address;
    string email;
    string phone;

public:
    Person(const string &name, const Address &address, const string &email, const string &phone)
        : name(name), address(address), email(email), phone(phone) {}
};

class Constants {
public:
    static const int MAX_BOOKS_ISSUED_TO_A_USER = 5;
    static const int MAX_LENDING_DAYS = 10;
};

class Account {
private:
    string id;
    string password;
    AccountStatus status;
    shared_ptr<Person> person;

public:
    Account(const string &id, const string &password, shared_ptr<Person> person, AccountStatus status = AccountStatus::ACTIVE)
        : id(id), password(password), status(status), person(person) {}

    virtual void resetPassword() = 0;
};

class Librarian : public Account {
public:
    Librarian(const string &id, const string &password, shared_ptr<Person> person, AccountStatus status = AccountStatus::ACTIVE)
        : Account(id, password, person, status) {}

    void addBookItem(/* parameters */) {
        // Implementation here
    }

    void blockMember(/* parameters */) {
        // Implementation here
    }

    void unBlockMember(/* parameters */) {
        // Implementation here
    }
};

class Member : public Account {
private:
    time_t dateOfMembership;
    int totalBooksCheckedout;

public:
    Member(const string &id, const string &password, shared_ptr<Person> person, AccountStatus status = AccountStatus::ACTIVE)
        : Account(id, password, person, status), totalBooksCheckedout(0) {
        dateOfMembership = time(0); // Current date/time
    }

    int getTotalBooksCheckedout() const {
        return totalBooksCheckedout;
    }

    void reserveBookItem(/* parameters */) {
        // Implementation here
    }

    void incrementTotalBooksCheckedout() {
        // Implementation here
    }

    bool checkoutBookItem(/* parameters */) {
        if (getTotalBooksCheckedout() >= Constants::MAX_BOOKS_ISSUED_TO_A_USER) {
            cout << "The user has already checked-out maximum number of books\n";
            return false;
        }
        // BookReservation bookReservation = BookReservation::fetchReservationDetails(bookItem.getBarcode());
        // Implement further as per original code
        // Update as per logic for checking out a book item

        incrementTotalBooksCheckedout();
        return true;
    }

    void checkForFine(/* parameters */) {
        // BookLending bookLending = BookLending::fetchLendingDetails(bookItemBarcode);
        // Implement fine checking logic
    }

    void returnBookItem(/* parameters */) {
        // checkForFine(bookItem.getBarcode());
        // Implement return book item logic
    }

    bool renewBookItem(/* parameters */) {
        // checkForFine(bookItem.getBarcode());
        // Implement renew book item logic

        return true;
    }
};

// Assuming the previous enums and classes are defined here

class BookReservation {
private:
    time_t creationDate;
    ReservationStatus status;
    string bookItemBarcode;
    string memberId;

public:
    BookReservation(time_t creationDate, ReservationStatus status, const string &bookItemBarcode, const string &memberId)
        : creationDate(creationDate), status(status), bookItemBarcode(bookItemBarcode), memberId(memberId) {}

    static shared_ptr<BookReservation> fetchReservationDetails(const string &barcode) {
        // Implementation to fetch reservation details
        return nullptr; // Placeholder return value
    }
};

class BookLending {
private:
    time_t creationDate;
    time_t dueDate;
    time_t returnDate;
    string bookItemBarcode;
    string memberId;

public:
    BookLending(time_t creationDate, time_t dueDate, const string &bookItemBarcode, const string &memberId)
        : creationDate(creationDate), dueDate(dueDate), returnDate(0), bookItemBarcode(bookItemBarcode), memberId(memberId) {}

    static bool lendBook(const string &barcode, const string &memberId) {
        // Implementation to lend book
        return true; // Placeholder return value
    }

    static shared_ptr<BookLending> fetchLendingDetails(const string &barcode) {
        // Implementation to fetch lending details
        return nullptr; // Placeholder return value
    }

    time_t getDueDate() const {
        return dueDate;
    }
};

class Fine {
private:
    time_t creationDate;
    string bookItemBarcode;
    string memberId;

public:
    Fine(time_t creationDate, const string &bookItemBarcode, const string &memberId)
        : creationDate(creationDate), bookItemBarcode(bookItemBarcode), memberId(memberId) {}

    static void collectFine(const string &memberId, int days) {
        // Implementation to collect fine
        cout << "Collecting fine for member: " << memberId << " for " << days << " days." << endl;
    }
};

class Book {
private:
    string ISBN;
    string title;
    string subject;
    string publisher;
    string language;
    int numberOfPages;
    vector<string> authors;

public:
    Book(const string &ISBN, const string &title, const string &subject,
         const string &publisher, const string &language, int numberOfPages)
        : ISBN(ISBN), title(title), subject(subject), publisher(publisher),
          language(language), numberOfPages(numberOfPages) {}
};

class BookItem : public Book {
private:
    string barcode;
    bool isReferenceOnly;
    bool borrowed;
    time_t dueDate;
    double price;
    BookFormat format;
    BookStatus status;
    time_t dateOfPurchase;
    time_t publicationDate;
    string placedAt;

public:
    BookItem(const string &ISBN, const string &title, const string &subject,
             const string &publisher, const string &language, int numberOfPages,
             const string &barcode, bool isReferenceOnly, bool borrowed, time_t dueDate,
             double price, BookFormat format, BookStatus status, time_t dateOfPurchase,
             time_t publicationDate, const string &placedAt)
        : Book(ISBN, title, subject, publisher, language, numberOfPages),
          barcode(barcode), isReferenceOnly(isReferenceOnly), borrowed(borrowed), dueDate(dueDate),
          price(price), format(format), status(status), dateOfPurchase(dateOfPurchase),
          publicationDate(publicationDate), placedAt(placedAt) {}

    bool checkout(const string &memberId) {
        if (isReferenceOnly) {
            cout << "This book is Reference only and can't be issued" << endl;
            return false;
        }
        if (!BookLending::lendBook(barcode, memberId)) {
            return false;
        }
        updateBookItemStatus(BookStatus::LOANED);
        return true;
    }

    string getBarcode() const {
        return barcode;
    }

    bool getIsReferenceOnly() const {
        return isReferenceOnly;
    }

    void updateBookItemStatus(BookStatus newStatus) {
        status = newStatus;
    }
};

class Rack {
private:
    string number;
    string locationIdentifier;

public:
    Rack(const string &number, const string &locationIdentifier)
        : number(number), locationIdentifier(locationIdentifier) {}
};

class Search {
public:
    virtual vector<string> searchByTitle(const string &title) = 0;
    virtual vector<string> searchByAuthor(const string &author) = 0;
    virtual vector<string> searchBySubject(const string &subject) = 0;
    virtual vector<string> searchByPubDate(const time_t &publishDate) = 0;
};

class Catalog : public Search {
private:
    map<string, vector<string>> bookTitles;
    map<string, vector<string>> bookAuthors;
    map<string, vector<string>> bookSubjects;
    map<time_t, vector<string>> bookPublicationDates;

public:
    Catalog() {}

    vector<string> searchByTitle(const string &query) override {
        if (bookTitles.find(query) != bookTitles.end()) {
            return bookTitles[query];
        }
        return {};
    }

    vector<string> searchByAuthor(const string &query) override {
        if (bookAuthors.find(query) != bookAuthors.end()) {
            return bookAuthors[query];
        }
        return {};
    }

    vector<string> searchBySubject(const string &query) override {
        if (bookSubjects.find(query) != bookSubjects.end()) {
            return bookSubjects[query];
        }
        return {};
    }

    vector<string> searchByPubDate(const time_t &publishDate) override {
        if (bookPublicationDates.find(publishDate) != bookPublicationDates.end()) {
            return bookPublicationDates[publishDate];
        }
        return {};
    }
};

int main() {
    // Create a Catalog
    Catalog catalog;

    // Sample data to populate the catalog for demonstration
    string sampleISBN = "123456789";
    string sampleTitle = "Sample Title";
    string sampleAuthor = "Sample Author";
    string sampleSubject = "Sample Subject";
    time_t now = time(0);

    // Adding sample data to the catalog
    catalog.searchByTitle(sampleTitle).push_back(sampleISBN);
    catalog.searchByAuthor(sampleAuthor).push_back(sampleISBN);
    catalog.searchBySubject(sampleSubject).push_back(sampleISBN);
    catalog.searchByPubDate(now).push_back(sampleISBN);

    // Demonstrate searching
    auto titles = catalog.searchByTitle("OK");
    auto authors = catalog.searchByAuthor("noT OK");
    auto subjects = catalog.searchBySubject("Why OK");
    auto pubDates = catalog.searchByPubDate(now);

    cout << "Books with title 'Sample Title':\n";
    for (const auto &isbn : titles) {
        cout << isbn << endl;
    }

    cout << "Books by author 'Sample Author':\n";
    for (const auto &isbn : authors) {
        cout << isbn << endl;
    }

    cout << "Books with subject 'Sample Subject':\n";
    for (const auto &isbn : subjects) {
        cout << isbn << endl;
    }

    cout << "Books published at given date:\n";
    for (const auto &isbn : pubDates) {
        cout << isbn << endl;
    }

    // Create a Person and Member
    shared_ptr<Person> person = make_shared<Person>("John Doe", Address("123 Street", "City", "State", "12345", "Country"), "email@example.com", "1234567890");


    // Create a BookItem
    BookItem bookItem(sampleISBN, sampleTitle, sampleSubject, "Sample Publisher", "English", 200,
                      "barcode123", false, false, now, 29.99, BookFormat::HARDCOVER, BookStatus::AVAILABLE, now, now, "Rack 1");


    return 0;
}

