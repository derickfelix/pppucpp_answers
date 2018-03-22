/*
  Create an enumerated type for the Book class called Genre. Have the type be
  fiction, nonfiction, periodical, biography, and children. Give each book a
  Genre and make the appropriate changes to the Book constructor and member
  functions
*/
#include "../std_lib_facilities.h"
#include "Chrono.h"

class Book
{
public:
  Book();
  Book(string ISBN, string title, string author, Chrono::Date date, bool checkedOut);
  class Invalid {};

  string getISBN() const { return m_ISBN; }
  string getTitle() const { return m_Title; }
  string getAuthor() const { return m_Author; }
  Chrono::Date getDate() const { return m_Date; }
  bool isCheckedOut() const { return m_CheckedOut; }

  void checkIn() { m_CheckedOut = false; }
  void checkOut() { m_CheckedOut = true; }

private:
  string m_ISBN;
  string m_Title;
  string m_Author;
  Chrono::Date m_Date;
  bool m_CheckedOut;
};

bool isValidBook(const Book& book)
{
  if (book.getISBN().size() != 7) {
    return false;
  }

  char *items = new char[book.getISBN().length() + 1];
  strcpy(items, book.getISBN().c_str());
  int size = sizeof(items) / sizeof(char);
  for (int i = 0; i < size-2; ++i) { // size - 2 == 0-0-0 instead of 0-0-0-a
    if (i % 2 == 0) {
      if (!isdigit(*(items + i))) {
          delete[] items;
          return false;
      }
    }
  }
  delete[] items;

  return true;
}

Book::Book(string ISBN, string title, string author, Chrono::Date date, bool checkedOut)
    : m_ISBN(ISBN), m_Title(title), m_Author(author), m_Date(date), m_CheckedOut(checkedOut)
{
  if (!isValidBook(*this)) throw Invalid();
}

const Book& default_book()
{
  static Book db {"0-0-0-a", "Unknown Title", "Unknown Author", Chrono::Date(), false};
  return db;
}

Book::Book()
  : m_ISBN(default_book().getISBN()), m_Title(default_book().getTitle()),
    m_Author(default_book().getAuthor()), m_Date(default_book().getDate()),
    m_CheckedOut(default_book().isCheckedOut()) { }

bool operator==(const Book& book, const Book& other)
{
  return book.getISBN() == other.getISBN();
}

bool operator!=(const Book& book, const Book& other)
{
  return !(book == other);
}

ostream& operator<<(ostream& os, const Book& book)
{
  os << "--------------------------------\n";
  os << "Book's ISBN: " << book.getISBN() << '\n';
  os << "Book's title: " << book.getTitle() << '\n';
  os << "Book's year: " << book.getDate().year() << '\n';
  return os;
}

int main()
{
  try {
    Book book;

  } catch (Book::Invalid& e) {
    cout << "Invalid Book!\n";
  }

  return 0;
}
