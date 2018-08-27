import QtQuick 2.11
import QtQuick.Controls 2.2

import QtQuick.Layouts 1.3

Page {
    id: page
    contentHeight: parent.height
    contentWidth:  parent.width
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

    CheckBox {
        id: checkBox
        text: qsTr("Отобразить Word")
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

//    ColumnLayout {
//        id: flow1
//        anchors.rightMargin: 10
//        anchors.leftMargin: 10
//        anchors.fill: parent

//        RowLayout{

//            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
//            Layout.preferredWidth: flow1.width

//            spacing: 10
//            Label {
//                id: label
//                text: qsTr("RShablon")
//                verticalAlignment: Text.AlignTop
//                horizontalAlignment: Text.AlignHCenter
//                color: "#ffffff"
//                Layout.preferredWidth: 100
//            }

//            TextField {
//                id: textField
//                text: qsTr("Text Field")
//                Layout.fillWidth: true
//            }

//            Button {
//                id: button
//                text: qsTr("Button")
//                Layout.fillWidth: true
//            }
//        }

//    }


}
