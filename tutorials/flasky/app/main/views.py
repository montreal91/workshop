
from flask      import render_template

from .          import main


@main.route( "/", methods=[ "GET", "POST" ] )
def Index():
    return render_template( "index.html" )
