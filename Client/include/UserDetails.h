//
// Created by shaiami@wincs.cs.bgu.ac.il on 06/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_USERDETAILS_H
#define BOOST_ECHO_CLIENT_USERDETAILS_H

#include <vector>
#include <string>
#include <unordered_map>
#include "book.h"

using namespace std;

class UserDetails {

private:
    vector<book*> bookList;
    vector<string> wishList;
    std::unordered_map<string,int> genreBySubscriptionIdMap; // <genre, SubId>
    std::unordered_map<int,string> receiptIdMap; // <receiptId, task>
    string UserName;
    int SubscriptionId = 1;
public:
    virtual ~UserDetails();

private:
    int receiptId = 1;
public:
    UserDetails(const string &userName);

public:
    const vector<string> &getWishList() const;
    int getSubscriptionId() const;
    int getReceiptId() const;
    void incrementSubId();
    void incrementReceiptId();
    bool insertBook(book* toInsert);
    void returnBook(book* toRemove);
    void removeFromWishList(string bookName);
    const string &getUserName() const;
    int FindIdByGenre(string genre);
    void updateGenreMap(string genre, int id);
    void removeFromGenreMap (string genre);
    book* getBook(string bookName, string genre);
    void updateReceiptIdMap(int id, string task);
    string findTaskById(int receiptId);
    const vector<book*> &getBookList() const;
    void UpdateBookStatus(string bookName, bool flag);
    void RemoveFromBookList (string bookName);
    string BookListToString(string genre);
    void addToWishLIst(string bookName);
    void setName(string basicString);
};


#endif //BOOST_ECHO_CLIENT_USERDETAILS_H
