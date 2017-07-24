package server;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.time.Clock;

import javax.xml.bind.JAXBException;

import common.ClientActions;
import common.ClientRequest;
import common.Directions;
import common.ServerResponse;

/**
 * @author montreal <br>
 *         Thread subclass which communicates with client through sockets.<br>
 *         It takes requests from client, dispatches them, updates the game
 *         state and then returns response to the client. Data is transferred
 *         using XML.
 */
public class ServerThread extends Thread {
    private Clock            clock;

    private boolean          first_request = true;

    private DataInputStream  in;
    private DataOutputStream out;
    private PakmanGameObject pakman;
    private boolean          process;

    private Socket           socket;

    private long             start_time;
    private int              ticks;

    /**
     * Time step in milliseconds
     */
    private final int        TIME_STEP     = 50;

    public ServerThread(Socket socket) {
        this.clock = Clock.systemUTC();
        this.socket = socket;
        this.process = true;

        this.pakman = new PakmanGameObject();
    }

    @Override
    public void run() {
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
        this.in = new DataInputStream(this.socket.getInputStream());
        this.out = new DataOutputStream(this.socket.getOutputStream());
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
        if (!this.socket.isClosed()) {
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
}
