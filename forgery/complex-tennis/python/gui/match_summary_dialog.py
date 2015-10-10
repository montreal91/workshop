# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'match_summary_dialog.ui'
#
# Created: Thu Aug 27 17:12:15 2015
#      by: pyside-uic 0.2.15 running on PySide 1.2.2
#
# WARNING! All changes made in this file will be lost!

from PySide import QtCore, QtGui

class Ui_MatchSummaryDialog(object):
    def setupUi(self, MatchSummaryDialog):
        MatchSummaryDialog.setObjectName("MatchSummaryDialog")
        MatchSummaryDialog.resize(400, 261)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Fixed, QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(MatchSummaryDialog.sizePolicy().hasHeightForWidth())
        MatchSummaryDialog.setSizePolicy(sizePolicy)
        self.gridLayout = QtGui.QGridLayout(MatchSummaryDialog)
        self.gridLayout.setObjectName("gridLayout")
        self.verticalLayout_4 = QtGui.QVBoxLayout()
        self.verticalLayout_4.setObjectName("verticalLayout_4")
        self.verticalLayout = QtGui.QVBoxLayout()
        self.verticalLayout.setObjectName("verticalLayout")
        self.header_lbl = QtGui.QLabel(MatchSummaryDialog)
        self.header_lbl.setAlignment(QtCore.Qt.AlignCenter)
        self.header_lbl.setObjectName("header_lbl")
        self.verticalLayout.addWidget(self.header_lbl)
        self.verticalLayout_4.addLayout(self.verticalLayout)
        self.main_score_layout = QtGui.QVBoxLayout()
        self.main_score_layout.setObjectName("main_score_layout")
        self.verticalLayout_4.addLayout(self.main_score_layout)
        self.verticalLayout_3 = QtGui.QVBoxLayout()
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.sets_won_lbl = QtGui.QLabel(MatchSummaryDialog)
        self.sets_won_lbl.setAlignment(QtCore.Qt.AlignCenter)
        self.sets_won_lbl.setObjectName("sets_won_lbl")
        self.verticalLayout_3.addWidget(self.sets_won_lbl)
        self.games_won_lbl = QtGui.QLabel(MatchSummaryDialog)
        self.games_won_lbl.setAlignment(QtCore.Qt.AlignCenter)
        self.games_won_lbl.setObjectName("games_won_lbl")
        self.verticalLayout_3.addWidget(self.games_won_lbl)
        self.total_points_won_lbl = QtGui.QLabel(MatchSummaryDialog)
        self.total_points_won_lbl.setAlignment(QtCore.Qt.AlignCenter)
        self.total_points_won_lbl.setObjectName("total_points_won_lbl")
        self.verticalLayout_3.addWidget(self.total_points_won_lbl)
        self.service_games_won_lbl = QtGui.QLabel(MatchSummaryDialog)
        self.service_games_won_lbl.setAlignment(QtCore.Qt.AlignCenter)
        self.service_games_won_lbl.setObjectName("service_games_won_lbl")
        self.verticalLayout_3.addWidget(self.service_games_won_lbl)
        self.service_points_won_lbl = QtGui.QLabel(MatchSummaryDialog)
        self.service_points_won_lbl.setAlignment(QtCore.Qt.AlignCenter)
        self.service_points_won_lbl.setObjectName("service_points_won_lbl")
        self.verticalLayout_3.addWidget(self.service_points_won_lbl)
        self.double_faults_lbl = QtGui.QLabel(MatchSummaryDialog)
        self.double_faults_lbl.setAlignment(QtCore.Qt.AlignCenter)
        self.double_faults_lbl.setObjectName("double_faults_lbl")
        self.verticalLayout_3.addWidget(self.double_faults_lbl)
        self.verticalLayout_4.addLayout(self.verticalLayout_3)
        self.horizontalLayout = QtGui.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.replay_match_btn = QtGui.QPushButton(MatchSummaryDialog)
        self.replay_match_btn.setObjectName("replay_match_btn")
        self.horizontalLayout.addWidget(self.replay_match_btn)
        self.close_btn = QtGui.QPushButton(MatchSummaryDialog)
        self.close_btn.setObjectName("close_btn")
        self.horizontalLayout.addWidget(self.close_btn)
        self.verticalLayout_4.addLayout(self.horizontalLayout)
        self.gridLayout.addLayout(self.verticalLayout_4, 0, 0, 1, 1)

        self.retranslateUi(MatchSummaryDialog)
        QtCore.QMetaObject.connectSlotsByName(MatchSummaryDialog)

    def retranslateUi(self, MatchSummaryDialog):
        MatchSummaryDialog.setWindowTitle(QtGui.QApplication.translate("MatchSummaryDialog", "Form", None, QtGui.QApplication.UnicodeUTF8))
        self.header_lbl.setText(QtGui.QApplication.translate("MatchSummaryDialog", "N. Djokovic - R. Federer", None, QtGui.QApplication.UnicodeUTF8))
        self.sets_won_lbl.setText(QtGui.QApplication.translate("MatchSummaryDialog", "1 Sets Won 2", None, QtGui.QApplication.UnicodeUTF8))
        self.games_won_lbl.setText(QtGui.QApplication.translate("MatchSummaryDialog", "13 Games Won 24", None, QtGui.QApplication.UnicodeUTF8))
        self.total_points_won_lbl.setText(QtGui.QApplication.translate("MatchSummaryDialog", "Points Won", None, QtGui.QApplication.UnicodeUTF8))
        self.service_games_won_lbl.setText(QtGui.QApplication.translate("MatchSummaryDialog", "Service Games Won", None, QtGui.QApplication.UnicodeUTF8))
        self.service_points_won_lbl.setText(QtGui.QApplication.translate("MatchSummaryDialog", "Service Points Won", None, QtGui.QApplication.UnicodeUTF8))
        self.double_faults_lbl.setText(QtGui.QApplication.translate("MatchSummaryDialog", "Double Faults", None, QtGui.QApplication.UnicodeUTF8))
        self.replay_match_btn.setText(QtGui.QApplication.translate("MatchSummaryDialog", "Replay Match", None, QtGui.QApplication.UnicodeUTF8))
        self.close_btn.setText(QtGui.QApplication.translate("MatchSummaryDialog", "Close", None, QtGui.QApplication.UnicodeUTF8))

