
import socket

class MyClientSocket( object ):
    def __init__( self ):
        super( MyClientSocket, self ).__init__()

        self.HOST   = "localhost"
        self.PORT   = 50007
        self.s      = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
        self.s.connect( ( self.HOST, self.PORT ) )


    def SendData( self, data ):
        data = str( data )
        self.s.sendall( bytes( data.encode() ) )


    def RecieveData( self ):
        data = self.s.recv( 1024 )
        self.s.close()
        return data.decode()
