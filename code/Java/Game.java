// Abstraction and Encapsulation
import java.util.Scanner;

public abstract class Game {
    protected int numberOfGuesses = 0;
    protected int totalscore = 0;

    public void startGame() { // Single player mode
        int targetNumber = generateTargetNumber();
        while (true) {
            int guessedNumber = guessNumber();
            if (guessedNumber > targetNumber) {
                System.out.println("COMPUTER: <Too high>");
            } else if (guessedNumber < targetNumber) {
                System.out.println("COMPUTER: <Too low>");
            } else {
                System.out.print("\033[H\033[2J");//clear output
                System.out.println("\n+++++++++++++ GAME COMPLETED! ++++++++++++++");
                System.out.println("\nCongratulations, my friend!");
                break;
            }
            numberOfGuesses++;
        }
        System.out.println("You guessed it in about " + numberOfGuesses + " attempt!");
    }

    public String startGame2(String player1, String player2) { // multiplayer mode
        int targetNumber = generateTargetNumber();
        Scanner sn = new Scanner(System.in);
        while (true) {
            // PLAYER 1:
            System.out.print("\n" + player1 + ", guess the number: ");
            int guessedNumber1 = sn.nextInt();
            if (guessedNumber1 > targetNumber) {
                System.out.println("COMPUTER: <Too high>");
            } else if (guessedNumber1 < targetNumber) {
                System.out.println("COMPUTER: <Too low>");
            } else {
                System.out.print("\033[H\033[2J");//clear output
                System.out.println("\n+++++++++++++ GAME COMPLETED! ++++++++++++++");
                System.out.println("\nCongratulations, " + player1 + "!");
                System.out.println("<10 points for player 1!>");
                return player1;
            }

            // PLAYER 2:
            System.out.print("\n" + player2 + ", guess the number: ");
            int guessedNumber2 = sn.nextInt();
            if (guessedNumber2 > targetNumber) {
                System.out.println("COMPUTER: <Too high>");
            } else if (guessedNumber2 < targetNumber) {
                System.out.println("COMPUTER: <Too low>");
            } else {
                System.out.print("\033[H\033[2J");//clear output
                System.out.println("\n+++++++++++++ GAME COMPLETED! ++++++++++++++");
                System.out.println("\nCongratulations, " + player2 + "!");
                System.out.println("<10 points for player 2!>");
                return player2;
            }
        }
    }

    protected abstract int generateTargetNumber();

    protected abstract int guessNumber();

    public int getNumberOfGuesses() {
        return numberOfGuesses;
    }

    public int getTotalScore() {
        return totalscore;
    }
}
