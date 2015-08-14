
from . import db


class XRole( db.Model ):
    __tablename__   = "roles"
    pk              = db.Column( db.Integer, primary_key= True )
    name            = db.Column( db.String( 64 ), unique=True )
    default         = db.Column( db.Boolean, default=False, index=True )
    permissions     = db.Column( db.Integer )
    users           = db.relationship( "XUser", backref="role" )


    def __repr__( self ):
        return "<Role %r>" % self.name


class XUser( db.Model ):
    __tablename__   = "users"
    pk              = db.Column( db.Integer, primary_key=True )
    username        = db.Column( db.String( 64 ), unique=True, index=True )
    role_pk         = db.Column( db.Integer, db.ForeignKey( "roles.pk" ) )

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
        return "<User %r>" % self.username


class XPermission:
    FOLLOW = 0x01
    COMMENT = 0x02
    WRITE_ARTICLES = 0x04
    MODERATE_COMMENTS = 0x08
    ADMINISTER = 0x80

