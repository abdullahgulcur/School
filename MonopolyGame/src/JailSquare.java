import java.util.ArrayList;

public class JailSquare extends Square {

    private ArrayList<Player> players;

    public JailSquare(String name){

        super(name);
        players = new ArrayList<Player>();
    }

    public void putPlayerIntoJail(Player player){

        player.setInJail(true);
        players.add(player);
    }

    public void removePlayerFromJail(Player player){

        player.setCountForJail(0);
        player.setInJail(false);
        players.remove(player);
    }

    public ArrayList<Player> getPlayers() {
        return players;
    }

    public void setPlayers(ArrayList<Player> players) {
        this.players = players;
    }
}
