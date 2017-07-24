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
import common.Directions;
import common.ServerResponse;

/**
 * @author montreal <br>
 *         Server that runs all game logic. Communicates with client using
 *         sockets.
 */
public class PakmanServer {
    private Socket           cl_socket;

    private Clock            clock;

    private boolean          first_request = true;
    private DataInputStream  in;
    private DataOutputStream out;
    private PakmanGameObject pakman;
    private int              port;

    private boolean          process;
    private ServerSocket     srv_socket;

    private long             start_time;
    private int              ticks;

    /**
     * Time step in milliseconds
     */
    private final int        TIME_STEP     = 50;

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
                this.pakman.Update();
                this.SendResponse();

            }
            System.out.println("Connection is closed");
        } catch (IOException | JAXBException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    private void DispatchRequest(ClientRequest request) {
        if (request.GetAction().equals(ClientActions.QUIT.GetAction())) {
            this.process = false;
        } else if (request.GetAction().equals(ClientActions.RESTART.GetAction())) {
            this.start_time = this.clock.millis();
            this.ticks = 0;
            this.pakman.Restart();
        } else if (request.GetAction().equals(ClientActions.MOVE.GetAction())) {
            this.ProcessDirectionRequest(request);
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

    private void ProcessDirectionRequest(ClientRequest request) {
        if (request.GetDirection().equals(Directions.RIGHT.toString())) {
            this.pakman.SetPakmanDirection(Directions.RIGHT);
        } else if (request.GetDirection().equals(Directions.LEFT.toString())) {
            this.pakman.SetPakmanDirection(Directions.LEFT);
        } else if (request.GetDirection().equals(Directions.UP.toString())) {
            this.pakman.SetPakmanDirection(Directions.UP);
        } else if (request.GetDirection().equals(Directions.DOWN.toString())) {
            this.pakman.SetPakmanDirection(Directions.DOWN);
        } else if (request.GetDirection().equals(Directions.NONE.toString())) {
            this.pakman.SetPakmanDirection(Directions.NONE);
        }
    }

    private void ProcessRequest() throws IOException, JAXBException {
        ClientRequest request;
        if (this.in.available() > 0) {
            request = ClientRequest.ConvertFromXml(this.in.readUTF());
            this.DispatchRequest(request);
        }
    }

    private void SendResponse() throws IOException, JAXBException {
        if (!this.cl_socket.isClosed()) {
            ServerResponse response = new ServerResponse(
                    this.pakman.GetPakmanPosition(), this.pakman.GetScore(), this.pakman.GetSize()
            );
            if (this.first_request) {
                response.SetWalls(this.pakman.GetWalls());
                this.first_request = false;
            }
            response.SetCookies(this.pakman.GetCookies());
            this.out.writeUTF(ServerResponse.ConvertToXml(response));
            this.out.flush();
        }
    }

    public static void main(String[] args) {
        PakmanServer pakman_server = new PakmanServer();
        try {
            pakman_server.Run();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
