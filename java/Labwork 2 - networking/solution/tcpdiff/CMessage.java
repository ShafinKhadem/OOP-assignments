package tcpdiff;

public class CMessage extends SMessage {
	String to;
	
	public CMessage (String from, String password, String text, String to) {
		super (from, password, text);
		this.to = to;
	}
	
	@Override
	public String toString () {
		return super.toString ();
	}
}
