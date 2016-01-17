
from werkzeug.security  import generate_password_hash, check_password_hash

from itsdangerous       import TimedJSONWebSignatureSerializer as Serializer

from flask              import current_app
from flask.ext.login    import UserMixin

from .                  import db, login_manager


class XRole( db.Model ):
    __tablename__   = "roles"
    pk              = db.Column( db.Integer, primary_key= True )
    name            = db.Column( db.String( 64 ), unique=True )
    default         = db.Column( db.Boolean, default=False, index=True )
    permissions     = db.Column( db.Integer )
    users           = db.relationship( "XUser", backref="role" )

    @staticmethod
    def InsertRoles():
        roles = {
            "User": ( 
                XPermission.FOLLOW | 
                XPermission.COMMENT | 
                XPermission.WRITE_ARTICLES, 
                True,
            ),
            "Moderator": (
                XPermission.FOLLOW | 
                XPermission.COMMENT | 
                XPermission.WRITE_ARTICLES |
                XPermission.MODERATE_COMMENTS,
                False,
            ),
            "Administrator": ( 0xff, False ),
        }

        for r in roles:
            role = XRole.query.filter_by( name=r ).first()
            if role is None:
                role = Role( name=r )
            role.permissions = roles[ r ][ 0 ]
            role.default = roles[ r ][ 1 ]
            db.session.add( role )
        db.session.commit()

    def __repr__( self ):
        return "<Role %r>" % self.name


class XUser( UserMixin, db.Model ):
    __tablename__   = "users"
    pk              = db.Column( db.Integer, primary_key=True )
    username        = db.Column( db.String( 64 ), unique=True, index=True )
    email           = db.Column( db.String( 64 ), unique=True, index=True )
    role_pk         = db.Column( db.Integer, db.ForeignKey( "roles.pk" ) )
    password_hash   = db.Column( db.String( 128 ) )
    confirmed       = db.Column( db.Boolean, default=False )


    @property
    def password( self ):
        raise AttributeError( "password is not a readable attribute" )


    @password.setter
    def password( self, password ):
        self.password_hash = generate_password_hash( password )


    def VerifyPassword( self, password ):
        return check_password_hash( self.password_hash, password )


    def GenerateConfirmationToken( self, expiration=3600 ):
        s = Serializer( current_app.config["SECRET_KEY"], expiration )
        return s.dumps( { "confirm": self.pk } )


    def Confirm( self, token ):
        s = Serializer( current_app.config["SECRET_KEY"] )
        try:
            data = s.loads( token )
        except:
            return False

        if data.get( "confirm" ) != self.pk:
            return False

        self.confirmed = True
        db.session.add( self )
        return True

    def GenerateResetToken( self, expiration=3600 ):
        s = Serializer( current_app.config["SECRET_KEY"], expiration )
        return s.dumps( {"reset": self.pk} )


    def ResetPassword( self, token, new_password ):
        s = Serializer( current_app.config["SECRET_KEY"] )
        try:
            data = s.loads( token )
        except:
            return False

        if data.get( "reset" ) != self.pk:
            return False

        self.password = new_password
        db.session.add( self )
        return True


    def GenerateEmailChangeToken( self, new_email, expiration=3600 ):
        s = Serializer( current_app.config["SECRET_KEY"], expiration )
        return s.dumps( {"change_email": self.pk, "new_email": new_email} )


    def ChangeEmail( self, token ):
        s = Serializer( current_app.config["SECRET_KEY"] )
        try:
            data = s.loads( token )
        except:
            return False

        if data.get( "change_email" ) != self.pk:
            return False

        new_email = data.get( "new_email" )
        if new_email is None:
            return False
        if self.query.filter_by( email=new_email ).first() is not None:
            return False

        self.email = new_email
        db.session.add( self )
        return True


    def get_id( self ):
        return self.pk
    

    def __repr__( self ):
        return "<User %r>" % self.username


@login_manager.user_loader
def load_user( user_id ):
    return XUser.query.get( int( user_id ) )


class XPermission:
    FOLLOW              = 0x01
    COMMENT             = 0x02
    WRITE_ARTICLES      = 0x04
    MODERATE_COMMENTS   = 0x08
    ADMINISTER          = 0x80
