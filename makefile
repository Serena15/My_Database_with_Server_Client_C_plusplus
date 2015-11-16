OBJ = record.o tree.o hash.o list.o com.o main.o


hh: $(OBJ)
	g++ $(OBJ) -g -ggdb -o hh
main.o: main.cpp tree.h hash.h list.h com.h record.h
	g++ -c -g -ggdb main.cpp
com.o: com.cpp tree.h hash.h list.h com.h record.h
	g++ -c -g -ggdb com.cpp
list.o: list.cpp hash.h list.h record.h
	g++ -c -g -ggdb list.cpp
hash.o: hash.cpp hash.h record.h
	g++ -c -g -ggdb hash.cpp
tree.o: tree.cpp tree.h record.h
	g++ -c -g -ggdb tree.cpp
record.o: record.cpp record.h
	g++ -c -g -ggdb record.cpp


clean:
	rm -rf $(OBJ) hh
