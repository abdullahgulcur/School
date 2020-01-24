import java.util.ArrayList;

public class CommunityChestSquare extends Square {

    //public static String [] cardNames;

    public String name;

    public CommunityChestSquare(String name){
        super(name);
    }

    public void incomeTaxRefund(Player player){

        int money = 20;
        player.setCash(player.getCash() + money);
    }

    public void fromSaleOfStock(Player player){

        int money = 45;
        player.setCash(player.getCash() + money);
    }

    public void secondPrizeInABeautyContest(Player player){

        int money = 10;
        player.setCash(player.getCash() + money);
    }

    public void getOutOfJail(Player player, JailSquare jailSquare){

        if(player.isInJail())
            jailSquare.removePlayerFromJail(player);
    }

    public void collectFiftyDollarsFromPlayers(ArrayList<Player> players, Player player){

        int collectedMoney = 150;

        for(int i = 0; i < players.size(); i++){

            if(players.get(i) != player) {

                if (player.getCash() >= collectedMoney)
                    players.get(i).setCash(players.get(i).getCash() - collectedMoney);
                else {
                    if (players.size() == 1) {
                        System.out.println("---------Winner is " + players.get(0).getName());
                        // stop the game
                    } else
                        players.remove(player); /* Player is kicked behind because of being out of money */

                }

            }
        }
    }

    public void bankErrorInYourFavor(Player player){

        int money = 10;
        player.setCash(player.getCash() + money);
    }

    public void advanceToGo(Player player){

        player.getPiece().setLocation(0);
        player.setCash(player.getCash() + 200);
    }

    public void lifeInsuranceMatures(ArrayList<Player> players, Player player){

        int money = 100;

        if (player.getCash() >= money)
            player.setCash(player.getCash() - money);
        else {
            if (players.size() == 1) {
                System.out.println("---------Winner is " + players.get(0).getName());
                // stop the game
            } else
                players.remove(player); /* Player is kicked behind because of being out of money */

        }
    }

    public void goToJail(Player player, JailSquare jailSquare){

        int jailLocation = 9;

        if(!player.isInJail()){
            player.getPiece().setLocation(jailLocation);
            jailSquare.putPlayerIntoJail(player);
        }
    }

    public void payHospitalHundredDollars(ArrayList<Player> players, Player player){

        int money = 100;

        if (player.getCash() >= money)
            player.setCash(player.getCash() - money);
        else {
            if (players.size() == 1) {
                System.out.println("---------Winner is " + players.get(0).getName());
                // stop the game
            } else
                players.remove(player); /* Player is kicked behind because of being out of money */

        }
    }

    public void paySchoolTaxOfHundredFiftyDollars(ArrayList<Player> players, Player player){

        int money = 150;

        if (player.getCash() >= money)
            player.setCash(player.getCash() - money);
        else {
            if (players.size() == 1) {
                System.out.println("---------Winner is " + players.get(0).getName());
                // stop the game
            } else
                players.remove(player); /* Player is kicked behind because of being out of money */

        }
    }

    public void youAreAssertedForStreetRepairs(Board boardObject,ArrayList<Player> players, Player player){

        int houseCount = 0;
        int hotelCount = 0;

        Square[] square = boardObject.getBoard();

        for(int i = 0; i < square.length; i++){

            if(square[i] instanceof PropertySquare){
                if(((PropertySquare)square[i]).getOwner() == player){
                    houseCount = ((PropertySquare)square[i]).getHouseCount();
                    hotelCount = ((PropertySquare)square[i]).getHotelCount();
                }

            }

        }

        int money = 40 * houseCount + 115 * hotelCount;

        if (player.getCash() >= money)
            player.setCash(player.getCash() - money);
        else {
            if (players.size() == 1) {
                System.out.println("---------Winner is " + players.get(0).getName());
                // stop the game
            } else
                players.remove(player); /* Player is kicked behind because of being out of money */

        }
    }

    public void youInheritHundredDollars(Player player){

        int money = 100;
        player.setCash(player.getCash() + money);
    }

    public void xMasFundMatures(Player player){

        int money = 100;
        player.setCash(player.getCash() + money);
    }

    public void doctorsFeePayFiftyDollars(ArrayList<Player> players, Player player){

        int money = 50;

        if (player.getCash() >= money)
            player.setCash(player.getCash() - money);
        else {
            if (players.size() == 1) {
                System.out.println("---------Winner is " + players.get(0).getName());
                // stop the game
            } else
                players.remove(player); /* Player is kicked behind because of being out of money */

        }
    }

    public void receiveForServicesTwentyFiveDollars(ArrayList<Player> players, Player player){

        int money = 25;

        if (player.getCash() >= money)
            player.setCash(player.getCash() - money);
        else {
            if (players.size() == 1) {
                System.out.println("---------Winner is " + players.get(0).getName());
                // stop the game
            } else
                players.remove(player); /* Player is kicked behind because of being out of money */

        }
    }



}
