import java.util.ArrayList;

public class TaxSquare extends Square {

    private int price;

    public TaxSquare(String name, int price){
        super(name);
        this.price = price;
    }

    public void takeTaxFromPlayer(ArrayList<Player> players, Player player){

        if(player.getCash() >= price)
            player.setCash(player.getCash() - price);
        else{
            // kick player behind
            if(players.size() == 1){
                System.out.println("---------Winner is "+ players.get(0).getName());
                // stop the game
            }
            else
                players.remove(player); /* Player is kicked behind because of being out of money */
        }

    }


}
