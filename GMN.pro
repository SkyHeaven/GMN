QT += widgets


SOURCES += \
    Controle.cpp \
    main.cpp \
    Histogramme.cpp \
    Masque.cpp \
    Pixel.cpp \
    Image.cpp \
    MainWindow.cpp \
    DialogRedim.cpp \
    FenHisto.cpp \
    ImageViewer.cpp


HEADERS += \
    Controle.h \
    Histogramme.h \
    Masque.h \
    Pixel.h \
    Image.h \
    MainWindow.h \
    DialogRedim.h \
    FenHisto.h \
    ImageViewer.h


FORMS += \
    MainWindow.ui \
    DialogRedim.ui \
    FenHisto.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../opt/Tools/QtCreator/lib/qtcreator/plugins/qwt-6.1.2/lib/release/ -lqwt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../opt/Tools/QtCreator/lib/qtcreator/plugins/qwt-6.1.2/lib/debug/ -lqwt
else:unix: LIBS += -L$$PWD/../../../opt/Tools/QtCreator/lib/qtcreator/plugins/qwt-6.1.2/lib/ -lqwt

INCLUDEPATH += $$PWD/../../../opt/Tools/QtCreator/lib/qtcreator/plugins/qwt-6.1.2/include
DEPENDPATH += $$PWD/../../../opt/Tools/QtCreator/lib/qtcreator/plugins/qwt-6.1.2/include
