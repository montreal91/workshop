
from flask.ext.wtf          import Form

from wtforms                import StringField, SubmitField, TextAreaField
from wtforms                import BooleanField, SelectField, ValidationError
from wtforms.validators     import Required, Length, Email
from wtforms.validators     import Regexp

from ..models               import XRole, XUser


class XNameForm( Form ):
    name    = StringField( "What is your name?", validators=[Required()] )
    submit  = SubmitField( "Submit" )


class XEditProfileForm( Form ):
    name        = StringField( "Real Name", validators=[Length( 0, 64 )] )
    location    = StringField( "Location", validators=[Length( 0, 64 )] )
    about_me    = TextAreaField( "About me" )
    submit      = SubmitField( "Submit" )


class XEditProfileAdminForm( Form ):
    email       = StringField( "Email", validators=[Required(), Length( 1, 64 ), Email()] )
    username    = StringField(
        "Username",
        validators= [
            Required(),
            Length( 1, 64 ),
            Regexp(
                "^[A-Za-z][A-Za-z0-9.]*$",
                0,
                "Usernames must have only letters, numbers, dots and underscores."
            )
        ]
    )
    confirmed   = BooleanField( "Confirmed" )
    role        = SelectField( "Role", coerce=int )
    name        = StringField( "Real Name", validators=[Length( 0, 64 )] )
    location    = StringField( "Location", validators=[Length( 0, 64 )] )
    about_me    = TextAreaField( "About me" )
    submit      = SubmitField( "Submit" )

    def __init__( self, user, *args, **kwargs ):
        super( XEditProfileAdminForm, self ).__init__( *args, **kwargs )

        self.role.choices = [
            ( role.pk, role.name ) for role in XRole.query.order_by( XRole.name ).all()
        ]
        self.user = user


    def validate_email( self, field ):
        if field.data != self.user.email and XUser.query.filter_by( email=field.data ).first():
            raise ValidationError( "Email is already registered." )


    def validate_username( self, field ):
        if field.data != self.user.username and XUser.query.filter_by( username=field.data ).first():
            raise ValidationError( "Username is already in use." )
