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
    ImageViewer.cpp \
    DialogFusion.cpp \
    SeamCarving.cpp \
    SeamCarving.cpp


HEADERS += \
    Controle.h \
    Histogramme.h \
    Masque.h \
    Pixel.h \
    Image.h \
    MainWindow.h \
    DialogRedim.h \
    FenHisto.h \
    ImageViewer.h \
    DialogFusion.h \
    SeamCarving.h \
    SeamCarving.h


FORMS += \
    MainWindow.ui \
    DialogRedim.ui \
    FenHisto.ui \
    DialogFusion.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../opt/Tools/QtCreator/lib/qtcreator/plugins/qwt-6.1.2/lib/release/ -lqwt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../opt/Tools/QtCreator/lib/qtcreator/plugins/qwt-6.1.2/lib/debug/ -lqwt
else:unix: LIBS += -L$$PWD/../../../opt/Tools/QtCreator/lib/qtcreator/plugins/qwt-6.1.2/lib/ -lqwt

INCLUDEPATH += $$PWD/../../../opt/Tools/QtCreator/lib/qtcreator/plugins/qwt-6.1.2/include
DEPENDPATH += $$PWD/../../../opt/Tools/QtCreator/lib/qtcreator/plugins/qwt-6.1.2/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../usr/local/qwt-6.1.2/lib/release/ -lqwt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../usr/local/qwt-6.1.2/lib/debug/ -lqwt
else:unix: LIBS += -L$$PWD/../../../../../../usr/local/qwt-6.1.2/lib/ -lqwt

INCLUDEPATH += $$PWD/../../../../../../usr/local/qwt-6.1.2/include
DEPENDPATH += $$PWD/../../../../../../usr/local/qwt-6.1.2/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../usr/local/qwt-6.1.2/lib/release/ -lqwt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../usr/local/qwt-6.1.2/lib/debug/ -lqwt
else:unix: LIBS += -L$$PWD/../../../../../../usr/local/qwt-6.1.2/lib/ -lqwt

INCLUDEPATH += $$PWD/../../../../../../usr/local/qwt-6.1.2/include
DEPENDPATH += $$PWD/../../../../../../usr/local/qwt-6.1.2/include
