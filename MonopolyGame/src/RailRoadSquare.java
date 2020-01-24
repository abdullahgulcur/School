import java.util.ArrayList;

public class RailRoadSquare extends EstateSquare{

    public RailRoadSquare(String name, int price){

        super(name, price);
    }

    public void setRent(){

        int count = super.owner.getOwnedRailRoadCount();

        switch(count){

            case 1:
                rentOrFee = 25;
                break;
            case 2:
                rentOrFee = 50;
                break;
            case 3:
                rentOrFee = 100;
                break;
            case 4:
                rentOrFee = 200;
                break;
        }
    }

}
