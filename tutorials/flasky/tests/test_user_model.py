
from unittest import TestCase

from app.models import XUser


class XUserModelTestCase( TestCase ):
    def test_password_setter( self ):
        u = XUser( password="cat" )
        self.assertTrue( u.password_hash is not None )

    def test_no_password_getter( self ):
        u = XUser( password="dog" )
        with self.assertRaises( AttributeError ):
            u.password

    def test_password_verification( self ):
        u = XUser( password="fox" )
        self.assertTrue( u.VerifyPassword( "fox" ) )
        self.assertFalse( u.VerifyPassword( "cat" ) )

    def test_password_salts_are_random( self ):
        u1 = XUser( password="cat" )
        u2 = XUser( password="fox" )
        self.assertTrue( u1.password_hash != u2.password_hash )
