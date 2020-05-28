//
// Created by shaiami@wincs.cs.bgu.ac.il on 06/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_ENCODERDECODER_H
#define BOOST_ECHO_CLIENT_ENCODERDECODER_H

#include <iostream>
#include "connectionHandler.h"
#include "UserDetails.h"
#include <mutex>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
using std::string;

class EncoderDecoder {

private:
    ConnectionHandler &handler;
    UserDetails user;
    string userName;
    void encodeSubscribe (string cmd);
    void encodeUnsubscribe (string cmd);
    void encodeAddBook (string cmd);
    void encodeBorrow (string cmd);
    void encodeReturn (string cmd);
    void encodeStatus (string cmd);
    void encodeDisConnect (string cmd);
    void encodeCONNECT(string cmd);
    bool decodeRECEIPT(int receiptId);
    string extractBookName(string cmd, int index);
    void splitVec(vector<string> &vectorToSplit, string line, string marker);

public:
    EncoderDecoder(ConnectionHandler &handler, UserDetails &user);
    bool EncodeCommand(string cmd);
    bool Decode();


};


#endif //BOOST_ECHO_CLIENT_ENCODERDECODER_H
