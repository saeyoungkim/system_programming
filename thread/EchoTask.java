import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.InputStreamReader;
import java.net.*;
import java.util.concurrent.*;

public class EchoTask implements Runnable {
    private final Socket sock;

    public EchoTask(Socket sock) {
        this.sock = sock;
    }

    @Override
    public void run() {
        try (
            BufferedReader br = new BufferedReader(new InputStreamReader(this.sock.getInputStream())); 
            PrintWriter pw = new PrintWriter(this.sock.getOutputStream(), true)
        ){
            String line;
            while((line = br.readLine()) != null){
                System.out.printf("[%s] %s\n", Thread.currentThread().getName(), line);
                pw.println(line);
            }
        } catch(IOException e) {
            e.printStackTrace();
        }
    }
}