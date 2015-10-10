
from flask.ext.wtf      import Form

from wtforms            import StringField, PasswordField
from wtforms            import BooleanField, SubmitField
from wtforms            import ValidationError

from wtforms.validators import Required, Email, Length
from wtforms.validators import Regexp, EqualTo

from ..models           import XUser


class XLoginForm( Form ):
    email       = StringField(
        "Email",
        validators=[ Required(), Length( 1, 64), Email() ]
    )
    password    = PasswordField( "Password", validators=[ Required() ] )
    remember_me = BooleanField( "Keep me logged in" )
    submit      = SubmitField( "Log In" )



class XRegistrationForm( Form ):
    email       = StringField(
        "Email",
        validators=[ Required(), Length( 1, 64), Email() ]
    )
    username    = StringField(
        "Userrname",
        validators=[
            Required(),
            Length( 1, 64 ),
            Regexp(
                "^[A-Za-z][A-Za-z0-9_.]*$",
                0,
                "Userrnames must have only letters, numbers, dots or underscores"
            )
        ]
    )
    password = PasswordField( 
        "Password",
        validators=[ Required(), EqualTo( "password2", message="Passwords must match." ) ] 
    )
    password2 = PasswordField( "Confirm password", validators=[ Required() ] )
    submit = SubmitField( "Register" )


    def validate_email( self, field ):
        if XUser.query.filter_by( email=field.data ).first():
            raise ValidationError( "Email already registered" )


    def validate_username( self, field ):
        if XUser.query.filter_by( username=field.data ).first():
            raise ValidationError( "Username is already in use." )
