#ifndef _KEYBOARD_IFACE_H_
#define _KEYBOARD_IFACE_H_ 

#include <QWidget>

class IKeyboard : public QWidget
{
    public:
        IKeyboard(QWidget *parent):
            QWidget(parent){}
};
#endif //_KEYBOARD_IFACE_H_ 
