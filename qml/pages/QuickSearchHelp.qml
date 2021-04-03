import QtQuick 2.5
import Sailfish.Silica 1.0

Page {
    id: helpPage
    property bool largeScreen: screen.width >= 1080
    SilicaFlickable {
        anchors.fill: parent
        contentWidth: parent.width
        contentHeight: col.height

        VerticalScrollDecorator {
        }

        Column {
            id: col
            spacing: Theme.paddingLarge
            width: parent.width
            PageHeader {
                title: qsTr("Help on Quick Search")
            }
            Label {
                width: col.width - Theme.paddingLarge * 2
                x: Theme.paddingLarge
                y: Theme.paddingLarge
                text: qsTr("<html><h2>Howto</h2><br>You can search for a category (which will show the related units) \
                or for a unit itself. The category name is a short name.<br>The first unit you tap will hold the <b>'1'</b> \
                value. Then tap on another unit, and the (quick) conversion will pop up on the screen.<br><p> \
                <i>Example:</i><br>Search for 'temp'. All temperature units show up. First tap on 'celsius', followed by a \
                tap on 'fahrenheit'. Now Quick Search will tell you how much fahrenheit <b>'1'</b> (degree) celsius is. \
                </html>")

                font.pixelSize: largeScreen ? Theme.fontSizeSmall : Theme.fontSizeExtraSmall
                wrapMode: Text.Wrap
            }
        }
    }
}
