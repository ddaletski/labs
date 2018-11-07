import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.CharBuffer;
import java.util.Scanner;

enum CommandStatus {
    STARTING,
    RUNNING,
    DONE,
    ERROR
}

class Command extends Thread {
    private String cmd;
    private Process proc;

    private PrintWriter outputStream;
    private BufferedReader inputStream;

    private CommandStatus status;
    private String errMsg = "";


    @Override
    public void run() {
        try {
            proc = Runtime.getRuntime().exec(cmd);
            status = CommandStatus.RUNNING;
        } catch (IOException e) {
            errMsg = e.getMessage();
            status = CommandStatus.ERROR;
        }

        InputStreamReader stdout = new InputStreamReader(proc.getInputStream());
        InputStreamReader stderr = new InputStreamReader(proc.getErrorStream());
        InputStreamReader[] out_err = new InputStreamReader[]{stdout, stderr};

        try {
            char[] buffer = new char[1000000];
            do {
                try {
                    boolean toWait = true;
                    for (InputStreamReader reader : out_err) {
                        if (reader.ready()) {
                            int readChars = stdout.read(buffer);
                            System.out.println(readChars);
                            String result = new String(buffer, 0, readChars);

                            outputStream.printf("UP %s\n", result.replaceAll("\\n", "\\\\n"));
                            outputStream.flush();
                            toWait = false;
                        }
                    }
                    if (inputStream.ready()) {
                        System.out.println("READY");
                    }
                    if (toWait) {
                        Thread.sleep(1);
                    }
                } catch (InterruptedException | IOException e) {
                    continue;
                }
            } while (proc.isAlive() || stdout.ready() || stderr.ready());
        } catch (IOException e) {
            System.out.println(e);
        }

        status = CommandStatus.DONE;
    }

    public Command(String cmd, OutputStream outputStream, InputStream inputStream) {
        this.status = CommandStatus.STARTING;
        this.cmd = cmd;

        this.outputStream = new PrintWriter(outputStream);
        this.inputStream = new BufferedReader(new InputStreamReader(inputStream));
    }

    public CommandStatus getStatus() {
        return status;
    }

    public void exit() {
        this.proc.destroy();
    }
};


class RemoteShellServer {
    private Command runningCommand;
};


public class CmdServer {
    public static void main(String[] args) throws IOException {
        ServerSocket listener = new ServerSocket(9090);
        try {
            System.out.println("waiting for a connection");
            Socket socket = listener.accept();
            System.out.println("connected");
            try {
                BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                PrintWriter out = new PrintWriter(socket.getOutputStream());

                String msg;
                do {
                    msg = in.readLine();

                    String[] cmd = msg.split(" ", 2);
                    String serverCmd = cmd[0], consoleCmd = cmd[1];

                    Command command = new Command(consoleCmd, socket.getOutputStream(), socket.getInputStream());
                    command.start();

                    try {
                        command.join();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }

                    out.println("END");
                    out.flush();

                } while (msg != null);

            } finally {
                socket.close();
            }
        } finally {
            listener.close();
        }
    }
}
