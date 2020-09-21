from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
import sys

class OtherDlg:
    def __init__(self):
        self.dlg = loadUi('dlg.ui')
        self.dlg.pushButton.clicked.connect( self.fn )
        self.dlg.exec() #모달다이아로그
    def fn(self):
        self.dlg.close()
class MyDlg:
    def __init__(self):
        self.dlg = loadUi('mainwindow.ui')
        self.dlg.pushButton.clicked.connect( self.fn )
        self.dlg.actiontest1.triggered.connect( self.menuClick )
        self.dlg.show()
    def menuClick(self):
        o = OtherDlg() #hang
        s = o.dlg.lineEditChild.text()
        self.dlg.lineEditMain.setText( s )
        print('click...')
    def fn(self):
        pass
app = QApplication(sys.argv)
dlg = MyDlg()
app.exec()