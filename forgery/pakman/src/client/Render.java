package client;

import org.lwjgl.LWJGLException;
import org.lwjgl.input.Keyboard;
import org.lwjgl.opengl.Display;
import org.lwjgl.opengl.DisplayMode;
import org.lwjgl.opengl.GL11;
import org.newdawn.slick.Color;

import common.ServerResponse;

/**
 * @author montreal <br>
 *         {@link Thread} subclass. <br>
 *         This class is used to render game state on the screen using OpenGL
 *         (LWJGL).
 */
class Render extends Thread {
    private CubbyHole      cubbyhole;
    private ServerResponse response;
    private Text           text;

    public Render(CubbyHole cubbyhole) {
        this.cubbyhole = cubbyhole;
        this.response = new ServerResponse();
    }

    @Override
    public void run() {
        this.InitGl(800, 600);
        this.InitText();
        boolean cont = true;
        while (!Display.isCloseRequested() && cont) {
            GL11.glClear(GL11.GL_COLOR_BUFFER_BIT);
            this.response = this.cubbyhole.GetServerResponse();
            if (this.response != null) {
                this.text.SetString(String.valueOf(this.response.GetScore()));
            }
            this.Draw();
            Display.update();
            while (Keyboard.next()) {
                if (Keyboard.getEventKey() == Keyboard.KEY_ESCAPE) {
                    cont = false;
                }
            }
        }

        this.cubbyhole.StopClient();
        Display.destroy();
    }

    private void Draw() {
        this.text.Draw();
    }

    private void InitGl(int width, int height) {
        try {
            Display.setDisplayMode(new DisplayMode(width, height));
            Display.create();
            Display.setVSyncEnabled(true);
        } catch (LWJGLException e) {
            e.printStackTrace();
            System.exit(0);
        }

        GL11.glEnable(GL11.GL_TEXTURE_2D);
        GL11.glShadeModel(GL11.GL_SMOOTH);
        GL11.glDisable(GL11.GL_DEPTH_TEST);
        GL11.glDisable(GL11.GL_LIGHTING);

        GL11.glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        GL11.glClearDepth(1);

        GL11.glEnable(GL11.GL_BLEND);
        GL11.glBlendFunc(GL11.GL_SRC_ALPHA, GL11.GL_ONE_MINUS_SRC_ALPHA);

        GL11.glViewport(0, 0, width, height);
        GL11.glMatrixMode(GL11.GL_PROJECTION);
        GL11.glLoadIdentity();
        GL11.glOrtho(0, width, height, 0, 1, -1);
        GL11.glMatrixMode(GL11.GL_MODELVIEW);
    }

    private void InitText() {
        this.text = new Text();
        this.text.SetColor(Color.gray);
        this.text.SetSize(24.0f);
    }
}
