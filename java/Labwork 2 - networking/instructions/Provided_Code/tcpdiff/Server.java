package tcpdiff;

import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;

import util.NetworkUtil;

public class Server {

    private ServerSocket serverSocket;
    public int i = 1;
    public HashMap<String, NetworkUtil> clientMap;

    Server() {
        clientMap = new HashMap<>();
        try {
            serverSocket = new ServerSocket(33333);
            new WriteThreadServer(clientMap, "Server");
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
        String clientName = (String) nc.read();
        clientMap.put(clientName, nc);
        new ReadThread(nc);
    }

    public static void main(String args[]) {
        Server server = new Server();
    }
}
