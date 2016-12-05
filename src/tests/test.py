import sys
from PyQt5.QtWidgets import QApplication, QWidget, QLineEdit, QMainWindow, QHBoxLayout, QVBoxLayout
from PyQOnScreenKeyboard.QOnScreenKeyboard import QOnScreenKeyboard   

if __name__ == '__main__':
    
    app = QApplication([])
    keyboard = QOnScreenKeyboard()
    w = QMainWindow()
    edit = QLineEdit();
    mainwidget = QWidget()
    if (len(sys.argv) == 2 and sys.argv[1] == "--numpad"):
        keyboard = QOnScreenKeyboard(mainwidget,QOnScreenKeyboard.Numeric);
        hlayout = QHBoxLayout();
        hlayout.addWidget(edit);
        hlayout.addWidget(keyboard);
        mainwidget.setLayout(hlayout);
    else:
        keyboard = QOnScreenKeyboard();
        vlayout = QVBoxLayout();
        vlayout.addWidget(edit);
        vlayout.addWidget(keyboard);
        mainwidget.setLayout(vlayout);
    w.setCentralWidget(mainwidget);
    w.show();

    
    sys.exit(app.exec_())
