public class GoToJailSquare extends Square {

    private JailSquare jailSquare;

    public GoToJailSquare(String name, JailSquare jailSquare){

        super(name);
        this.jailSquare = jailSquare;
    }

    public void putPlayerIntoJailSquare(Player player){

        /* Jail is in 10th square*/
        player.getPiece().setLocation(10);
        jailSquare.putPlayerIntoJail(player);
    }

    public JailSquare getJailSquare() {
        return jailSquare;
    }

    public void setJailSquare(JailSquare jailSquare) {
        this.jailSquare = jailSquare;
    }
}
