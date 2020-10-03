import java.io.*;
import java.net.*;

public class EchoServer {
    public static void main(String[] args) {
        final int port = 9999;

        ServerSocket s_sock = null;
        Socket sock = null;

        try {
            s_sock = new ServerSocket(port);

            sock = s_sock.accept();

            BufferedReader br = 
            new BufferedReader(
                new InputStreamReader(sock.getInputStream()));

            BufferedWriter bw =
            new BufferedWriter(
                new OutputStreamWriter(sock.getOutputStream()));

            String line;

            while(sock.isConnected()) {
                line = br.readLine();
                bw.write(line + "\n");
                bw.flush();
            }

            sock.close();
            s_sock.close();
        } catch (IOException e) {
            System.out.println("Error message : " + e.getMessage());
            return ;
        }
    }
}