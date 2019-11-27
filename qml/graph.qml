import QtQuick 2.7
import QtQuick.Controls 2.0
import QtCharts 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0

Item {
    width: 100
    height: 100
    id: graphView

    signal selected(string from, string to)

    function setUids(anArray){
//        for (var i=0; i<anArray.length; i++)
//                  console.log("Array item:", anArray[i])
        // PROFILING
        console.time("firstPart");

        chart.graphCount = anArray.length

        series1.clear()
        for (var i = 0; i < anArray.length; i++) {
            series1.append(i,  parseInt(anArray[i]) );
            //series2.append(i, Math.random()*10);
        }

        console.timeEnd("firstPart");
    }

    function update(){
        //dataSource.update(chart.series(0));
        dataSource.update(series1);

    }


    ChartView {

        title: "old of uids"
        anchors.fill: parent
        legend.visible: false
        antialiasing: true
        id: chart
        property int graphCount: 100
        property int viewCount: 10

        property bool openGL: true
        property bool openGLSupported: true

        onHeightChanged: {
            line.width=0
        }

        ValueAxis {
            id: axisX
            min: 0
            max: chart.viewCount
            tickCount: chart.viewCount/8
        }

        CategoryAxis {
            id: axisY
            min: 0
            max: 400000000
            CategoryRange {
                label: "0"
                endValue: 10000
            }
            CategoryRange {
                label: "0"
                endValue: 100000
            }
            CategoryRange {
                label: "2010"
                endValue: 100000000
            }
            CategoryRange {
                label: "2012"
                endValue: 180000000
            }
            CategoryRange {
                label: "2014"
                endValue: 300000000
            }
            CategoryRange {
                label: "2015"
                endValue: 400000000
            }
        }

        LineSeries {
            id: series1
            axisX: axisX
            axisY: axisY
            useOpenGL: true

            onCountChanged: {
                console.log("series")

            }
        }

//        onSeriesAdded: {
//            console.log("val",series1.at(100))
//            series1.axisX.max = 50//count
//        }


//        ScatterSeries {
//            id: series2
//            axisX: axisX
//            axisY: axisY
//            visible: false
//        }

        Rectangle{
            id: line
            x:chart.plotArea.x
            y:chart.plotArea.y
            width: 0
            height: chart.plotArea.height
            color: Qt.rgba(180,180,0,0.38)
        }

        MouseArea{
            id: mouses
            anchors.fill: parent
            hoverEnabled: true
            property bool mouseClick: false
            property bool selected: false

            function getSelectedItems(start,end) {
                var result=[]
                console.log(start,end)
                for(var i=start; i<end; i++){
                    result.push(series1.at(i))
                }
                return result
            }

            onSelectedChanged: {
                if (selected){
                    //count of items for 1 pixel on screen
                    var ipp = (series1.count/chart.plotArea.width)
                    // start point
                    var sp = line.x-chart.plotArea.x
                    // items offset to start point
                    var start = Math.round(sp*ipp)
                    // count of selected items
                    var seli = Math.round(line.width*ipp)
                    var end = start+seli;
                    console.log(getSelectedItems(start,end))
                    graphView.selected(start,end)
                }
            }

            onPositionChanged: {
                if( mouses.mouseClick){
                    if(mouses.mouseX>chart.plotArea.x){
                        if(mouses.mouseX<(chart.plotArea.x+chart.plotArea.width)){

                            if(mouses.mouseX<=(chart.plotArea.x+chart.plotArea.width)){
                                line.width = mouses.mouseX-line.x
                            }else{
                                line.width = chart.plotArea.width-line.x
                            }
                        }
                    }
                }
            }
            onPressed: {
                if(mouses.mouseX>chart.plotArea.x){
                    if(mouses.mouseX<(chart.plotArea.x+chart.plotArea.width)){
                line.width = 0
                selected = false
                line.x = mouses.mouseX
                mouseClick = true
                }
                }
            }
            onReleased: {
                if(mouseClick){
                    selected = true
                    mouseClick = false
                }
                }


        }
    }

    // Add data dynamically to the series
    Component.onCompleted: {

    }
}
