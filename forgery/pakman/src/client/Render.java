package client;

import java.time.Clock;
import java.util.ArrayList;

import org.lwjgl.LWJGLException;
import org.lwjgl.input.Keyboard;
import org.lwjgl.opengl.Display;
import org.lwjgl.opengl.DisplayMode;
import org.lwjgl.opengl.GL11;
import org.newdawn.slick.Color;

import common.ClientActions;
import common.ClientRequest;
import common.Directions;
import common.ServerResponse;
import common.Vector;

/**
 * @author montreal <br>
 *         {@link Thread} subclass. <br>
 *         This class is used to render game state on the screen using OpenGL
 *         (LWJGL).
 */
class Render extends Thread {

    private Clock           clock;
    private CubbyHole       cubbyhole;
    private boolean         is_running;
    private Quad            pakman;
    private final Color     PAKMAN_COLOR = Color.yellow;
    private final Vector    PAKMAN_SIZE  = new Vector(17, 17);

    private ServerResponse  response;
    private final int       SCALE        = 25;
    private Text            text;
    private final Color     WALL_COLOR   = Color.gray;
    private final Vector    WALL_SIZE    = new Vector(25, 25);
    private ArrayList<Quad> walls;

    public Render(CubbyHole cubbyhole) {
        this.cubbyhole = cubbyhole;
        this.is_running = true;
        this.clock = Clock.systemUTC();
        this.response = new ServerResponse();
        this.walls = new ArrayList<Quad>();
        this.InitPakman();
    }

    @Override
    public void run() {
        Render.InitGl(800, 600);
        this.InitText();

        long start_time = this.clock.millis();
        long ticks = 0;
        long targeted_time, new_time, time_to_wait;
        while (!Display.isCloseRequested() && this.is_running) {
            new_time = this.clock.millis();
            ticks++;
            targeted_time = start_time + Render.TIME_STEP * ticks;
            time_to_wait = targeted_time - new_time;
            if (time_to_wait > 0) {
                try {
                    Thread.sleep(time_to_wait);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                    return;
                }
            }
            GL11.glClear(GL11.GL_COLOR_BUFFER_BIT);
            this.response = this.cubbyhole.GetServerResponse();
            if (this.response != null) {
                this.SetupWalls();
                this.Update();
            }
            this.Draw();
            this.ProcessUserInput();
            Display.update();
        }

        this.cubbyhole.StopClient();
        Display.destroy();
    }

    private void Draw() {
        this.pakman.Draw();
        this.text.Draw();
        this.DrawWalls();
    }

    private void DrawWalls() {
        for (Quad brick : this.walls) {
            brick.Draw();
        }
    }

    private void InitPakman() {
        this.pakman = new Quad(new Vector(-100, -100), this.PAKMAN_SIZE);
        this.pakman.SetGlColor(this.PAKMAN_COLOR.r, this.PAKMAN_COLOR.g, this.PAKMAN_COLOR.b);

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
            if (Keyboard.isKeyDown(Keyboard.KEY_RIGHT)) {
                ClientRequest request = new ClientRequest(ClientActions.MOVE, Directions.RIGHT);
                this.cubbyhole.PutClientRequest(request);
            } else if (Keyboard.isKeyDown(Keyboard.KEY_LEFT)) {
                ClientRequest request = new ClientRequest(ClientActions.MOVE, Directions.LEFT);
                this.cubbyhole.PutClientRequest(request);
            } else if (Keyboard.isKeyDown(Keyboard.KEY_DOWN)) {
                ClientRequest request = new ClientRequest(ClientActions.MOVE, Directions.DOWN);
                this.cubbyhole.PutClientRequest(request);
            } else if (Keyboard.isKeyDown(Keyboard.KEY_UP)) {
                ClientRequest request = new ClientRequest(ClientActions.MOVE, Directions.UP);
                this.cubbyhole.PutClientRequest(request);
            } else {
                ClientRequest request = new ClientRequest(ClientActions.MOVE, Directions.NONE);
                this.cubbyhole.PutClientRequest(request);
            }
        }
    }

    private void SetupWalls() {
        ArrayList<Vector> server_walls = this.response.GetWalls();
        if (server_walls.size() > 0) {
            for (Vector server_pos : server_walls) {
                Vector pos = new Vector(server_pos.GetX() * this.SCALE, server_pos.GetY() * this.SCALE);
                Quad brick = new Quad(pos, this.WALL_SIZE);
                brick.SetGlColor(this.WALL_COLOR.r, this.WALL_COLOR.g, this.WALL_COLOR.b);
                this.walls.add(brick);
            }
        }
    }

    private void Update() {
        Vector new_pakman_pos = this.response.GetPosition();
        new_pakman_pos.SetX(new_pakman_pos.GetX() * this.SCALE + 4);
        new_pakman_pos.SetY(new_pakman_pos.GetY() * this.SCALE + 4);
        this.pakman.SetPosition(new_pakman_pos);
        this.text.SetString(String.valueOf(this.response.GetScore()));

    }

    private static final long TIME_STEP = 50;

    private static void InitGl(int width, int height) {
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
}
