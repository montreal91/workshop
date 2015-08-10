
#! /usr/bin/python

import os

from datetime               import datetime

from flask                  import Flask
from flask                  import redirect, session, url_for
from flask                  import flash, render_template
from flask.ext.bootstrap    import Bootstrap
from flask.ext.migrate      import Migrate, MigrateCommand
from flask.ext.moment       import Moment
from flask.ext.script       import Manager, Shell
from flask.ext.sqlalchemy   import SQLAlchemy
from flask.ext.wtf          import Form

from wtforms                import StringField, SubmitField
from wtforms.validators     import Required


basedir = os.path.abspath( os.path.dirname( __file__ ) )

app         = Flask( __name__ )
app.config[ "SECRET_KEY" ] = "vivid vervet"
app.config[ "SQLALCHEMY_DATABASE_URI" ] = "sqlite:///" + os.path.join( basedir, "data.sqlite" )
app.config[ "SQLALCHEMY_COMMIT_ON_TEARDOWN" ] = True

manager     = Manager( app )
bootstrap   = Bootstrap( app )
db          = SQLAlchemy( app )
migrate     = Migrate( app, db )
moment      = Moment( app )


class XRole( db.Model ):
    __tablename__   = "roles"
    pk              = db.Column( db.Integer, primary_key= True )
    name            = db.Column( db.String( 64 ), unique=True )
    users           = db.relationship( "XUser", backref="role" )

    def __repr__( self ):
        return "<Role %r>" % self.name

class XUser( db.Model ):
    __tablename__   = "users"
    pk              = db.Column( db.Integer, primary_key=True )
    username        = db.Column( db.String( 64 ), unique=True, index=True )
    role_pk         = db.Column( db.Integer, db.ForeignKey( "roles.pk" ) )

    def __repr__( self ):
        return "<User %r>" % self.username


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
        user = XUser.query.filter_by( username=form.name.data ).first()
        if user is None:
            user = XUser( username=form.name.data )
            db.session.add( user )
            db.session.commit()
            session[ "known" ] = False
        else:
            session[ "known" ] = True

        session[ "name" ]   = form.name.data
        form.name.data      = ""
        return redirect( url_for( "Index" ) )
    return render_template(
        "index.html",
        form=form,
        name=session.get( "name" ),
        known=session.get( "known", False ),
    )


def MakeShellContext():
    return dict(
        app=app,
        db=db,
        XUser=XUser,
        XRole=XRole,
    )

manager.add_command( "shell", Shell( make_context=MakeShellContext ) )
manager.add_command( "db", MigrateCommand )


if __name__ == '__main__':
    manager.run()
