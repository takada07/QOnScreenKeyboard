#ifndef QONSCREENKEYBOARD_H
#define QONSCREENKEYBOARD_H

#include <QtCore/qglobal.h>

#if defined(QONSCREENKEYBOARD_LIBRARY)
#  define QONSCREENKEYBOARDSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QONSCREENKEYBOARDSHARED_EXPORT Q_DECL_IMPORT
#endif

#include <QWidget>

class IKeyboard;

class QONSCREENKEYBOARDSHARED_EXPORT QOnScreenKeyboard : public QWidget
{

public:
    enum KeyboardType
    {
        Numeric,
        Full,
        Custom
    };
    QOnScreenKeyboard(QWidget* parent=0, KeyboardType kbdType=Full);

    void setReceiver(QWidget* receiver);
    QWidget* receiver();

private:
    KeyboardType m_kbdType;
    IKeyboard *m_pKeyboard;
};

#endif // QONSCREENKEYBOARD_H
