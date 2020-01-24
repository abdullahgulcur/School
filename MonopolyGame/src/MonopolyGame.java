import java.io.IOException;

import java.io.FileReader;
import java.util.Iterator;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.*;

import java.util.ArrayList;

public class MonopolyGame {

    private int gameCycle;
    private ArrayList<Player> players;
    private ArrayList<Piece> pieces;
    private Board boardObject;
    private Square[] board;

    private int tempLocation = 0;

    public MonopolyGame(){

        gameCycle = 0;
        pieces =  new ArrayList<Piece>();
        players = new ArrayList<Player>();
        boardObject = new Board();
        board = boardObject.getBoard();
    }

    public static void play(){

        MonopolyGame monopolyGame = new MonopolyGame();
        monopolyGame.run();
    }

    private void run(){

        /*Project takes all data in here*/
        readJsonFile();

        /* Player are aligned relative to their sum of face of dices */
        lineUpPlayers();

        /* each cycle */
        int cycleCounter= 0;

        /*Project runs*/
        while(true){

            Player player = players.get(gameCycle % players.size());

            System.out.println("------");

            tempLocation = player.getPiece().getLocation();

            if(gameCycle % players.size() == 0){
                cycleCounter++;
            }

            /* Increases jail count for each cycle */
            jailMechanism(player);

            /* Initial information */
            printInitialStatus(player, cycleCounter);

            /* Dice rolling */
            rollDice(player);

            /* Updates player */
            updatePlayer(player);

            printLastInformation(player);

            /* Prints last status */
            if(gameCycle % players.size() == players.size() - 1)
                printLastStatusOfPlayers();


            if(players.size() == 1){
                System.out.println("---------Winner is "+ players.get(0).getName());
                break;
            }

            gameCycle++;
        }
    }

    private String getTypeOfSquare(Square sq){

        if(sq instanceof JailSquare)
            return "Jail Square";
        else if(sq instanceof GoSquare)
            return "Go Square";
        else if(sq instanceof RailRoadSquare)
            return "RailRoad Square";
        else if(sq instanceof TaxSquare)
            return "Tax Square";
        else if(sq instanceof  PropertySquare)
            return "Property Square";
        else if(sq instanceof  CommunityChestSquare)
            return "CommunityChest Square";
        else if(sq instanceof  ChanceSquare)
            return "Chance Square";
        else if(sq instanceof  UtilitySquare)
            return "Utility Square";
        else if(sq instanceof  FreeParkingSquare)
            return "Free Parking Square";
        else if(sq instanceof  GoToJailSquare)
            return "Go to Jail Square";

        return "None";
    }

    private void readJsonFile(){

        Object obj = null;
        try {
            obj = new JSONParser().parse(new FileReader("playersData.json"));
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ParseException e) {
            e.printStackTrace();
        }

        // typecasting obj to JSONObject
        JSONObject jo = (JSONObject) obj;

        JSONArray ja = (JSONArray) jo.get("players");
        Iterator itr2 = ja.iterator();

        int count = 0;

        while (itr2.hasNext())
        {
            count++;
            Iterator<Map.Entry> itr1 = ((Map) itr2.next()).entrySet().iterator();
            Map.Entry pair;
            String playerName = "";
            String piece = "";

            while (itr1.hasNext()) {

                pair = itr1.next();
                if(pair.getKey().equals("playerName"))
                    playerName = pair.getValue().toString();
                else if(pair.getKey().equals("piece"))
                    piece = pair.getValue().toString();
            }
            players.add(new Player(playerName, new Piece(piece)));
            //pieces.add(new Piece())
        }
    }

    private void lineUpPlayers(){

        int initialDice0 = 0;
        int initialDice1 = 0;
        int initialSum = 0;

        for(int i = 0; i < players.size(); i++){

            initialDice0 = Dice.getRandomDiceFaces()[0];
            initialDice1 = Dice.getRandomDiceFaces()[1];
            initialSum = initialDice0 + initialDice1;

            System.out.println(players.get(i).getName() + " is rolling dice initially... Dice 1: " + initialDice0 +
                    " Dice 2: " + initialDice1 + " Total: " + initialSum);
            players.get(i).setInitialDiceTotal(initialSum);
        }

        int n = players.size();
        for (int i = 0; i < n-1; i++)
            for (int j = 0; j < n-i-1; j++)
                if (players.get(j).getInitialDiceTotal() < players.get(j + 1).getInitialDiceTotal())
                {
                    Player temp = players.get(j);
                    players.set(j, players.get(j + 1));
                    players.set(j + 1, temp);
                }
    }

