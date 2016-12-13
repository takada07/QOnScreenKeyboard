This repository contains virtual Keyboard library for QT5 (without dependency on QML). 
Usefull for embedded Linux systems.

For tutorials check src/tests directory

To build both python and C++ bindings, run:

./configure.py

To build only C++ library, go to src directory and run:

qmake -qt5 
make
make install

To build only python bindings (in case you have C++ bindings 
already installed) run:

./configure.py --lib-path [path to libQOnscreenKeyboard.so]