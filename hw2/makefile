all: clean driver2

driver2: driver2.cpp tetris.cpp tetromino.cpp
	@g++ -std=c++11 -o driver2 driver2.cpp tetris.cpp tetromino.cpp
	./driver2

driver1: driver1.cpp tetris.cpp tetromino.cpp
	@g++ -std=c++11 -o driver1 driver1.cpp tetris.cpp tetromino.cpp
	./driver1

clean:
	@rm -f *.o
	@rm -f driver1 driver2