import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import QtQuick.Controls 1.4

TableView{
    id: variableExplorer
    width: 500
    height: 500

    Material.theme: Material.Dark
    Material.accent: Material.Purple

    function returnColor(dt){
        switch (dt){
        case 'int':
            return "#CCFFCC"
        case 'list':
            return "#FFFFCC"
        case 'string':
            return "#E6CCCC"
        case 'dataframe':
            return "#82CDFF"
        default:
            return "red"
        }
    }

    onClicked:{
        console.log("ORIG")
    }

    itemDelegate: Rectangle{
        color: variableExplorer.returnColor(model.datatype)
        id: curRow
        Text{
            anchors.verticalCenter: parent.verticalCenter
            //anchors.horizontalCenter: parent.horizontalCenter
            anchors.leftMargin: 5
            anchors.left: parent.left
            text: styleData.value
            color: styleData.textColor
            elide: Text.ElideLeft
            width: curRow.width-45
            clip: true
            maximumLineCount: 1
            wrapMode: Text.WrapAnywhere

        }
        Image{
            anchors.right: parent.right
            anchors.rightMargin: 10
            source: "qrc:/images/horiz_black.svg"
            height: parent.height
            fillMode: Image.PreserveAspectFit
            visible: styleData.column == 3
            MouseArea{
                anchors.fill: parent
                propagateComposedEvents: true
                onClicked: {
                    curRow.menu.popup()
                    mouse.accepted = false
                }
            }
        }

        property Menu menu: Menu {
            MenuItem {
                text: "Load to Graph..."
            }
            MenuItem {
                text: "Edit..."
            }
            MenuSeparator{}
            MenuItem {
                text: "Save as json"
            }
        }
    }

    TableViewColumn {
        id: col1
        role: "name"
        title: "Name"
        width: 80
    }
    TableViewColumn {
        id: col2
        role: "datatype"
        title: "Datatype"
        width: 80
    }
    TableViewColumn {
        id: col3
        role: "size"
        title: "Size"
        width: 80
    }
    TableViewColumn {
        role: "value"
        title: "Value"
        width: variableExplorer.width-col1.width-col2.width-col3.width
    }
    model: variableModel
}




