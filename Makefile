final: tetfoo.o tetfoo.hpp main.o
	g++ tetfoo.o main.o -o tetris24.out -lsfml-graphics -lsfml-window -lsfml-system

start: final
	./tetris24.out
rebuild: clean main.cpp tetfoo.cpp tetfoo.hpp
	g++ main.cpp -c -o main.o
	g++ tetfoo.cpp -c -o tetfoo.o
	g++ tetfoo.o main.o -o tetris24.out -lsfml-graphics -lsfml-window -lsfml-system
	./tetris24.out
clean:
	rm *.o; rm *.out; echo cleared

tetfoo.o: tetfoo.cpp tetfoo.hpp
	g++ tetfoo.cpp -c -o tetfoo.o

main.o: main.cpp
	g++ main.cpp -c -o main.o

test4: test4.cpp
	g++ test4.cpp -o test4.out -lsfml-graphics -lsfml-window -lsfml-system
	./test4.out
	rm test4.out
test3: test3.cpp
	g++ test3.cpp -o test3.out -lsfml-graphics -lsfml-window -lsfml-system
	./test3.out
	rm test3.out
	
test2: test2.cpp
	g++ test2.cpp -o test2.out -lsfml-graphics -lsfml-window -lsfml-system
	./test2.out
	rm test2.out


test1: test1.cpp	
	g++ test1.cpp -o test1.out -lsfml-graphics -lsfml-window -lsfml-system
	./test1.out
	rm test1.out
