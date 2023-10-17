all: clean driver2

driver2: Driver2.java Tetris.java Tetromino.java
	@javac -d . Driver2.java Tetris.java Tetromino.java
	@java tetris/Driver2

clean:
	@rm -rf tetris