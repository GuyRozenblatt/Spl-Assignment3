//
// Created by shaiami@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include <iostream>
#include "KeyboardReader.h"

KeyboardReader::KeyboardReader(EncoderDecoder *encoderDecoder) : encdec(encoderDecoder) {}

void KeyboardReader::run() {
    bool run = true;
    while(run) {
        const short  bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        run = encdec->EncodeCommand(line);
        string FirstWord = line.substr(0, line. find_first_of(' '));
        if (FirstWord=="logout") {
            run=false;
        }
    }


}
