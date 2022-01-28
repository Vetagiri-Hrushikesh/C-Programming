import java.io.DataInputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.net.Socket;
import java.net.UnknownHostException;

public class webClient {
    private static final String TAG = "SesamPTUPluginClient";
    // SetServerDetails
    private String address;
    private int port;

    // Initialize Socket
    private Socket socket;
    private DataInputStream dataInputStream;
    PrintStream out;

    // Variables
    public int var1;
    public String messsage;
    public byte[] dataBuff;

    public void setServerDetails(String address, int port) {
        this.address = address;
        this.port = port;
    }

    public int initialize() {
        int flag = 0;
        try {
            this.socket = new Socket(address, port);
            if (this.socket != null) {
                flag = 1;
                dataInputStream = new DataInputStream(socket.getInputStream());
                out = new PrintStream(this.socket.getOutputStream());
                System.out.println("Connected!");
            }
        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return flag;
    }

    public byte[] getDataFromServer() {
        String line = "";
        try {
            int length;
            length = dataInputStream.readInt();
            System.out.println(length);
        } catch (Exception e) {
            System.out.println(e);
        }
        return dataBuff;
    }

    public void sendDataToServer() {
        String str = "1,2,3,4,5,6,7,8,9,10";
        out.print(str + "\n");
    }

    public void closeSocketAndStream() {
        try {
            System.out.println("Closing socket and terminating program.");
            dataInputStream.close();
            out.flush();
            socket.close();
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public static int getInt(byte[] array, int offset) {
        return ((array[offset] & 0xff) << 24) |
                ((array[offset + 1] & 0xff) << 16) |
                ((array[offset + 2] & 0xff) << 8) |
                ((array[offset + 3] & 0xff << 0));
    }
}