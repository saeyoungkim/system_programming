import java.io.*;
import java.net.*;

public class QuoteClient {
    public static void main(String args[]) {
        final int port = 17;

        Socket sock = null;

        try {
            sock = new Socket("localhost", port);

            BufferedReader br = new BufferedReader(new InputStreamReader(sock.getInputStream()));
            String line;
            while((line = br.readLine()) != null){
                System.out.println(line);
            }

            close(sock);
        } catch (IOException e) {
            System.out.println("IOException is occurred. error.msg  : " + e.getMessage());
        }
    }

    private static void close(Socket ... socks) throws IOException {
        for(Socket sock : socks) sock.close();
    }
}
