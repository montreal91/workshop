
class MyName( object ):
    def __init__( self, first_name="Random", last_name="Dude" ):
        super( MyName, self ).__init__()
        self.__first_name   = first_name
        self.__last_name    = last_name

    @property
    def first_name( self ):
        return self.__first_name

    @property
    def last_name( self ):
        return self.__last_name

    @property
    def full_name( self ):
        return self.first_name + " " + self.last_name
    