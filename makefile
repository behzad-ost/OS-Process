main: main.cpp client.o bank.o utils.o
	g++ -o check main.cpp client.o bank.o utils.o

client.o: client.cpp
	g++ -c client.cpp

bank.o: bank.cpp
	g++ -c bank.cpp

utils.o: utils.cpp
	g++ -c utils.cpp