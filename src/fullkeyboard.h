#ifndef FULLKEYBOARD_H
#define FULLKEYBOARD_H

#include "IKeyboard.h"
namespace Ui {
class FullKeyboard;
}

class QPushButton;

class FullKeyboard : public IKeyboard
{
    Q_OBJECT
public:
    explicit FullKeyboard(QWidget *parent = 0);
    ~FullKeyboard();

public slots:
    void keyHandler();

private:
    void processShift();
    void processCapsLock();

    void processElements();

    Ui::FullKeyboard*   m_ui;
    bool                m_shiftActivated;
    bool                m_capsActivated;
    QPushButton*        m_shiftButton;
    QPushButton*        m_capsButton;
};

#endif // FULLKEYBOARD_H
