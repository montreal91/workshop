
class MyServe( object ):
    """docstring for MyServe"""
    def __init__( self, accuracy=50, quality=50 ):
        super( MyServe, self ).__init__()
        self.__accuracy = accuracy # Percentage of successive serves
        self.__quality  = quality

    @property 
    def accuracy( self ):
        return self.__accuracy

    @property 
    def quality( self ):
        return self.__quality
        