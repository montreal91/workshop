package client;

import common.ServerResponse;

/**
 * @author montreal <br>
 *         Monitor class which helps to solve producer-consumer problem for
 *         {@link Render} and {@link NetworkGateway} classes.
 */
class CubbyHole {
    private ServerResponse response;
    private boolean response_available = false;
    private boolean is_client_running = true;

    public ServerResponse GetServerResponse() {
        if (response_available == true) {
            response_available = false;
            return response;
        } else {
            return null;
        }
    }

    public boolean IsClientRunning() {
        return this.is_client_running;
    }

    public void PutServerResponse(ServerResponse response) {
        this.response = response;
        this.response_available = true;
    }

    public void StopClient() {
        this.is_client_running = false;
    }
}
