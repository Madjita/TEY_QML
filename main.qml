import QtQuick 2.9
import QtQuick.Controls 2.2

import QtQuick.Layouts 1.3
import QtQuick.Window 2.3
import QtQuick.Controls.Styles 1.4

import Qt.labs.platform 1.0

import QtQuick.Controls.Styles.Flat 1.0 as Flat

ApplicationWindow {
    id:main
    visible: true
    width: 640
    height: 480
    color: "#272c32"
    title: qsTr("Карты рабочих режимов")





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
                visible: false;


                onClicked: {

                    if(stack.get(1).objectName ==="pageSecond")
                    {

                        stack.get(1).startButton.visible = true;
                        stack.get(1).endButton.visible = false;
                    }

                    stack.pop();
                    console.log("stack.depth = ",stack.depth);
                    if(stack.depth == 1)
                    {
                        controlPop.visible = false;
                        controlSeitting.visible = true;
                    }




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
                text: "Карты рабочих режимов"
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
                color: colorTittle
                font.pointSize: 15
            }


            SettingsIcon {
                id:controlSeitting
                visible: true
                width: Math.round(32 * Flat.FlatStyle.scaleFactor)
                height: Math.round(32 * Flat.FlatStyle.scaleFactor)
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right - 10;
                anchors.rightMargin: textMargins - Math.round(8 * Flat.FlatStyle.scaleFactor)
                color: settingsButton.pressed ? "#48bfbb" : colorTittle

                MouseArea {
                    id: settingsButton
                    anchors.fill: parent
                    onClicked:
                    {
                        //menu.open();
                        //filePicker.visible = false;

                        console.log("stack.depth = ",stack.depth);
                        stack.push(mainViewPageSeittings);
                        if(stack.depth == 2)
                        {
                            controlSeitting.visible = false;
                            controlPop.visible = true;
                        }

                    }
                }
            }


            /*
            ToolButton {
                id: controlSeitting
                width: 320
                text: qsTr("⋮")
                visible: true
                font.pointSize: 20

                onClicked:
                {
                    //menu.open();
                    //filePicker.visible = false;

                    console.log("stack.depth = ",stack.depth);
                    stack.push(mainViewPageSeittings);
                    if(stack.depth == 2)
                    {
                      controlSeitting.visible = false;
                      controlPop.visible = true;
                    }

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
            */
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

        focus: true

        Keys.onReturnPressed:  {

            if(stack.get(0).objectName ==="pageFirst" && stack.depth <= 1)
            {

                stack.get(0).startWork.clicked(this);
            }

            if(stack.get(1).objectName ==="pageSecond" && stack.get(1).startButton.visible === true)
            {

                stack.get(1).startButton.clicked(this);
            }

            if(stack.get(1).objectName ==="pageSecond" && stack.get(1).endButton.visible === true)
            {

                stack.get(1).endButton.clicked(this);
            }



            console.log("enter",stack.get(1).objectName);
        }


        pushEnter: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 0
                to:1
                duration: 200
            }
        }
        pushExit: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 1
                to:0
                duration: 200
            }
        }
        popEnter: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 0
                to:1
                duration: 200
            }
        }
        popExit: Transition {
            PropertyAnimation {
                property: "opacity"
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
        }
    }

    Component {
        id: mainViewPage2
        Page2Form {
            id: page2
            colorBackground: colorBackground
            colorTittle:  colorTittle

        }
    }

    Component {
        id: mainViewPageSeittings
        PageSeittings {
            id: page3
            colorBackground: colorBackground
            colorTittle:  colorTittle

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

            controlSeitting.visible = false;
            controlPop.visible = false;

        }
    }





}
