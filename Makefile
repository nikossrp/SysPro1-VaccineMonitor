CC = g++
FLAGS = -std=c++11 -c -g #-Wall

OBJS = vaccineMonitor.o Date.o Citizen.o Record.o HashTable.o SkipList.o BloomFilter.o Application.o AdditionFunctions.o
Headers = Date.h Citizen.h Record.h HashTable.h SkipList.h Nodes.h BloomFilter.h Application.h AdditionTypes.h


EXEC = vaccineMonitor

$(EXEC): $(OBJS) $(Headers)
	$(CC) $(OBJS) -o $(EXEC)

vaccineMonitor.o: vaccineMonitor.cpp 
	$(CC) $(FLAGS) vaccineMonitor.cpp

Date.o: Date.cpp
	$(CC) $(FLAGS) Date.cpp

Citizen.o: Citizen.cpp
	$(CC) $(FLAGS) Citizen.cpp

Record.o: Record.cpp
	$(CC) $(FLAGS) Record.cpp

HashTable.o: HashTable.cpp
	$(CC) $(FLAGS) HashTable.cpp

SkipList.o: SkipList.cpp
	$(CC) $(FLAGS) SkipList.cpp

BloomFilter.o: BloomFilter.cpp
	$(CC) $(FLAGS) BloomFilter.cpp

Application.o: Application.cpp
	$(CC) $(FLAGS) Application.cpp

AdditionFunctions.o: AdditionFunctions.cpp
	$(CC) $(FLAGS) AdditionFunctions.cpp

clean:
	rm -f $(EXEC) $(OBJS)

run:
	./vaccineMonitor  -c citizenRecordsFile -b 100000