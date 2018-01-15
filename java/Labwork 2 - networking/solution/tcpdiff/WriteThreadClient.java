package tcpdiff;

import java.util.Scanner;

import util.NetworkUtil;

public class WriteThreadClient implements Runnable {

    private Thread thr;
    private NetworkUtil nc;
    String from, password;

    public WriteThreadClient(NetworkUtil nc, RMessage Id) {
        this.nc = nc;
		this.from = Id.username;
		this.password = Id.password;
        this.thr = new Thread(this);
        thr.start();
    }

    public void run() {
        try {
            Scanner input = new Scanner(System.in);
            while (true) {
				System.out.println ("press 1 to send message to server or press 2 to send message to client");
				String s = input.nextLine();
				if (s.equals ("1")) {
					System.out.println ("enter message");
					String text = input.nextLine ();
					nc.write(new SMessage (from, password, text));
				}
				else if (s.equals ("2")) {
					System.out.println ("enter receiver client username");
					String to = input.nextLine ();
					System.out.println ("enter message");
					String text = input.nextLine ();
					nc.write (new CMessage (from, password, text, to));
				}
            }
        } catch (Exception e) {
            System.out.println(e);
        } finally {
            nc.closeConnection();
        }
    }
}



