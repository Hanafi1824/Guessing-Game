import java.io.*;
// import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Scanner;
// Polymorphism
public class Main {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);

        // GAME TITLE:
        System.out.println("       _________  __   __    _____     _____    ____");
        System.out.println("      //   _____  ||   ||  //  ___|  //  ___|  //   \\\\");
        System.out.println("     ||   |____ | ||   || ||  ___|  ||  ___|  ||_____");
        System.out.println("     ||  ______|| ||   || ||  \\\\___ ||  \\\\___        ||");
        System.out.println("      \\\\_______//  \\\\__//  \\\\______| \\\\______| \\\\____//");
        System.out.println(" __      __   __   __    __  ______     ______    _____");
        System.out.println("||\\\\  || ||   ||  ||\\\\  //| ||   _ \\   //  ___|  ||  _ \\");
        System.out.println("|| \\\\ || ||   ||  || \\\\//|| ||   __/  ||  ___|   || ____|");
        System.out.println("||  \\\\|| ||   ||  ||     || ||   _ \\  ||  \\___   ||   \\\\");
        System.out.println("||   \\\\|  \\\\__//  ||     || ||_____/   \\\\_____|  ||    \\\\");
        System.out.println("        _________  ______   ___   __   ______");
        System.out.println("       //   _____  || _ || ||\\\\  //|  //  ___|");
        System.out.println("      ||   |____ | ||___|| || \\\\//|| ||  ___|");
        System.out.println("      ||  ______|| ||   || ||     || ||  \\\\___");
        System.out.println("       \\\\_______// ||   || ||     ||  \\\\______|");

        System.out.print("\n[Reminder:]");
        System.out.print("\n|Input all commands in the command section.");
        System.out.print("\n|Type [y] or [n] for other prompts outside the game.");
        
        //Main menu:
        System.out.println("\n\n>> Start? Enter [Y].");
        System.out.print("\n<< Command: ");
        char start = sc.next().charAt(0);
        start = Character.toUpperCase(start);
        
        while(start == 'Y'){
            System.out.print("\033[H\033[2J");//clear output
            String name;

            // MENU SECTION:
            System.out.println("============ GUESS NUMBER GAME ================");
            System.out.println("[0] Game rules.");
            System.out.println("[1] Start the game.");
            System.out.println("[2] View leaderboard.");
            System.out.println("[3] Exit the game.");
            System.out.print("\n<< Command: ");
            int command = sc.nextInt();

            // GAME RULES SECTION:
            if (command == 0){
                int rules;
                System.out.print("\033[H\033[2J");//clear output
                System.out.println("Select LeaderBoard Type:");
                System.out.println("[1] Solo Challenge: Face the computer.");
                System.out.println("[2] Battle mode: Compete with friends.");
                System.out.print("\n<< Command: ");
                rules = sc.nextInt();
                System.out.print("\033[H\033[2J");//clear output
                System.out.println("============================== GAME RULES ====================================");

                // SINGLE PLAYER RULES:
                if (rules == 1){
                    System.out.println("<[                        Solo Challenge Rules                              ]>");
                    System.out.print("[1] Guess a number based on the difficulty mode.");
                    System.out.print("\n[2] Fewer attempts means a higher score.");
                    System.out.print("\n[3] Match the computer's number to win.");
                    System.out.print("\n[4] Follow the computer's hints to succeed.");
                    System.out.print("\n\n>> Continue?");
                    System.out.print("\n<< Command: ");
                    start = sc.next().charAt(0);
                    start = Character.toUpperCase(start);
                }

                // MULTIPLAYER RULES:
                else if (rules == 2){
                    System.out.println("<[                          Battle Mode Rules                               ]>");
                    System.out.print("[1] Guess a number based on the chosen levels.");
                    System.out.print("\n[2] Earn points for guessing the target number before others.");
                    System.out.print("\n[3] Score increases with each correct guess.");
                    System.out.print("\n[4] Gain 10 points per round.");
                    System.out.print("\n\n>> Continue?");
                    System.out.print("\n<< Command: ");
                    start = sc.next().charAt(0);
                    start = Character.toUpperCase(start);
                }
            }

            // GAME START SECTION:
            if (command == 1){
                int mode;
                System.out.print("\033[H\033[2J");//clear output
                System.out.println("Choose Your Gameplay:");
                System.out.println("[1] Solo Challenge: Face the computer.");
                System.out.println("[2] Battle mode: Compete with friends.");
                System.out.print("\n<< Command: ");
                mode = sc.nextInt();
                
                // SINGLEPLAYER MODE:
                if (mode == 1){
                    int level;
                    Game game = null;
                    System.out.print("\033[H\033[2J");//clear output
                    System.out.println("What's your name my friend?");
                    System.out.print("\n<< Command: ");
                    name = sc.next();

                    // SELECT DIFFICULTY:
                    System.out.println("\nSelect Gameplay Difficulty:");
                    System.out.println("[1] Easy mode: Guess between 1 and 50.");
                    System.out.println("[2] Normal mode: Guess between 1 and 100.");
                    System.out.println("[3] Extreme mode: Guess between 1 and 1000.");
                    System.out.print("\n<< Command: ");
                    level = sc.nextInt();

                    if (level == 1){
                        System.out.print("\033[H\033[2J");//clear output
                        System.out.println("<[        Easy mode         ]>");
                        game = new GuessNumberGame(1, 50);
                    } else if (level == 2){
                        System.out.print("\033[H\033[2J");//clear output
                        System.out.println("<[        Normal mode         ]>");
                        game = new GuessNumberGame(1, 100);
                    } else if (level == 3){
                        System.out.print("\033[H\033[2J");//clear output
                        System.out.println("<[        Extreme mode         ]>");
                        game = new GuessNumberGame(1, 1000);
                    }
                    System.out.println("\nAre you ready? Good luck!");
                    System.out.print("<< Command: ");
                    start = sc.next().charAt(0);
                    start = Character.toUpperCase(start);
                    
                    if (start == 'Y'){
                        System.out.print("\033[H\033[2J");//clear output
                        System.out.println("\n============ GAME START!! ================");
                        game.startGame();

                        PlayerDatabase playerDatabase = new PlayerDatabase("SinglePlayerGame.txt");
                        playerDatabase.addOrUpdatePlayer(name, game.numberOfGuesses);
                        System.out.println("Player name: " + playerDatabase.getPlayer(name).getName());
                        
                        System.out.println("\nPlay again?");
                        System.out.println(">> Enter [Y] to continue.");
                        System.out.println(">> Enter [N] to exit.");
                        System.out.print("\n<< Command: ");
                        start = sc.next().charAt(0);
                        start = Character.toUpperCase(start);
                    }
                }

                // MULTIPLAYER MODE:
                else if (mode == 2){
                    String player1, player2;
                    Game game = null;
                    int rounds;
                    System.out.print("\033[H\033[2J");//clear output
                    System.out.println("Enter your name to begin your challenge!");
                    System.out.println("\nPlayer 1:");
                    System.out.print("<< Command: ");
                    player1 = sc.next();
                    System.out.println("\nPlayer 2:");
                    System.out.print("<< Command: ");
                    player2 = sc.next();

                    // SET GAMEPLAY ROUND SETTINGS:
                    System.out.print("\033[H\033[2J");//clear output
                    System.out.println("\nChoose your challenge level (number of rounds):");
                    System.out.print("\n<< Command: ");
                    rounds = sc.nextInt();

                    PlayerDatabase multiplayerDatabase = new PlayerDatabase("MultiplayerGame.txt");
                    System.out.print("\033[H\033[2J");//clear output
                    String winner = "";
                    // int score = 10;  // Points per win
                    for (int i = 0; i < rounds; i++) {
                        System.out.println("\n============ GAME START!! ================");
                        System.out.println("          <[   Round " + (i + 1) + "    ]>");
                        game = new GuessNumberGame(1, 50);
                        // score = score + 10;
                        winner = game.startGame2(player1, player2);

                        if (winner != null) {
                            multiplayerDatabase.addOrUpdatePlayer2(winner, 10);
                            System.out.println("Player name: " + multiplayerDatabase.getPlayer(winner).getName());
                        }
                    }

                    System.out.println("\nPlay again?");
                    System.out.println(">> Enter [Y] to continue.");
                    System.out.println(">> Enter [N] to exit.");
                    System.out.print("\n<< Command: ");
                    start = sc.next().charAt(0);
                    start = Character.toUpperCase(start);
                }
            }

            // LEADERBOARD SECTION:
            if (command == 2){
                int board;
                System.out.print("\033[H\033[2J");//clear output
                System.out.println("Select LeaderBoard Type:");
                System.out.println("[1] Solo Challenge: Face the computer.");
                System.out.println("[2] Battle mode: Compete with friends.");
                System.out.print("\n<< Command: ");
                board = sc.nextInt();
                System.out.print("\033[H\033[2J");//clear output
                System.out.println("====================== LEADERBOARD ========================");
                
                // SINGLEPLAYER LEADERBOARD:
                if (board == 1){
                    PlayerDatabase database = new PlayerDatabase("SinglePlayerGame.txt");  // Ensure correct file for single player
                    List<Player> players = database.readPlayersFromFile();

                    // Sort players by lowest guess attempts (ascending)
                    players.sort(Comparator.comparingInt(Player::getLowestGuesses));

                    // Display top 3 players with the lowest guesses
                    System.out.println("<[  Top 3 Players with Lowest Guesses in Solo Challenge  ]>");
                    for (int i = 0; i < Math.min(3, players.size()); i++) {
                        Player player = players.get(i);
                        System.out.println((i + 1) + ". " + player.getName() + ": " + player.getLowestGuesses());
                    }
                }
                
                // MULTIPLAYER LEADERBOARD:
                else if (board == 2){
                    PlayerDatabase multiplayerDatabase = new PlayerDatabase("MultiplayerGame.txt");
                    List<Player> topPlayers = multiplayerDatabase.getTopPlayers(3);

                    System.out.println("<[    Top 3 Players with Highest Scores in Battle Mode    ]>");
                    for (int i = 0; i < Math.min(3, topPlayers.size()); i++) {
                        Player player = topPlayers.get(i);
                        System.out.println((i + 1) + ". " + player.getName() + ": " + player.getHighestScore());
                    }
                }
                
                System.out.println("\nBack to main menu?");
                System.out.print("<< Command: ");
                start = sc.next().charAt(0);
                start = Character.toUpperCase(start); 
            }
            
            // EXIT GAME SECTION:
            if (command == 3){
                System.out.print("\033[H\033[2J");//clear output
                System.out.println("Do you want to exit?");
                System.out.println(">> Enter [Y] to continue.");
                System.out.println(">> Enter [N] to exit.");
                System.out.print("\n<< Command: ");
                start = sc.next().charAt(0);
                start = Character.toUpperCase(start);
            }
            System.out.print("\033[H\033[2J");//clear output
            System.out.println("You are now leaving the game.");
            System.out.println("Thanks for playing, see you again soon!");
        }
        sc.close();
    }
}