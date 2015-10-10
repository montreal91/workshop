
from server_socket import MyServerSocket

class MyServerApp( object ):
    def __init__( self ):
        super( MyServerApp, self ).__init__()
        self.socket = MyServerSocket()
        

    def GetData( self ):
        return int( self.socket.GetData() )


    def ProcessData( self, data ):
        data += 10
        return data


    def SendData( self, data ):
        message = str( data )
        self.socket.SendData( message )


    def ServeForever( self ):
        while True:
            income_data = self.GetData()
            outcome_data = self.ProcessData( income_data )
            self.SendData( outcome_data )
