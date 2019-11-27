QT += widgets quickwidgets core qml quick network svg charts

TARGET          = VKTool
HEADERS         = mainwindow.h \
    connection/apimethodexecutor.h \
    connection/autosaver.h \
    connection/customnetworkmanager.h \
    graph.h \
    usersview.h \
    vktool.h \
    vkauthenticator/vkauthenticator.h \
    filter.h

SOURCES         = main.cpp \
    mainwindow.cpp \
    connection/apimethodexecutor.cpp \
    connection/autosaver.cpp \
    connection/customnetworkmanager.cpp \
    graph.cpp \
    usersview.cpp \
    vktool.cpp \
    vkauthenticator/vkauthenticator.cpp \
    filter.cpp

INCLUDEPATH += H:/PythonQt3.1/src \
               C:/Users/user/Desktop/WinPython-32bit-3.4.3.7/python-3.4.3/include

LIBS += H:/VKTool/PythonQt/lib/libPythonQt.a \
        C:/Users/user/Desktop/WinPython-32bit-3.4.3.7/python-3.4.3/libs/libpython34.a \
        H:/VKTool/PythonQt/lib/libPythonQt_QtAll.a

include ( H:/PythonQt3.1/build/common.prf )
include ( H:/PythonQt3.1/build/PythonQt.prf )
include ( H:/PythonQt3.1/build/PythonQt_QtAll.prf )

RESOURCES       = dockwidgets.qrc \
    dockwidgets.qrc
OTHER_FILES += \
                qml/menu.qml \
                qml/groupList.qml \
                qml/membersList.qml \
                qml/graph.qml \
                qml/usersView.qml \
                qml/filter.qml

RC_ICONS = vkico.ico
# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/dockwidgets
INSTALLS += target

DISTFILES += \
    Scripts/main.py


