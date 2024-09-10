public class Player {
    private String name;
    private int lowestGuesses;
    private int highestScore;
    private int score;

    public Player(String name, int lowestGuesses) {
        this.name = name;
        this.lowestGuesses = lowestGuesses;
    }

    public String getName() {
        return name;
    }

    public int getLowestGuesses() {
        return lowestGuesses;
    }
    
    public int getHighestScore() {
        return highestScore;
    }

    public int getScore() {
        return score;
    }

    public void setScore(int score) {
        this.lowestGuesses = score;
    }

    public void setLowestGuesses(int lowestGuesses) {
        this.lowestGuesses = lowestGuesses;
    }

    public void setHighestScore(int highestScore) {
        this.highestScore = highestScore;
    }
}
