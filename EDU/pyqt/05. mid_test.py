from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
import sys
class MyDlg:
    def __init__(self):
        self.dlg = loadUi('b.ui')
        self.dlg.pushButton.clicked.connect( self.fn )
        self.dlg.show()
    def fn(self):
        a = self.dlg.spinBox.value()
        b = self.dlg.spinBox_2.value()
        self.dlg.lineEdit.setText(f'합은:{a+b}')

app = QApplication(sys.argv)
dlg = MyDlg()
app.exec()
