
import socket

class MyServerSocket( object ):
    def __init__( self ):
        super( MyServerSocket, self ).__init__()
        self.HOST   = ""
        self.PORT   = 50007

        self.s      = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
        self.s.setsockopt( socket.SOL_SOCKET, socket.SO_REUSEADDR, 1 )
        self.s.bind( ( self.HOST, self.PORT ) )
        
    def GetData( self ):
        self.s.listen( 1 )
        self.conn = self.s.accept()[ 0 ]
        return self.conn.recv( 1024 )

    def SendData( self, data ):
        self.conn.sendall( bytes( data.encode() ) )
        self.conn.close()
