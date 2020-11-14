import java.net.MulticastSocket;
import java.net.UnknownHostException;
import java.io.IOException;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.NetworkInterface;
import java.util.Scanner;
import java.net.DatagramPacket;
import java.util.concurrent.*;
import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;

public class GroupChat {
    private static List<String> TERMINATE_COMMANDS = new ArrayList<String>(Arrays.asList("quit","terminate","exit","q"));
        
    public static void main(String[] args) {
        if(args.length != 2){
            System.err.println("2 arguments required : [multicast_ip] [port_number]");
            return ;
        }

        //set name
        String name;
        Scanner sc = new Scanner(System.in);

        System.out.print("Please enter the name : ");
        name = sc.nextLine();

        System.out.println("Start group chatting with name '" + name + "'");

        int port = Integer.parseInt(args[1]);


        try{
            /// set inetaddress & socketAddress
            InetAddress address = InetAddress.getByName(args[0]);
            InetSocketAddress group = new InetSocketAddress(address, port);

            // set NetworkInterface
            NetworkInterface nif = NetworkInterface.getByName("eth0");

            /// set socket
            MulticastSocket sock = new MulticastSocket(port);

            sock.joinGroup(group, nif);
            
            /// ExecutorService
            ExecutorService pool = Executors.newSingleThreadExecutor();
            /// read thread
            pool.submit(ReadChat.getInstance(name, sock, port));

            String enteringMessage = name + " is entered!!";

            sock.send(new DatagramPacket(enteringMessage.getBytes(), enteringMessage.getBytes().length, group));
            
            while(!sock.isClosed()){
                /// write thread
                String msg = sc.nextLine();
                if(TERMINATE_COMMANDS.contains(msg)) break;

                msg = name + ": " + msg;

                DatagramPacket p = new DatagramPacket(msg.getBytes(), msg.getBytes().length, group);
                sock.send(p);
            }

            /// socket terminated
            sock.leaveGroup(group, nif);
            sock.close();
            pool.shutdown();
        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
