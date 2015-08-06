
#! /usr/bin/python

from datetime               import datetime

from flask                  import Flask, render_template
from flask.ext.bootstrap    import Bootstrap
from flask.ext.script       import Manager
from flask.ext.moment       import Moment

app         = Flask( __name__ )
bootstrap   = Bootstrap( app )
moment      = Moment( app )

manager     = Manager( app )


@app.errorhandler( 404 )
def PageNotFound( e ):
    return render_template( "404.html" ), 404


@app.errorhandler( 500 )
def InternalServerError( e ):
    return render_template( "500.html" ), 500


@app.route( "/" )
def Index():
    return render_template( "index.html", current_time=datetime.utcnow() )

@app.route( "/user/<name>/" )
def User( name ):
    return render_template( "user.html", name=name )

if __name__ == '__main__':
    manager.run()
