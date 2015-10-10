
from string                     import ascii_lowercase, capwords
from random                     import choice

from PySide.QtGui               import QWidget, QTableWidgetItem

from gui.create_player_dialog   import Ui_CreatePlayerDialog

from name                       import MyName
from serve                      import MyServe
from player                     import MyPlayer


class MyPlayerDialog( QWidget ):
    """docstring for MyPlayerDialog"""
    def __init__( self ):
        super(MyPlayerDialog, self).__init__()
        self.setWindowTitle( "Create Player" )
        self.window = Ui_CreatePlayerDialog()
        self.window.setupUi( self )


    def GetPlayer( self ):
        if self.window.first_name_ln_ed.text():
            first_name = capwords( self.window.first_name_ln_ed.text() )
        else:
            first_name = self.__CreateRandomName()

        if self.window.last_name_ln_ed.text():
            last_name = capwords( self.window.last_name_ln_ed.text() )
        else:
            last_name = self.__CreateRandomName()

        name            = MyName( first_name, last_name )
        first_serve     = self.__CreateServe(
            self.window.srv1_accuracy_sp_b.value(), 
            self.window.srv1_quality_sp_b.value() 
        )
        second_serve    = self.__CreateServe(
            self.window.srv2_accuracy_sp_b.value(),
            self.window.srv2_quality_sp_b.value()
        )
        return MyPlayer( name, first_serve, second_serve )


    def __CreateRandomName( self ):
        res = ''
        for i in range( 5 ):
            res += choice( ascii_lowercase )
        return capwords( res )


    def __CreateServe( self, serve_in, serve_win ):
        return MyServe( serve_in, serve_win )
