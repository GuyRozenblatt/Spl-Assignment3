//
// Created by shaiami@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include "EncoderDecoder.h"
using namespace std;
#include <mutex>
#include<bits/stdc++.h>
#include<boost/algorithm/string.hpp>

EncoderDecoder::EncoderDecoder(ConnectionHandler &handler, UserDetails &user) : handler(handler), user(user), userName() {}

bool EncoderDecoder::EncodeCommand(string cmd) {

    int index;
    index = cmd.find_first_of(' ');
    string FirstWord = cmd.substr(0, index);
    cmd = cmd.substr(index + 1, cmd.length());

    if (FirstWord.compare("login")==0) {
        encodeCONNECT(cmd);
        return true;
    }
    else if (FirstWord.compare("join")==0) {
        encodeSubscribe(cmd);
        return true;
    }
    else if (FirstWord.compare("exit")==0) {
        encodeUnsubscribe(cmd);
        return true;
    }
    else if (FirstWord.compare("add")==0) {
        encodeAddBook(cmd);
        return true;
    }
    else if (FirstWord.compare("borrow")==0) {
        encodeBorrow(cmd);
        return true;
    }
    else if (FirstWord.compare("return")==0) {
        encodeReturn(cmd);
        return true;
    }
    else if (FirstWord.compare("status")==0) {
        encodeStatus(cmd);
        return true;
    }
    else if (FirstWord.compare("logout")==0) {
        encodeDisConnect(cmd);
        return true;
    }
    else return false;
}

void EncoderDecoder::encodeCONNECT(string cmd) {
    vector<string> wordsSplit;
    splitVec(wordsSplit, cmd, " ");
    string userName = wordsSplit.at(1);
    user.setName(userName);
    string toSend;
    toSend = toSend + "CONNECT" + "\n";
    toSend = toSend + "accept-version:1.2" + "\n";
    toSend = toSend + "host:stomp.cs.bgu.ac.il" + "\n";
    toSend = toSend + "login:" + wordsSplit.at(1) + "\n";
    toSend = toSend + "passcode:" + wordsSplit.at(2) + "\n" + "\n" + '\0';
    handler.sendLine(toSend);
}

void EncoderDecoder::encodeSubscribe(string cmd) {
    vector<string> wordsSplit;
    splitVec(wordsSplit, cmd, " ");
    string toSend;
    toSend = toSend + "SUBSCRIBE" + "\n";
    toSend = toSend + "destination:" + wordsSplit.at(0) + "\n";
    int SubscriptionId = user.getSubscriptionId();
    user.updateReceiptIdMap(user.getReceiptId(), "subscribe " + to_string(SubscriptionId) + " " + wordsSplit.at(0)); // subId + genre.
    toSend = toSend + "id:" + to_string(SubscriptionId) + "\n";
    user.incrementSubId();
    toSend = toSend + "receipt:" + to_string(user.getReceiptId()) + "\n" + "\n" + '\0';
    user.incrementReceiptId();
    handler.sendLine(toSend);
}

void EncoderDecoder::encodeUnsubscribe(string cmd) {
    vector<string> wordsSplit;
    splitVec(wordsSplit, cmd, " ");
    string toSend;
    toSend = toSend + "UNSUBSCRIBE" + "\n";
    int SubId = user.FindIdByGenre(wordsSplit.at(0));
    toSend = toSend + "id:" + to_string(SubId) + "\n";
    toSend = toSend + "receipt:" + to_string(user.getReceiptId()) + "\n" + "\n" + '\0';
    user.updateReceiptIdMap(user.getReceiptId(), "unsubscribe " + to_string(user.getSubscriptionId()) + " " + wordsSplit.at(0)); // subId + genre.
    user.incrementReceiptId();
    handler.sendLine(toSend);
}

void EncoderDecoder::encodeAddBook(string cmd) {
    vector<string> wordsSplit;
    splitVec(wordsSplit, cmd," ");
    string toSend;
    string bookName = extractBookName(cmd, 1);
    string bookGenre = wordsSplit.at(0);
    string bookOwner = user.getUserName();
    book* bookToAdd = new book (bookName, bookOwner, bookGenre, false);
    bool bookAlreadyExists = user.insertBook(bookToAdd);
    if (!bookAlreadyExists) { // we add a book only if it doesnt already exist.
        toSend = toSend + "SEND" + "\n";
        toSend = toSend + "destination:" + bookGenre + "\n" + "\n";
        toSend = toSend + bookOwner + " has added the book " + bookName + "\n" + '\0';
        handler.sendLine(toSend);
    }
}

