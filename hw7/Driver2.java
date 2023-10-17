package tetris;

import java.util.ArrayList;
import java.util.Scanner;

public class Driver2 {

	public static void main(String[] args) throws InterruptedException {

		Scanner scanner = new Scanner(System.in);
		ArrayList<Tetromino> tetrominos = new ArrayList<>();
		
		int height, width;
		char shape;
		
		System.out.println("--------- Welcome to TETRIS!! ---------");
		System.out.println("Enter the height of the board: ");
		height = scanner.nextInt();
		System.out.println("Enter the width of the board: ");
		width = scanner.nextInt();

		Tetris tetris = new Tetris(height, width);
		boolean gameOver = false;

		do {
			
			System.out.println("Enter the tetromino shape(I, O, T, J, L, S, Z  &  R for random, Q for quit): ");
			shape = scanner.next().charAt(0);
			shape = Character.toUpperCase(shape);
			while (shape != 'I' && shape != 'O' && shape != 'T' && shape != 'J' && shape != 'L' && shape != 'S' && shape != 'Z' && shape != 'R' && shape != 'Q') {
				System.out.println("Enter the tetromino shape(I, O, T, J, L, S, Z  &  R for random, Q for quit): ");
				shape = scanner.next().charAt(0);
				shape = Character.toUpperCase(shape);
			}
			if (shape == 'Q') {
				break;
			}
			if (shape == 'R') {
				shape = Tetromino.randShape();
			}

			tetrominos.add(new Tetromino(shape));
			tetris.addTetromino(tetrominos.get(tetrominos.size() - 1));
			tetris.animate(tetrominos.get(tetrominos.size() - 1));

		} while (!gameOver);
		
		tetris.addTetromino(tetrominos.get(tetrominos.size() - 1));
		tetris.animate(tetrominos.get(tetrominos.size() - 1));

	}

}
