package client;

import common.ClientRequest;
import common.ServerResponse;

/**
 * @author montreal <br>
 *         Monitor class which helps to solve producer-consumer problem for
 *         {@link Render} and {@link NetworkGateway} classes.
 */
class CubbyHole {
    private ServerResponse response;
    private boolean        response_available = false;
    private boolean        is_client_running  = true;

    private ClientRequest  request;
    private boolean        request_available  = false;

    public ClientRequest GetClientRequest() {
        if (this.request_available == true) {
            this.request_available = false;
            return this.request;
        } else {
            return null;
        }
    }

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

    public void PutClientRequest(ClientRequest request) {
        this.request = request;
        this.request_available = true;
    }

    public void PutServerResponse(ServerResponse response) {
        if (this.response_available == false) {
            this.response = response;
            this.response_available = true;
        }
    }

    public void StopClient() {
        this.is_client_running = false;
    }
}
