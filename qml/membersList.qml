import "URLQuery.js" as URLQuery
import "XHR.js" as XHR

import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import Qt.labs.settings 1.0
import VKTool 1.0 as VKTool

Page {
    id: wraper
    width: parent.width
    height: parent.height
    title: "Members"
    objectName: "membersListObject"
    property Item myParent;
    property int feed_loading: 0;
    property string group_id;
    property int offsetGlobal: 0
    property Item curLike: likePrev;

    // prevent change curLike link if prev hasnt already return answer
    Item { id: likePrev; property string free: "true" }

    function answerCurLike(answer){
        if (answer!==""){
            curLike.source = "images/1.png"
            curLike.children[0].text=answer
            console.log(answer)
        }else{
            console.log("cant like")
        }
        curLike=likePrev;
    }

    signal getFilterUser(string id, string offset, string sex)
    signal likeAvaClicked(string id, string obj) // like avata of user by id

    //-------------GET LIKE INFO
    property ListModel members: ListModel{}
    property var tmpMembers: new Array()
    property var ids: new Array()
    property var tmpIds: new Array()
    property var likesFinal: new Array()
    property var countFinal: new Array()

    // get members info
    function getMembers(g_offset){
        tmpMembers=[]
        ids=[]
        tmpIds=[]
        likesFinal=[]
        countFinal=[]

        membersList.feed_loading = 1
        var params = {
            fields: "sex,bdate,city,country,photo_id,photo_50,photo_100,photo_200,online,online_mobile,lists,contacts,connections,site,education,universities,schools,can_write_private_message,status,last_seen,common_count,relation,relatives,counters",
            access_token: VKTool.Shared.token,
            group_id: group_id,
            offset: g_offset,
            count: '100'
        }
        function callback(request) {
            if (request.status && request.status === 200) {
                var result = JSON.parse(request.responseText)
                tmpMembers = result.response.users
                console.log("MEMBERS ",request.responseText)
                getLikes()
            } else {
                console.log("HTTP:", request.status, request.statusText)
            }
        }
        XHR.sendXHR('POST', 'https://api.vk.com/method/groups.getMembers', callback, URLQuery.serializeParams(params))
    }

    // fill liked and likes count arrays
    function getLikes(){
        tmpMembers.forEach(function(item, i, tmpMembers){
            if(item['photo_id']){
                ids.push(item['photo_id'])
            }else{
                likesFinal[i] = "0";
                countFinal[i] = " ";
            }
        }
        )
        getPhotoIds(ids)
    }

    // get photo info by id
    function getPhotoIds(pid){
        var params = {
            access_token: VKTool.Shared.token,
            photos: pid,
            extended: '1'
        }
        function callback(request) {
            if (request.status && request.status === 200) {
                var result = JSON.parse(request.responseText)
                tmpIds = result.response
                console.log("IDS ",request.responseText)

                for (var i=0; i<100; i++)
                {
                    if (countFinal[i]!==" ")
                    {
                        likesFinal[i] = tmpIds[i].likes.user_likes
                        countFinal[i] = tmpIds[i].likes.count
                    }else // hook
                    {
                        tmpIds.splice(i,0,"");
                    }
                    tmpMembers[i].liked = likesFinal[i]
                    tmpMembers[i].likesCount = countFinal[i]
                }
                //progressBar.visible = false
                members.append(tmpMembers)
                membersList.feed_loading = 0
            } else {
                console.log("HTTP:", request.status, request.statusText)
            }
        }
        XHR.sendXHR('POST', 'https://api.vk.com/method/photos.getById', callback, URLQuery.serializeParams(params))
    }
    //------------

    onGroup_idChanged: {
        getMembers(0)
    }

    Component.onCompleted: {
        membersList.likeAvaClicked.connect(likeAvaClicked)
        offsetGlobal = 100
    }

    Dialog {
        id: filterDialog
        title: "Filter parameters"

        Controls.ExclusiveGroup {
            id: optionGroup
        }

        RadioButton {
            text: "Girl"
            property string val: "1"
            checked: true
            exclusiveGroup: optionGroup
        }
        RadioButton {
            text: "Man"
            property string val: "1"
            exclusiveGroup: optionGroup
        }
        Label {
            font.family: "Roboto"
            text: "Offset"
            font.pixelSize: Units.dp(16)
        }
        TextField {
            id: offset
            width: parent.width
            placeholderText: "0"
            onAccepted: {
                filterDialog.close()
                filterDialog.accepted()
            }
        }
        onAccepted: {
            VKTool.Shared.mainWindow.showFilterUser(wraper.group_id, optionGroup.current.val, offset.text)
        }
        positiveButtonText: "filter"
        //negativeButtonText: "disagree"
    }

    actions: [

        Action {
            iconName: "action/search"
            //name: "search"
            onTriggered: {
                filterDialog.show()
            }
        },
        Action {
            iconName: "action/home"
            //name: "home"
            onTriggered: {
                myParent.popAll()
            }
        }
    ]

    GridView {
        id: membersList
        objectName: "memGridObject"
        anchors.fill: parent
        cellWidth: 135;
        cellHeight: 135
        focus: true
        clip: true
        model: members
        delegate: membersDelegate

        footer: Item{
            width: parent.width
            height: Units.dp(70)
            ProgressCircle {
                id: progressBar
                visible: membersList.feed_loading
                color: "#2196F3"
                width: Units.dp(50)
                height: Units.dp(50)
                anchors.centerIn: parent.Center
                x: parent.width/2 - progressBar.width/2
                y: 10

            }
        }

        property int before: 0
        property int now: 0
        property int feed_loading: 1

        signal likeAvaClicked(string id, string obj) // like avata of user by id

        onFlickEnded: {
            // END OF FLICK ACTION AND END OF FEED
            if (atYEnd){
                console.log("End of MEMBERS list", atYEnd)
                // IF FEED NOT LOADING YET
                if (feed_loading==0)
                {
                    console.log("feed not loading Start Load Members")
                    getMembers(offsetGlobal)
                    offsetGlobal += 100
                }else{
                    console.log("feed already loading")
                }
            }
            // JUST AND OF FLICK ACTION
            else{
                 console.log("Just End of FLICK", atYEnd)
            }
        }

        OverlayView {
            id: overlayView

            width: Units.dp(200)
            height: Units.dp(200)

            Image {
                id: contentImage
                source: overlayView.sourceView.sizedPhoto
                anchors.fill: parent
                asynchronous: true
                Label{
                    id: server
                    text:"cant load"
                    visible: contentImage.status === 0
                    anchors.centerIn: parent
                }

                ProgressCircle {
                    id: determinateProgress
                    indeterminate: false
                    minimumValue: 0
                    maximumValue: 100
                    anchors.centerIn: parent
                    value: (contentImage.progress*100)
                    width:100
                    height: 100
                    visible: contentImage.status === 2
                    color: "#2196F3"

                    Label {
                        anchors.centerIn: parent
                        text: Math.round(determinateProgress.value) + "%"
                    }
                }
            }


            Rectangle{
                id: info
                anchors.top: contentImage.bottom
                anchors.left: contentImage.left
                width: contentImage.width
                height: infoList.height+20
                Column{
                    id: infoList
                    spacing:10
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.margins: 10
                    visible: overlayView.transitionOpacity===1
                    Row{
                        id: nameRow
                        Label{
                            id: name
                            text: overlayView.sourceView.first_n + " " + overlayView.sourceView.last_n
                            Rectangle{
                                anchors.leftMargin: 5
                                anchors.left: name.right
                                anchors.verticalCenter: name.verticalCenter
                                color: "green"
                                visible: parseInt(overlayView.sourceView.online_n);
                                height: name.height/2
                                width: height
                                radius: width/2
                            }
                        }

                    }
                    Label{
                        id: status1
                        text: overlayView.sourceView.status_n
                        visible: (overlayView.sourceView.status_n!=="") ? 1: 0
                        width: info.width

                        elide: Text.ElideRight
                        wrapMode: Text.Wrap
                        maximumLineCount: 1
                    }

                    Label{
                        id: country1
                        text: overlayView.sourceView.country_n + ", " + overlayView.sourceView.city_n
                        visible: (overlayView.sourceView.country_n!=="") ? 1: 0
                    }
                    Label{
                        id: last_seen1
                        text: parseInt(overlayView.sourceView.online_n) ? "" : ("Был: " + overlayView.sourceView.last_seen_n)
                    }
                    Label{
                        id: can_write_private_message1
                        text: parseInt(overlayView.sourceView.can_write_private_message_n) ? "Могу написать: Да" : "Могу написать: Нет"
                    }
                }
            }

            // actions
            Row {
                anchors {
                    top: parent.top
                    right: parent.right
                    rightMargin: Units.dp(16)
                }
                height: Units.dp(48)
                opacity: overlayView.transitionOpacity

                spacing: Units.dp(24)

                Repeater {
                    model: ["social/share"]

                    delegate: IconButton {
                        id: iconAction

                        iconName: modelData

                        color: Theme.dark.iconColor
                        size: iconName == "content/add" ? Units.dp(27) : Units.dp(24)
                        anchors.verticalCenter: parent.verticalCenter
                        onClicked: {
                            console.log("clicked share ", overlayView.sourceView.id_n, overlayView.sourceView.sizedPhoto)
                            myParent.share(overlayView.sourceView.id_n)
                        }
                    }
                }
            }
        }

        Component {
            id: membersDelegate
            Item{
                id: itemView
                height: 135
                width: 135

                MouseArea {
                          id: mArea
                          anchors.fill: parent
                          hoverEnabled: true
                          onClicked: {
                              //console.log("clicked  ", " members id ", membersList.count)
                              //groupList.groupClicked(id)
                              //groupList.parent.parent.showWall( currentItem.link);
                          }
                          onEntered: {
                              membersList.currentIndex = index
                          }
                     }

                Item {
                    id: frame
                    anchors.fill: parent
                    // Member photo
                    Image{
                        id: memberPhoto
                        source: photo_100
                        property string id_n: uid
                        property string sizedPhoto: photo_200
                        property string first_n: first_name
                        property string last_n: last_name
                        property string country_n: country
                        property string city_n: city
                        property string online_n: online
                        property string education_n: education
                        property string status_n: status //!!! BUG CHAGE STATUS NAME IN VK MODEL TO STATUSES, QT RESERV NAME
                        property string last_seen_n: last_seen
                        property string relation_n: relation
                        property string can_write_private_message_n: can_write_private_message

                        width: 100
                        height: 100
                        fillMode: Image.Stretch
                        smooth: true
                        cache: true
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter:  parent.verticalCenter

                        ProgressCircle {
                            id: determinateProgress
                            indeterminate: false
                            minimumValue: 0
                            maximumValue: 100
                            anchors.centerIn: parent
                            value: (memberPhoto.progress*100)
                            width: 50
                            height: 50
                            visible: memberPhoto.status === 2
                            color: "#2196F3"

                            Label {
                                anchors.centerIn: parent
                                text: Math.round(determinateProgress.value) + "%"
                            }
                        }

                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                overlayView.open(memberPhoto)
                            }
                        }

                        // Name
                        Row{
                            id: nameRow
                            anchors.horizontalCenter: memberPhoto.horizontalCenter
                            opacity: 0.85
                            Label{
                                id: name
                                font.family:  "Open Sans"
                                font.weight: Font.Bold
                                font.pixelSize: 16
                                text: first_name
                                Rectangle{
                                    anchors.leftMargin: 5
                                    anchors.left: name.right
                                    anchors.verticalCenter: name.verticalCenter
                                    color: "green"
                                    opacity: parseInt(online);
                                    height: name.height/2
                                    width: height
                                    radius: width/2
                                }
                            }
                        }

                        // Like
                        Image{
                            id: like
                            property string free: "false"
                            anchors.horizontalCenter: memberPhoto.horizontalCenter
                            //anchors.verticalCenter: memberPhoto.verticalCenter
                            anchors.bottom: parent.bottom
                            source: "images/"+liked+".png" //!!! DEBUG
                            fillMode: Image.Stretch
                            smooth: true
                            cache: true
                            opacity: 0.85
                            state: "RELEASED"
                            transformOrigin: Item.Center

                            states: [
                                State {
                                    name: "PRESSED"
                                    PropertyChanges { target: like;  scale: 3}   //width: 100; height: 100;}
                                },
                                State {
                                    name: "RELEASED"
                                    PropertyChanges { target: like; scale: 1.0}
                                }
                            ]

                            transitions: [
                                Transition {
                                     PropertyAnimation { easing.amplitude: 2.5; easing.period: 1.5; duration: 100; properties: "scale"; easing.type: Easing.InOutElastic }
                                }

                            ]

                            // Likes count
                            Text {
                                id: likeCount
                                text: likesCount
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.bottom: parent.bottom
                                anchors.bottomMargin: (parent.height/2-height/2)+height/4
                                color: "#5555ec"
                                font.family:  "Open Sans"
                                font.weight: Font.Bold
                                font.pixelSize: 12
                            }
                            MouseArea{
                                anchors.fill: parent
                                hoverEnabled: true
                                onEntered: {

                                    //like.opacity = 0.98
                                }
                                onExited: {

                                     //like.opacity = 0.85
                                }
                                onPressed: {
                                    console.log("LIKE")

                                    // if we hadnt like it, and dont like after model load
                                    if ((liked!==1)&(like.source!=="images/1.png")){
                                        // if we dont wait answer from prev like
                                        if (curLike.free==="true"){
                                            like.state="PRESSED"
                                            curLike = like
                                            likeAvaClicked(photo_id,"member")
                                        }else{
                                            console.log("PREV LIKE WAITING")
                                        }
                                    }else{
                                        console.log("already liked")
                                    }
                                }
                                onReleased: {
                                    like.state="RELEASED"
                                    //like.opacity = 0.4
                                }
                            }
                        }
                    }
                }
            }
        }

        Scrollbar {
            flickableItem: membersList
        }
    }
}
