
from flask import Flask, request, jsonify
from flask import session
from flask.ext.bcrypt import Bcrypt
from flask.ext.sqlalchemy import SQLAlchemy

from project.config import BaseConfig


# Config
app = Flask(__name__)
app.config.from_object(BaseConfig)

bcrypt = Bcrypt(app)
db = SQLAlchemy(app)


from project.models import User

# Routes
@app.route("/")
def index():
    return app.send_static_file("index.html")


@app.route("/api/register/", methods=["POST"])
def register():
    json_data   = request.json
    user        = User(
        email=json_data["email"],
        password=json_data["password"]
    )
    try:
        db.session.add(user)
        db.session.commit()
        status = "success"
    except:
        status = "this user is already registered"

    db.session.close()
    return jsonify({"result": status})


@app.route("/api/login/", methods=["POST"])
def login():
    json_data = request.json
    user = User.query.filter_by(email=json_data["email"]).first()
    if user and bcrypt.check_password_hash(
        user.password,
        json_data["password"]
    ):
        session["logged_in"] = True
        status = True
    else:
        status = False
    return jsonify({"result": status})


@app.route("/api/logout/")
def logout():
    session.pop("logged_in", None)
    return jsonify({"result": "success"})
