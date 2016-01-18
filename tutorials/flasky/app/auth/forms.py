
from flask.ext.wtf      import Form

from wtforms            import StringField, PasswordField, BooleanField
from wtforms            import SubmitField, ValidationError

from wtforms.validators import Required, Email, Length
from wtforms.validators import Regexp, EqualTo

from ..models           import XUser


class XLoginForm( Form ):
    email       = StringField(
        "Email",
        validators=[Required(), Length( 1, 64), Email()]
    )
    password    = PasswordField( "Password", validators=[Required()] )
    remember_me = BooleanField( "Keep me logged in" )
    submit      = SubmitField( "Log In" )


class XRegistrationForm( Form ):
    email       = StringField(
        "Email",
        validators=[Required(), Length( 1, 64), Email()]
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
    password    = PasswordField(
        "Password",
        validators=[Required(), EqualTo( "password2", message="Passwords must match." )]
    )
    password2   = PasswordField( "Confirm password", validators=[Required()] )
    submit      = SubmitField( "Register" )


    def validate_email( self, field ):
        if XUser.query.filter_by( email=field.data ).first():
            raise ValidationError( "Email already registered" )


    def validate_username( self, field ):
        if XUser.query.filter_by( username=field.data ).first():
            raise ValidationError( "Username is already in use." )


class XChangePasswordForm( Form ):
    old_password    = PasswordField( "Old password", validators=[Required()] )
    password        = PasswordField( 
        "New password", 
        validators=[
            Required(),
            EqualTo("password2", message="Passwords must match"),
        ]
    )
    password2       = PasswordField( "Confirm new password", validators=[Required()] )
    submit          = SubmitField( "Update Password" )


class XPasswordResetRequestForm( Form ):
    email   = StringField( 
        "Email",
        validators=[
            Required(),
            Length( 1, 64 ),
            Email()
        ]
    )
    submit  = SubmitField( "Reset Password" )


class XPasswordResetForm( Form ):
    email           = StringField( 
        "Email",
        validators=[
            Required(),
            Length( 1, 64 ),
            Email()
        ]
    )
    password        = PasswordField( 
        "New password", 
        validators=[
            Required(),
            EqualTo("password2", message="Passwords must match"),
        ]
    )
    password2       = PasswordField( "Confirm new password", validators=[Required()] )
    submit          = SubmitField( "Reset Password" )

    def validate_email( self, field ):
        if User.query.filter_by( email=field.data ).first() is None:
            raise ValidationError( "Unknown email address." )


class XChangeEmailForm( Form ):
    email       = StringField( 
        "Email",
        validators=[
            Required(),
            Length( 1, 64 ),
            Email()
        ]
    )
    password    = PasswordField( 
        "Password", 
        validators=[
            Required(),
            EqualTo("password2", message="Passwords must match"),
        ]
    )
    submit      = SubmitField( "Update Email Address" )

    def validate_email( self, field ):
        if User.query.filter_by( email=field.data ).first() is None:
            raise ValidationError( "Email already registered." )
