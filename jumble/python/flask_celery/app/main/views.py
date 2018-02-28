
import json

from flask import jsonify
from flask import render_template
from flask import request

from app.main import main
# from app.main.tasks import countdown


# from app import socketio

# print(__name__, socketio.server)

@main.route("/")
def index():
    return render_template("index.html")

@main.route("/start_countdown/", methods=["POST"])
def start_countdown():
    data = json.loads(request.data.decode())
    # countdown.delay(int(data["time"]))
    return jsonify(time_to_wait=data["time"])