    private void printLastInformation(Player player){

        if(board[tempLocation] instanceof PropertySquare){

            if(((PropertySquare)board[tempLocation]).getOwner() != null)
                System.out.println("Rent / Fee: " + ((PropertySquare)board[tempLocation]).getRentOrFee());
            else
                System.out.println("Rent / Fee: None");
        }else if(board[tempLocation] instanceof RailRoadSquare){
            if(((RailRoadSquare)board[tempLocation]).getOwner() != null)
                System.out.println("Rent / Fee: " + ((RailRoadSquare)board[tempLocation]).getRentOrFee());
            else
                System.out.println("Rent / Fee: None");
        }
        System.out.println("Player Money: " + player.getCash());
    }

    private void rollDice(Player player){

        if(!player.isInJail()){
            int die0 = Dice.getRandomDiceFaces()[0];
            int die1 = Dice.getRandomDiceFaces()[1];
            int sum = die0 + die1;

            System.out.println("Dice Rolling... Dice 1: " + die0 + " Dice 2: " + die1 + " Total: " + sum); //owner

            tempLocation += sum;
            tempLocation = tempLocation % boardObject.getBoard().length;

            player.getPiece().setLocation(tempLocation);
        }else
            System.out.println("Player is in jail... Cannot roll dice!");


        System.out.println("New Location: Square " + player.getPiece().getLocation());
        System.out.println("Square Name: " + board[tempLocation].getName());
        System.out.println("Square Type: " + getTypeOfSquare(board[tempLocation]));
    }

    private void updatePlayer(Player player){

        /*Jail Check*/
        if(board[tempLocation] instanceof JailSquare)
            if(!player.isInJail())
                ((JailSquare)board[tempLocation]).putPlayerIntoJail(player);

        if(board[tempLocation] instanceof GoToJailSquare)
            ((GoToJailSquare)board[tempLocation]).putPlayerIntoJailSquare(player);

        /* Takes taxes from player */
        if(board[tempLocation] instanceof TaxSquare)
            ((TaxSquare)board[tempLocation]).takeTaxFromPlayer(players, player);



        /*------- Decisions --------*/

        /* If player money is enough and decide to buy a property*/
        if(board[tempLocation] instanceof PropertySquare)
            player.buyProperty((PropertySquare)board[tempLocation]);

        /* If player wants to buy house or hotel */
        if(board[tempLocation] instanceof PropertySquare)
            boardObject.decideBuyHouseOrHotel(tempLocation, player);

        /* If player money is enough and decide to buy a railroad*/
        if(board[tempLocation] instanceof RailRoadSquare)
            player.buyRailRoad((RailRoadSquare)board[tempLocation]);

        /*------ Decisions ------*/


        /* Square takes rent from player and gives it to its owner */
        if(board[tempLocation] instanceof PropertySquare)
            ((PropertySquare)board[tempLocation]).takeRentFromPlayer(players, player);
        else if(board[tempLocation] instanceof RailRoadSquare)
            ((RailRoadSquare)board[tempLocation]).takeRentFromPlayer(players, player);

    }

    private void jailMechanism(Player player){

        if(player.isInJail()){
            player.setCountForJail(player.getCountForJail() + 1);
            if(player.getCountForJail() == 3)
                ((JailSquare)board[tempLocation]).removePlayerFromJail(player);
        }
    }

    private void printInitialStatus(Player player, int cycleCounter){

        System.out.println("Name: " + player.getName() + " Piece: " + player.getPiece().getPieceName());
        System.out.println("Cycle Counter: " + cycleCounter);
        System.out.println("Turn Counter: " + (gameCycle % players.size() + 1));
        System.out.println("User Location: Square " + tempLocation);
        System.out.println("Square Name: " + board[tempLocation].getName());
        System.out.println("Square Type: " + getTypeOfSquare(board[tempLocation]));

        if(board[tempLocation] instanceof PropertySquare){
            if(((PropertySquare)board[tempLocation]).getOwner() != null)
                System.out.println("Owner: " + ((PropertySquare)board[tempLocation]).getOwner().getName()); //owner
        }
        else if(board[tempLocation] instanceof RailRoadSquare){
            if(((RailRoadSquare)board[tempLocation]).getOwner() != null)
                System.out.println("Owner: " + ((RailRoadSquare)board[tempLocation]).getOwner().getName()); //owner
        }
        else
            System.out.println("Owner: None");


        if(board[tempLocation] instanceof PropertySquare)
            System.out.println("Hotels: " + ((PropertySquare)board[tempLocation]).getHotelCount() + " Houses: " + ((PropertySquare)board[tempLocation]).getHouseCount());

    }

    private void printLastStatusOfPlayers(){

        for(int i = 0; i < players.size(); i++){
            System.out.println("---------------");
            System.out.println("Player: " + players.get(i).getName());
            System.out.println("Location: " + players.get(i).getPiece().getLocation());
            System.out.println("Balance: " + players.get(i).getCash());
            System.out.println("Number of Properties: " + players.get(i).getTotalAssets());
            System.out.println("Value of Properties: " + players.get(i).getTotalValuesOfProperties(boardObject));
            System.out.println("---------------");
        }

    }


}
