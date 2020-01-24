public class UtilitySquare extends EstateSquare{

    public UtilitySquare(String name, int price){

        super(name, price);
    }

    @Override
    public void setRent() {

    }

    public int getRent(int totalDiceAmount){

        int rent = 0;

        if(owner.getTotalUtilities() == 1)
            rent = totalDiceAmount * 4;
        else if(owner.getTotalUtilities() == 2)
            rent = totalDiceAmount * 10;

        return rent;
    }
}
