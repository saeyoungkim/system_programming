import java.io.*;
import java.net.*;
import java.util.Scanner;

public class EchoClient {
    public static void main(String[] args) {
        final int port = 9999;

        System.out.println("PORT : " + port);

        Socket sock = null;

        try {
            sock = new Socket("localhost", port);

            BufferedReader br = 
            new BufferedReader(
                new InputStreamReader(sock.getInputStream()));

            BufferedWriter bw =
            new BufferedWriter(
                new OutputStreamWriter(sock.getOutputStream()));

            Scanner scanner = new Scanner(System.in);

            System.out.println("======= start =======");

            while(sock.isConnected()) {
                System.out.print("client > ");
                String line = scanner.nextLine();

                bw.write(line+"\n");
                bw.flush();

                line = br.readLine();
                System.out.print("server > ");
                System.out.println(line);   
            }

            scanner.close();
            close(sock);
        } catch (IOException e) {
            System.out.println("IOException is occurred. error.msg  : " + e.getMessage());
        }
    }

    private static void close(Socket ... socks) throws IOException {
        for(Socket sock : socks) sock.close();
    }
}