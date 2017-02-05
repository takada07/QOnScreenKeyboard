#ifndef _KEYBOARD_IFACE_H_
#define _KEYBOARD_IFACE_H_ 

#include <QWidget>
#include <QPointer>

class IKeyboard : public QWidget
{
    public:
        IKeyboard(QWidget *parent):
            QWidget(parent){}

        void setReceiver(QWidget* receiver) { mReceiver = receiver; }
        QWidget* receiver() const { return mReceiver; }

    protected:
        QPointer<QWidget> mReceiver;
};
#endif //_KEYBOARD_IFACE_H_ 
