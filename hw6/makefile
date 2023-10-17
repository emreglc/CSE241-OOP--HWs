all: clean driver

driver: driver.cpp 
	@g++ -std=c++11 -o driver driver.cpp PFArrayPlus.cpp
	./driver

clean:
	@rm -f *.o
	@rm -f driver