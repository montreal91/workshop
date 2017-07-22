package common;

/**
 * @author montreal <br>
 *         Enumeration of all possible client actions.
 */
public enum ClientActions {
    QUIT("quit"), RESTART("restart");

    private String action;

    private ClientActions(String action) {
        this.action = action;
    }

    public String GetAction() {
        return this.action;
    }
}
