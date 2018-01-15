package tcpdiff;

public class SMessage {
	String from, password, text;
	
	public SMessage (String from, String password, String text) {
		this.from = from;
		this.password = password;
		this.text = text;
	}
	
	@Override
	public String toString () {
		return "Message{"+"from='"+from+'\''+", password='"+password+'\''+", text='"+text+'\''+'}';
	}
}
