import QtQuick 2.11
import QtQuick.Controls 2.2

import QtQuick.Studio.Components 1.0
import QtQuick.Studio.Effects 1.0

import QtGraphicalEffects 1.0

import "utils.js" as Utils

Page {
    id: page
    width: 600
    height: 400
    smooth: false
    antialiasing: false
    anchors.fill: parent

    property string colorBackground: "#272c32"
    property string colorTittle: "#f6fbff"
    property bool selected: false

    property ListModel myModel: myModel

    // property PieItem pieBar: pie
    background: Rectangle {
        anchors.fill: parent
        color: colorBackground
    }

    ListView {
        anchors.fill: parent
        model: myModel
        delegate: contactDelegate

        // @disable-check M221
        Component {
            id: contactDelegate
            Rectangle {
                id: wrapper
                height: contactInfo.height
                color: ListView.isCurrentItem ? "black" : "red"
                Text {
                    id: contactInfo
                    text: name + " : "
                    font.pointSize: 20
                    color: wrapper.ListView.isCurrentItem ? "red" : "green"
                }
            }
        }
        focus: true
    }

    ListModel {
        id: myModel
        ListElement {
            name: "R"
            //count: wordQMLModel.dataFind[0]
        }
        ListElement {
            name: "C Z"
            //count: wordQMLModel.dataFind[1]
        }
        ListElement {
            name: "XP XS XW X"
            //count: wordQMLModel.dataFind[2]
        }
    }
}
