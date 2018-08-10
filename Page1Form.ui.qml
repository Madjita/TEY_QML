import QtQuick 2.9
import QtQuick.Controls 2.2

import QtQuick.Studio.Components 1.0
import QtQuick.Studio.Effects 1.0

//import QtQuick.Timeline 1.0
import QtGraphicalEffects 1.0

Page {
    id: page
    width: 600
    height: 400
    smooth: false
    antialiasing: false
    anchors.fill: parent

    property string colorBackground: "#272c32"
    property string colorTittle: "#f6fbff"

    background: Rectangle {
        anchors.fill: parent
        color: colorBackground
    }

    header: Label {
        text: qsTr("Page 1")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
        color: colorTittle
    }

    Item {
        id: rectangle
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        height: page.height / 2
        width: page.height / 2

        Label {
            text: "Загрузить перечень"
            font.family: "Arial"
            font.bold: false
            font.pointSize: 14
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignHCenter
            color: "#f1f6fc"
        }

        PieItem {
            id: pieUnder
            antialiasing: true
            vendorExtensionsEnabled: true
            hideLine: true
            anchors.fill: parent
            strokeWidth: 6
            end: 360
            strokeColor: "#3f444a"
            smooth: true
        }

        PieItem {
            id: pie
            antialiasing: true
            vendorExtensionsEnabled: true
            hideLine: true
            anchors.fill: parent
            strokeWidth: 6
            end: 360
            strokeColor: "#e2b62f" //f3717d"
            smooth: true

            // @disable-check M221
            ParallelAnimation {
                id: aim
                ColorAnimation {
                    target: pie
                    property: "strokeColor"
                    from: "#e2b62f"
                    to: "#9fcd61"
                    duration: 3600
                }
                NumberAnimation {
                    target: pie
                    property: "end"
                    from: 0
                    to: 360
                    duration: 3600
                }

//                NumberAnimation {
//                    target: pie
//                    property: "begin"
//                    from: 360
//                    to: 0
//                    duration: 3600
//                }

                running: true

                loops: 300
            }

            //            // @disable-check M224
            //            NumberAnimation on end{
            //                id: anim1
            //                from: 0
            //                to: 90
            //                duration: 3600

            //                // @disable-check M223
            //                onStopped: {

            //                    // @disable-check M223
            //                    if(anim1.running == true){
            //                    // @disable-check M222
            //                    console.log("anim1")
            //                    pie.strokeColor = "#ff6d89"
            //                    // @disable-check M222
            //                    anim2.start()
            //                    }
            //                }
            //            }

            //            // @disable-check M224
            //            NumberAnimation on end {
            //                id: anim2
            //                from: 90
            //                to: 300
            //                duration: 3600

            //                // @disable-check M223
            //                onRunningChanged: {
            //                    console.log("st2 = " + anim1.running.toString())
            //                }

            //                // @disable-check M223
            //                onStopped: {

            //                    // @disable-check M223
            //                    if(anim1.running == false && anim2.running == false && anim3.running == false){
            //                    // @disable-check M222
            //                    console.log("anim2")
            //                    pie.strokeColor = "#f9b33a"
            //                    // @disable-check M222
            //                    anim3.start()
            //                    }
            //                }
            //            }

            //            // @disable-check M224
            //            NumberAnimation on end {
            //                id: anim3
            //                from: 300
            //                to: 360
            //                duration: 3600

            //                // @disable-check M223
            //                onStopped: {
            //                    // @disable-check M223
            //                    if(anim3.running == false){
            //                    // @disable-check M222
            //                    console.log("anim3")
            //                    pie.strokeColor = "#9fcd61"
            //                    }
            //                }
            //            }
        }

        //        ArcItem {
        //            id: arc
        //            x: 8
        //            y: 0
        //            width: 200
        //            height: 200
        //            strokeColor: "#e87e88"
        //            anchors.horizontalCenter: parent.horizontalCenter
        //            anchors.verticalCenter: parent.verticalCenter
        //            joinStyle: 128
        //            asynchronous: true
        //            strokeWidth: 2
        //            alpha: page.height * 100
        //            end: 1000
        //            begin: -79.9

        //        }

        //        Timeline {
        //            id: timeline
        //            animations: [
        //                TimelineAnimation {
        //                    id: timelineAnimation
        //                    property: "currentFrame"
        //                    to: 1000
        //                    from: 0
        //                    running: true
        //                    loops: 1
        //                    duration: 1000
        //                }
        //            ]
        //            enabled: true
        //            endFrame: 1000
        //            startFrame: 0

        //            KeyframeGroup {
        //                target: arc
        //                property: "begin"

        //                Keyframe {
        //                    value: -40.9
        //                    frame: 100
        //                }

        //                Keyframe {
        //                    value: -0.9
        //                    frame: 200
        //                }

        //                Keyframe {
        //                    value: 40.9
        //                    frame: 300
        //                }

        //                Keyframe {
        //                    value: 90.9
        //                    frame: 400
        //                }

        //                Keyframe {
        //                    value: 30.9
        //                    frame: 500
        //                }
        //            }
        //        }
    }

    //    Label {
    //        // @disable-check M222
    //        text: qsTr(stack.depth.toString())
    //        anchors.centerIn: parent
    //        color: colorTittle
    //    }

    //    Image {
    //        id: img
    //        property bool rounded: true
    //        property bool adapt: true
    //        x: 12
    //        y: 6
    //        width: 50
    //        height: 50
    //        fillMode: Image.PreserveAspectCrop
    //        source: "Best.jpg"

    //        layer.enabled: rounded
    //        layer.effect: OpacityMask {
    //            maskSource: Item {
    //                width: img.width
    //                height: img.height
    //                Rectangle {
    //                    anchors.centerIn: parent
    //                    width: img.adapt ? img.width : Math.min(img.width,
    //                                                            img.height)
    //                    height: img.adapt ? img.height : width
    //                    radius: Math.min(width, height)
    //                }
    //            }
    //        }
    //    }
}
