CFLAGS:= -c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system -pthread


all: StompBookClubClient


StompBookClubClient: bin/ClientsMain.o bin/connectionHandler.o bin/book.o bin/EncoderDecoder.o bin/UserDetails.o bin/KeyboardReader.o
	@echo 'Building target: StompBookClubClient'
	@echo 'Invoking: C++ Linker'
	g++ -o bin/StompBookClubClient bin/ClientsMain.o bin/connectionHandler.o bin/book.o bin/EncoderDecoder.o bin/UserDetails.o bin/KeyboardReader.o $(LDFLAGS)
	@echo 'Finished building target: StompBookClubClient'
	@echo ' '

bin/ClientsMain.o: src/ClientsMain.cpp
	g++ $(CFLAGS) -o bin/ClientsMain.o src/ClientsMain.cpp

bin/connectionHandler.o: src/connectionHandler.cpp
	g++ $(CFLAGS) -o bin/connectionHandler.o src/connectionHandler.cpp

bin/book.o: src/book.cpp
	g++ $(CFLAGS) -o bin/book.o src/book.cpp

bin/EncoderDecoder.o: src/EncoderDecoder.cpp
	g++ $(CFLAGS) -o bin/EncoderDecoder.o src/EncoderDecoder.cpp

bin/KeyboardReader.o: src/KeyboardReader.cpp
	g++ $(CFLAGS) -o bin/KeyboardReader.o src/KeyboardReader.cpp

bin/UserDetails.o: src/UserDetails.cpp
	g++ $(CFLAGS) -o bin/UserDetails.o src/UserDetails.cpp

clean:
	rm -f bin/*