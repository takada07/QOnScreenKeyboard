#include "numpadkeyboard.h"
#include "ui_numpadkeyboard.h"
#include <QKeyEvent>
NumpadKeyboard::NumpadKeyboard(QWidget *parent) :
    IKeyboard(parent),
    m_ui(new Ui::NumpadKeyboard)
{
    m_ui->setupUi(this);
    processElements();
}

NumpadKeyboard::~NumpadKeyboard()
{
    delete m_ui;
}

void NumpadKeyboard::processElements()
{
    QList<QPushButton*> button_list = findChildren<QPushButton*>();
    printf("Size = %d\n",button_list.size());

    QList<QPushButton*>::iterator iter = button_list.begin();
    for (;iter != button_list.end(); ++iter)
    {
        connect(*iter, SIGNAL(clicked()), this, SLOT(keyHandler()));
    }
}

void NumpadKeyboard::keyHandler()
{
    QObject *button = sender();
    QPushButton *pushButton = static_cast<QPushButton*>(button);
    QVariant variant = pushButton->property("key");
    QKeySequence key = variant.value<QKeySequence>(); 
    unsigned int presskey = key[0];
    QChar chr(presskey);
    printf("%d\n",presskey);
    QKeyEvent keyPress(QEvent::KeyPress, presskey, Qt::NoModifier, QString(chr));
    QWidget* w = QApplication::focusWidget();
    if (w)
        QApplication::sendEvent(w, &keyPress);
}

