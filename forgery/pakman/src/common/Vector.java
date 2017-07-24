
package common;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlRootElement;

/**
 * @author montreal <br>
 *         Simple implementation of the abstract 2D vector.<br>
 *         Can be marshaled to and from XML.
 *
 */
@XmlRootElement
@XmlAccessorType(XmlAccessType.FIELD)
public class Vector {
    private int x, y;

    public Vector() {
        this.x = 0;
        this.y = 0;
    }

    public Vector(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public Vector(Vector v) {
        this.x = v.x;
        this.y = v.y;
    }

    public int GetX() {
        return this.x;
    }

    public int GetY() {
        return this.y;
    }

    public void SetX(int x) {
        this.x = x;
    }

    public void SetY(int y) {
        this.y = y;
    }
}
