import QtQuick 2.11
import QtQuick.Controls 2.2

import QtQuick.Studio.Components 1.0
import QtQuick.Studio.Effects 1.0

import QtGraphicalEffects 1.0

import "utils.js" as Utils

Page {
    id: page
    objectName: "pageSecond"
    contentHeight: parent.implicitHeight
    contentWidth:  parent.implicitWidth
    smooth: false
    antialiasing: false

    property string colorBackground: "#272c32"
    property string colorTittle: "#f6fbff"
    property bool selected: false

    property ListModel myModel: myModel

    property Button startButton: button
    property Button endButton: buttonCompleted

    // property PieItem pieBar: pie
    background: Rectangle {
        color: "#272c32"
        anchors.fill: parent
    }

    Component.onCompleted:
    {
        controlPop.visible = true;
    }

    GridView {
        id: myGrid
        cellHeight: main.height / 4
        cellWidth: main.height / 4
        contentHeight: main.height / 4
        contentWidth: main.height / 4
        anchors.fill: parent
        model: wordQMLModel.dataList
        anchors.rightMargin: 0
        anchors.leftMargin: 10
        anchors.bottomMargin: 10
        anchors.topMargin: 10

        delegate: Item {
            id: layoutRow

            PieItem {
                id: pieUnder
                height: myGrid.cellHeight - 10
                width: myGrid.cellHeight - 10
                asynchronous: true
                antialiasing: true
                vendorExtensionsEnabled: true
                hideLine: true
                strokeWidth: 6
                begin: 0.0001
                end: 360
                strokeColor: "#3f444a"
                smooth: true

                layer.enabled: true
                layer.smooth: true
                layer.samples: 8

                Text {
                    text: model.modelData.myPercent + " %"
                    font.pointSize: myGrid.cellHeight / 10
                    horizontalAlignment: Text.AlignHCenter
                    color: "#fbffff"

                    //anchors.verticalCenterOffset: height
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter


                    onTextChanged: {

                        if (model.modelData.myPercent === "100.00")
                        {

                            console.log("MY 360 GR")
                            Utils.Rse = Utils.Rs
                            Utils.Gse = Utils.Gs
                            Utils.Bse = Utils.Bs


                            console.log("index = ", index)

                            console.log("wordQMLModel.dataList.length-1 = ",
                                        wordQMLModel.dataList.length - 1)

                            if (index === wordQMLModel.dataList.length - 1)
                            {
                                controlPop.visible = true
                                buttonCompleted.visible = true
                            }
                        }
                    }
                }

                Text {
                    text: model.modelData.myName + ": " + model.modelData.myCount
                    font.pointSize: myGrid.cellHeight / 15
                    horizontalAlignment: Text.AlignHCenter
                    color: "#b8bdc3"

                    //anchors.verticalCenterOffset: height * (-2)
                    anchors.verticalCenterOffset: height * 2

                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            PieItem {
                objectName: model.modelData.myName
                height: myGrid.cellHeight - 10
                width: myGrid.cellHeight - 10
                asynchronous: true
                antialiasing: true
                vendorExtensionsEnabled: true
                hideLine: true
                strokeWidth: 6
                begin: 0.0001
                end: model.modelData.myPercentBar
                strokeColor: "#f3717d" //f3717d"
                smooth: true

                layer.enabled: true
                layer.smooth: true
                layer.samples: 8


                onEndChanged: {


                    if (model.modelData.myPercentBar !== 360) {


                        Utils.myColorAnimation(model.modelData.myCountMax)


                        console.log(this.strokeColor)

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

                        this.strokeColor = strColor;

                    }
                }


                Component.onCompleted: {
                    Utils.Rse = Utils.Rs
                    Utils.Gse = Utils.Gs
                    Utils.Bse = Utils.Bs
                }
            }
        }
    }

    Button {
        id: button
        text: qsTr("Создать карты")
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0


        onClicked: {

            word.qml_CreateShablon()
            button.visible = false
            controlPop.visible = false
        }
    }
    Button {
        id: buttonCompleted
        text: qsTr("‹ Карты созданны.")
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        visible: false


        onClicked: {

            controlPop.clicked()
        }
    }

}
