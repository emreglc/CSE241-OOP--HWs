all: clean driver

driver: driver.cpp DayofYearSet.cpp
	@g++ -std=c++11 -o driver driver.cpp DayofYearSet.cpp
	@./driver

clean:
	@rm -f *.o
	@rm -f driver