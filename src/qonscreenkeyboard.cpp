#include "IKeyboard.h"
#include "fullkeyboard.h"
#include "numpadkeyboard.h"
#include "qonscreenkeyboard.h"
#include <QVBoxLayout>

QOnScreenKeyboard::QOnScreenKeyboard(QWidget *parent, KeyboardType kbdType):
    m_kbdType(kbdType),
    m_pKeyboard(NULL)

{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    switch (m_kbdType)
    {
        case Numeric:
            m_pKeyboard = new NumpadKeyboard(parent);
            break;
        case Full:
        default:
            m_pKeyboard = new FullKeyboard(parent);
    }
    mainLayout->addWidget(m_pKeyboard);
    setLayout(mainLayout);

}

void QOnScreenKeyboard::setReceiver(QWidget* receiver)
{
    m_pKeyboard->setReceiver(receiver);
}

QWidget* QOnScreenKeyboard::receiver() const
{
    return m_pKeyboard->receiver();
}

