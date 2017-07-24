
package common;

import java.io.StringReader;
import java.io.StringWriter;
import java.util.ArrayList;

import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Marshaller;
import javax.xml.bind.Unmarshaller;
import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.transform.stream.StreamResult;

import server.PakmanServer;

/**
 * @author montreal <br>
 *         This class is used by {@link PakmanServer} to send all important
 *         information to the client.<br>
 */
@XmlRootElement
public class ServerResponse {
    @XmlElement
    private Vector            position;

    @XmlAttribute
    private int               score;

    @XmlElement
    private Vector            size;

    @XmlElement
    private ArrayList<Vector> walls;

    public ServerResponse() {
        this.position = new Vector(Integer.MIN_VALUE, Integer.MIN_VALUE);
        this.score = Integer.MIN_VALUE;
        this.size = new Vector();
        this.walls = new ArrayList<Vector>();
    }

    public ServerResponse(Vector position, int score, Vector size) {
        this.position = position;
        this.score = score;
        this.size = size;
        this.walls = new ArrayList<Vector>();
    }

    public Vector GetPosition() {
        return this.position;
    }

    public int GetScore() {
        return this.score;
    }

    public Vector GetSize() {
        return this.size;
    }

    public ArrayList<Vector> GetWalls() {
        return this.walls;
    }

    public void SetWalls(ArrayList<Vector> walls) {
        this.walls = walls;
    }

    public static ServerResponse ConvertFromXml(String xml) throws JAXBException {
        JAXBContext jc = JAXBContext.newInstance(ServerResponse.class);
        Unmarshaller um = jc.createUnmarshaller();

        StringReader reader = new StringReader(xml);
        return (ServerResponse) um.unmarshal(reader);
    }

    @SuppressWarnings("boxing")
    public static String ConvertToXml(ServerResponse server_response) throws JAXBException {
        JAXBContext jc;
        jc = JAXBContext.newInstance(ServerResponse.class);

        Marshaller m = jc.createMarshaller();
        m.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT, true);
        StringWriter str_writer = new StringWriter();
        StreamResult result = new StreamResult(str_writer);
        m.marshal(server_response, result);
        return str_writer.toString();
    }
}
