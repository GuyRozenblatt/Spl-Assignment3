#include <stdlib.h>
#include <connectionHandler.h>
#include <EncoderDecoder.h>
#include <KeyboardReader.h>
#include <thread>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

void splitVector(vector<string> &vectorToSplit, string line, string marker);
string createWord(vector<string> &line);

/**
* This code assumes that the server replies the exact text the client sent it (as opposed to the practical session example)
*/
int main (int argc, char *argv[]) {

    ///////////////////// wait for the first input from the user to be login ///////////////////////////////////////////

    string FirstWord;
    std::string line;
    vector<string> wordsSplit;
    do {
        const short  bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        FirstWord = line.substr(0, line.find_first_of(' '));
        splitVector(wordsSplit, line, " ");
    } while(FirstWord.compare("login")!=0);
    line = createWord(wordsSplit);
    string userName = wordsSplit.at(2);
    string SecondWord = wordsSplit.at(1);
    int index = SecondWord.find_first_of(':');
    string host(SecondWord.substr(0, index));
    string port = std:: string(wordsSplit.at(1).substr(index+1, wordsSplit.size()));
    short portInShorts = std::stoi(port);

    /////////////////////////// initialize the user, the handler and the keyboard reader ///////////////////////////////

    UserDetails user(userName);
    ConnectionHandler connectionHandler(host, portInShorts);
    if (!connectionHandler.connect()) {
        std::cout << "Could not connect to server" << std::endl;
        return 1;
    }
    EncoderDecoder* encdec = new EncoderDecoder(connectionHandler, user);
    encdec->EncodeCommand(line);
    KeyboardReader keyboardReader(encdec);
    thread KeyboardReaderThread(&KeyboardReader::run, &keyboardReader);

    ////////////////////////////// read from the socket until disconnection ////////////////////////////////////////////

    bool decode = true;
    while (decode) {
        decode = encdec->Decode();
    }
    KeyboardReaderThread.join();
    delete(encdec);
    return 0;
}

////////////////////////////////// private methods for splitting and editing a string //////////////////////////////////

void splitVector(vector<string> &vectorToSplit, string line, string marker) {
    int index;
    while (index!=-1) {
        index = line.find_first_of(marker);
        vectorToSplit.push_back(line.substr(0, index));
        line = line.substr(index+1, line.length());
    }
}

string createWord(vector<string> &line) {
    string toReturn;
    for (size_t i=0; i<line.size(); i++) {
        toReturn = toReturn + " " + line.at(i) + " ";
    }
    toReturn = toReturn.substr(1, toReturn.size()-1);
    return toReturn;
}
