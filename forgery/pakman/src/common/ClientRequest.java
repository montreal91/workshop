package common;

import java.io.StringReader;
import java.io.StringWriter;

import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Marshaller;
import javax.xml.bind.Unmarshaller;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.transform.stream.StreamResult;

import client.PakmanClient;

/**
 * @author montreal <br>
 *         This class is used by {@link PakmanClient} to send all important
 *         information to the server.<br>
 */
@XmlRootElement
public class ClientRequest {

    @XmlElement
    private String action;

    public ClientRequest() {
        this.action = ClientActions.QUIT.GetAction();
    }

    public ClientRequest(ClientActions action) {
        this.action = action.GetAction();
    }

    public String GetAction() {
        return this.action;
    }

    public static String ConvertToXml(ClientRequest request) throws JAXBException {
        JAXBContext jc;
        jc = JAXBContext.newInstance(ClientRequest.class);

        Marshaller m = jc.createMarshaller();
        m.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT, true);
        StringWriter str_writer = new StringWriter();
        StreamResult result = new StreamResult(str_writer);
        m.marshal(request, result);
        return str_writer.toString();
    }

    public static ClientRequest ConvertFromXml(String xml) throws JAXBException {
        JAXBContext jc = JAXBContext.newInstance(ClientRequest.class);
        Unmarshaller um = jc.createUnmarshaller();

        StringReader reader = new StringReader(xml);
        return (ClientRequest) um.unmarshal(reader);
    }
}
