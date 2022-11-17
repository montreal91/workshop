
from PySide import QtCore, QtGui

from mainwindow import Ui_MainWindow

class ControlMainWindow( QtGui.QMainWindow ):
    def __init__( self, parent=None ):
        super( ControlMainWindow, self ).__init__( parent )
        self.ui = Ui_MainWindow()
        self.ui.setupUi( self )
        self.ui.exit_button.clicked.connect( self.CloseProgram )

    @QtCore.Slot()
    def CloseProgram( self ):
        sys.exit()


if __name__ == '__main__':
    import sys
    app = QtGui.QApplication( sys.argv )
    cmw = ControlMainWindow()
    cmw.show()
    sys.exit( app.exec_() )
