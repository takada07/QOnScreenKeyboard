%Module QOnScreenKeyboard

%Import QtCore/QtCoremod.sip
%Import QtWidgets/QtWidgetsmod.sip

%If (Qt_5_0_0 -)

class QOnScreenKeyboard : public QWidget
{

%TypeHeaderCode
#include <qonscreenkeyboard.h>
%End

public:
    enum KeyboardType
    {
        Numeric,
        Full,
        Custom
    };
    explicit QOnScreenKeyboard(QWidget* parent=0, QOnScreenKeyboard::KeyboardType kbdType=QOnScreenKeyboard::Full);

    void setReceiver(QWidget* receiver);
    QWidget* receiver() const;
};

%End