void EncoderDecoder::encodeBorrow(string cmd) {
    vector<string> wordsSplit;
    splitVec(wordsSplit, cmd, " ");
    string toSend;
    string bookName = extractBookName(cmd, 1);
    string genre = wordsSplit.at(0);
    book* toBorrow = user.getBook(bookName, genre);
    if (toBorrow == nullptr) {
        toSend = toSend + "SEND" + "\n";
        toSend = toSend + "destination:" + wordsSplit.at(0) + "\n" + "\n";
        toSend = toSend + user.getUserName() + " wish to borrow " + bookName + "\n" + '\0';
        user.addToWishLIst(bookName);
        handler.sendLine(toSend);
    }
}

void EncoderDecoder::encodeReturn(string cmd) {
    vector<string> wordsSplit;
    splitVec(wordsSplit, cmd, " ");
    string toSend;
    string bookName = extractBookName(cmd, 1);
    string genre = wordsSplit.at(0);
    book* toReturn = user.getBook(bookName, genre);
    if (toReturn!=nullptr && toReturn->getOwner()!=user.getUserName()) { // here we make sure you cant return a book which you do not have and if you are the owner of the book.
        user.returnBook(toReturn);
        toSend = toSend + "SEND" + "\n";
        toSend = toSend + "destination:" + wordsSplit.at(0) + "\n" + "\n";
        string nameOfLoaner = toReturn->getOwner();
        toSend = toSend + "Returning " + bookName + " to " + nameOfLoaner + "\n" + '\0';
        user.RemoveFromBookList(bookName);
        handler.sendLine(toSend);
    }
}

void EncoderDecoder::encodeStatus(string cmd) {
    vector<string> wordsSplit;
    splitVec(wordsSplit, cmd, " ");
    string toSend;
    toSend = toSend + "SEND" + "\n";
    toSend = toSend + "destination:" + wordsSplit.at(0) + "\n" + "\n";
    toSend = toSend + "Book status" + "\n" + '\0';
    handler.sendLine(toSend);
}

void EncoderDecoder::encodeDisConnect(string cmd) {
    vector<string> wordsSplit;
    splitVec(wordsSplit, cmd, " ");
    string toSend;
    toSend = toSend + "DISCONNECT" + "\n";
    toSend = toSend + "receipt:" + to_string(user.getReceiptId()) + "\n" + "\n" + '\0';
    user.updateReceiptIdMap(user.getReceiptId(), "disconnect");
    user.incrementReceiptId();
    handler.sendLine(toSend);
}


