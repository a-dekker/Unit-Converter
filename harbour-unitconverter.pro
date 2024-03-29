# The name of your app.
# NOTICE: name defined in TARGET has a corresponding QML filename.
#         If name defined in TARGET is changed, following needs to be
#         done to match new name:
#         - corresponding QML filename must be changed
#         - desktop icon filename must be changed
#         - desktop filename must be changed
#         - icon definition filename in desktop file must be changed
TARGET = harbour-unitconverter

CONFIG += sailfishapp c++11 sailfishapp_i18n
QT += network \
      dbus
DEPLOYMENT_PATH = /usr/share/$${TARGET}
PKGCONFIG += nemonotifications-qt5

SOURCES += src/harbour-unitconverter.cpp \
    src/custommodel.cpp \
    src/converter.cpp \
    src/settings.cpp \
    src/currencycache.cpp

OTHER_FILES += qml/harbour-unitconverter.qml \
    qml/cover/CoverPage.qml \
    rpm/harbour-unitconverter.spec \
    rpm/harbour-unitconverter.yaml \
    harbour-unitconverter.desktop \
    translations/*.ts \
    qml/pages/QuickSearchPage.qml \
    qml/pages/QuickSearchHelp.qml \
    qml/pages/MainPage.qml \
    qml/pages/scripts/Unitconverter.js \
    qml/pages/scripts/HelperVariables.js \
    qml/pages/components/UnitWindow.qml \
    qml/pages/components/Resultpanel.qml \
    qml/pages/AboutPage.qml \
    qml/pages/UnitConvertPage.qml \
    qml/pages/RulerPage.qml \
    qml/pages/components/Ruler.qml \
    qml/pages/OptionsPage.qml \
    qml/pages/components/Line.qml \
    qml/pages/scripts/Logic.js \
    qml/pages/components/AcceptPopup.qml \
    qml/pages/scripts/UnitConververDB.js \
    qml/pages/FavouritesPage.qml \
    qml/pages/FavouriteDialog.qml

isEmpty(VERSION) {
    VERSION = $$system( egrep "^Version:\|^Release:" rpm/harbour-unitconverter.spec | tr -d "[A-Z][a-z]: " | tr "\\\n" "-" | sed "s/\.$//g" | tr -d "[:space:]")
    message("VERSION is unset, assuming $$VERSION")
}
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

TRANSLATIONS = translations/harbour-unitconverter-nl.ts \
               translations/harbour-unitconverter-fr.ts \
               translations/harbour-unitconverter-sv.ts \
               translations/harbour-unitconverter-zh_CN.ts \
               translations/harbour-unitconverter-ru.ts
translations.files = translations
translations.path = $${DEPLOYMENT_PATH}
# only include these files for translation:
lupdate_only {
    SOURCES = qml/*.qml \
              qml/pages/*.qml \
              qml/pages/components/*.qml
}

icon86.files += icons/86x86/harbour-unitconverter.png
icon86.path = /usr/share/icons/hicolor/86x86/apps

icon108.files += icons/108x108/harbour-unitconverter.png
icon108.path = /usr/share/icons/hicolor/108x108/apps

icon128.files += icons/128x128/harbour-unitconverter.png
icon128.path = /usr/share/icons/hicolor/128x128/apps

icon172.files += icons/172x172/harbour-unitconverter.png
icon172.path = /usr/share/icons/hicolor/172x172/apps

icon256.files += icons/256x256/harbour-unitconverter.png
icon256.path = /usr/share/icons/hicolor/256x256/apps

INSTALLS += translations icon86 icon108 icon128 icon172 icon256

HEADERS += \
    src/custommodel.h \
    src/converter.h \
    src/settings.h \
    src/currencycache.h

RESOURCES += \
    MyResource.qrc
