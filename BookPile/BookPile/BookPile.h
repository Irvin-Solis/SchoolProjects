#ifndef BOOKPILE_H
#define BOOKPILE_H

#include "Book.h"
#include <string>

class BookPile
{
private:
	int getTitleLength(std::string title);
	int bookAmount;
	Book* headPtr;

public:
	BookPile();
	BookPile(const BookPile& pile);
	/**
* Removing a book, locating it by its Title
*
* @param string title, the name of the book
* @return true or fales, if the book was removed
* @pre Book must be inside pile, and title must be not empty to work.
**/
	bool removeBook(std::string title);
	/**
* Removing a book, locating it by its position
*
* @param int position, the number in the pile the book is believed located
* @return true or fales, if the book was removed
* @pre Book must be inside pile, and position must be between 1 and bookAmount to work.
**/
	bool removeBook(int position);
	/**
* add a book to the BookPile
*
* @param title, the name of the book
* @return true or fales, if the book was added
* @pre Book must be not already in BookPile, and title must be not empty to work.
**/
	bool addBook(std::string title);
	/**
* Find the positon in BookPile of a book
*
* @param title, the name of the book
* @return int, the number in the pile the book is in.
* @pre Book must be inside pile, otherwise returns -1
**/
	int findBook(std::string title);
	/**
* Spits out all Book title in format ,position "Title" (title length) to console.
*
**/
	void displayPile();
	/**
* returns the title of a specific book, given its positon
*
* @param int position, the number in the pile the book is believed located
* @return string title of the book
* @pre Book must be inside pile and positon between 1 and bookAmount, otherwise retruns empty string
**/
	std::string getBook(int position);
	/**
* Rename a specif book, given its title, and new title
*
* @param oldName, the name of the book
* @param newName, the name wising to change it to
* @return true or flase if book name was changed
* @pre Book must be inside pile and new name must not be an empty string
**/
	bool renameBook(std::string oldName, std::string newName);
	/**
* returns the number of books inside BookPile
*
* @return int, the number of books inside the Pile
**/
	int bookCount();
	/**
* deletes all books and sets bookAmount to 0.
*
**/
	void clear();
	/**
* returns the pointer of a book, given the position of it
*
* @param int position, the number in the pile the book is believed located
* @return Book, the pointer of the book in the given position
* @pre positon must be between 1 and bookAmount
**/
	Book* summonBook(int position);

};
#endif // !BOOKPILE_H
