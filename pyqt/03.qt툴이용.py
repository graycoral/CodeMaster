from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
import sys

# model : data
# view : xml
# control : event 처리 (코딩)

class MyDlg:
    def __init__(self):
        # xml 정보를 해석 해서 객체를 생성 윈도우(다이아로그)
        self.dlg = loadUi('a.ui')
        self.dlg.pushButton.clicked.connect(self.fn)
        self.dlg.show()
    def fn(self):
        print('hello')
        # self.dlg.lineEdit.setText('Korea')
        s = self.dlg.lineEdit.text()
        print(s)


app = QApplication(sys.argv)
dlg = MyDlg()
app.exec()