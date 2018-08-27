import QtQuick 2.11
import QtQuick.Controls 2.2

import QtQuick.Studio.Components 1.0
import QtQuick.Studio.Effects 1.0

import QtGraphicalEffects 1.0

import "utils.js" as Utils

Page {
    id: page
    contentHeight: parent.height
    contentWidth:  parent.width
    smooth: false
    antialiasing: false


    property string colorBackground: "#272c32"
    property string colorTittle: "#f6fbff"
    property bool selected: false

    property ListModel myModel: myModel

    // property PieItem pieBar: pie
    background: Rectangle {
        color: "#272c32"
        anchors.fill: parent
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

                    // @disable-check M223
                    onTextChanged: {

                        if(model.modelData.myPercent === "100.00")
                            // @disable-check M223
                        {
                            // @disable-check M222
                            console.log("MY 360 GR");
                            Utils.Rse =Utils.Rs;
                            Utils.Gse =Utils.Gs;
                            Utils.Bse = Utils.Bs;
                        }
                    }
                }
                //                Text {
                //                    text: model.modelData.myCount
                //                    horizontalAlignment: Text.AlignHCenter
                //                    anchors.right: parent.right
                //                    anchors.rightMargin: 15
                //                    anchors.left: parent.left
                //                    anchors.leftMargin: 15

                //                    anchors.horizontalCenter: parent.horizontalCenter
                //                    anchors.verticalCenter:  parent.verticalCenter

                //                    color: colorTittle
                //                }
                Text {
                    text: model.modelData.myName + ": "+model.modelData.myCount
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

                // @disable-check M223
                onEndChanged: {

                    // @disable-check M223
                    if (model.modelData.myPercentBar !== 360) {



                        // @disable-check M222
                        Utils.myColorAnimation(model.modelData.myCountMax)

                        // @disable-check M222
                        console.log(this.strokeColor)

                        // @disable-check M222
                        this.strokeColor = "#" + Math.round(Utils.Rse).toString(
                                    // @disable-check M222
                                    16) + Math.round(Utils.Gse).toString(
                                    // @disable-check M222
                                    16) + Math.round(Utils.Bse).toString(16)
                    }

                }



                // @disable-check M223
                Component.onCompleted: {
                    Utils.Rse =Utils.Rs;
                    Utils.Gse =Utils.Gs;
                    Utils.Bse = Utils.Bs;

                }
            }
        }

        focus: true
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


        // @disable-check M223
        onClicked: {
            // @disable-check M222
            word.qml_CreateShablon();
            button.visible = false;
        }
    }

}
