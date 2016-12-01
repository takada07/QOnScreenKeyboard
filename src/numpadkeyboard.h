#ifndef NUMPADKEYBOARD_H
#define NUMPADKEYBOARD_H

#include <IKeyboard.h>

namespace Ui {
class NumpadKeyboard;
}

class NumpadKeyboard : public IKeyboard
{
    Q_OBJECT

public:
    explicit NumpadKeyboard(QWidget *parent = 0);
    ~NumpadKeyboard();
public slots:
    void keyHandler();

private:
    void processElements();
    Ui::NumpadKeyboard *m_ui;
};

#endif // NUMPADKEYBOARD_H
