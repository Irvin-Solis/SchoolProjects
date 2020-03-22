/**
* Irvin Jimenez-Solis
* BookPile.cpp
**/
#include "BookPile.h"
#include "Book.h"
#include <iostream>

BookPile::BookPile() : headPtr(nullptr), bookAmount(0) {

}

BookPile::BookPile(const BookPile& pile) {
	Book* currentBook = pile.headPtr;
	headPtr = nullptr;
	bookAmount = 0;

	while (currentBook != nullptr) {

		addBook(currentBook->getTitle());
		currentBook = currentBook->getNext();
	}
}

int BookPile::getTitleLength(std::string title) {
	return title.length();
}

int BookPile::findBook(std::string title) {
	int counter = bookAmount; // first book will in position bookAmount
	bool found = false;
	Book* bookTitle = headPtr;
	while (!found && bookTitle != nullptr) //loop through until you title is found, or we've searched all books
	{
		if (title == bookTitle->getTitle()) {
			found = true;
		}
		else {
			bookTitle = bookTitle->getNext();
			counter--; // add 1 to the counter/move to the next position
		}
		
	}
	if (found == false) { // if while broke due to nullptr, will set count to -1 & return -1
		counter = -1;
	}
	return counter;
}
bool BookPile::removeBook(std::string title) {
	bool successfulRemoval = false;
	if (headPtr->getTitle() == title) { // if the book we are deleting is the headPtr
		Book* tempPtr = headPtr->getNext();
		delete headPtr;
		headPtr = tempPtr;
		bookAmount--;
	}
	else {
		Book* currentBook = headPtr->getNext(); //already know its not headptr so skip to next
		Book* pastBook = headPtr; // book to wrap around book we want to delete
		while (currentBook != nullptr && currentBook->getTitle() != title) //will look through pile until title match or until end of pile
		{
			pastBook = currentBook;
			currentBook = currentBook->getNext();
		}
		if (currentBook != nullptr) {
			Book* tempPtr = currentBook->getNext(); // get pointer to next book
			delete currentBook; // delete book
			pastBook->setNext(tempPtr); // set pointer to book after deleted book
			bookAmount--;
			successfulRemoval = true;
		}
	}
	return successfulRemoval;
}

bool BookPile::removeBook(int position) {
	bool successfulRemoval;
	position = (-1 * position) + 11; // numbers are flipped so get right number
	if (position > bookAmount || position < 1) {
		successfulRemoval = false;
	}
	else if (position == bookAmount) { //if book we are delting is headPtr
		Book* tmpBook = headPtr->getNext();
		removeBook(headPtr->getTitle()); // remove headptr and sets next book to headptr

	}
	else { // nothing special, regular book removal
		Book* currrentBook = headPtr->getNext();
		Book* pastBook = headPtr;
		for (int i = 2; i < position; i++) //loops to position of book needed
		{
			pastBook = currrentBook;
			currrentBook = currrentBook->getNext();
		}
		Book* tmpPtr = currrentBook->getNext(); //get pointer to next book
		delete currrentBook; // delete book
		pastBook->setNext(tmpPtr); //set pointer to book after deleted book
		successfulRemoval = true;
		bookAmount--;
	}
	return successfulRemoval;
}

bool BookPile::addBook(std::string title) {
	bool successfulAdd = true;
	if (getTitleLength(title) == 0 || findBook(title) != -1) { // if title is empty or book already exists, fails
		successfulAdd = false;
	}
	else if(headPtr == nullptr) { // if BookPile is empty set book as headPtr
		Book* newBook = new Book(title, nullptr);

		headPtr = newBook;
		bookAmount++;
	}
	else {
		Book* newBook = new Book(title, nullptr); // creates sad excuse of a book

		if (getTitleLength(title) <= getTitleLength(headPtr->getTitle())) { // if newBook title is less  than/equal to headPtr title, makes newBook headPtr

			newBook->setNext(headPtr);
			headPtr = newBook;
			bookAmount++;
		}
		else{ // adds Book to where it belongs

			if (bookAmount == 1) { // if their was only 1 book in the pile and it was bigger than headPtr
				headPtr->setNext(newBook);
				bookAmount++;
			}
			else { // just adding another waste of paper to the pile
				Book* currentBook = headPtr; // already establish newBook wont be behind headPtr
				Book* pastBook = nullptr;

				while (currentBook != nullptr && getTitleLength(title) > getTitleLength(currentBook->getTitle())) // while not past the last book in pile, or book title smaller than current book 
				{			

					pastBook = currentBook;
					currentBook = currentBook->getNext();
				}
				if (currentBook == nullptr) { // we are at the end of the pile, so add book to end
					pastBook->setNext(newBook);
				}
				else { // put that book in it s place!!!
					pastBook->setNext(newBook);
					newBook->setNext(currentBook);
				}

				bookAmount++;
			}

		}

	}
	return successfulAdd;
}
std::string BookPile::getBook(int position){
	int counter = bookAmount; // first book will in position 1
	std::string title;
	Book* book = headPtr;
	if(position > bookAmount || position < 1){
		title = "";
	}
	else{
		while (position != counter)
		{
			book = book->getNext();
			counter--;
		}
		title = book->getTitle();
	}

	return title;
}
void BookPile::displayPile(){
	int counter = bookAmount;
	for (int i = 1; i < bookAmount+1; i++)
	{
		std::cout << i << ". " << getBook(i) << "(" << getTitleLength(summonBook(counter)->getTitle()) << ")" << "\n";
		counter--;
	}
}

bool BookPile::renameBook(std::string oldName, std::string newName){
	bool success = true;
	if(getTitleLength(newName) == 0 || findBook(oldName) == -1){
		success = false;
	}
	else if (getTitleLength(oldName) != getTitleLength(newName)){ // if the newName length isnt the same to oldName
		removeBook(oldName);
		addBook(newName);
	}
	return success;
}

int BookPile::bookCount(){
	return bookAmount;
}

void BookPile::clear() {
	int counter = bookAmount; //starting with the very last book
	
	while (counter != 0) {
		Book* currentBook = summonBook(counter); //set the book for punishment
		delete currentBook; // punish the book
		counter--; // set counter for next victum;
	} // repeat
	bookAmount = 0;
}

Book* BookPile::summonBook(int position) {

	int counter = 1; // first book will in position 1
	Book* theHolyBook = headPtr; // book we are looking for, starting with headPtr

	if (position > bookAmount || position < 1) {
		theHolyBook = nullptr;
	}
	else {
		while (position != counter)
		{
			theHolyBook = theHolyBook->getNext();
			counter++;
		}
	}

	return theHolyBook;
}