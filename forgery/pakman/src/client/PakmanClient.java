package client;

/**
 * @author montreal <br>
 *         Entry point for client application.<br>
 *         Runs {@link NetworkGateway} and {@link Render} in two different
 *         threads.
 *
 */
public class PakmanClient {
    public static void main(String[] main) {
        CubbyHole ch = new CubbyHole();
        NetworkGateway ng = new NetworkGateway(ch);
        Render render = new Render(ch);

        ng.start();
        render.start();
    }
}
