package client;

import org.lwjgl.opengl.GL11;

import common.Vector;

/**
 * @author montreal <br>
 *         Simple rectangle class to draw it on the screen.
 *
 */
public class Quad {
    private float  gl_blue;
    private float  gl_green;
    private float  gl_red;
    private Vector pos;
    private Vector size;

    public Quad(Vector pos, Vector size) {
        this.pos = pos;
        this.size = size;

        this.gl_red = 0;
        this.gl_green = 0;
        this.gl_blue = 0;
    }

    public void Draw() {
        GL11.glColor4f(this.gl_red, this.gl_green, this.gl_blue, 1.0f);

        // draw quad
        GL11.glBegin(GL11.GL_QUADS);
        {
            GL11.glVertex2f(this.pos.GetX(), this.pos.GetY());
            GL11.glVertex2f(this.pos.GetX() + this.size.GetX(), this.pos.GetY());
            GL11.glVertex2f(this.pos.GetX() + this.size.GetX(), this.pos.GetY() + this.size.GetY());
            GL11.glVertex2f(this.pos.GetX(), this.pos.GetY() + this.size.GetY());
        }
        GL11.glEnd();
    }

    public void SetGlColor(float red, float green, float blue) {
        this.gl_red = red;
        this.gl_green = green;
        this.gl_blue = blue;
    }

    public void SetPosition(Vector pos) {
        this.pos = pos;
    }

}
