import java.io.BufferedReader;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.MulticastSocket;
import java.net.*;
import java.util.*;

public class ReadChat implements Runnable {
    private MulticastSocket sock;
    private int port;
    private String name;

    private final int SIZE = 4096;

    private ReadChat(String _name, MulticastSocket _sock, int _port) {
        this.name = _name;
        this.sock = _sock;
        this.port = _port;
    }

    public static ReadChat getInstance(String _name, MulticastSocket _sock, int _port) { return new ReadChat(_name, _sock, _port); }

    @Override
    public void run() {
        byte[] buf = new byte[SIZE];
        DatagramPacket p = new DatagramPacket(buf, SIZE, sock.getInetAddress(), this.port);
        while(true){
            try {
                if(sock.isClosed()) break;
                sock.receive(p);
                System.out.println(new String(p.getData()));
                Arrays.fill(buf, (byte)0);
            } catch (IOException e){
                e.printStackTrace();
                return ;
            }
        }   
    }
}
