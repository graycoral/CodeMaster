from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
import sys
class MyDlg:
    def __init__(self):
        self.dlg = loadUi('d.ui')
        self.dlg.pushButton.clicked.connect( self.fn )
        self.dlg.show()

    def insertTableData(self, name, age, addr):
        nRow = self.dlg.tableWidget.rowCount()
        self.dlg.tableWidget.setRowCount(nRow+1)
        self.dlg.tableWidget.setItem(nRow,0, QTableWidgetItem(name))
        self.dlg.tableWidget.setItem(nRow,1, QTableWidgetItem(str(age)))
        self.dlg.tableWidget.setItem(nRow,2, QTableWidgetItem(addr))

    def fn(self):
        self.insertTableData('홍길동','20','서울시')
        self.insertTableData('이순','30','경기')
        self.insertTableData('임','40','충청')
#        self.dlg.tableWidget.setRowCount(2)

        # self.dlg.tableWidget.setItem(0,0, QTableWidgetItem('홍길동'))
        # self.dlg.tableWidget.setItem(0,1, QTableWidgetItem('20'))
        # self.dlg.tableWidget.setItem(0,2, QTableWidgetItem('서울시'))
        #
        # self.dlg.tableWidget.setItem(1,0, QTableWidgetItem('이순'))
        # self.dlg.tableWidget.setItem(1,1, QTableWidgetItem('30'))
        # self.dlg.tableWidget.setItem(1,2, QTableWidgetItem('경기'))

app = QApplication(sys.argv)
dlg = MyDlg()
app.exec()
