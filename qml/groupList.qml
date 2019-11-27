import "URLQuery.js" as URLQuery
import "XHR.js" as XHR

import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import Qt.labs.settings 1.0
import VKTool 1.0 as VKTool



Page {
    id: list
    objectName: "groupListObject"
    title: "Groups"

    property var groups
    property var groupAnswer

    property var groupsCount

    property string user_id
    property string token
    signal getMembers(string group, string offset, string count)


    signal groupsVar(string name, string type, string variable)

    onGroupAnswerChanged: {
        console.log(" DEBUG ", groupAnswer)
        groupsVar("groups", "json", groupAnswer)
    }

    function getGroups(){
        var params = {
            fields: "members_count",
            access_token: token,
            user_id: user_id,
            extended: '1',
            count: '1000'
        }
        function callback(request) {
            console.log("SOME LOG")
            if (request.status && request.status === 200) {
                groupAnswer = request.responseText
                var result = JSON.parse(request.responseText)                
                progressBar.visible = false
                groupsCount = result.response[0]
                result.response.splice(0,1)
                groups = result.response               
            } else {
                console.log("HTTP:", request.status, request.statusText)
            }
        }
        XHR.sendXHR('POST', 'https://api.vk.com/method/groups.get', callback, URLQuery.serializeParams(params))
    }

    onUser_idChanged: {
        console.log(user_id)
    }
    onTokenChanged: {
        console.log(token)
        getGroups()
    }

    ProgressBar{
        id: progressBar
        visible: true
        //color: "#2196F3"
        x: parent.width/2-width/2
        y: parent.height/2-height/2
        width: 64
        height: 64
    }

    property int feed_loading: 0; // use for prevent calling more members function many in one time

    signal groupClicked(string id) // show group by id
    signal membersClicked(string id) // show folowers of group by id
    signal moreGroups(string user_id, string offset, string count)

    function endOfLoading(){
         feed_loading = 0
    }

    ListView{
        id: groupList
        anchors.fill: parent

        focus: true
        clip: true

        onFlickEnded: {
            // END OF FLICK ACTION AND END OF FEED
            if (atYEnd){
                console.log("End of GROUPS", atYEnd)
                // IF FEED NOT LOADING YET
                if (list.feed_loading==0)
                {
                    list.feed_loading = 1
                    console.log("f = 1 ?", list.feed_loading)
                    //list.moreGroups(list.user_id, groupList.count, 100)
                    console.log("f = 0 ?", list.feed_loading)
                }else{
                    console.log("feed loading")
                }
            }
            // JUST AND OF FLICK ACTION
            else{
                console.log("End FLICK", atYEnd)
            }
        }

        model: groups

        delegate:  ItemDelegate {
            id: delegat
            Image {
                id: image
                anchors.top: parent.top
                width: 50
                height: width
                source: modelData['photo']
                sourceSize: Qt.size(parent.width, parent.height)

                cache: true
            }
            Item{
                id: tex
                anchors.top: parent.top
                anchors.left: image.right
                Column{
                    anchors.leftMargin: 8
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.topMargin: 15
                    Text{

                        text: modelData['name']
                    }
                    Text{
                        text:modelData['members_count']
                        font.pixelSize: 10
                        color: "green"
                    }
                }
            }
            width: parent.width
            height: 50

            highlighted: ListView.isCurrentItem

            Popup {
                id: popup
                x: ((parent.width/2)-(width/2))
                y: parent.height
                width: parent.width/2
                height: 120

                //modal: true
                focus: true
                closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

                contentWidth: width
                contentHeight: height

                contentItem: Item{
                    id: itm
                            width: popup.width
                            height: popup.height
                            Column{
                                spacing: 5
                                Column{
                                    Label{
                                        text: "From offset"
                                    }
                                    TextField{
                                        id: offs
                                        width: itm.width
                                    }
                                }
                                Column{
                                    Label{
                                        text: "Count"
                                    }
                                    TextField{
                                        id: coun
                                        width: itm.width
                                        onAccepted: {
                                            list.getMembers(modelData['gid'], offs.text, coun.text)
                                            popup.close()
                                        }
                                    }
                                }
                                Button{
                                    text: "load"
                                    width: itm.width
                                    height: 20
                                    onClicked: {
                                        list.getMembers(modelData['gid'], offs.text, coun.text)
                                        popup.close()
                                    }
                                }
                            }
                        }
                    }

                    property Menu menu: Menu {
                        MenuItem {
                            text: "load all members"
                            onTriggered: {
                                list.getMembers(modelData['gid'], '0',modelData['members_count'])
                            }
                        }
                        MenuItem {
                            text: "load offset members"
                            onTriggered: {
                                popup.open()
                            }
                        }

//                        MenuSeparator{}
//                        MenuItem {
//                            text: "Save as json"
//                        }
                    }
                    onClicked: {
                        //list.getMembers(modelData['gid'])

                        menu.popup()
                    }
                }

        ScrollIndicator.vertical: ScrollIndicator{

        }
    }
}
