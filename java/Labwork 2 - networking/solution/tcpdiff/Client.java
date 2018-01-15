package tcpdiff;

import java.util.Scanner;

import util.NetworkUtil;

public class Client {

    public Client(String serverAddress, int serverPort) {
        try {
            System.out.print("Enter name of the client: ");
            Scanner scanner = new Scanner(System.in);
			String clientName = scanner.nextLine();
			System.out.println ("Enter password");
			String clientPass = scanner.nextLine ();
            NetworkUtil nc = new NetworkUtil(serverAddress, serverPort);
			RMessage clientId = new RMessage (clientName, clientPass);
			nc.write (clientId);
            new ReadThread(nc);
            new WriteThreadClient(nc, clientId);
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public static void main(String args[]) {
        String serverAddress = "127.0.0.1";
        int serverPort = 33333;
        Client client = new Client(serverAddress, serverPort);
    }
}

