package server;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.time.Clock;

import javax.xml.bind.JAXBException;

import common.ClientActions;
import common.ClientRequest;
import common.ServerResponse;

/**
 * @author montreal <br>
 *         Server that runs all game logic. Communicates with client using
 *         sockets.
 */
public class PakmanServer {
    private int              port;
    private int              ticks;

    private ServerSocket     srv_socket;
    private Socket           cl_socket;
    private Clock            clock;
    private DataInputStream  in;
    private DataOutputStream out;

    private boolean          process;
    private boolean          first_request = true;

    /**
     * Time step in milliseconds
     */
    private final int        TIME_STEP     = 500;
    private long             start_time;

    private PakmanGameObject pakman;

    public PakmanServer() {
        this.port = 54321;
        try {
            this.srv_socket = new ServerSocket(this.port);
        } catch (IOException e) {
            e.printStackTrace();
        }
        this.clock = Clock.systemUTC();
        this.cl_socket = null;
        this.process = true;

        this.pakman = new PakmanGameObject();
    }

    public static void main(String[] args) {
        PakmanServer pakman_server = new PakmanServer();
        try {
            pakman_server.Run();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void Run() {
        try {
            this.EstablishConnection();
            this.start_time = this.clock.millis();
            long targeted_time, new_time, time_to_wait;
            while (this.process) {
                new_time = this.clock.millis();
                this.ticks++;
                targeted_time = this.start_time + this.TIME_STEP * this.ticks;
                time_to_wait = targeted_time - new_time;
                if (time_to_wait > 0) {
                    Thread.sleep(time_to_wait);
                }
                this.ProcessRequest();
                this.SendResponse();

            }
            System.out.println("Connection is closed");
        } catch (IOException | JAXBException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    private void EstablishConnection() throws IOException {
        System.out.println("Waiting for clients");
        this.cl_socket = this.srv_socket.accept();
        System.out.println("Got a client...");

        this.in = new DataInputStream(this.cl_socket.getInputStream());
        this.out = new DataOutputStream(this.cl_socket.getOutputStream());
        String cl_request = this.in.readUTF();
        System.out.println("Client Wrote:");
        System.out.println(cl_request);
        this.out.flush();
    }

    private void ProcessRequest() throws IOException, JAXBException {
        ClientRequest request;
        if (this.in.available() > 0) {
            request = ClientRequest.ConvertFromXml(this.in.readUTF());
            this.DispatchRequest(request);
        }
    }

    private void DispatchRequest(ClientRequest request) {
        if (request.GetAction().equals(ClientActions.QUIT.GetAction())) {
            this.process = false;
        } else if (request.GetAction().equals(ClientActions.RESTART.GetAction())) {
            this.start_time = this.clock.millis();
            this.ticks = 0;
        }

    }

    private void SendResponse() throws IOException, JAXBException {
        if (!this.cl_socket.isClosed()) {
            ServerResponse response = new ServerResponse(1, 1, this.ticks, this.pakman.GetSize());
            if (this.first_request) {
                response.SetWalls(this.pakman.GetWalls());
                this.first_request = false;
            }
            this.out.writeUTF(ServerResponse.ConvertToXml(response));
            this.out.flush();
        }
    }
}
