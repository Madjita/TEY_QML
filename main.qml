import QtQuick 2.9
import QtQuick.Controls 2.2

import QtQuick.Layouts 1.3
import QtQuick.Window 2.3
import QtQuick.Controls.Styles 1.4

import Qt.labs.platform 1.0

ApplicationWindow {
    id:main
    visible: true
    width: 640
    height: 480
    title: qsTr("Tabs")




    property int dpi: Screen.pixelDensity * 25.4
    property string colorBackground: "#272c32"
    property string colorTittle: "#f6fbff"

    function dp(x){
        if(dpi < 120) {
            return x; // Для обычного монитора компьютера
        } else {
            return x*(dpi/160);
        }
    }



    header: ToolBar {
        background: Rectangle {
            anchors.fill: parent
            color: colorBackground
        }



        RowLayout {
            anchors.fill: parent

            ToolButton {
                id: controlPop
                text: qsTr("‹")
                font.pointSize: 20


                onClicked: {
                    stack.pop()
                }

                contentItem: Text {
                    text: controlPop.text
                    font: controlPop.font
                    opacity: enabled ? 1.0 : 0.3
                    color: controlPop.down ? "#48bfbb" : colorTittle
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    implicitWidth: 40
                    implicitHeight: 40
                    color: Qt.darker("#33333333", controlPop.enabled
                                     && (controlPop.checked
                                         || controlPop.highlighted) ? 1.5 : 1.0)
                    opacity: enabled ? 1 : 0.3
                    visible: controlPop.down || (controlPop.enabled
                                                 && (controlPop.checked
                                                     || controlPop.highlighted))
                }
            }
            Label {
                text: "Create TEY cards"
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
                color: colorTittle
                font.pointSize: 15
            }

            ToolButton {
                id: controlSeitting
                width: 320
                text: qsTr("⋮")
                font.pointSize: 20

                onClicked:
                {
                    //menu.open();
                    filePicker.visible = false;
                }
                contentItem: Text {
                    text: controlSeitting.text
                    font: controlSeitting.font
                    opacity: enabled ? 1.0 : 0.3
                    color: controlSeitting.down ? "#48bfbb" : colorTittle
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                    implicitWidth: 40
                    implicitHeight: 40
                    color: Qt.darker("#33333333", controlSeitting.enabled
                                     && (controlSeitting.checked
                                         || controlSeitting.highlighted) ? 1.5 : 1.0)
                    opacity: enabled ? 1 : 0.3
                    visible: controlSeitting.down || (controlSeitting.enabled
                                                      && (controlSeitting.checked
                                                          || controlSeitting.highlighted))
                }

            }
        }

    }



    StackView {
        id: stack
        initialItem: mainView
        anchors.fill: parent

        states: State {
            name: "stack"
            PropertyChanges { target: rect; x: 150 }
        }

        pushEnter: Transition {

            PropertyAnimation { properties: "x,y"; easing.type: Easing.InOutQuad }

        }
        pushExit: Transition {
            PropertyAnimation {
                //property: "opacity"
                from: 1
                to:0
                duration: 200
            }
        }
        popEnter: Transition {
            PropertyAnimation {
                //property: "opacity"
                from: 0
                to:1
                duration: 200
            }
        }
        popExit: Transition {
            PropertyAnimation {
                // property: "opacity"
                from: 1
                to:0
                duration: 200
            }
        }
    }

    Component {
        id: mainView
        Page1Form {
            id: page1
            colorBackground: colorBackground
            colorTittle:  colorTittle
            anchors.fill: parent

        }
    }

    Component {
        id: filePicker
        FilePicker {
            anchors.fill: parent
            showDotAndDotDot: true
            nameFilters: "*.docx"

            onFileSelected: {
                stack.get(0).aim.start();
                console.log(currentFolder()+ "/" + fileName);
                controlPop.clicked();
            }


        }
    }

    FileDialog {
        id: fileDialogWindows
        folder:StandardPaths.writableLocation(StandardPaths.DocumentsLocation)

        onAccepted: {

           // stack.get(0).aim.start();

            stack.get(0).pieBar.begin = "0";

            word.qml_getFileName(fileDialogWindows.file);

            word.qml_StartFind();

            controlPop.clicked();
        }
    }
}
