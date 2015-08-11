
#!/usr/bin/env python

import os

from flask.ext.script import Manager, Shell
from flask.ext.migrate import Migrate, MigrateCommand

from app import CreateApp, db
from app.models import XUser, XRole


app = CreateApp( os.getenv( "FLASK_CONFIG" ) or "default" )
manager = Manager( app )
migrate = Migrate( app, db )

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

