
from PySide.QtGui                   import QWidget

from gui.match_configuration_dialog import Ui_MatchConfigDialog

class MyMatchConfigDialog( QWidget ):
    """docstring for MyMatchConfigDialog"""
    def __init__( self ):
        super(MyMatchConfigDialog, self).__init__()
        self.window = Ui_MatchConfigDialog()
        self.window.setupUi( self )
        self.setWindowTitle( "Match configs" )
