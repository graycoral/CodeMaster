from PyQt5.QtWidgets import *
import sys

class MyDlg:
    def __init__(self):
        self.dlg = QDialog()
        self.dlg.setWindowTitle('타이틀')
        self.dlg.setGeometry(100,100,300,400) # x,y, width, height
        self.vbox = QVBoxLayout()
        self.btn = QPushButton('클릭')
        self.btn.clicked.connect( self.fn ) #이벤트등록
        self.lineEdit = QLineEdit()
        self.vbox.addWidget(self.btn)
        self.vbox.addWidget(self.lineEdit)
        self.dlg.setLayout(self.vbox)
        self.dlg.show()
    def fn(self):
        print('click hello')

app = QApplication(sys.argv)
dlg = MyDlg()
app.exec()