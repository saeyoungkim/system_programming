import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.io.IOException;
import java.lang.InterruptedException;

public class DateServer {
  private static ServerSocket ss;
  private static Socket sock;
  private static ExecutorService service;

  public static void main(String args[]) {
    try{
     ss = new ServerSocket(80);

     service = Executors.newFixedThreadPool(4);
     while(true){
       service.submit(new DateServerHelper(ss.accept()));
     }
   } catch (IOException e) {
     e.printStackTrace();
   } finally {
     service.shutdown();
     return ;
   }
  }
}
