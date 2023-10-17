package tetris;

import java.util.Arrays;
import java.util.Random;

/**
 * 
 * @author emre
 */

public class Tetromino {

	private char[][] tetro;
	private int xPos;
	private int yPos;

	/**
	 * constructor
	 * @param shape tetromino shape as char to be created
	 */
	public Tetromino(char shape) {

		init(shape);
		yPos = 0;
		
	}

	/**
	 * getter for the shape array
	 * @return 2d shape char array
	 */
	public char[][] getTetro() {
		return Arrays.copyOf(tetro, tetro.length);
	}

	/**
	 * returns the position of the tetromino horizontally
	 * @return xPos variable
	 */
	public int getxPos() {
		return xPos;
	}

	/**
	 * sets the position of the tetromino horizontally
	 * @param xPos xPos variable
	 */
	public void setxPos(int xPos) {
		this.xPos = xPos;
	}

	/**
	 * returns the position of the tetromino vertically
	 * @return yPos variable
	 */
	public int getyPos() {
		return yPos;
	}

	/**
	 * sets the position of the tetromino vertically
	 * @param yPos yPos variable
	 */
	public void setyPos(int yPos) {
		this.yPos = yPos;
	}
	
	/**
	 * rotates the tetromino shape to the left or right respect to given parameter
	 * @param dir direction to rotate
	 */
	public void rotate(String dir){
		
		if("right".equals(dir))
		{
			char temp[][] = new char[this.tetro[0].length][this.tetro.length];

			for (int row = 0; row < this.tetro.length; row++)
			{
				for (int col = 0; col < this.tetro[row].length; col++)
				{
					temp[col][row] = this.tetro[row][col];
				}

			}
			for (int row = 0; row < temp.length; row++)
			{
				for (int col = 0; col < temp[row].length/2; col++)
				{
					char dump = temp[row][col];
					temp[row][col] = temp[row][temp[row].length - col - 1];
					temp[row][temp[row].length - col - 1] = dump;
				}

			}

			this.tetro = temp;

		}
		if("left".equals(dir))
		{

			for (int row = 0; row < this.tetro.length; row++)
			{
				for (int col = 0; col < this.tetro[row].length/2; col++)
				{
					char dump = this.tetro[row][col];
					this.tetro[row][col] = this.tetro[row][this.tetro[row].length - col - 1];
					this.tetro[row][this.tetro[row].length - col - 1] = dump;
				}

			}

			char temp[][] = new char[this.getTetro()[0].length][this.getTetro().length];

			for (int row = 0; row < this.getTetro().length; row++)
			{
				for (int col = 0; col < this.getTetro()[row].length; col++)
				{
					temp[col][row] = this.getTetro()[row][col];
				}

			}

			this.tetro = temp;

		}
		
	}
	
	/**
	 * initializes the tetromino array
	 * @param shape tetromino shape
	 */
	public final void init(char shape){
		switch (shape) {
			case 'I' ->
				tetro = new char[][]{
					{'I', 'I', 'I', 'I'}
				};
			case 'O' ->
				tetro = new char[][]{
					{'O', 'O'},
					{'O', 'O'}
				};
			case 'T' ->
				tetro = new char[][]{
					{'T', 'T', 'T'},
					{' ', 'T', ' '}
				};
			case 'J' ->
				tetro = new char[][]{
					{' ', 'J'},
					{' ', 'J'},
					{'J', 'J'}
				};
			case 'L' ->
				tetro = new char[][]{
					{'L', ' '},
					{'L', ' '},
					{'L', 'L'}
				};
			case 'S' ->
				tetro = new char[][]{
					{' ', 'S', 'S'},
					{'S', 'S', ' '}
				};
			case 'Z' ->
				tetro = new char[][]{
					{'Z', 'Z', ' '},
					{' ', 'Z', 'Z'}
				};
			case 'R' ->
				init(randShape());
		}
	}
	
	/**
	 * returns a random shape
	 * @return random shape as char
	 */
	public static char randShape(){
		
		Random random = new Random();
		
		int rand = random.nextInt(7) + 1;
		
		switch (rand)
		{
		case 1 -> {
			return 'I';
			}
		case 2 -> {
			return 'O';
			}
		case 3 -> {
			return 'T';
			}
		case 4 -> {
			return 'J';
			}
		case 5 -> {
			return 'L';
			}
		case 6 -> {
			return 'S';
			}
		case 7 -> {
			return 'Z';
			}						
		}
		return 'Q';		
	}

}
