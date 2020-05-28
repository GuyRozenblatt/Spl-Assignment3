//
// Created by shaiami@wincs.cs.bgu.ac.il on 09/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_BOOK_H
#define BOOST_ECHO_CLIENT_BOOK_H

#include <string>

using namespace std;

class book {
private:
    string name;
    string owner;
    string genre;
    bool isBorrowed;
public:
    const string &getName() const;
    bool isBorrowed1() const;
    void setIsBorrowed(bool status);

    book(const string &name, const string &owner, const string &genre, bool isBorrowed);

    const string &getOwner() const;

    const string &getGenre() const;

};

#endif //BOOST_ECHO_CLIENT_BOOK_H
