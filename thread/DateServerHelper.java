import java.net.*;
import java.io.*;
import java.lang.InterruptedException;

public class DateServerHelper implements Runnable {
  private Socket sock;
  private PrintWriter pw;

  public DateServerHelper(Socket sock) {
      this.sock = sock;
  }

  @Override
  public void run() {
    try{
      pw = new PrintWriter(sock.getOutputStream(), true);

      pw.println(new java.util.Date().toString());

      pw.close();
      sock.close();
    } catch (IOException e) {
      e.printStackTrace();
    }
  }
}
