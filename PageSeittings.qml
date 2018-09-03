import QtQuick 2.11
import QtQuick.Controls 2.2

import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

import Qt.labs.platform 1.0

Page {
    id: page
    contentHeight: parent.implicitHeight
    contentWidth:  parent.implicitWidth
    smooth: false
    antialiasing: false

    property string colorBackground: "#272c32"
    property string colorTittle: "#f6fbff"
    property bool selected: false

    property ParallelAnimation aim: aim

    property ListView listSeitings: listSeitings

    background: Rectangle {
        // anchors.fill: parent
        color: colorBackground
    }

    header: Label {
        text: qsTr("Настройки")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
        color: colorTittle
    }

    //    ListView
    //    {
    //        id: listSeitings
    //        anchors.fill: parent

    //    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 5

        CheckBox {
            id: checkBox
            text: qsTr("Отобразить Word")
            Layout.fillWidth: false
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            checkState: word.getViewFlag()
            contentItem: Text {
                text: checkBox.text
                font: checkBox.font
                color: colorTittle
                verticalAlignment: Text.AlignVCenter
                leftPadding: checkBox.indicator.width + checkBox.spacing
            }

            onCheckedChanged: {
                word.setViewFlag(checkBox.checkState);
            }


        }

        RowLayout {
            transformOrigin: Item.Center
            Layout.fillWidth: false
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop

            Label {
                id: label
                color: "#ffffff"
                text: qsTr("Температура кружающей среды")
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                Layout.fillWidth: false
                Layout.preferredHeight: 37
                Layout.preferredWidth: 106
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }

            TextField {
                id: textField_Temprature
                text: qsTr(word.getTemp())
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                Layout.fillWidth: false
                Layout.preferredHeight: 27
                Layout.preferredWidth: 58
                selectByMouse: true



                onTextChanged: {
                    word.setTemp(textField_Temprature.text);
                    console.log("Temprature = " + textField_Temprature.text);
                }


                MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.IBeamCursor
                        acceptedButtons: Qt.NoButton

                        onDoubleClicked: {
                            textField_Temprature.selectAll();
                        }
                    }
            }
        }

        ListView {
            id: listView
            x: 0
            y: 0
            width: 110
            height: 160
            clip: true
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: word.qml_getlistMYWORD()
            delegate: Item {
                id: item1
                x: 5
                height: 60
                Row {
                    id: row1
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 0

                    Text {
                        width: 100
                        text: model.modelData.split('/')[model.modelData.split('/').length-1].split('.')[0] +":"
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        font.bold: true
                        color: "#ffffff"
                    }


                    Text {
                        width: page.contentWidth/3 + (page.contentWidth/3-100)
                        text: model.modelData
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        font.bold: true
                        anchors.verticalCenter: parent.verticalCenter
                        color: "#ffffff"
                    }

                    Button{
                        height: 30
                        width: page.contentWidth/3 -50
                        text: qsTr("Задать")
                        font.bold: true
                        anchors.verticalCenter: parent.verticalCenter


                        onClicked: {
                            fileDialogChangeShablon.open();

                        }

                        FileDialog {
                            id: fileDialogChangeShablon
                            folder:StandardPaths.writableLocation(StandardPaths.DocumentsLocation)

                            onAccepted: {

                                        listView.model = word.qml_setChangeListMYWORD(index.toString(),fileDialogChangeShablon.file);

                            }
                        }

                    }

                    spacing: 10
                }
            }
        }
    }



}

/*##^## Designer {
    D{i:8;anchors_x:0;anchors_y:0}
}
 ##^##*/
