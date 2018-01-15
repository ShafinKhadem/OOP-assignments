package tcpdiff;

import util.NetworkUtil;

public class ReadThread implements Runnable {
    private Thread thr;
    private NetworkUtil nc;

    public ReadThread(NetworkUtil nc) {
        this.nc = nc;
        this.thr = new Thread(this);
        thr.start();
    }

    public void run() {
        try {
            while (true) {
				SMessage r = (SMessage) nc.read ();
				if (r!=null) {
					System.out.println (r);
				}
			}
        } catch (Exception e) {
            System.out.println(e);
        } finally {
            nc.closeConnection();
        }
    }
}



