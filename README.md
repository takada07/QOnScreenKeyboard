This repository contains virtual Keyboard library for QT5 (without dependency on QML). <br>
Usefull for embedded Linux systems.<br>
<br>
For tutorials check src/tests directory<br>

To build both python and C++ bindings, run:<br>

```$
./configure.py
make
make install
```
<br>
To build only C++ library run:
<br>
```$
cd src
qmake -qt5
make
make install
```
To build only python bindings (in case you have C++ bindings 
already installed) run:
```$
./configure.py --lib-path [path to libQOnscreenKeyboard.so]
make
make install
```
