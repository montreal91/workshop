# -*- coding: utf-8 -*-

import sys

from PySide.QtCore          import Slot, Qt

from PySide.QtGui           import QApplication, QWidget
from PySide.QtGui           import QAction, QMenu

from gui.main_window        import Ui_MainWindow


from helpers                import match_config

from match_config_dialog    import MyMatchConfigDialog
from create_player_dialog   import MyPlayerDialog
from match_summary_dialog   import MyMatchSummaryDialog


qt_app = QApplication( sys.argv )


class MyTennisMatchGui( QWidget ):
    """docstring for MyTennisMatchGui"""
    def __init__( self ):
        super( MyTennisMatchGui, self ).__init__()
        self.setMinimumWidth( 400 )

        self.player_list    = list()
        self.lobby_list     = list()
        self.window         = Ui_MainWindow()
        self.window.setupUi( self )
        self.match_cfg      = MyMatchConfigDialog()
        self.create_player  = MyPlayerDialog()

        self.__UpdateMatchConfigs()
        self.__SetUpEvents()
        self.__SetUpMenus()

        self.setWindowTitle( "Complex Tennis" )


    @Slot()
    def __ShowMatchCfgDialog( self ):
        self.match_cfg.show()


    @Slot()
    def __CloseMatchCfgDialog( self ):
        self.match_cfg.close()


    @Slot()
    def __ShowCreatePlayerDialog(self):
        self.create_player.show()


    @Slot()
    def __SendDialogValues( self ):
        self.__GetDialogValues()
        self.__UpdateMatchConfigs()
        self.match_cfg.close()


    @Slot()
    def __CloseCreatePlayerDialog( self ):
        self.create_player.close()


    @Slot()
    def __AddNewPlayerToList( self ):
        player = self.create_player.GetPlayer()
        self.create_player.close()
        self.player_list.append( player )
        self.window.players_lst.addItem( str( player ) )


    @Slot()
    def PlayMatch( self ):
        self.match_summary_dialog = MyMatchSummaryDialog(
            self.lobby_list[ 0 ],
            self.lobby_list[ 1 ],
            match_config
        )
        self.match_summary_dialog.show()


    def __SetUpEvents( self ):
        self.window.show_modal_btn.clicked.connect( self.__ShowMatchCfgDialog )
        self.window.create_player_btn.clicked.connect( self.__ShowCreatePlayerDialog )
        self.window.play_match_btn.clicked.connect( self.PlayMatch )
        self.match_cfg.window.cancel_btn.clicked.connect( self.__CloseMatchCfgDialog )
        self.match_cfg.window.ok_btn.clicked.connect( self.__SendDialogValues )
        self.create_player.window.cancel_btn.clicked.connect( self.__CloseCreatePlayerDialog )
        self.create_player.window.ok_btn.clicked.connect( self.__AddNewPlayerToList )


    def __GetDialogValues( self ):
        match_config.points_to_win_game     = self.match_cfg.window.pts_to_win_game_sp_b.value()
        match_config.points_to_win_tiebreak = self.match_cfg.window.pts_to_win_tiebreak_sp_b.value()
        match_config.games_to_win_set       = self.match_cfg.window.games_to_win_set_sp_b.value()
        match_config.sets_to_win_match      = self.match_cfg.window.sets_to_win_match_sp_b.value()

        match_config.tiebreaks              = self.match_cfg.window.tiebreaks_ch_b.isChecked()
        match_config.final_set_tiebreak     = self.match_cfg.window.final_set_tiebreak_ch_b.isChecked()


    def __UpdateMatchConfigs( self ):
        self.window.pts_to_win_game_lbl.setText( str( match_config.points_to_win_game ) )
        self.window.pts_to_win_tiebreak_lbl.setText( str( match_config.points_to_win_tiebreak ) )
        self.window.games_to_win_set_lbl.setText( str( match_config.games_to_win_set ) )
        self.window.sets_to_win_match_lbl.setText( str( match_config.sets_to_win_match ) )

        if match_config.tiebreaks:
            self.window.tiebreaks_lbl.setText( "Enabled" )
        else:
            self.window.tiebreaks_lbl.setText( "Disabled" )

        if match_config.final_set_tiebreak:
            self.window.final_set_tiebreak_lbl.setText( "Enabled" )
        else:
            self.window.final_set_tiebreak_lbl.setText( "Disabled" )


    def __SetUpMenus( self ):
        self.window.players_lst.setContextMenuPolicy( Qt.CustomContextMenu )
        self.window.players_lst.customContextMenuRequested.connect( self.__PlayersListMenu )

        self.window.lobby_lst.setContextMenuPolicy( Qt.CustomContextMenu )
        self.window.lobby_lst.customContextMenuRequested.connect( self.__LobbyListMenu )


    def __PlayersListMenu( self, position ):
        list_menu           = QMenu()

        add_player_to_lobby = QAction( self )
        add_player_to_lobby.setText( "Add player to lobby" )
        add_player_to_lobby.triggered.connect( self._AddToLobbyAction )

        rm_player           = QAction( self )
        rm_player.setText( "Remove player" )
        rm_player.triggered.connect( self._RemoveFromPlayersListAction )

        list_menu.addAction( rm_player )
        list_menu.addAction( add_player_to_lobby )

        list_menu.exec_( self.window.players_lst.viewport().mapToGlobal( position ) )


    def __LobbyListMenu( self, position ):
        lobby_menu      = QMenu()

        rm_from_lobby   = QAction( self )
        rm_from_lobby.setText( "Remove player from lobby" )
        rm_from_lobby.triggered.connect( self._RemoveFromLobbyListAction )

        lobby_menu.addAction( rm_from_lobby )

        lobby_menu.exec_( self.window.lobby_lst.viewport().mapToGlobal( position ) )


    def _RemoveFromPlayersListAction( self ):
        try:
            selection   = self.window.players_lst.selectedItems()[ 0 ]
            pos         = self.window.players_lst.row( selection )
            self.window.players_lst.takeItem( pos )
            self.player_list.pop( pos )
        except IndexError:
            pass


    def _RemoveFromLobbyListAction( self ):
        try:
            sel = self.window.lobby_lst.selectedItems()[ 0 ]
            pos     = self.window.lobby_lst.row( sel )

            item = self.window.lobby_lst.takeItem( pos )
            self.window.players_lst.addItem( item )

            player = self.lobby_list.pop( pos )
            self.player_list.append( player )
        except IndexError:
            pass


    def _AddToLobbyAction( self ):
        try:
            selection   = self.window.players_lst.selectedItems()[ 0 ]
            pos         = self.window.players_lst.row( selection )

            if len( self.lobby_list ) < 2:
                self.window.players_lst.takeItem( pos )
                player = self.player_list.pop( pos )
                self.window.lobby_lst.addItem( player.name.full_name )
                self.lobby_list.append( player )
            else:
                pass

        except IndexError:
            pass


    def Run( self ):
        self.show()
        qt_app.exec_()


if __name__ == '__main__':
    app = MyTennisMatchGui()
    app.Run()
