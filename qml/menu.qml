import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import Qt.labs.settings 1.0
import VKTool 1.0 as VKTool

Item{
    id: menu

    property string user_id
    property string token: ""
    signal showGroups(string user,string token)

    onTokenChanged: {
        VKTool.Shared.token = token;
        console.log(token)
    }
    onUser_idChanged: {
        VKTool.Shared.user_id = user_id;
         console.log(user_id)
    }

    ListView {
        id: listView
        currentIndex: -1
        anchors.fill: parent


        delegate: ItemDelegate {
            width: parent.width
            text: model.title
            highlighted: ListView.isCurrentItem
            onClicked: {
                menu.showGroups(user_id, token)
            }
        }

        model: ListModel {
            ListElement { title: "Groups"; }
            ListElement { title: "Search"; }
        }

        ScrollIndicator.vertical: ScrollIndicator { }
    }
}
