from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
import sys
class MyDlg:
    def __init__(self):
        self.dlg = loadUi('b.ui')
        self.dlg.pushButton.clicked.connect( self.fn )
        self.dlg.show()
    def fn(self):
        pass

app = QApplication(sys.argv)
dlg = MyDlg()
app.exec()
