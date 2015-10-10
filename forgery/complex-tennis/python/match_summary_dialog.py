
from PySide.QtGui               import QWidget, QLabel

from PySide.QtCore              import Slot, Qt

from tennis_match               import MyTennisMatch
from gui.match_summary_dialog   import Ui_MatchSummaryDialog


class MyMatchSummaryDialog( QWidget ):
    """docstring for MyMatchSummaryDialog"""
    def __init__( self, player_one, player_two, match_config ):
        super( MyMatchSummaryDialog, self ).__init__()
        self._player_one    = player_one
        self._player_two    = player_two
        self._match_config  = match_config
        self._label_scores  = list()

        self.window         = Ui_MatchSummaryDialog()
        self.window.setupUi( self )
        self.setWindowTitle( "Match Summary" )

        self._PlayMatch()

        self.window.replay_match_btn.clicked.connect( self._PlayMatch )
        self.window.close_btn.clicked.connect( self._Quit )


    @Slot()
    def _PlayMatch( self ):
        self._player_one.DropEverything()
        self._player_two.DropEverything()
        match = MyTennisMatch(
            player_one=self._player_one,
            player_two=self._player_two,
            points_to_win_game=self._match_config.points_to_win_game,
            points_to_win_tiebreak=self._match_config.points_to_win_tiebreak,
            games_to_win_set=self._match_config.games_to_win_set,
            sets_to_win_match=self._match_config.sets_to_win_match,
            tiebreaks=self._match_config.tiebreaks,
            final_set_tiebreak=self._match_config.final_set_tiebreak
        )
        match.PlayMatch()
        self._SetUpScoreLabels( match )
        self._SetUpSummaryLabels( match )


    @Slot()
    def _Quit( self ):
        self.close()


    def _SetUpSummaryLabels( self, match ):
        self.window.header_lbl.setText( "<b>%s</b>" % match.match_title )
        self.window.sets_won_lbl.setText( 
            "<b>{0:d}</b> Sets Won <b>{1:d}</b>".format(
                match.sets_won[ 0 ],
                match.sets_won[ 1 ]
            )
        )
        self.window.games_won_lbl.setText(
            "<b>{0:d}</b> Total Games Won <b>{1:d}</b>".format(
                match.total_games_won[ 0 ],
                match.total_games_won[ 1 ]
            )
        )
        self.window.total_points_won_lbl.setText(
            "<b>{0:d}</b> Total Points Won <b>{1:d}</b>".format(
                match.total_points_won[ 0 ],
                match.total_points_won[ 1 ]
            )
        )
        self.window.service_games_won_lbl.setText(
            "<b>{0:d}/{1:d}</b> Service Games Won <b>{2:d}/{3:d}</b>".format(
                match.games_on_serve[ 0 ] - match.brakes[ 1 ],
                match.games_on_serve[ 0 ],
                match.games_on_serve[ 1 ] - match.brakes[ 0 ],
                match.games_on_serve[ 1 ],
            )
        )
        self.window.service_points_won_lbl.setText(
            "<b>{0:d}/{1:d}</b> Service Points Won <b>{2:d}/{3:d}</b>".format(
                match.service_points_won[ 0 ],
                match.service_points_played[ 0 ],
                match.service_points_won[ 1 ],
                match.service_points_played[ 1 ],
            )
        )
        self.window.double_faults_lbl.setText(
            "<b>{0:d}</b> Double Faults <b>{1:d}</b>".format(
                match.double_faults[ 0 ],
                match.double_faults[ 1 ]
            )
        )


    def _SetUpScoreLabels( self, match ):
        self._CleanUpScore()

        for sset in match.result:
            for score in sset:
                res = "{0:d}:{1:d}".format( score[ 0 ], score[ 1 ] )
                if abs( score[ 0 ] - score[ 1 ] ) == 1:
                    res += " ({0:1d}:{1:1d})".format( sset[ score ][ -1 ][ 0 ], sset[ score ][ -1 ][ 1 ] )
                label = QLabel( res )
                self._label_scores.append( label )
                label.setAlignment( Qt.AlignHCenter )
                self.window.main_score_layout.addWidget( label )


    def _CleanUpScore( self ):
        for l in self._label_scores:
            l.deleteLater()
        self._label_scores = list()
