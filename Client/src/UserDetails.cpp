//
// Created by shaiami@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include "UserDetails.h"

UserDetails::UserDetails(const string &userName) : bookList(), wishList(), genreBySubscriptionIdMap(), receiptIdMap(), UserName(userName) {}

int UserDetails::getSubscriptionId() const {
    return SubscriptionId;
}

int UserDetails::getReceiptId() const {
    return receiptId;
}

void UserDetails::incrementReceiptId() {
    receiptId++;
}

void UserDetails::incrementSubId() {
    SubscriptionId++;
}

const string &UserDetails::getUserName() const {
    return UserName;
}

bool UserDetails::insertBook(book* book) {
    for (size_t i=0; i<bookList.size(); i++) {
        if (bookList.at(i)->getName()==book->getName() && bookList.at(i)->getGenre()==book->getGenre()) {
            return true;
        }
    }
    bookList.push_back(book);
    return false;
}

void UserDetails::returnBook(book* toRemove) {
    for (size_t i=0; i<bookList.size(); i++) {
        if ((bookList.at(i)!= nullptr) && (bookList.at(i)->getName()==toRemove->getName())) {
            bookList.erase(bookList.begin()+i);
        }
    }
}

int UserDetails::FindIdByGenre(string genre) {
    std::unordered_map<std::string,int>::const_iterator got = genreBySubscriptionIdMap.find (genre);
    if (got != genreBySubscriptionIdMap.end() )
        return got->second;
    return 0;
}

void UserDetails::updateGenreMap(string genre, int id) {
    genreBySubscriptionIdMap.insert({genre, id});
}

void UserDetails::removeFromGenreMap(string genre) {
    genreBySubscriptionIdMap.erase(genre);
}

book* UserDetails::getBook(string bookName, string genre) {
    for (size_t i=0; i<bookList.size(); i++) {
        if (bookList.at(i)->getName()==bookName && bookList.at(i)->getGenre()==genre) {
            return bookList.at(i);
        }
    }
    return NULL;
}

void UserDetails::updateReceiptIdMap(int id, string task) {
    receiptIdMap.insert({id, task});
}

string UserDetails::findTaskById(int receiptId) {
    std::unordered_map<int,string>::const_iterator got = receiptIdMap.find(receiptId);
    if ( got != receiptIdMap.end() )
        return got->second;
    return nullptr;
}

const vector<book*> &UserDetails::getBookList() const {
    return bookList;
}

const vector<string> &UserDetails::getWishList() const {
    return wishList;
}

void UserDetails::removeFromWishList(string bookName) {
    for (size_t i=0; i<wishList.size(); i++) {
        if (wishList.at(i)==bookName) {
            wishList.erase(wishList.begin() + i);
        }
    }
}

void UserDetails::RemoveFromBookList(string bookName) {
    for (size_t i = 0; i < bookList.size(); i++) {
        if (bookList.at(i)->getName() == bookName) {
            bookList.erase(bookList.begin() + i);
        }
    }
}


    void UserDetails::UpdateBookStatus(string bookName, bool flag) {
        for (size_t i = 0; i < bookList.size(); i++) {
            if (bookList.at(i)->getName() == bookName) {
                bookList.at(i)->setIsBorrowed(flag);
            }
        }
    }

string UserDetails::BookListToString(string genre) {
    string toReturn;
    for(size_t i=0 ; i<bookList.size(); i++){
        if(bookList.at(i)->getGenre()==genre && !bookList.at(i)->isBorrowed1())
            toReturn=toReturn + "," + bookList.at(i)->getName();
    }
    if (toReturn.size()>0) {
        toReturn=toReturn.substr(1,toReturn.size()-1);
    }
    return toReturn;
}

void UserDetails::addToWishLIst(string bookName) {
    wishList.push_back(bookName);
}

UserDetails::~UserDetails() {
    for (size_t i=0; i<bookList.size(); i++) {
        delete(bookList.at(i));
    }
}

void UserDetails::setName(string userName) {
    UserName=userName;
}


