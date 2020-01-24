/**
 This class is used to represent the player in this game. 
 **/

public class Player {

	private int Money;
	private int totalAssets;
	private String nameOfPlayer;//enter name of player
	private int playerLocation;
	private int initialDiceTotal;
	private Piece piece;
	private boolean isInJail;
	private int countForJail;
	private int ownedRailRoadCount;
	private int totalUtilities;

	public Player(String nameOfPlayer, Piece piece) {

		this(nameOfPlayer, piece, 0);
	}

	public Player(String nameOfPlayer,Piece piece, int playerLocation) {

		totalAssets = 0;
		initialDiceTotal = 0;
		isInJail = false;
		this.piece = piece;
		this.Money = 1500;
		this.nameOfPlayer = nameOfPlayer;
		this.playerLocation = playerLocation;
	}

	public Piece getPiece() {
		return piece;
	}

	public void setPiece(Piece piece) {
		this.piece = piece;
	}

	public int getTotalValuesOfProperties(Board boardObject){

		int totalValues = 0;
		Square[] square = boardObject.getBoard();

		for(int i = 0; i < square.length; i++){

			if(square[i] instanceof PropertySquare)
				if(((PropertySquare)square[i]).getOwner() == this)
					totalValues += ((PropertySquare)square[i]).getPrice();

		}

		return totalValues;
	}

	public int getTotalUtilities() {
		return totalUtilities;
	}

	public void setTotalUtilities(int totalUtilities) {
		this.totalUtilities = totalUtilities;
	}

	public int getOwnedRailRoadCount() {
		return this.ownedRailRoadCount;
	}

	public void setOwnedRailRoadCount(int ownedRailRoadCount) {
		this.ownedRailRoadCount = ownedRailRoadCount;
	}
	public int getInitialDiceTotal() {
		return initialDiceTotal;
	}

	public void setInitialDiceTotal(int initialDiceTotal) {
		this.initialDiceTotal = initialDiceTotal;
	}

	public int getPlayerLocation() {
		return playerLocation;
	}

	public void setPlayerLocation(int playerLocation) {
		this.playerLocation = playerLocation;
	}

	public int getCash() {
		return Money;
	}

	public void setCash(int cash) {
		Money = cash;
	}

	public void setTotalAssets(int totalAssets) {
		this.totalAssets = totalAssets;
	}

	public int getTotalAssets() {
		return totalAssets;
	}

	public int getCountForJail() {
		return countForJail;
	}

	public void setCountForJail(int countForJail) {
		this.countForJail = countForJail;
	}

	public boolean isInJail() {
		return isInJail;
	}

	public void setInJail(boolean inJail) {
		isInJail = inJail;
	}

	public String getName() {
		return nameOfPlayer;
	}

	/* If player money is enough and decide to buy a property*/
	public void buyProperty(PropertySquare square){

		if(Dice.purchaseDecision(1f) &&
				getCash() >= square.getPrice() &&
				square.getOwner() == null){

			square.setOwner(this);
			setCash(getCash() - square.getPrice());
			setTotalAssets(getTotalAssets() + 1);
		}
	}

	public void buyRailRoad(RailRoadSquare square){

		if(Dice.purchaseDecision(1f) &&
				getCash() >= square.getPrice() &&
				square.getOwner() == null){

			square.setOwner(this);
			setCash(getCash() - square.getPrice());
			setTotalAssets(getTotalAssets() + 1);
			this.ownedRailRoadCount++;
			square.setRent();
		}
	}

	public void buyHouseOrHotel(PropertySquare square, boolean canBuyHouse, boolean canBuyHotel){

		if(square.getHotelCount() == 1)
			canBuyHouse = false;

		if(canBuyHouse && getCash() >= square.getPricePerHouse()){

			square.setHouseCount(square.getHouseCount() + 1);
			setCash(getCash() - square.getPricePerHouse());
		}

		if(canBuyHotel){
			square.setHotelCount(1);
			setCash(getCash() - square.getPricePerHouse());
		}

	}
}
