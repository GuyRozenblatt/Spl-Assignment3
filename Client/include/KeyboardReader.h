//
// Created by shaiami@wincs.cs.bgu.ac.il on 06/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_KEYBOARDREADER_H
#define BOOST_ECHO_CLIENT_KEYBOARDREADER_H
#include "EncoderDecoder.h"
using std::string;
class KeyboardReader {
private:
    EncoderDecoder *encdec;
public:
    KeyboardReader(EncoderDecoder *encoderDecoder);
    void run();

};

#endif //BOOST_ECHO_CLIENT_KEYBOARDREADER_H
