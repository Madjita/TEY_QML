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

            onClicked: {

                if (Qt.platform.os == "windows") {

                    fileDialogWindows.open()

                } else {

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


                onEntered: {
                    selected = true;

                }

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


            onEndChanged: {


                console.log("wordQMLModel = " + wordQMLModel.rows * 100)


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


                    Utils.myColorAnimation(wordQMLModel.rows)
                    var strColor = "#";

                    if(Math.round(Utils.Rse) < 16)
                    {
                       strColor +=  "0" + Math.round(Utils.Rse).toString(16);
                    }
                    else
                    {
                      strColor +=  Math.round(Utils.Rse).toString(16);
                    }

                    if(Math.round(Utils.Gse) < 16)
                    {
                       strColor +=  "0" + Math.round(Utils.Gse).toString(16);
                    }
                    else
                    {
                       strColor +=  Math.round(Utils.Gse).toString(16);
                    }

                    if(Math.round(Utils.Bse) < 16)
                    {
                       strColor +=  "0" + Math.round(Utils.Bse).toString(16);
                    }
                    else
                    {
                       strColor +=  Math.round(Utils.Bse).toString(16);
                    }

                    pie.strokeColor = strColor;
                    console.log(pie.strokeColor);

                } else {
                    label.scale = 1.0
                    pie.begin = "0.0001"
                    pie.strokeColor = "#ff0000"
                    Utils.CountLoadingFileBar = 0

                    Utils.Rse = 0xff
                    Utils.Gse = 0x00
                    Utils.Bse = 0x00


                    if (label.text != "Загрузить перечень")
                    {
                        stack.push(mainViewPage2)
                        controlPop.visible = true
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
