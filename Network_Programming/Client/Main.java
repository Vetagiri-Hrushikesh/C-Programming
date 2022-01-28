import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException {
        webClient client = new webClient();
        client.setServerDetails("localhost", 8080);
        client.initialize(); // Should call while app loads
        int i = 0;
        while (true) {
            try {
                client.getDataFromServer();
                i++;
            } catch (Exception e) {
                System.out.println(e);
                client.closeSocketAndStream();
            }
        }
    }
}
