import java.util.ArrayList;

public class PropertySquare extends EstateSquare{

    private int pricePerHouse;
    private int houseCount;//If square contains houses this attribute holds that value else holds -1
    private int hotelCount;//If square contains hotels this attribute holds that value else holds -1
    private String color;//Colors can be: brown, gray, purple, orange, red, yellow, green, blue or null

    public PropertySquare (String color, String name, int price, int pricePerHouse){

        super(name, price);

        this.color = color;
        this.pricePerHouse = pricePerHouse;
        this.houseCount = 0;
        this.hotelCount = 0;
        setRent();
    }

    String getColor() {
        return color;
    }

    public int getPricePerHouse() {
        return pricePerHouse;
    }

    public void setPricePerHouse(int pricePerHouse) {
        this.pricePerHouse = pricePerHouse;
    }

    public void setRent(){

        int rentOrFee = 0;

        switch (this.name){

            case "mediterraneanAvenue":
                switch (houseCount){
                    case 0:
                        rentOrFee = 2;
                        break;
                    case 1:
                        rentOrFee = 10;
                        break;
                    case 2:
                        rentOrFee = 30;
                        break;
                    case 3:
                        rentOrFee = 90;
                        break;
                    case 4:
                        rentOrFee = 160;
                        break;
                }
                if(hotelCount == 1)
                    rentOrFee = 250;

                break;

            case "balticAvenue":
                switch (houseCount){
                    case 0:
                        rentOrFee = 4;
                        break;
                    case 1:
                        rentOrFee = 20;
                        break;
                    case 2:
                        rentOrFee = 60;
                        break;
                    case 3:
                        rentOrFee = 180;
                        break;
                    case 4:
                        rentOrFee = 320;
                        break;
                }
                if(hotelCount == 1)
                    rentOrFee = 450;

                break;

            case "orientalAvenue":
                switch (houseCount){
                    case 0:
                        rentOrFee = 6;
                        break;
                    case 1:
                        rentOrFee = 30;
                        break;
                    case 2:
                        rentOrFee = 90;
                        break;
                    case 3:
                        rentOrFee = 270;
                        break;
                    case 4:
                        rentOrFee = 400;
                        break;
                }
                if(hotelCount == 1)
                    rentOrFee = 550;
                break;

            case "vermontAvenue":
                switch (houseCount){
                    case 0:
                        rentOrFee = 6;
                        break;
                    case 1:
                        rentOrFee = 30;
                        break;
                    case 2:
                        rentOrFee = 90;
                        break;
                    case 3:
                        rentOrFee = 270;
                        break;
                    case 4:
                        rentOrFee = 400;
                        break;
                }
                if(hotelCount == 1)
                    rentOrFee = 550;
                break;

            case "connecticutAvenue":
                switch (houseCount){
                    case 0:
                        rentOrFee = 8;
                        break;
                    case 1:
                        rentOrFee = 40;
                        break;
                    case 2:
                        rentOrFee = 100;
                        break;
                    case 3:
                        rentOrFee = 300;
                        break;
                    case 4:
                        rentOrFee = 450;
                        break;
                }
                if(hotelCount == 1)
                    rentOrFee = 600;
                break;

            case "stCharlesPlace":
                switch (houseCount){
                    case 0:
                        rentOrFee = 10;
                        break;
                    case 1:
                        rentOrFee = 50;
                        break;
                    case 2:
                        rentOrFee = 150;
                        break;
                    case 3:
                        rentOrFee = 450;
                        break;
                    case 4:
                        rentOrFee = 625;
                        break;
                }
                if(hotelCount == 1)
                    rentOrFee = 750;
                break;

            case "statesAvenue":
                switch (houseCount){
                    case 0:
                        rentOrFee = 10;
                        break;
                    case 1:
                        rentOrFee = 50;
                        break;
                    case 2:
                        rentOrFee = 150;
                        break;
                    case 3:
                        rentOrFee = 450;
                        break;
                    case 4:
                        rentOrFee = 625;
                        break;
                }
                if(hotelCount == 1)
                    rentOrFee = 750;
                break;

            case "virginiaAvenue":
                switch (houseCount){
                    case 0:
                        rentOrFee = 12;
                        break;
                    case 1:
                        rentOrFee = 60;
                        break;
                    case 2:
                        rentOrFee = 180;
                        break;
                    case 3:
                        rentOrFee = 500;
                        break;
                    case 4:
                        rentOrFee = 700;
                        break;
                }
                if(hotelCount == 1)
                    rentOrFee = 900;
                break;

            case "stJamesPlace":
                switch (houseCount){
                    case 0:
                        rentOrFee = 14;
                        break;
                    case 1:
                        rentOrFee = 70;
                        break;
                    case 2:
                        rentOrFee = 200;
                        break;
                    case 3:
                        rentOrFee = 550;
                        break;
                    case 4:
                        rentOrFee = 750;
                        break;
                }
                if(hotelCount == 1)
                    rentOrFee = 950;
                break;

            case "tennesseeAvenue":
                switch (houseCount){
                    case 0:
                        rentOrFee = 14;
                        break;
                    case 1:
                        rentOrFee = 70;
                        break;
                    case 2:
                        rentOrFee = 200;
                        break;
                    case 3:
                        rentOrFee = 550;
                        break;
                    case 4:
                        rentOrFee = 750;
                        break;
                }
                if(hotelCount == 1)
                    rentOrFee = 950;
                break;

            case "newYorkAvenue":
                switch (houseCount){
                    case 0:
                        rentOrFee = 16;
                        break;
                    case 1:
                        rentOrFee = 80;
                        break;
                    case 2:
                        rentOrFee = 220;
                        break;
                    case 3:
                        rentOrFee = 600;
                        break;
                    case 4:
                        rentOrFee = 800;
                        break;
                }
                if(hotelCount == 1)
                    rentOrFee = 1000;
                break;

            case "kentuckyAvenue":
                switch (houseCount){
                    case 0:
                        rentOrFee = 18;
                        break;
                    case 1:
                        rentOrFee = 90;
                        break;
                    case 2:
                        rentOrFee = 250;
                        break;
                    case 3:
                        rentOrFee = 700;
                        break;
                    case 4:
                        rentOrFee = 875;
                        break;
                }
                if(hotelCount == 1)
                    rentOrFee = 1050;
                break;

            case "indianaAvenue":
                switch (houseCount){
                    case 0:
                        rentOrFee = 18;
                        break;
                    case 1:
                        rentOrFee = 90;
                        break;
                    case 2:
                        rentOrFee = 250;
                        break;
                    case 3:
                        rentOrFee = 700;
                        break;
                    case 4:
                        rentOrFee = 875;
                        break;
                }
                if(hotelCount == 1)
                    rentOrFee = 1050;
                break;

            case "illinoisAvenue":
                switch (houseCount){
                    case 0:
                        rentOrFee = 20;
                        break;
                    case 1:
                        rentOrFee = 100;
                        break;
                    case 2:
                        rentOrFee = 300;
                        break;
                    case 3:
                        rentOrFee = 750;
                        break;
                    case 4:
                        rentOrFee = 925;
                        break;
                }
                if(hotelCount == 1)
                    rentOrFee = 1100;
                break;

            case "atlanticAvenue":
                switch (houseCount){
                    case 0:
                        rentOrFee = 22;
                        break;
                    case 1:
                        rentOrFee = 110;
                        break;
                    case 2:
                        rentOrFee = 330;
                        break;
                    case 3:
                        rentOrFee = 800;
                        break;
                    case 4:
                        rentOrFee = 975;
                        break;
                }
                if(hotelCount == 1)
                    rentOrFee = 1150;
                break;

            case "ventnorAvenue":
                switch (houseCount){
                    case 0:
                        rentOrFee = 22;
                        break;
                    case 1:
                        rentOrFee = 110;
                        break;
                    case 2:
                        rentOrFee = 330;
                        break;
                    case 3:
                        rentOrFee = 800;
                        break;
                    case 4:
                        rentOrFee = 975;
                        break;
                }
                if(hotelCount == 1)
                    rentOrFee = 1150;
                break;

            case "marvinGardens":
                switch (houseCount){
                    case 0:
                        rentOrFee = 24;
                        break;
                    case 1:
                        rentOrFee = 120;
                        break;
                    case 2:
                        rentOrFee = 360;
                        break;
                    case 3:
                        rentOrFee = 850;
                        break;
                    case 4:
                        rentOrFee = 1025;
                        break;
                }
                if(hotelCount == 1)
                    rentOrFee = 1200;
                break;

            case "pacificAvenue":
                switch (houseCount){
                    case 0:
                        rentOrFee = 26;
                        break;
                    case 1:
                        rentOrFee = 130;
                        break;
                    case 2:
                        rentOrFee = 390;
                        break;
                    case 3:
                        rentOrFee = 900;
                        break;
                    case 4:
                        rentOrFee = 1100;
                        break;
                }
                if(hotelCount == 1)
                    rentOrFee = 1275;
                break;

            case "northCarolinaAvenue":
                switch (houseCount){
                    case 0:
                        rentOrFee = 26;
                        break;
                    case 1:
                        rentOrFee = 130;
                        break;
                    case 2:
                        rentOrFee = 390;
                        break;
                    case 3:
                        rentOrFee = 900;
                        break;
                    case 4:
                        rentOrFee = 1100;
                        break;
                }
                if(hotelCount == 1)
                    rentOrFee = 1275;
                break;

            case "pennsylvaniaAvenue":
                switch (houseCount){
                    case 0:
                        rentOrFee = 28;
                        break;
                    case 1:
                        rentOrFee = 150;
                        break;
                    case 2:
                        rentOrFee = 450;
                        break;
                    case 3:
                        rentOrFee = 1000;
                        break;
                    case 4:
                        rentOrFee = 1200;
                        break;
                }
                if(hotelCount == 1)
                    rentOrFee = 1400;
                break;

            case "parkPlace":
                switch (houseCount){
                    case 0:
                        rentOrFee = 35;
                        break;
                    case 1:
                        rentOrFee = 175;
                        break;
                    case 2:
                        rentOrFee = 500;
                        break;
                    case 3:
                        rentOrFee = 1100;
                        break;
                    case 4:
                        rentOrFee = 1300;
                        break;
                }
                if(hotelCount == 1)
                    rentOrFee = 1500;
                break;

            case "boardwalk":
                switch (houseCount){
                    case 0:
                        rentOrFee = 50;
                        break;
                    case 1:
                        rentOrFee = 200;
                        break;
                    case 2:
                        rentOrFee = 600;
                        break;
                    case 3:
                        rentOrFee = 1400;
                        break;
                    case 4:
                        rentOrFee = 1700;
                        break;
                }
                if(hotelCount == 1)
                    rentOrFee = 2000;
                break;


        }

        this.setRentOrFee(rentOrFee);
    }

    int getHouseCount() {
        return houseCount;
    }

    public void setHouseCount(int newHouseCount) {
        houseCount = newHouseCount;
        setRent();
    }

    int getHotelCount() {
        return hotelCount;
    }

    public void setHotelCount(int newHotelCount) {

        if(newHotelCount >= 1)
            this.houseCount = 0;

        this.hotelCount = newHotelCount;

        setRent();
    }
}
