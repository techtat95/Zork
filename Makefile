CFLAGS = -g -Wall -Wshadow --pedantic -Wvla #-Werror
PFLAGS = -pthread
COVFLAGS = -fprofile-arcs -ftest-coverage
#DEFINES =
VALGRIND = valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all
VALGRIND += --verbose --track-origins=yes --log-file=
G++ = g++ $(CFLAGS) $(COVFLAGS) # $(DEFINES)
EXTERNAL = ./libraries/tinyxml2.cpp

all: main

main: main.o play.o player.o setup.o container.o creature.o item.o map.o room.o trigger.o
	$(G++) main.o setup.o play.o player.o container.o creature.o item.o map.o room.o trigger.o $(EXTERNAL) -o main -lm

main.o: main.cpp Map.h Room.h Player.h Setup.h
	$(G++) -c main.cpp -o main.o
	
play.o: Play.cpp Play.h Map.h Player.h Room.h Trigger.h
	$(G++) -c Play.cpp -o play.o
	
player.o: Player.cpp Player.h Item.h
	$(G++) -c Player.cpp -o player.o
	
setup.o: Setup.cpp Setup.h Map.h Room.h Trigger.h
	$(G++) -c Setup.cpp -o setup.o
	
container.o: Container.cpp Container.h Item.h Trigger.h
	$(G++) -c Container.cpp -o container.o

creature.o: Creature.cpp Creature.h Item.h Trigger.h
	$(G++) -c Creature.cpp -o creature.o

item.o: Item.cpp Item.h $(TRIGGERS)
	$(G++) -c Item.cpp -o item.o
	
map.o: Map.cpp Map.h Room.h
	$(G++) -c Map.cpp -o map.o
	
room.o: Room.cpp Room.h Container.h Creature.h Item.h Trigger.h
	$(G++) -c Room.cpp -o room.o
	
trigger.o: Trigger.cpp Trigger.h
	$(G++) -c Trigger.cpp -o trigger.o

test: main
	echo "TESTING Sample"
	./main samples/sample.xml -d
	
test2: main
	echo "TESTING Sample"
	./main samples/Free_Map.xml -d
	
testItem: main
	echo "TESTING Item Sample"
	./main samples/itemsample.xml -d
	
testRoom: main
	echo "TESTING Room Sample"
	./main samples/roomsample.xml -d
	
testRoom2: main
	echo "TESTING Room Sample 2"
	./main samples/rooms.xml -d
	
testContainer: main
	echo "TESTING Container Sample"
	./main samples/containersample.xml -d
	
testContainer2: main
	echo "TESTING Container Sample 2"
	./main samples/container.xml -d
	
testCreature: main
	echo "TESTING Creature Sample"
	./main samples/creaturesample.xml -d
	
testCreature2: main
	echo "TESTING Creature Sample 2"
	./main samples/creatures.xml -d
	
testTrigger: main
	echo "TESTING Trigger Sample"
	./main samples/triggersample.xml -d

clean:
	/bin/rm -f *.o
	/bin/rm -f *.gcda *.gcno gmon.out *gcov
	#/bin/rm -f main.exe
