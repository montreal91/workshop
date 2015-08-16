
from flask.ext.wtf      import Form

from wtforms            import StringField, PasswordField
from wtforms            import BooleanField, SubmitField

from wtforms.validators import Required, Email, Length

class XLoginForm( Form ):
    email = StringField(
        "Email",
        validators=[ Required(), Length( 1, 64), Email() ]
    )
    password = PasswordField( "Password", validators=[ Required() ] )
    remember_me = BooleanField( "Keep me logged in" )
    submit = SubmitField( "Log In" )
