package tcpdiff;

import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;

import util.NetworkUtil;

public class Server {

    private ServerSocket serverSocket;
    public int i = 1;
    public HashMap<RMessage, NetworkUtil> clientMap;

    Server() {
        clientMap = new HashMap<>();
        try {
            serverSocket = new ServerSocket(33333);
            while (true) {
                Socket clientSocket = serverSocket.accept();
                serve(clientSocket);
            }
        } catch (Exception e) {
            System.out.println("Server starts:" + e);
        }
    }

    public void serve(Socket clientSocket) {
        NetworkUtil nc = new NetworkUtil(clientSocket);
		RMessage clientId = (RMessage) nc.read ();
		clientMap.put (clientId, nc);
        new ReadThread(nc);
		new WriteThreadServer (clientMap, clientId);
    }

    public static void main(String args[]) {
        Server server = new Server();
    }
}
