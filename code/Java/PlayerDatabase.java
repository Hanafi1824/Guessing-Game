import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class PlayerDatabase {
    private List<Player> players = new ArrayList<>();
    private String fileName;

    public PlayerDatabase(String fileName) {
        this.fileName = fileName;
        // Ensure the file exists
        try {
            File file = new File(fileName);
            if (!file.exists()) {
                file.createNewFile();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // SINGLEPLAYER MODE:
    public void addOrUpdatePlayer(String name, int attempts) throws IOException {
        List<Player> players = readPlayersFromFile();
        boolean playerExists = false;

        for (Player player : players) {
            if (player.getName().equals(name)) {
                player.setLowestGuesses(Math.min(player.getLowestGuesses(), attempts));
                playerExists = true;
                break;
            }
        }

        if (!playerExists) {
            players.add(new Player(name, attempts));
        }

        writePlayersToFile(players, false);
    }

    // MULTIPLAYER MODE:
    public void addOrUpdatePlayer2(String name, int scores) throws IOException {
        // List<Player> players = readPlayersFromFile();
        boolean playerExists = false;

        for (Player player : players) {
            if (player.getName().equals(name)) {
                player.setHighestScore(player.getHighestScore() + scores); // Update total score
                playerExists = true;
                break;
            }
        }

        if (!playerExists) {
            players.add(new Player(name, scores));
        }

        writePlayersToFile(players, true);
    }

    public Player getPlayer(String name) throws IOException {
        List<Player> players = readPlayersFromFile();
        for (Player player : players) {
            if (player.getName().equals(name)) {
                return player;
            }
        }
        return null;
    }

    public List<Player> readPlayersFromFile() throws IOException {
        List<Player> players = new ArrayList<>();

        BufferedReader reader = new BufferedReader(new FileReader(fileName));
        String line;
        while ((line = reader.readLine()) != null) {
            String[] parts = line.split(",");
            String name = parts[0];
            int value = Integer.parseInt(parts[1]);
            players.add(new Player(name, value));
        }
        reader.close();

        players.sort(Comparator.comparingInt(Player::getLowestGuesses));

        return players;
    }

    public void writePlayersToFile(List<Player> players, boolean isMultiplayer) throws IOException {
        BufferedWriter writer = new BufferedWriter(new FileWriter(fileName));
        for (Player player : players) {
            if (isMultiplayer) {
                writer.write(player.getName() + "," + player.getHighestScore() + "\n");  // Write highest scores for multiplayer
            } else {
                writer.write(player.getName() + "," + player.getLowestGuesses() + "\n");  // Write lowest guesses for single player
            }
        }
        writer.close();
    }

    public List<Player> getTopPlayers(int count) throws IOException {
        List<Player> players = readPlayersFromFile();
    
        // Sort players by highest score (descending)
        players.sort((p1, p2) -> Integer.compare(p2.getHighestScore(), p1.getHighestScore()));
    
        // Limit to top 'count' players
        List<Player> topPlayers = new ArrayList<>();
        for (int i = 0; i < Math.min(count, players.size()); i++) {
            topPlayers.add(players.get(i));
        }
    
        return topPlayers;
    }
}