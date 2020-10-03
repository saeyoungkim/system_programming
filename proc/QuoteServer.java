import java.io.*;
import java.net.*;
import java.util.Random;

public class QuoteServer {
    public static void main(String args[]) {
        final int port = 17;
        final String quotes[] = new String[] {
            "The purpose of our lives is to be happy.",
            "Life is what happens when you’re busy making other plans.",
            "Get busy living or get busy dying.",
            "You only live once, but if you do it right, once is enough.",
            "Many of life’s failures are people who did not realize how close they were to success when they gave up.",
            "If you want to live a happy life, tie it to a goal, not to people or things.",
            "Never let the fear of striking out keep you from playing the game.",
            "Your time is limited, so don’t waste it living someone else’s life. Don’t be trapped by dogma – which is living with the results of other people’s thinking.",
            "Not how long, but how well you have lived is the main thing.",
            "In order to write about life first you must live it.",
            "The big lesson in life, baby, is never be scared of anyone or anything",
            "The unexamined life is not worth living.",
            "Turn your wounds into wisdom."
        };

        ServerSocket s_sock = null;
        Socket c_sock = null;

        Random r = new Random();

        try {
            s_sock = new ServerSocket(port);
            
            boolean b = true;

            while(b) {
                c_sock = s_sock.accept();

                PrintWriter pw = new PrintWriter(c_sock.getOutputStream(), true); 
                String quote = quotes[r.nextInt(quotes.length)];
                pw.println(quote);

                c_sock.close();
            }

            s_sock.close();
        } catch (IOException e) {
            System.out.println("IOException is occurred. error.msg  : " + e.getMessage());
        }
    }
}