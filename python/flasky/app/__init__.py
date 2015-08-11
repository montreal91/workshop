
# Application package constructor

from flask                  import Flask
from flask                  import render_template
from flask.ext.bootstrap    import Bootstrap
from flask.ext.mail         import Mail
from flask.ext.moment       import Moment
from flask.ext.sqlalchemy   import SQLAlchemy

from config                 import config


bootstrap   = Bootstrap()
mail        = Mail()
moment      = Moment()
db          = SQLAlchemy()


def CreateApp( config_name ):
    app = Flask( __name__ )
    app.config.from_object( config[ config_name ] )
    config[ config_name ].InitApp( app )

    bootstrap.init_app( app )
    mail.init_app( app )
    moment.init_app( app )
    db.init_app( app )

    # Blueprints registration
    from .main import main as main_blueprint
    app.register_blueprint( main_blueprint )

    return app