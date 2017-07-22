package client;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.InetAddress;
import java.net.Socket;

import javax.xml.bind.JAXBException;

import common.ClientRequest;
import common.ServerResponse;

/**
 * @author montreal <br>
 *         {@link Tread} subclass. <br>
 *         This class exchanges information with server.
 */
class NetworkGateway extends Thread {
    private CubbyHole        cubbyhole;
    private ServerResponse   response;
    private String           address;
    private int              port;
    private Socket           socket;

    private DataInputStream  in;
    private DataOutputStream out;

    public NetworkGateway(CubbyHole c) {
        this.address = "127.0.0.1";
        this.port = 54321;
        try {
            InetAddress ip_address = InetAddress.getByName(this.address);
            this.socket = new Socket(ip_address, port);
            this.socket.setKeepAlive(true);

            this.in = new DataInputStream(this.socket.getInputStream());
            this.out = new DataOutputStream(this.socket.getOutputStream());
        } catch (IOException e) {
            e.printStackTrace();
        }

        this.cubbyhole = c;
        this.response = new ServerResponse();
    }

    @Override
    public void run() {
        try {
            this.CommunicateWithServer();
        } catch (IOException | JAXBException e) {
            e.printStackTrace();
        }

    }

    private void CommunicateWithServer() throws IOException, JAXBException {
        this.out.writeUTF("Hello, I am Pakman");
        this.out.flush();

        String returned_xml;

        while (this.cubbyhole.IsClientRunning()) {
            if (this.in.available() > 0) {
                returned_xml = in.readUTF();
                this.response = ServerResponse.ConvertFromXml(returned_xml);
                this.cubbyhole.PutServerResponse(this.response);
            }
        }
        this.DisconnectFromServer();
    }

    private void DisconnectFromServer() throws IOException, JAXBException {
        ClientRequest request = new ClientRequest();
        this.out.writeUTF(ClientRequest.ConvertToXml(request));
        this.socket.close();

    }
}
