# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'create_player_dialog.ui'
#
# Created: Sat Aug 22 19:14:06 2015
#      by: pyside-uic 0.2.15 running on PySide 1.2.2
#
# WARNING! All changes made in this file will be lost!

from PySide import QtCore, QtGui

class Ui_CreatePlayerDialog(object):
    def setupUi(self, CreatePlayerDialog):
        CreatePlayerDialog.setObjectName("CreatePlayerDialog")
        CreatePlayerDialog.resize(274, 258)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Fixed, QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(CreatePlayerDialog.sizePolicy().hasHeightForWidth())
        CreatePlayerDialog.setSizePolicy(sizePolicy)
        CreatePlayerDialog.setMinimumSize(QtCore.QSize(274, 258))
        CreatePlayerDialog.setMaximumSize(QtCore.QSize(274, 258))
        self.gridLayout = QtGui.QGridLayout(CreatePlayerDialog)
        self.gridLayout.setObjectName("gridLayout")
        self.verticalLayout = QtGui.QVBoxLayout()
        self.verticalLayout.setObjectName("verticalLayout")
        self.formLayout_2 = QtGui.QFormLayout()
        self.formLayout_2.setObjectName("formLayout_2")
        self.label_7 = QtGui.QLabel(CreatePlayerDialog)
        self.label_7.setObjectName("label_7")
        self.formLayout_2.setWidget(0, QtGui.QFormLayout.LabelRole, self.label_7)
        self.first_name_ln_ed = QtGui.QLineEdit(CreatePlayerDialog)
        self.first_name_ln_ed.setObjectName("first_name_ln_ed")
        self.formLayout_2.setWidget(0, QtGui.QFormLayout.FieldRole, self.first_name_ln_ed)
        self.label_8 = QtGui.QLabel(CreatePlayerDialog)
        self.label_8.setObjectName("label_8")
        self.formLayout_2.setWidget(1, QtGui.QFormLayout.LabelRole, self.label_8)
        self.last_name_ln_ed = QtGui.QLineEdit(CreatePlayerDialog)
        self.last_name_ln_ed.setObjectName("last_name_ln_ed")
        self.formLayout_2.setWidget(1, QtGui.QFormLayout.FieldRole, self.last_name_ln_ed)
        self.label = QtGui.QLabel(CreatePlayerDialog)
        self.label.setObjectName("label")
        self.formLayout_2.setWidget(2, QtGui.QFormLayout.LabelRole, self.label)
        self.label_2 = QtGui.QLabel(CreatePlayerDialog)
        self.label_2.setObjectName("label_2")
        self.formLayout_2.setWidget(3, QtGui.QFormLayout.LabelRole, self.label_2)
        self.label_3 = QtGui.QLabel(CreatePlayerDialog)
        self.label_3.setObjectName("label_3")
        self.formLayout_2.setWidget(4, QtGui.QFormLayout.LabelRole, self.label_3)
        self.label_4 = QtGui.QLabel(CreatePlayerDialog)
        self.label_4.setObjectName("label_4")
        self.formLayout_2.setWidget(5, QtGui.QFormLayout.LabelRole, self.label_4)
        self.label_5 = QtGui.QLabel(CreatePlayerDialog)
        self.label_5.setObjectName("label_5")
        self.formLayout_2.setWidget(6, QtGui.QFormLayout.LabelRole, self.label_5)
        self.label_6 = QtGui.QLabel(CreatePlayerDialog)
        self.label_6.setObjectName("label_6")
        self.formLayout_2.setWidget(7, QtGui.QFormLayout.LabelRole, self.label_6)
        self.srv1_accuracy_sp_b = QtGui.QSpinBox(CreatePlayerDialog)
        self.srv1_accuracy_sp_b.setFrame(True)
        self.srv1_accuracy_sp_b.setButtonSymbols(QtGui.QAbstractSpinBox.UpDownArrows)
        self.srv1_accuracy_sp_b.setProperty("value", 50)
        self.srv1_accuracy_sp_b.setObjectName("srv1_accuracy_sp_b")
        self.formLayout_2.setWidget(3, QtGui.QFormLayout.FieldRole, self.srv1_accuracy_sp_b)
        self.srv2_accuracy_sp_b = QtGui.QSpinBox(CreatePlayerDialog)
        self.srv2_accuracy_sp_b.setProperty("value", 50)
        self.srv2_accuracy_sp_b.setObjectName("srv2_accuracy_sp_b")
        self.formLayout_2.setWidget(6, QtGui.QFormLayout.FieldRole, self.srv2_accuracy_sp_b)
        self.srv1_quality_sp_b = QtGui.QSpinBox(CreatePlayerDialog)
        self.srv1_quality_sp_b.setProperty("value", 50)
        self.srv1_quality_sp_b.setObjectName("srv1_quality_sp_b")
        self.formLayout_2.setWidget(4, QtGui.QFormLayout.FieldRole, self.srv1_quality_sp_b)
        self.srv2_quality_sp_b = QtGui.QSpinBox(CreatePlayerDialog)
        self.srv2_quality_sp_b.setProperty("value", 50)
        self.srv2_quality_sp_b.setObjectName("srv2_quality_sp_b")
        self.formLayout_2.setWidget(7, QtGui.QFormLayout.FieldRole, self.srv2_quality_sp_b)
        self.line = QtGui.QFrame(CreatePlayerDialog)
        self.line.setFrameShape(QtGui.QFrame.HLine)
        self.line.setFrameShadow(QtGui.QFrame.Sunken)
        self.line.setObjectName("line")
        self.formLayout_2.setWidget(2, QtGui.QFormLayout.FieldRole, self.line)
        self.line_2 = QtGui.QFrame(CreatePlayerDialog)
        self.line_2.setFrameShape(QtGui.QFrame.HLine)
        self.line_2.setFrameShadow(QtGui.QFrame.Sunken)
        self.line_2.setObjectName("line_2")
        self.formLayout_2.setWidget(5, QtGui.QFormLayout.FieldRole, self.line_2)
        self.verticalLayout.addLayout(self.formLayout_2)
        self.horizontalLayout_2 = QtGui.QHBoxLayout()
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.ok_btn = QtGui.QPushButton(CreatePlayerDialog)
        self.ok_btn.setObjectName("ok_btn")
        self.horizontalLayout_2.addWidget(self.ok_btn)
        self.cancel_btn = QtGui.QPushButton(CreatePlayerDialog)
        self.cancel_btn.setObjectName("cancel_btn")
        self.horizontalLayout_2.addWidget(self.cancel_btn)
        self.verticalLayout.addLayout(self.horizontalLayout_2)
        self.gridLayout.addLayout(self.verticalLayout, 0, 0, 1, 1)

        self.retranslateUi(CreatePlayerDialog)
        QtCore.QMetaObject.connectSlotsByName(CreatePlayerDialog)

    def retranslateUi(self, CreatePlayerDialog):
        CreatePlayerDialog.setWindowTitle(QtGui.QApplication.translate("CreatePlayerDialog", "Create Player", None, QtGui.QApplication.UnicodeUTF8))
        self.label_7.setText(QtGui.QApplication.translate("CreatePlayerDialog", "First Name", None, QtGui.QApplication.UnicodeUTF8))
        self.label_8.setText(QtGui.QApplication.translate("CreatePlayerDialog", "Last Name", None, QtGui.QApplication.UnicodeUTF8))
        self.label.setText(QtGui.QApplication.translate("CreatePlayerDialog", "1st Serve", None, QtGui.QApplication.UnicodeUTF8))
        self.label_2.setText(QtGui.QApplication.translate("CreatePlayerDialog", "In %", None, QtGui.QApplication.UnicodeUTF8))
        self.label_3.setText(QtGui.QApplication.translate("CreatePlayerDialog", "Win %", None, QtGui.QApplication.UnicodeUTF8))
        self.label_4.setText(QtGui.QApplication.translate("CreatePlayerDialog", "2nd Serve", None, QtGui.QApplication.UnicodeUTF8))
        self.label_5.setText(QtGui.QApplication.translate("CreatePlayerDialog", "In %", None, QtGui.QApplication.UnicodeUTF8))
        self.label_6.setText(QtGui.QApplication.translate("CreatePlayerDialog", "Win %", None, QtGui.QApplication.UnicodeUTF8))
        self.ok_btn.setText(QtGui.QApplication.translate("CreatePlayerDialog", "OK", None, QtGui.QApplication.UnicodeUTF8))
        self.cancel_btn.setText(QtGui.QApplication.translate("CreatePlayerDialog", "Cancel", None, QtGui.QApplication.UnicodeUTF8))
