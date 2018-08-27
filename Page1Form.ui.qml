import QtQuick 2.11
import QtQuick.Controls 2.2

import QtQuick.Studio.Components 1.0
import QtQuick.Studio.Effects 1.0

import QtGraphicalEffects 1.0

import "utils.js" as Utils

Page {
    id: page
    objectName: "pageFirst"
    contentHeight: parent.height
    contentWidth: parent.width
    smooth: false
    antialiasing: false

    property string colorBackground: "#272c32"
    property string colorTittle: "#f6fbff"
    property bool selected: false

    property ParallelAnimation aim: aim

    property PieItem pieBar: pie
    property MouseArea startWork: mouseAreaStart

    background: Rectangle {
        anchors.fill: parent
        color: colorBackground
    }

    header: Label {
        text: qsTr("")
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

        MouseArea {
            anchors.fill: parent
            id: mouseAreaStart
            // @disable-check M223
            onClicked: {
                // @disable-check M223
                if (Qt.platform.os == "windows") {
                    // @disable-check M222
                    fileDialogWindows.open()
                    // @disable-check M223
                } else {
                    // @disable-check M222
                    stack.push(filePicker)
                }
            }
        }

        Label {
            id: label
            text: "Загрузить перечень"
            font.family: "Arial"
            font.bold: false
            font.pointSize: 14
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignHCenter
            color: "#f1f6fc"
            //            color: selected ? "#f1f6fc" : "#ebebdd"
            //            scale: selected ? 1.15 : 1.0

            /*
            MouseArea {
                anchors.fill: parent

                hoverEnabled: true;

                // @disable-check M223
                onEntered: {
                    selected = true;

                }
            // @disable-check M223
                onExited: {
                    selected = false;
                }
            }
            */
        }

        PieItem {
            id: pieUnder
            objectName: "pieUnderBar"
            asynchronous: true
            antialiasing: true
            vendorExtensionsEnabled: true
            hideLine: true
            anchors.fill: parent
            strokeWidth: 6
            begin: 0.0001
            end: 360
            strokeColor: "#3f444a"
            smooth: true

            layer.enabled: true
            layer.smooth: true
            layer.samples: 8
        }

        PieItem {
            id: pie
            objectName: "pieBar"
            antialiasing: true
            asynchronous: true
            vendorExtensionsEnabled: true
            hideLine: true
            anchors.fill: parent
            strokeWidth: 6
            begin: 0.0001
            end: wordQMLModel.countBar
            strokeColor: "#b0b3b6" //f3717d"
            smooth: true

            layer.enabled: true
            layer.smooth: true
            layer.samples: 8

            // @disable-check M223
            onEndChanged: {

                // @disable-check M222
                console.log("wordQMLModel = " + wordQMLModel.rows * 100)

                // @disable-check M223
                if (wordQMLModel.countBar !== 0) {
                    Utils.CountLoadingFileBar += 100 / wordQMLModel.rows
                    label.text = Math.round(Utils.CountLoadingFileBar) + " %"
                    label.scale = 1.15

                    //                    Utils.stepR = (Utils.Re - Utils.Rs) / wordQMLModel.rows
                    //                    Utils.stepG = (Utils.Ge - Utils.Gs) / wordQMLModel.rows
                    //                    Utils.stepB = (Utils.Be - Utils.Bs) / wordQMLModel.rows

                    //                    Utils.Rse += Utils.stepR
                    //                    Utils.Gse += Utils.stepG
                    //                    Utils.Bse += Utils.stepB

                    // @disable-check M222
                    Utils.myColorAnimation(wordQMLModel.rows)

                    // @disable-check M222
                    console.log(pie.strokeColor)

                    // @disable-check M222
                    pie.strokeColor = "#" + Math.round(Utils.Rse).toString(
                                // @disable-check M222
                                16) + Math.round(Utils.Gse).toString(
                                // @disable-check M222
                                16) + Math.round(Utils.Bse).toString(16)

                    // @disable-check M223
                } else {
                    label.scale = 1.0
                    pie.begin = "0.0001"
                    pie.strokeColor = "#3f444a"
                    Utils.CountLoadingFileBar = 0

                    Utils.Rse = 0xe2
                    Utils.Gse = 0xb6
                    Utils.Bse = 0x2f

                    // @disable-check M222
                    if (label.text != "Загрузить перечень") // @disable-check M223
                        // @disable-check M223
                    {

                        // @disable-check M222
                        stack.push(mainViewPage2)

                        controlPop.visible = true

                        // @disable-check M222
                    }

                    label.text = "Загрузить перечень"
                }
            }

            //            // @disable-check M221
            //            ParallelAnimation {
            //                id: aim
            //                objectName: "aimBar"

            //                // @disable-check M221
            //                SequentialAnimation {
            //                    ColorAnimation {
            //                        target: pie
            //                        property: "strokeColor"
            //                        from: "#e2b62f"
            //                        to: "#9fcd61"
            //                        duration: 3600
            //                    }
            //                    ColorAnimation {
            //                        target: pie
            //                        property: "strokeColor"
            //                        from: "#9fcd61"
            //                        to: colorBackground
            //                        duration: 3600 / 4 + 100
            //                    }
            //                }

            //                // @disable-check M221
            //                SequentialAnimation {
            //                    NumberAnimation {
            //                        target: pie
            //                        property: "end"
            //                        from: 0
            //                        to: 360
            //                        duration: 3600
            //                    }
            //                    NumberAnimation {
            //                        target: pie
            //                        property: "begin"
            //                        from: 0
            //                        to: 360
            //                        duration: 3600 / 4
            //                    }
            //                    NumberAnimation {
            //                        target: pie
            //                        property: "begin"
            //                        from: 0
            //                        to: 0
            //                        duration: 1
            //                    }
            //                }
            //                loops: Animation.Infinite
            //            }
        }
    }
}
