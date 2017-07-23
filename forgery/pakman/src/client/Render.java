package client;

import java.util.ArrayList;

import org.lwjgl.LWJGLException;
import org.lwjgl.input.Keyboard;
import org.lwjgl.opengl.Display;
import org.lwjgl.opengl.DisplayMode;
import org.lwjgl.opengl.GL11;
import org.newdawn.slick.Color;

import common.ClientActions;
import common.ClientRequest;
import common.ServerResponse;
import common.Vector;

/**
 * @author montreal <br>
 *         {@link Thread} subclass. <br>
 *         This class is used to render game state on the screen using OpenGL
 *         (LWJGL).
 */
class Render extends Thread {
    private CubbyHole       cubbyhole;
    private boolean         is_running;
    private ServerResponse  response;
    private Text            text;
    private ArrayList<Quad> walls;

    private final Vector    WALL_SIZE  = new Vector(25, 25);
    private final Color     WALL_COLOR = Color.gray;
    private final int       SCALE      = 25;

    public Render(CubbyHole cubbyhole) {
        this.cubbyhole = cubbyhole;
        this.is_running = true;
        this.response = new ServerResponse();
        this.walls = new ArrayList<Quad>();
    }

    @Override
    public void run() {
        this.InitGl(800, 600);
        this.InitText();

        System.out.println("OpenGL version: " + GL11.glGetString(GL11.GL_VERSION));
        while (!Display.isCloseRequested() && this.is_running) {
            GL11.glClear(GL11.GL_COLOR_BUFFER_BIT);
            this.response = this.cubbyhole.GetServerResponse();
            if (this.response != null) {
                this.text.SetString(String.valueOf(this.response.GetScore()));
                this.SetupWalls();
            }
            this.Draw();
            this.ProcessUserInput();
            Display.update();
        }

        this.cubbyhole.StopClient();
        Display.destroy();
    }

    private void SetupWalls() {
        ArrayList<Vector> server_walls = this.response.GetWalls();
        if (server_walls.size() > 0) {
            for (Vector server_pos : server_walls) {
                Vector pos = new Vector(server_pos.GetX() * SCALE, server_pos.GetY() * SCALE);
                Quad brick = new Quad(pos, WALL_SIZE);
                brick.SetGlColor(WALL_COLOR.r, WALL_COLOR.g, WALL_COLOR.b);
                this.walls.add(brick);
            }
        }
    }

    private void Draw() {
        this.text.Draw();
        this.DrawWalls();
    }

    private void DrawWalls() {
        for (Quad brick : this.walls) {
            brick.Draw();
        }
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
        this.text.SetPosition(700, 50);
    }

    private void ProcessUserInput() {
        while (Keyboard.next()) {
            if (Keyboard.getEventKey() == Keyboard.KEY_ESCAPE) {
                this.is_running = false;
            }
            if (Keyboard.getEventKey() == Keyboard.KEY_R) {
                ClientRequest request = new ClientRequest(ClientActions.RESTART);
                this.cubbyhole.PutClientRequest(request);
            }
        }
    }
}
