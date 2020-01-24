/* This class represents a monopoly game board.
 * After generating a new board object, you can call function "getBoard".
 * "getBoard" function returns an array of Square objects which is going to be used as game board
 * */
class Board {

    private Square[] board;

    public Board() {
        this.setBoard();
    }

    private void setBoard() {

        Square go = new GoSquare("Go");
        Square communityChest = new CommunityChestSquare("Community Chest");
        Square chance = new ChanceSquare("Chance");
        Square jail = new JailSquare("Jail");
        Square freeParking = new FreeParkingSquare("Free Parking");
        Square goToJail = new GoToJailSquare("Go to Jail", (JailSquare) jail);

        Square incomeTax = new TaxSquare("incomeTax", 200);
        Square luxuryTax = new TaxSquare("luxuryTax", 100);

        Square readingRailroad = new RailRoadSquare("readingRailroad", 200);
        Square pennsylvaniaRailroad = new RailRoadSquare("pennsylvaniaRailroad", 200);
        Square boRailroad = new RailRoadSquare("boRailroad", 200);
        Square shortLine = new RailRoadSquare("shortLine", 200);

        Square electricCompany = new UtilitySquare("Electric Company",150);
        Square waterWorks = new UtilitySquare("Water Works",150);

        Square mediterraneanAvenue = new PropertySquare("brown", "mediterraneanAvenue",60,50);
        Square balticAvenue = new PropertySquare("brown","balticAvenue", 60,50);

        Square orientalAvenue = new PropertySquare("gray","orientalAvenue", 100,50);
        Square vermontAvenue = new PropertySquare("gray",  "vermontAvenue", 100,50);
        Square connecticutAvenue = new PropertySquare("gray",  "connecticutAvenue", 120,50);

        Square stCharlesPlace = new PropertySquare("purple",  "stCharlesPlace", 140,100);
        Square statesAvenue = new PropertySquare("purple",  "statesAvenue", 140,100);
        Square virginiaAvenue = new PropertySquare("purple",  "virginiaAvenue", 160,100);

        Square stJamesPlace = new PropertySquare("orange",  "stJamesPlace", 180,100);
        Square tennesseeAvenue = new PropertySquare("orange",  "tennesseeAvenue", 180,100);
        Square newYorkAvenue = new PropertySquare("orange",  "newYorkAvenue", 200,100);

        Square kentuckyAvenue = new PropertySquare("red",  "kentuckyAvenue", 220,150);
        Square indianaAvenue = new PropertySquare("red",  "indianaAvenue", 220,150);
        Square illinoisAvenue = new PropertySquare("red",  "illinoisAvenue", 240,150);

        Square atlanticAvenue = new PropertySquare("yellow",  "atlanticAvenue", 260,150);
        Square ventnorAvenue = new PropertySquare("yellow",  "ventnorAvenue", 260,150);
        Square marvinGardens = new PropertySquare("yellow",  "marvinGardens", 280,150);

        Square pacificAvenue = new PropertySquare("green",  "pacificAvenue", 300,200);
        Square northCarolinaAvenue = new PropertySquare("green",  "northCarolinaAvenue", 300,200);
        Square pennsylvaniaAvenue = new PropertySquare("green",  "pennsylvaniaAvenue", 320,200);

        Square parkPlace = new PropertySquare("blue",  "parkPlace", 350,200);
        Square boardwalk = new PropertySquare("blue",  "boardwalk", 400,200);

        board = new Square[]{go, communityChest, mediterraneanAvenue, balticAvenue, incomeTax,
                readingRailroad, orientalAvenue, chance, vermontAvenue, connecticutAvenue,
                jail, stCharlesPlace, electricCompany, statesAvenue, virginiaAvenue,
                pennsylvaniaRailroad, stJamesPlace, communityChest, tennesseeAvenue, newYorkAvenue, freeParking,
                kentuckyAvenue, chance, indianaAvenue, illinoisAvenue,
                boRailroad, atlanticAvenue, ventnorAvenue, waterWorks, marvinGardens,
                goToJail, pacificAvenue, northCarolinaAvenue, communityChest, pennsylvaniaAvenue,
                shortLine, chance, parkPlace, luxuryTax, boardwalk
        };
    }

    public Square[] getBoard() {
        return board;
    }


    public void decideBuyHouseOrHotel(int tempLocation, Player player){

        if(board[tempLocation] instanceof PropertySquare && Dice.purchaseDecision(1f)){

            boolean canBuyHouse = permissionForBuyingHouseOrHotel(tempLocation, player)[0];
            boolean canBuyHotel = permissionForBuyingHouseOrHotel(tempLocation, player)[1];

            player.buyHouseOrHotel((PropertySquare)board[tempLocation], canBuyHouse, canBuyHotel);
        }
    }

    public boolean [] permissionForBuyingHouseOrHotel(int tempLocation, Player player){

        int houseCount = ((PropertySquare)board[tempLocation]).getHouseCount();
        boolean canBuyHouse = false;

        for(int i = 0; i < board.length; i++){

            PropertySquare ps;

            if(board[i] instanceof PropertySquare)
                ps = (PropertySquare) board[i];
            else
                continue;

            if(ps.getColor().equals(((PropertySquare)board[tempLocation]).getColor())){

                if(ps.getOwner() == player){

                    if(houseCount - ps.getHouseCount() < 1 && houseCount < 4)
                        canBuyHouse = true;
                    else{
                        canBuyHouse = false;
                        break;
                    }

                }else{

                    canBuyHouse = false;
                    break;
                }

            }
        }

        boolean canBuyHotel = false;

        for(int i = 0; i < board.length; i++){

            PropertySquare ps;

            if(board[i] instanceof PropertySquare)
                ps = (PropertySquare) board[i];
            else
                continue;

            if(ps.getColor().equals(ps.getColor())){

                if(ps.getOwner() == player && (ps.getHouseCount() == 4 || ps.getHotelCount() == 1)){
                    canBuyHotel = true;
                }else{
                    canBuyHotel = false;
                    break;
                }

            }
        }

        return new boolean[]{canBuyHouse,canBuyHotel};
    }
}
