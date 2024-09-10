import java.util.Scanner;
import java.util.concurrent.ThreadLocalRandom;

// Inheritance
public class GuessNumberGame extends Game{
    private int minNumber;
    private int maxNumber;

    public GuessNumberGame(int minNumber, int maxNumber) {
        this.minNumber = minNumber;
        this.maxNumber = maxNumber;
    }

    @Override
    protected int generateTargetNumber() {
        return ThreadLocalRandom.current().nextInt(minNumber, maxNumber + 1);
    }

    @Override
    protected int guessNumber() {
        Scanner sn = new Scanner(System.in);
        System.out.print("\nGuess the number: ");
        return sn.nextInt();
    }
}