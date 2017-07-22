package client;

import java.awt.Font;
import java.io.InputStream;

import org.newdawn.slick.Color;
import org.newdawn.slick.TrueTypeFont;
import org.newdawn.slick.util.ResourceLoader;

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

    public Text() {
        this.string = "";
        this.color = Color.white;
        this.size = 10.0f;
        this.LoadFont();
    }

    public Text(String string, int size) {
        this.string = string;
        this.size = size;
        this.color = Color.white;
        this.LoadFont();
    }

    public void Draw() {
        this.font.drawString(50, 50, this.string, this.color);
    }

    public void SetColor(Color color) {
        this.color = color;
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
