package client;

import java.awt.Font;
import java.io.InputStream;

import org.lwjgl.opengl.GL11;
import org.newdawn.slick.Color;
import org.newdawn.slick.TrueTypeFont;
import org.newdawn.slick.util.ResourceLoader;

import common.Vector;

/**
 * @author montreal <br>
 *         Helper class to render text on the screen.
 */
public class Text {
    private TrueTypeFont font;
    private Font         awt_font;
    private String       string;
    private float        size;
    private Color        color;
    private Vector       position;

    public Text() {
        this.string = "";
        this.color = Color.white;
        this.size = 10.0f;
        this.position = new Vector();
        this.LoadFont();
    }

    public Text(String string, int size) {
        this.string = string;
        this.size = size;
        this.color = Color.white;
        this.position = new Vector();
        this.LoadFont();
    }

    public void Draw() {
        GL11.glEnable(GL11.GL_BLEND);
        GL11.glBlendFunc(GL11.GL_SRC_ALPHA, GL11.GL_ONE_MINUS_SRC_ALPHA);
        this.font.drawString(this.position.GetX(), this.position.GetY(), this.string, this.color);
        GL11.glDisable(GL11.GL_BLEND);
    }

    public void SetColor(Color color) {
        this.color = color;
    }

    public void SetPosition(int x, int y) {
        this.position = new Vector(x, y);
    }

    public void SetSize(float size) {
        this.size = size;
        this.ReloadFont();
    }

    public void SetString(String string) {
        this.string = string;
    }

    private void LoadFont() {
        try {
            InputStream inputStream = ResourceLoader.getResourceAsStream("DroidSansMono.ttf");
            this.awt_font = Font.createFont(Font.TRUETYPE_FONT, inputStream);
            this.awt_font = this.awt_font.deriveFont(10.0f);
            this.font = new TrueTypeFont(this.awt_font, true);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void ReloadFont() {
        this.awt_font = this.awt_font.deriveFont(this.size);
        this.font = new TrueTypeFont(this.awt_font, true);
    }
}
