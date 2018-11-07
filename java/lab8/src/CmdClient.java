import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;


public class CmdClient {

    public static void main(String[] args) throws IOException {
        InputStreamReader readerIn = new InputStreamReader(System.in);
        BufferedReader stdin = new BufferedReader(readerIn);

        String serverAddress;
        int serverPort;

        if (args.length >= 2) {
            serverAddress = args[0];
            serverPort = Integer.parseInt(args[1]);
        } else {

            System.out.print("server address: ");
            serverAddress = stdin.readLine();

            System.out.print("server port: ");
            serverPort = Integer.parseInt(stdin.readLine());
        }

        Socket socket = new Socket(serverAddress, serverPort);
        System.out.println("connected");

        BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

        char[] buffer = new char[1024];
        String answer;
        do {
            System.out.print("> ");
            String command = stdin.readLine();

            out.printf("START %s\n", command);

            while(true) {
                if (readerIn.ready()) {
                    int readChars = readerIn.read(buffer);
                    String stringForCmd = new String(buffer, 0, readChars);
                    System.out.printf("read: %s\n", stringForCmd);
                }
                if (in.ready()) {
                    answer = in.readLine().replaceAll("\\\\n", "\n");

                    if (answer.equals("END")) {
                        break;
                    } else {
                        String[] results = answer.split(" ", 2);
                        if (results[0].equals("UP")) {
                            System.out.print(results[1]);
                        }
                    }
                }
            }


        } while (answer != null);
    }
}

