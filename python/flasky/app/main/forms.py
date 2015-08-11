
from flask.ext.wtf          import Form

from wtforms                import StringField, SubmitField
from wtforms.validators     import Required


class XNameForm( Form ):
    name    = StringField( "What is your name?", validators=[ Required() ] )
    submit  = SubmitField( "Submit" )
