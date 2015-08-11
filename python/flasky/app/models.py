
from . import db


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