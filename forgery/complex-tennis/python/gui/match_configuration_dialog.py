# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'match_configuration_dialog.ui'
#
# Created: Tue Aug 11 21:39:56 2015
#      by: pyside-uic 0.2.15 running on PySide 1.2.2
#
# WARNING! All changes made in this file will be lost!

from PySide import QtCore, QtGui

class Ui_MatchConfigDialog(object):
    def setupUi(self, MatchConfigDialog):
        MatchConfigDialog.setObjectName("MatchConfigDialog")
        MatchConfigDialog.resize(295, 214)
        self.gridLayout = QtGui.QGridLayout(MatchConfigDialog)
        self.gridLayout.setObjectName("gridLayout")
        self.verticalLayout = QtGui.QVBoxLayout()
        self.verticalLayout.setObjectName("verticalLayout")
        self.formLayout = QtGui.QFormLayout()
        self.formLayout.setObjectName("formLayout")
        self.label = QtGui.QLabel(MatchConfigDialog)
        self.label.setObjectName("label")
        self.formLayout.setWidget(0, QtGui.QFormLayout.LabelRole, self.label)
        self.pts_to_win_game_sp_b = QtGui.QSpinBox(MatchConfigDialog)
        self.pts_to_win_game_sp_b.setProperty("value", 4)
        self.pts_to_win_game_sp_b.setObjectName("pts_to_win_game_sp_b")
        self.formLayout.setWidget(0, QtGui.QFormLayout.FieldRole, self.pts_to_win_game_sp_b)
        self.label_2 = QtGui.QLabel(MatchConfigDialog)
        self.label_2.setObjectName("label_2")
        self.formLayout.setWidget(1, QtGui.QFormLayout.LabelRole, self.label_2)
        self.pts_to_win_tiebreak_sp_b = QtGui.QSpinBox(MatchConfigDialog)
        self.pts_to_win_tiebreak_sp_b.setProperty("value", 7)
        self.pts_to_win_tiebreak_sp_b.setObjectName("pts_to_win_tiebreak_sp_b")
        self.formLayout.setWidget(1, QtGui.QFormLayout.FieldRole, self.pts_to_win_tiebreak_sp_b)
        self.label_3 = QtGui.QLabel(MatchConfigDialog)
        self.label_3.setObjectName("label_3")
        self.formLayout.setWidget(2, QtGui.QFormLayout.LabelRole, self.label_3)
        self.games_to_win_set_sp_b = QtGui.QSpinBox(MatchConfigDialog)
        self.games_to_win_set_sp_b.setProperty("value", 6)
        self.games_to_win_set_sp_b.setObjectName("games_to_win_set_sp_b")
        self.formLayout.setWidget(2, QtGui.QFormLayout.FieldRole, self.games_to_win_set_sp_b)
        self.label_4 = QtGui.QLabel(MatchConfigDialog)
        self.label_4.setObjectName("label_4")
        self.formLayout.setWidget(3, QtGui.QFormLayout.LabelRole, self.label_4)
        self.sets_to_win_match_sp_b = QtGui.QSpinBox(MatchConfigDialog)
        self.sets_to_win_match_sp_b.setProperty("value", 2)
        self.sets_to_win_match_sp_b.setObjectName("sets_to_win_match_sp_b")
        self.formLayout.setWidget(3, QtGui.QFormLayout.FieldRole, self.sets_to_win_match_sp_b)
        self.tiebreaks_ch_b = QtGui.QCheckBox(MatchConfigDialog)
        self.tiebreaks_ch_b.setChecked(True)
        self.tiebreaks_ch_b.setObjectName("tiebreaks_ch_b")
        self.formLayout.setWidget(4, QtGui.QFormLayout.FieldRole, self.tiebreaks_ch_b)
        self.final_set_tiebreak_ch_b = QtGui.QCheckBox(MatchConfigDialog)
        self.final_set_tiebreak_ch_b.setChecked(True)
        self.final_set_tiebreak_ch_b.setObjectName("final_set_tiebreak_ch_b")
        self.formLayout.setWidget(5, QtGui.QFormLayout.FieldRole, self.final_set_tiebreak_ch_b)
        self.verticalLayout.addLayout(self.formLayout)
        self.gridLayout.addLayout(self.verticalLayout, 0, 0, 1, 1)
        self.horizontalLayout = QtGui.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.ok_btn = QtGui.QPushButton(MatchConfigDialog)
        self.ok_btn.setObjectName("ok_btn")
        self.horizontalLayout.addWidget(self.ok_btn)
        self.cancel_btn = QtGui.QPushButton(MatchConfigDialog)
        self.cancel_btn.setObjectName("cancel_btn")
        self.horizontalLayout.addWidget(self.cancel_btn)
        self.gridLayout.addLayout(self.horizontalLayout, 1, 0, 1, 1)

        self.retranslateUi(MatchConfigDialog)
        QtCore.QMetaObject.connectSlotsByName(MatchConfigDialog)

    def retranslateUi(self, MatchConfigDialog):
        MatchConfigDialog.setWindowTitle(QtGui.QApplication.translate("MatchConfigDialog", "Dialog", None, QtGui.QApplication.UnicodeUTF8))
        self.label.setText(QtGui.QApplication.translate("MatchConfigDialog", "Points to win game", None, QtGui.QApplication.UnicodeUTF8))
        self.label_2.setText(QtGui.QApplication.translate("MatchConfigDialog", "Ponts to win tiebreak", None, QtGui.QApplication.UnicodeUTF8))
        self.label_3.setText(QtGui.QApplication.translate("MatchConfigDialog", "Games to win set", None, QtGui.QApplication.UnicodeUTF8))
        self.label_4.setText(QtGui.QApplication.translate("MatchConfigDialog", "Sets to win match", None, QtGui.QApplication.UnicodeUTF8))
        self.tiebreaks_ch_b.setText(QtGui.QApplication.translate("MatchConfigDialog", "Tiebreaks", None, QtGui.QApplication.UnicodeUTF8))
        self.final_set_tiebreak_ch_b.setText(QtGui.QApplication.translate("MatchConfigDialog", "Final set tiebreak", None, QtGui.QApplication.UnicodeUTF8))
        self.ok_btn.setText(QtGui.QApplication.translate("MatchConfigDialog", "Ok", None, QtGui.QApplication.UnicodeUTF8))
        self.cancel_btn.setText(QtGui.QApplication.translate("MatchConfigDialog", "Cancel", None, QtGui.QApplication.UnicodeUTF8))

