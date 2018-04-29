
from flask import Flask
from flask import render_template
from flask import request
from flask import jsonify


app = Flask( __name__ )
app.clicks = 0

@app.route( "/" )
def hello():
    return render_template( "base.html", clicks=app.clicks )

@app.route( "/_count_characters/", methods=["POST"] )
def count_characters():
    text = request.form["text"]
    app.clicks += 1
    return jsonify( result=len( text ),clicks=app.clicks )

if __name__ == '__main__':
    app.run(debug=True)
