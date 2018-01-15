package tcpdiff;

import java.util.HashMap;
import java.util.Scanner;
import java.util.StringTokenizer;

import util.NetworkUtil;

public class WriteThreadServer implements Runnable {

    private Thread thr;
	RMessage clientId;
    public HashMap<RMessage, NetworkUtil> clientMap;
	NetworkUtil nc;

    public WriteThreadServer(HashMap<RMessage, NetworkUtil> map, RMessage clientId) {
        this.clientMap = map;
        this.clientId = clientId;
		nc = map.get (clientId);
        this.thr = new Thread(this);
        thr.start();
    }

    public void run() {
        try {
            while (true) {
				CMessage c = (CMessage) nc.read ();
				if (c != null) {
					NetworkUtil nc2 = clientMap.get (c.to);
					if (nc2 != null) {
						nc2.write (c);
					}
				}
				SMessage r = (SMessage) nc.read ();
				if (r!=null) {
					System.out.println (r);
				}
            }
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}



