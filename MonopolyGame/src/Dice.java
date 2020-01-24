import java.util.Random;

public class Dice {

    /*Application class which takes inputs from json or xml file
     and run application till it ends... */

    /* Returns faces of two dices as number array */
    public static int [] getRandomDiceFaces(){

        Random rand = new Random();

        // Generate random integers in range 1 to 6
        int randomDiceNumber0 = rand.nextInt(6) + 1;
        int randomDiceNumber1 = rand.nextInt(6) + 1;

        int [] randomDiceArray = {randomDiceNumber0, randomDiceNumber1};

        return randomDiceArray;
    }

    /* Returns true relevant to the percentage of input when players decide to buy something */
    public static boolean purchaseDecision(float percentage){ // 0.7583

        if(percentage >= 1)
            return true;

        Random rand = new Random();
        int decimal = (int)(percentage * 100);

        // Generate random integers in range 0 to 100
        int randomNumber = rand.nextInt(101) + 0;

        if(randomNumber <= decimal)
            return true;

        return false;
    }

}
