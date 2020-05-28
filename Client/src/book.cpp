//
// Created by shaiami@wincs.cs.bgu.ac.il on 09/01/2020.
//

#include "book.h"

book::book(const string &name, const string &owner, const string &genre, bool isBorrowed) : name(name), owner(owner),genre(genre),isBorrowed(isBorrowed) {}

const string &book::getName() const {
    return name;
}

const string &book::getGenre() const {
    return genre;
}

void book::setIsBorrowed(bool status) {
    isBorrowed = status;
}

bool book::isBorrowed1() const {
    return isBorrowed;
}

const string &book::getOwner() const {
    return owner;
}