bool EncoderDecoder::Decode() {
    string inputFromServer;
    if (handler.getLine(inputFromServer) && inputFromServer!="") {
        vector<string> wordsSplit;
        splitVec(wordsSplit, inputFromServer, "\n");
        string firstWord = wordsSplit.at(0);
        if (firstWord == "CONNECTED") {
            cout << "login successful" << endl;
        } else if (firstWord == "RECEIPT") {
            string line = wordsSplit.at(1);
            int receiptId = stoi(line.substr(11));
            return decodeRECEIPT(receiptId);
        } else if (firstWord == "MESSAGE") {
            string relevantLine = wordsSplit.at(4);
            vector<string> words;
            string genre = wordsSplit.at(3).substr(12);
            splitVec(words, relevantLine, " ");
            if (words.size()>2 && words.at(2) == "added" && inputFromServer!="") {
            } else if (words.size()>1 && words.at(1) == "wish" && inputFromServer!="") {
                string bookName = extractBookName(relevantLine, 4);
                string genre;
                for (size_t i = 0; i < user.getBookList().size(); i++) {
                    if (user.getBookList().at(i)->getName() == bookName && !user.getBookList().at(i)->isBorrowed1()) { // we loan a book only if we have it and its available.
                        genre = user.getBookList().at(i)->getGenre();
                        string toSend;
                        toSend = toSend + "SEND" + "\n";
                        toSend = toSend + "destination:" + genre + "\n" + "\n";
                        toSend = toSend + user.getUserName() + " has " + bookName + "\n" + '\0';
                        handler.sendLine(toSend);
                    }
                }
            } else if (words.size()>1 && words.at(1) == "has" && inputFromServer!="") {
                string bookName = extractBookName(relevantLine, 2);
                int index = relevantLine.find_first_of(" ");
                string BorrowerName = relevantLine.substr(0, index);
                for (size_t i = 0; i < user.getWishList().size(); i++) { // here we check if we want the book.
                    if (user.getWishList().at(i) == bookName) {
                        string toSend;
                        toSend = toSend + "SEND" + "\n";
                        toSend = toSend + "destination:" + genre + "\n" + "\n";
                        toSend = toSend + "Taking " + bookName + " from " + BorrowerName + "\n" + '\0';
                        handler.sendLine(toSend);
                        book *toAdd = new book(bookName, BorrowerName, genre, false);
                        user.insertBook(toAdd);
                        user.removeFromWishList(bookName); // make sure to remove it from the wish list so it wont be added twice.
                    }
                }
            } else if (words.at(0) == "Taking" && inputFromServer!="") {
                string myName = words.at(words.size() - 1);
                string bookName;
                for (size_t i = 1; i < words.size() - 2; i++) {
                    bookName = bookName + words.at(i) + " ";
                }
                bookName = bookName.substr(0, bookName.size()-1);
                if (user.getUserName() == myName) {
                    user.UpdateBookStatus(bookName, true); // make the book unavailable.
                }
            } else if (words.at(0) == "Returning" && inputFromServer!="") {
                string bookName;
                for (size_t i = 1; i < words.size() - 2; i++) {
                    bookName = bookName + words.at(i) + " ";
                }
                bookName = bookName.substr(0, bookName.size()-1);
                if (words.at(words.size() - 1) == user.getUserName())
                    user.UpdateBookStatus(bookName, false); // make the book available.

            } else if (words.size()>1 && words.at(1) == "status" && inputFromServer!="") {
                string genre = wordsSplit.at(3).substr(12);
                string Booklist = user.BookListToString(genre); // create the relevant book list.
                string toSend;
                toSend = toSend + "SEND" + "\n";
                toSend = toSend + "destination:" + genre + "\n" + "\n";
                toSend = toSend + user.getUserName() + ":" + Booklist + "\n" + '\0';
                handler.sendLine(toSend);
            }
            cout << genre + ":" + relevantLine << endl;
        } else if (firstWord == "ERROR" && inputFromServer!="") {
            cout << wordsSplit.at(1).substr(0) << endl;
        }
    }
    return true;
}

bool EncoderDecoder::decodeRECEIPT(int receiptId) {
    string task = user.findTaskById(receiptId);
    vector<string> wordsSplit;
    splitVec(wordsSplit, task, " ");
    if (wordsSplit.at(0) == "subscribe") {
        string genre = wordsSplit.at(2);
        int SubId = stoi(wordsSplit.at(1));
        user.updateGenreMap(genre, SubId);
        cout << "Joined club "+ genre << endl;
    }
    else if (wordsSplit.at(0) == "unsubscribe") {
        string genre = wordsSplit.at(2);
        user.removeFromGenreMap(genre);
        cout<< "Exited club "+ genre << endl;
    }
    else if (wordsSplit.at(0) == "disconnect") {
        handler.close();
        return false;
    }
    return true;
}

string EncoderDecoder::extractBookName(string cmd, int index) {
    string toReturn;
    vector<string> wordsSplit;
    splitVec(wordsSplit, cmd, " ");
    for (size_t i = index; i<wordsSplit.size(); i++){
        toReturn = toReturn + wordsSplit.at(i)+" ";
    }
    return toReturn.substr(0, toReturn.size()-1);
}

void EncoderDecoder::splitVec(vector<string> &vectorToSplit, string line, string marker) {
    int index;
    while (index!=-1) {
        index = line.find_first_of(marker);
        if (line.substr(0, index)!="") {
            vectorToSplit.push_back(line.substr(0, index));
        }
        line = line.substr(index+1, line.length());
    }
}


