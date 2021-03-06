
#!/usr/bin/env python

import os

from flask.ext.script   import Manager, Shell
from flask.ext.migrate  import Migrate, MigrateCommand

from app                import CreateApp, db
from app.models         import XUser, XRole, XPermission
from app.models         import XPost


app     = CreateApp( os.getenv( "FLASK_CONFIG" ) or "default" )
manager = Manager( app )
migrate = Migrate( app, db )

def MakeShellContext():
    return dict(
        app=app,
        db=db,
        XUser=XUser,
        XRole=XRole,
        XPermission=XPermission,
        XPost=XPost
    )

manager.add_command( "shell", Shell( make_context=MakeShellContext ) )
manager.add_command( "db", MigrateCommand )


@manager.command
def test():
    import unittest
    tests = unittest.TestLoader().discover( "tests" )
    unittest.TextTestRunner( verbosity=2 ).run( tests )

if __name__ == '__main__':
    manager.run()

