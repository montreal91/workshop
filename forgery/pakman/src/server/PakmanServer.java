package server;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * @author montreal <br>
 *         Server that deals with multiple connections. For each connection
 *         server runs different {@link ServerThread}. Runs forever until
 *         interrupted.
 */
public class PakmanServer {
    static final int PORT = 54321;

    @SuppressWarnings("resource")
    public static void main(String[] args) {
        ServerSocket server_socket;
        Socket client_socket;

        try {
            server_socket = new ServerSocket(PORT);
        } catch (IOException e) {
            e.printStackTrace();
            return;

        }

        while (true) {
            try {
                client_socket = server_socket.accept();
            } catch (IOException e) {
                e.printStackTrace();
                return;
            }
            if (client_socket != null) {
                new ServerThread(client_socket).start();
            }
        }
    }
}
