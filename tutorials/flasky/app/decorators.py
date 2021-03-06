
from functools          import wraps

from flask              import abort
from flask.ext.login    import current_user

from .models            import XPermission


def PermissionRequired( permission ):
    def decorator( f ):
        @wraps( f )
        def decorated_function( *args, **kwargs ):
            if not current_user.Can( permission ):
                abort( 403 )
            return f( *args, **kwargs )
        return decorated_function
    return decorator


def AdminRequired( f ):
    return PermissionRequired( XPermission.ADMINISTER )( f )
