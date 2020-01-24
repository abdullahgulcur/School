import java.util.ArrayList;

public abstract class EstateSquare extends Square {

    protected int price;
    protected int rentOrFee;
    protected Player owner;

    public EstateSquare(String name, int price){
        super(name);
        this.price = price;
    }

    public int getRentOrFee() {
        return rentOrFee;
    }

    public void setRentOrFee(int rentOrFee) {
        this.rentOrFee = rentOrFee;
    }

    public Player getOwner() {
        return owner;
    }

    public void setOwner(Player owner) {
        this.owner = owner;
    }

    int getPrice() {
        return price;
    }

    public abstract void setRent();

    public void takeRentFromPlayer(ArrayList<Player> players, Player player){

        if(getOwner() != null){
            System.out.println("Owner: " + getOwner().getName()); //owner

            /* Player does not take fee from himself ;) */
            if(getOwner() != player){

                /* Player pays rent if has enough money*/
                if(player.getCash() >= getRentOrFee())
                    player.setCash(player.getCash() - getRentOrFee());
                else{
                    if(players.size() == 1){
                        System.out.println("---------Winner is "+ players.get(0).getName());
                        // stop the game
                    }
                    else
                        players.remove(player); /* Player is kicked behind because of being out of money */
                }

            }
        }
        else
            System.out.println("Owner: None");
    }
}
