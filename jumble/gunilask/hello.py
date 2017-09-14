
from flask import Flask
from werkzeug.contrib.fixers import ProxyFix

app = Flask(__name__)

@app.route("/")
def hello():
    return "Hello World!"


@app.route("/<text>/")
def custom_hello(text):
    return "Hello %s" % text

app.wsgi_app = ProxyFix(app.wsgi_app)
