import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.InputStreamReader;
import java.net.*;
import java.util.concurrent.*;

public class EchoServer {
    public static void main(String[] args) {
        int port = 8080;

        ExecutorService pool = Executors.newFixedThreadPool(8);

        try(ServerSocket ss = new ServerSocket(port)){
            while(true) {
                try{
                    Socket sock = ss.accept();
                    System.out.println("connected!");
                    pool.submit(new EchoTask(sock));
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        } catch(IOException e){
            e.printStackTrace();
        }
    }
}