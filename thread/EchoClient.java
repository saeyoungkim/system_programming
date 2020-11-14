import java.net.*;
import java.util.Scanner;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.InputStreamReader;

public class EchoClient {
    public static void main(String[] args){
        try{
            Socket sock = new Socket("localhost", 8080);
            
            try (
                BufferedReader br = new BufferedReader(new InputStreamReader(sock.getInputStream())); 
                PrintWriter pw = new PrintWriter(sock.getOutputStream(), true);
                BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));
            ){
                System.out.println("start echo chatting...");
                String line;
                
                while((line = stdin.readLine()) != null) {
                    pw.println(line);
                    System.out.println("echo: " + br.readLine());
                }

            } catch(IOException e) {
                e.printStackTrace();
            }
            
            sock.close();
        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
