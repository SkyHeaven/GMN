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
    DialogMasque_T.cpp



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
    DialogMasque_T.h


FORMS += \
    MainWindow.ui \
    DialogRedim.ui \
    FenHisto.ui \
    DialogFusion.ui \
    DialogMasque_T.ui

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
