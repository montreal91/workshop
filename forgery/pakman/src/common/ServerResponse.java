
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
    @XmlAttribute
    private int               x;

    @XmlAttribute
    private int               y;

    @XmlAttribute
    private int               score;

    @XmlElement
    private Vector            size;

    @XmlElement
    private ArrayList<Vector> walls;

    public ServerResponse() {
        this.x = Integer.MIN_VALUE;
        this.y = Integer.MIN_VALUE;
        this.score = Integer.MIN_VALUE;
        this.size = new Vector();
        this.walls = new ArrayList<Vector>();
    }

    public ServerResponse(int x, int y, int score, Vector size) {
        this.x = x;
        this.y = y;
        this.score = score;
        this.size = size;
    }

    public int GetX() {
        return this.x;
    }

    public int GetY() {
        return this.y;
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

    public static ServerResponse ConvertFromXml(String xml) throws JAXBException {
        JAXBContext jc = JAXBContext.newInstance(ServerResponse.class);
        Unmarshaller um = jc.createUnmarshaller();

        StringReader reader = new StringReader(xml);
        return (ServerResponse) um.unmarshal(reader);
    }
}
