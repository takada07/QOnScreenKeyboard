#include "qonscreenkeyboard.h"
#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <strings.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow w;
    QLineEdit *edit = new QLineEdit();
    QOnScreenKeyboard* keyboard;
    QWidget *mainwidget = new QWidget();
    printf("params %d %s\n",argc, argv[1]);
    if ((argc == 2) && (strcmp(argv[1],"--numpad")==0))
    {
        keyboard = new QOnScreenKeyboard(mainwidget,QOnScreenKeyboard::Numeric);
        QHBoxLayout *hlayout = new QHBoxLayout();
        hlayout->addWidget(edit);
        hlayout->addWidget(keyboard);
        mainwidget->setLayout(hlayout);

    }
    else
    {
        keyboard = new QOnScreenKeyboard();
        QVBoxLayout *vlayout = new QVBoxLayout();
        vlayout->addWidget(edit);
        vlayout->addWidget(keyboard);
        mainwidget->setLayout(vlayout);
    }
    w.setCentralWidget(mainwidget);
    w.show();

    return (a.exec());
}
