from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
from PyQt5.QtCore import *

import sys
class MyDlg:
    def __init__(self):
        self.dlg = loadUi('c.ui')
        self.initEvent()
        self.initWidget()
        self.dlg.show()
    def initEvent(self):
        self.dlg.pushButton.clicked.connect( self.buttonClick )
        self.dlg.comboBox.currentIndexChanged.connect(self.comboChange)

    def initWidget(self):
        self.dlg.comboBox.addItem('com1')
        self.dlg.comboBox.addItems(['com1', 'com2', 'com3', '기업4'])

    def buttonClick(self):
        s = self.dlg.comboBox.currentText()
        self.dlg.lineEdit.setText(s)
        # self.dlg.dateEdit.setDate(QDate(2020,9,3))
        d = self.dlg.dateEdit.date()
        s = f'{d.year()}년{d.month()}월{d.day()}일'
        self.dlg.lineEdit.setText(s)

    def comboChange(self):
        s = self.dlg.comboBox.currentText()
        self.dlg.lineEdit.setText(s)

app = QApplication(sys.argv)
dlg = MyDlg()
app.exec()
"""
from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
import sys
class MyDlg:
    def __init__(self):
        self.dlg = loadUi('c.ui')
        self.initEvent()
        self.initWidget()
        self.dlg.show()
    def initEvent(self):
        self.dlg.pushButton.clicked.connect( self.buttonClick )
        self.dlg.comboBox.currentIndexChanged.connect(self.comboChange)
    def initWidget(self):
        self.dlg.comboBox.addItem('기업1')
        self.dlg.comboBox.addItems( ['기업2','기업3','기업4'])
    def comboChange(self):
        s = self.dlg.comboBox.currentText()
        self.dlg.lineEdit.setText(s)
    def buttonClick(self):
        s = self.dlg.comboBox.currentText()
        self.dlg.lineEdit.setText(s)
app = QApplication(sys.argv)
dlg = MyDlg()
app.exec()
"""
'''
from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
import sys
class MyDlg:
    def __init__(self):
        self.dlg = loadUi('c.ui')
        self.dlg.pushButton.clicked.connect( self.buttonClick )
        self.dlg.comboBox.addItem('기업1')
        self.dlg.comboBox.addItems( ['기업2','기업3','기업4'])
        self.dlg.show()
    def buttonClick(self):
        pass
app = QApplication(sys.argv)
dlg = MyDlg()
app.exec()
'''