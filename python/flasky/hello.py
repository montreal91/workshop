
#! /usr/bin/python

from datetime               import datetime

from flask                  import Flask
from flask                  import redirect, session, url_for
from flask                  import flash, render_template
from flask.ext.bootstrap    import Bootstrap
from flask.ext.script       import Manager
from flask.ext.moment       import Moment
from flask.ext.wtf          import Form

from wtforms                import StringField, SubmitField
from wtforms.validators     import Required


app         = Flask( __name__ )
app.config[ "SECRET_KEY" ] = "vivid vervet"

manager     = Manager( app )
bootstrap   = Bootstrap( app )
moment      = Moment( app )



class NameForm( Form ):
    name    = StringField( "What is your name?", validators=[ Required() ] )
    submit  = SubmitField( "Submit" )


@app.errorhandler( 404 )
def PageNotFound( e ):
    return render_template( "404.html" ), 404


@app.errorhandler( 500 )
def InternalServerError( e ):
    return render_template( "500.html" ), 500


@app.route( "/", methods=[ "GET", "POST" ] )
def Index():
    form = NameForm()
    if form.validate_on_submit():
        old_name = session.get( "name" )
        if old_name is not None and old_name != form.name.data:
            flash( "Looks like you have changed your name!" )
        session[ "name" ] = form.name.data
        return redirect( url_for( "Index" ) )
    return render_template( "index.html", form=form, name=session.get( "name" ) )


if __name__ == '__main__':
    manager.run()
