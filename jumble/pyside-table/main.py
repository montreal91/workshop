# coding: UTF-8

import sys

from PySide import QtGui, QtCore


u""" サンプルデータ """
title = ["hoge", "fuga", "piyo"]
data = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]


class TableWindow(QtGui.QWidget):

    def __init__(self, parent=None):
        super(TableWindow, self).__init__(parent)
        colcnt = len(data[0])
        rowcnt = len(data)
        self.tablewidget = QtGui.QTableWidget(rowcnt, colcnt)

        u""" ヘッダー設定 """
        vheader = QtGui.QHeaderView(QtCore.Qt.Orientation.Vertical)
        vheader.setResizeMode(QtGui.QHeaderView.ResizeToContents)
        self.tablewidget.setVerticalHeader(vheader)
        
        hheader = QtGui.QHeaderView(QtCore.Qt.Orientation.Horizontal)
        hheader.setResizeMode(QtGui.QHeaderView.ResizeToContents)
        self.tablewidget.setHorizontalHeader(hheader)
        self.tablewidget.setHorizontalHeaderLabels(title)

        u""" テーブルの中身作成 """
        for i in range(rowcnt):
            for j in range(colcnt):
                item = QtGui.QTableWidgetItem(str(data[i][j]))
                self.tablewidget.setItem(i, j, item)

        u""" レイアウト """
        layout = QtGui.QHBoxLayout()
        layout.addWidget(self.tablewidget)
        self.setLayout(layout)


def main():
    app = QtGui.QApplication(sys.argv)
    widget = TableWindow()
    widget.show()
    widget.raise_()
    sys.exit(app.exec_())

if __name__ == "__main__":
    main()