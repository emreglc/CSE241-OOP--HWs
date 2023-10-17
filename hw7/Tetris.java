package tetris;

import java.util.Random;

/**
 * 
 * @author emre
 */

public class Tetris {

	private char[][] board;
	private final int height;
	private final int width;
	
	/**
	 * constructor
	 * @param height height of the board
	 * @param width width of the board
	 */
	public Tetris(int height, int width){
		this.height = height;
		this.width = width;
		board = new char[height][width];
		for(int i = 0; i < height; i++)
			for(int j = 0; j < width; j++)
				board[i][j] = ' ';
		for(int i = 0; i < width; i++)
			board[height - 1][i] = '#';
	}
	
	/**
	 * default constructor which creates a board of size 20, 40
	 */
	public Tetris(){
		this(20, 40);
	}
	
	/**
	 * draws the game board on terminal
	 */
	public void drawBoard(){
		
		for(int i = 0; i < width + 2; i++) System.out.print("#");
		System.out.println();
		
		for (char[] row : board){
			System.out.print("#");
			for (char col : row)
				System.out.print(col);
			System.out.println("#");
		}
		
		System.out.println();
			
	}
	
	/**
	 * Adds the given tetromino to the board
	 * @param tetro tetris piece(tetromino)
	 */
	public void addTetromino(Tetromino tetro){
		
		tetro.setxPos((width - tetro.getTetro()[0].length)/2);
		for (int i = 0; i < tetro.getTetro().length; i++)
			System.arraycopy(tetro.getTetro()[i], 0, board[i], tetro.getxPos(), tetro.getTetro()[0].length);
		
	}
	
	/**
	 * removes the tetromino at the top
	 * @param tetro tetris piece(tetromino)
	 */
	public void removeTetromino(Tetromino tetro){
		
		for (int i = 0; i < tetro.getTetro().length; i++)
			for (int j = tetro.getxPos(); j < tetro.getTetro()[0].length + tetro.getxPos(); j++)
				board[i][j] = ' ';
		
	}
	
	/**
	 * moves the tetromino horizontally to given position at the top row
	 * @param tetro tetris piece(tetromino)
	 * @param x index of x-axis where to move tetromino at the top horizontally
	 */
	public void moveTetromino(Tetromino tetro, int x){
		
		for (int i = 0; i < tetro.getTetro().length; i++)
			for (int j = 0; j < tetro.getTetro()[0].length; j++)
				board[i][j + x] = tetro.getTetro()[i][j];
		
	}
	
	/**
	 * animates the tetromino falling down to the bottom of the board
	 * @param tetro tetris piece(tetromino)
	 * @throws InterruptedException exception needed for sleep function
	 */
	public void animate(Tetromino tetro) throws InterruptedException{
		
		Random rand = new Random();
		
		int count;
		
		drawBoard();
		removeTetromino(tetro);
		
		count = rand.nextInt(4);
		for (int i = 0; i <= count; i++) tetro.rotate("right");
		tetro.setxPos((width - tetro.getTetro()[0].length)/2);
		count = rand.nextInt(width - tetro.getTetro()[0].length);
		System.out.println(count);
		moveTetromino(tetro, count);
		tetro.setxPos(count);
		
		drawBoard();
		
		while (canFall(tetro)) {
			
			Thread.sleep(50);
			
			for (int i = tetro.getyPos(); i < tetro.getTetro().length + tetro.getyPos(); i++)
				for (int j = tetro.getxPos(); j < tetro.getTetro()[0].length + tetro.getxPos(); j++)
					board[i][j] = ' ';

			tetro.setyPos(tetro.getyPos() + 1);

			for (int i = 0; i < tetro.getTetro().length; i++)
				for (int j = 0; j < tetro.getTetro()[0].length; j++)
					if(board[i+tetro.getyPos()][j+tetro.getxPos()] == ' ')
						board[i+tetro.getyPos()][j+tetro.getxPos()] = tetro.getTetro()[i][j];
			
			drawBoard();
			
		}
		
		Thread.sleep(50);
		
	}
	
	/**
	 * checks if the tetromino can be lowered one tile, returns true if so, false otherwise
	 * @param tetro tetris piece(tetromino)
	 * @return boolean whether tetromino can be lowered one tile or not
	 */
	public boolean canFall(Tetromino tetro){
		
		for (int i = 0, c = 0; i < tetro.getTetro()[0].length; i++)
		{
			if (tetro.getTetro()[tetro.getTetro().length-1][i] == ' ')
			{
				c++;
			}
			else if(board[tetro.getyPos() + tetro.getTetro().length][tetro.getxPos()+i] == ' ' &&
					board[tetro.getyPos() + tetro.getTetro().length-1][tetro.getxPos()+i] == tetro.getTetro()[tetro.getTetro().length-1][i]){
				c++;
			}
			if (c == tetro.getTetro()[0].length)
				return true;
		}

		return false;

	}
	
}
