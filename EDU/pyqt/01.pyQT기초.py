from PyQt5.QtWidgets import *
import sys
# python a.py aa bb cc
# sys.argv ['aa','bb','cc']

def fn():
    print("clikc hello")

app = QApplication(sys.argv)
dlg = QDialog()
dlg.setWindowTitle('타이틀')
dlg.setGeometry(100,100,300,400) # x,y, width, height
vbox = QVBoxLayout()
btn = QPushButton('클릭')
btn.clicked.connect( fn )  # 이벤트 등록
lineEdit = QLineEdit()
vbox.addWidget(btn)
vbox.addWidget(lineEdit)
dlg.setLayout(vbox)
dlg.show()
app.exec() #hang 무한 loop  #큐메모리 감시
print('hello')