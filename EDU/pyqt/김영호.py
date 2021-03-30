from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
import sys

class OtherDlg:
    def __init__(self):
        self.dlg = loadUi('dlgMD.ui')
        self.dlg.pushButton.clicked.connect( self.fn )
        self.dlg.exec() #모달다이아로그

    def fn(self):
        self.dlg.close()

class MyDlg:
    def __init__(self):
        self.dlg = loadUi('MD.ui')
        self.dlg.actioninput.triggered.connect( self.menuClick )
        self.dlg.actionshow.triggered.connect( self.showClick )
        self.dlg.show()
    def menuClick(self):
        o = OtherDlg() #hang
        s1 = o.dlg.lineEdit.text()
        s2 = o.dlg.lineEdit_2.text()
        s3 = o.dlg.lineEdit_3.text()
        self.insertTableData(s1, s2, s3)

    def insertTableData(self, name, age, addr):
        nRow = self.dlg.tableWidget.rowCount()
        self.dlg.tableWidget.setRowCount(nRow+1)
        self.dlg.tableWidget.setItem(nRow, 0, QTableWidgetItem(name))
        self.dlg.tableWidget.setItem(nRow, 1, QTableWidgetItem(str(age)))
        self.dlg.tableWidget.setItem(nRow, 2, QTableWidgetItem(addr))

    def showClick(self):
        print("show")
        pass

app = QApplication(sys.argv)
dlg = MyDlg()
app.exec()

'''
from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
import sys
import sqlite3
def createTable():
    try:
        sql = 'create table if not exists product(pname varchar(20),cnt int, pdate date)'
        db = sqlite3.connect("my.db")
        db.execute(sql)
        db.close()
    except Exception as err:
        print(err)
def insertDataFormat(pname, cnt, pdate):
    try:
        sql = "insert into product values(?,?,?)"
        db = sqlite3.connect("my.db")
        db.execute(sql, (pname, cnt, pdate) )
        db.commit()
        db.close()
        print("insert data ")
    except Exception as err:
        print(err)
def selectData():
    try:
        sql="select * from product"
        db = sqlite3.connect("my.db")
        cur = db.cursor()
        cur.execute(sql)
        data = cur.fetchall()
        db.close()
        return data
    except Exception as err:
        print(err)
        return None
class InputDlg:
    def __init__(self):
        self.dlg = loadUi('input.ui')
        self.dlg.pushButton.clicked.connect( self.btnClick )
        self.dlg.exec()
    def btnClick(self):
        pname = self.dlg.lineEdit.text()
        cnt = self.dlg.spinBox.value()
        d = self.dlg.dateEdit.date()
        sdt =f'{d.year()}-{d.month()}-{d.day()}'
        insertDataFormat(pname,cnt, sdt)
        self.dlg.close()
class MyDlg:
    def __init__(self):
        createTable()
        self.dlg = loadUi('four.ui')
        self.dlg.actioninput.triggered.connect(self.inputClick)
        self.dlg.actionview.triggered.connect(self.viewClick)
        # self.dlg.pushButton.clicked.connect( self.fn )
        self.dlg.show()
    def inputClick(self):
        inDlg = InputDlg()
    def insertTableData(self,pname, cnt, pdate):
        nRow = self.dlg.tableWidget.rowCount()
        self.dlg.tableWidget.setRowCount( nRow+1 )
        self.dlg.tableWidget.setItem( nRow,0, QTableWidgetItem(pname))
        self.dlg.tableWidget.setItem( nRow,1, QTableWidgetItem( str(cnt)) )
        self.dlg.tableWidget.setItem( nRow,2, QTableWidgetItem( str(pdate)) )
    def viewClick(self):
        for n,c,d in selectData():
            self.insertTableData(n,c,d)
            # print(n,c,d)
app = QApplication(sys.argv)
dlg = MyDlg()
app.exec()

'''