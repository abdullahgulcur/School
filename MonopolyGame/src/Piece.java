import java.lang.Object;
		import java.util.*;

public class Piece {

	private String pieceName;// {"Plane","Car","Ship","Shoe","Hat","Cat","Robot","Cannon"}
	private int location;

	public Piece(String pieceName) {
		this.pieceName = pieceName;
	}

	public String getPieceName() {
		return pieceName;
	}

	public void setPiece(String piece) {
		this.pieceName = piece;
	}

	public int getLocation() {
		return location;
	}

	public void setLocation(int location) {
		this.location = location;
	}

}
