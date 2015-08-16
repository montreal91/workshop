
from flask import render_template
from . import auth


@auth.route( "/login" )
def Login():
    return render_template( "auth/login.html" )
