import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import QtQuick.Controls 1.4
import "URLQuery.js" as URLQuery
import "XHR.js" as XHR
import VKTool 1.0 as VKTool

GridView{
    id: usersView
    width: 500
    height: 500

    Material.theme: Material.Dark
    Material.accent: Material.Purple
    cellHeight: photoSize+10
    cellWidth: photoSize+10

    property int photoSize: 100

    signal likeClicked(string pid)

    property string answer
    property var ansLikes

    property string token

    property var curLiked
    property var curLikes
    property var clicked


    header: Component{
        Item{
            id: somes
            width: usersView.width
            height: 35
            signal clicked()
            Button{
                text:"AUTO LIKE"
                height: 35
                width: 140
                anchors.horizontalCenter: somes.horizontalCenter
                anchors.verticalCenter: somes.verticalCenter
                onClicked: {
                    somes.clicked()
                }
            }
        }
    }

    Connections{
        target: headerItem
        onClicked: autoLike()
    }

    function getRandom(min, max) {
      return Math.floor((Math.random() * (max - min) + min));
    }

    property int likeLoop: 0;
    property int error: 0;

    onErrorChanged: {
        if (error==14){
            likeTimer.stop()
        }else if(error==1){
            likeTimer.start()
        }
    }

    onLikeLoopChanged: {
        if (likeLoop>usersView.count){
            likeTimer.stop()
        }
    }

    function autoLike(){
        console.log("Auto Like")
        likeLoop = 0
        likeTimer.start()
    }

    Timer {
        id: likeTimer
        interval: 1000; running: false; repeat: true; triggeredOnStart: false;
        onTriggered: {
            // TIME BETWEEN AUTO LIKES
            interval = getRandom(3000,5000)
            console.log(usersModel.length,likeLoop," wait ", interval)
            if (usersModel[likeLoop].photoid!=="nan"){
                addLike(usersModel[likeLoop].photoid)
            }else{
                console.log(" nan next")
            }
            likeLoop += 1;
        }
    }


    onTokenChanged: {
        //console.log(token, "USER VIEW ")
    }

    onModelChanged: {
        //        for (var i=0; i<usersView.count; i++){
        //            pidInfo(usersModel[i].photoid)
        //            console.log(usersModel[i].liked)
        //            usersModel[i].setLiked(curLiked)
        //            console.log("curliked ",curLiked)
        //        }
    }

    Popup {
        id: captcha
        x: ((parent.width/2)-(width/2))
        y: ((parent.height/2)-(height/2))
        width: 160
        height: 110

        //modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        contentWidth: width
        contentHeight: height

        property string img: ""
        property string sid: ""
        property string pid: ""

        contentItem: Item{
            id: itm
            width: 160
            height: 110

            Image {
                id: captcha_img
                anchors.top: itm.top
                anchors.left: itm.left
                source: captcha.img
            }
            TextField{
                id: captcha_text
                width: itm.width
                anchors.topMargin: 5
                anchors.bottomMargin: 5
                anchors.top: captcha_img.bottom
                anchors.left: itm.left
                onAccepted: {
                    addLikeCaptcha(captcha.pid, captcha.sid, captcha_text.text)
                    captcha.close()
                    captcha.pid = ""
                    captcha.sid = ""
                    captcha_text.text = ""
                }
            }
            Button{
                text: "ok"
                anchors.top: captcha_text.bottom
                anchors.left: itm.left
                width: itm.width
                height: 20
                onClicked: {
                    addLikeCaptcha(captcha.pid, captcha.sid, captcha_text.text)
                    captcha.close()
                    captcha.pid = ""
                    captcha.sid = ""
                    captcha_text.text = ""
                }
            }
        }
    }

    function showCaptcha(src,sid,pid){
        captcha.img = src
        captcha.sid = sid
        captcha.pid = pid
        captcha.open()
    }

    function addLikeCaptcha(pid, sid, text){
        var params = {
            type: "photo",
            access_token: token,
            owner_id: pid.split("_")[0],
            item_id: pid.split("_")[1],
            captcha_sid: sid,
            captcha_key: text
        }
        function callback(request) {
            if (request.status && request.status === 200) {
                answer = request.responseText
                console.log(answer)

                usersView.error=1

                var result = JSON.parse(request.responseText)
                ansLikes = result.response.likes
                console.log("LIKE ", ansLikes)
            } else {
                console.log("HTTP:", request.status, request.statusText)
            }
        }
        XHR.sendXHR('POST', 'https://api.vk.com/method/likes.add', callback, URLQuery.serializeParams(params))
    }

    function addLike(pid){
        console.log("add like call ", pid)
        var params = {
            type: "photo",
            access_token: token,
            owner_id: pid.split("_")[0],
            item_id: pid.split("_")[1]
        }
        function callback(request, pid) {
            if (request.status && request.status === 200) {
                answer = request.responseText
                console.log("ANSWER ", answer)
                var result = JSON.parse(request.responseText)

                if (result.error){
                    if (result.error.error_code === 14){
                        usersView.error = 14
                        console.log("CAPTCHA NEED ", result.error.error_code)
                        showCaptcha(result.error.captcha_img, result.error.captcha_sid, pid)
                        //console.log(result.error.captcha_sid)
                    }
                }else{
                    ansLikes = result.response.likes
                    console.log("LIKE ", ansLikes)
                }
            } else {
                console.log("HTTP:", request.status, request.statusText)
            }
        }
        XHR.sendXHRLike(pid, 'POST', 'https://api.vk.com/method/likes.add', callback, URLQuery.serializeParams(params))
    }






    onLikeClicked:{
        if (pid!=="nan"){
            console.log(pid)
            usersView.addLike(pid)
        }else{
            console.log("pid is nan")
        }
    }

    delegate: Item{

        width: photoSize
        height: photoSize

        Column {
            anchors.fill: parent
             Image { source: photoSize==50 ? photo50 : photo100; anchors.horizontalCenter: parent.horizontalCenter

                Image{
                    id: like
                    source: "qrc:/images/like.svg"
                    width: 32
                    height: 32
                    fillMode: Image.PreserveAspectFit
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom

                    Text{
                        id: tex
                        color: "red"
                        font.pixelSize: 12

                    }
                    Component.onCompleted: {
                        usersView.curLiked = 0
                        usersView.curLikes = 0
                        //console.log("ID",photoid, "UV=0?",usersView.curLikes)
                        ///pidInfo(photoid, callbackPH)
                        //console.log("UVafPID", usersView.curLikes)
                        //tex.text = usersView.curLikes
                    }


                    //anchors.bottomMargin: 5
                    MouseArea{
                        anchors.fill: parent

                        onClicked: {
                            usersView.likeClicked(photoid)
                            usersView.clicked = index
                        }
                    }
                }
                Text { text: first_name ; anchors.horizontalCenter: parent.horizontalCenter; anchors.top: parent.top; anchors.topMargin: 10
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        Qt.openUrlExternally("http://vk.com/id"+id)
                    }
                }
                }
             }             
         }
    }
    model: usersModel

    ScrollIndicator.vertical: ScrollIndicator{

    }
}

