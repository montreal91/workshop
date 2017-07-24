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
    private String           address;
    private CubbyHole        cubbyhole;
    private DataInputStream  in;
    private DataOutputStream out;
    private int              port;

    private ServerResponse   response;
    private Socket           socket;

    public NetworkGateway(CubbyHole c) {
        this.address = "127.0.0.1";
        this.port = 54321;
        try {
            InetAddress ip_address = InetAddress.getByName(this.address);
            this.socket = new Socket(ip_address, this.port);
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
        ClientRequest request;

        while (this.cubbyhole.IsClientRunning()) {
            if (this.in.available() > 0) {
                returned_xml = this.in.readUTF();
                this.response = ServerResponse.ConvertFromXml(returned_xml);
                this.cubbyhole.PutServerResponse(this.response);
            }
            request = this.cubbyhole.GetClientRequest();
            if (request != null) {
                this.out.writeUTF(ClientRequest.ConvertToXml(request));
                this.out.flush();
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
