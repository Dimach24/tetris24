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
