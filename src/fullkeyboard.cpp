#include "fullkeyboard.h"
#include "ui_fullkeyboard.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QApplication>
#include <QVariant>
#include <QKeyEvent>

FullKeyboard::FullKeyboard(QWidget *parent) :
    IKeyboard(parent),
    m_ui(new Ui::FullKeyboard),
    m_shiftActivated(false),
    m_capsActivated(false),
    m_shiftButton(nullptr),
    m_capsButton(nullptr)
{
    m_ui->setupUi(this);
    processElements();
}

FullKeyboard::~FullKeyboard()
{
    delete m_ui;
}

void FullKeyboard::processElements()
{
    QList<QPushButton*> button_list = findChildren<QPushButton*>();
    printf("Size = %d\n",button_list.size());

    QList<QPushButton*>::iterator iter = button_list.begin();
    for (;iter != button_list.end(); ++iter)
    {
        QPushButton *button = static_cast<QPushButton *>(*iter);
        if (button->objectName() == "key_id16")
            m_shiftButton=button;
        if (button->objectName() == "key_id58")
            m_capsButton=button;
        connect(*iter, SIGNAL(clicked()), this, SLOT(keyHandler()));
    }
}

void FullKeyboard::processCapsLock()
{
    if (m_capsActivated==false)
    {
        m_capsButton->setDown(true);
        m_capsActivated=true;
    }
    else
    {
        m_capsButton->setDown(false);
        m_capsActivated=false;
    }
    QList<QPushButton*> button_list = findChildren<QPushButton*>();
    QList<QPushButton*>::iterator iter = button_list.begin();
    for (;iter != button_list.end(); ++iter)
    {
        QVariant variant;
        QPushButton *button = static_cast<QPushButton *>(*iter);
        variant = button->property("key");
        if (variant.isNull())
        {
            if (button == m_shiftButton)
            {
                if (m_capsActivated==true)
                    button->setEnabled(false);
                else
                    button->setEnabled(true);
            }

        }
        else
        {
            QKeySequence key = variant.value<QKeySequence>(); 
            variant = button->property("shift_enabled");
            if ((!variant.isNull()) && (variant.toBool()==true))
            {
                variant = button->property("shift_key");
                if (variant.isNull())
                {
                    if (m_capsActivated)
                        button->setText(button->text().toUpper());
                    else
                        button->setText(button->text().toLower());
                }
            }
        }
    }
}

void FullKeyboard::processShift()
{
    if (m_shiftActivated==false)
    {
        m_shiftButton->setDown(true);
        m_shiftActivated=true;
    }
    else
    {
        m_shiftButton->setDown(false);
        m_shiftActivated=false;
    }
    QList<QPushButton*> button_list = findChildren<QPushButton*>();
    QList<QPushButton*>::iterator iter = button_list.begin();
    for (;iter != button_list.end(); ++iter)
    {
        QVariant variant;
        QPushButton *button = static_cast<QPushButton *>(*iter);
        variant = button->property("key");
        if (variant.isNull())
        {
            variant = button->property("modifier");
            if (!variant.isNull())
            {
                if (variant.toString() == "CAPSLOCK")
                {
                    if (m_shiftActivated==true)
                        button->setEnabled(false);
                    else
                        button->setEnabled(true);
                }
            }
        }
        else
        {
            QKeySequence key = variant.value<QKeySequence>(); 
            variant = button->property("shift_enabled");
            if (variant.isNull() || variant.toBool()==false)
            {
                if (m_shiftActivated)
                {
                    button->setText(" ");
                    button->setEnabled(false);
                }
                else
                {
                    char str[2];
                    str[0]=(char)key[0];
                    str[1]='\0';
                    button->setText(str);
                    button->setEnabled(true);
                }
            }
            else
            {
                bool has_shift = variant.toBool();
                if (has_shift)
                {
                    variant = button->property("shift_key");
                    if (variant.isNull())
                    {
                        if (m_shiftActivated)
                            button->setText(button->text().toUpper());
                        else
                            button->setText(button->text().toLower());
                    }
                    else
                    {
                        if (m_shiftActivated)
                            key = variant.value<QKeySequence>();
                        if ((key[0] != Qt::Key_Backspace) && 
                            (key[0] != Qt::Key_Return))
                        {
                            char str[2];
                            str[0]=(char)key[0];
                            str[1]='\0';
                            button->setText(str);
                        }
                    }
                }
            }
        }
    }
}

void FullKeyboard::keyHandler()
{
    QObject *button = sender();
    QPushButton *pushButton = static_cast<QPushButton*>(button);
    if (pushButton->objectName() == "key_id16")
    {
        processShift();
    }
    else if (pushButton->objectName() == "key_id58")
    {
        processCapsLock();
    }
    else
    {
        QVariant variant = pushButton->property("key");
        QKeySequence key = variant.value<QKeySequence>(); 
        Qt::KeyboardModifier modifier = Qt::NoModifier;
        if (m_shiftActivated)
        {
            variant = pushButton->property("shift_enabled");
            if (variant.toBool()==true)
            {
                variant = pushButton->property("shift_key");
                if (!variant.isNull())
                    key = variant.value<QKeySequence>(); 
                else
                    modifier = Qt::ShiftModifier;
            }
        }
        unsigned int presskey = key[0];
        QChar chr(presskey);
        if ((presskey >= 65) && (presskey <= 90) && (!m_shiftActivated) && (!m_capsActivated))
            chr = presskey+32;
        QKeyEvent keyPress(QEvent::KeyPress, presskey, modifier, QString(chr));
        QWidget* w = QApplication::focusWidget();
        QApplication::sendEvent(w, &keyPress);
        if (m_shiftActivated)
            processShift();
    }
}
