import QtQuick 2.9
import QtQuick.Controls 2.2

import QtQuick.Layouts 1.3
import QtQuick.Window 2.3
import QtQuick.Controls.Styles 1.4

import Qt.labs.platform 1.0

import QtQuick.Controls.Styles.Flat 1.0 as Flat

import QtWinExtras 1.0
import QtMultimedia 5.0
ApplicationWindow {
    id:mainWindow
    objectName: "mainWindow"
    visible: true
    width: 640
    height: 480
    color: "#272c32"
    title: qsTr("Карты рабочих режимов режимов")


    property string stWindow: ""
    onVisibilityChanged:
    {
        console.log("mainWindow.visibility = ",mainWindow.visibility,"  ; "+stWindow);
        if(stWindow === "43" && mainWindow.visibility === 2)
        {
            stWindow == "";
            mainWindow.showMaximized();
        }

    }

    SystemTrayIcon {
        id: sysTryIcon
        visible: true
        iconSource: "qrc:/logo.ico"

        menu: Menu {
            MenuItem {
                text: qsTr("Quit")
                onTriggered: Qt.quit()
            }
        }
    }

    DwmFeatures {
        id: dwmFeatures
        topGlassMargin: -1
        leftGlassMargin: -1
        rightGlassMargin: -1
        bottomGlassMargin: -1


    }

    TaskbarButton {
        id: taskbarButton
        overlay.iconSource: "qrc:/logo.ico"
        overlay.accessibleDescription: "qrc:/logo.ico"
        progress.visible: true
        progress.value: 0

    }



    ThumbnailToolBar {
        ThumbnailToolButton { iconSource: "qrc:/icons/closePNG.png"; tooltip: "Exit"; onClicked: Qt.quit() }
    }

    JumpList {
        id: jumpList
        recent.visible: true
        frequent.visible: true
        tasks.visible: true
    }



     flags: Qt.Window | Qt.FramelessWindowHint // Отключаем обрамление окна



    // Объявляем свойства, которые будут хранить позицию зажатия курсора мыши
    property int previousX
    property int previousY

    MouseArea {
        id: topArea
        z:1
        height: 5
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        // Устанавливаем форму курсора, чтобы было понятно, что это изменение размера
        cursorShape: Qt.SizeVerCursor

        onPressed: {
            // Запоминаем позицию по оси Y
            previousY = mouseY
        }

        // При изменении позиции делаем пересчёт позиции окна, и его высоты
        onMouseYChanged: {
            var dy = mouseY - previousY
            mainWindow.setY(mainWindow.y + dy)
            mainWindow.setHeight(mainWindow.height - dy)
        }
    }

    // Аналогичные расчёты для остальных трёх областей ресайза
    MouseArea {
        id: bottomArea
        z:1
        height: 5
        anchors {
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }
        cursorShape: Qt.SizeVerCursor

        onPressed: {
            previousY = mouseY
        }

        onMouseYChanged: {
            var dy = mouseY - previousY
            mainWindow.setHeight(mainWindow.height + dy)
        }
    }

    MouseArea {
        id: leftArea
        z:1
        width: 5
        anchors {
            top: topArea.bottom
            bottom: bottomArea.top
            left: parent.left
        }
        cursorShape: Qt.SizeHorCursor

        onPressed: {
            previousX = mouseX
        }

        onMouseXChanged: {
            var dx = mouseX - previousX
            mainWindow.setX(mainWindow.x + dx)
            mainWindow.setWidth(mainWindow.width - dx)
        }
    }

    MouseArea {
        id: rightArea
        z:1
        width: 5
        anchors {
            top: topArea.bottom
            bottom: bottomArea.top
            right: parent.right
        }
        cursorShape:  Qt.SizeHorCursor

        onPressed: {
            previousX = mouseX
        }

        onMouseXChanged: {
            var dx = mouseX - previousX
            mainWindow.setWidth(mainWindow.width + dx)
        }
    }




    //////////////////////////////////////////////////////////////////////
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

    /////////////////////////////////////////////

    MyMenu
    {
        id: windowTitle
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0

        tittleLabel: title

    }

    //////////////////////////////////////////////

    Item{
        id: topMenu
        height: 40;
        anchors.top: windowTitle.bottom
        anchors.topMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        ToolBar {
            id: toolBar
            anchors.fill: parent
            background: Rectangle {
                anchors.fill: parent
                color: colorBackground
            }



            ToolButton {
                id: controlPop
                text: qsTr("‹")
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 0
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
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
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
                z:20;
                visible: true
                width: Math.round(32 * Flat.FlatStyle.scaleFactor)
                height: Math.round(32 * Flat.FlatStyle.scaleFactor)

                //anchors.right: parent.right - 10;
                color: settingsButton.pressed ? "#48bfbb" : colorTittle
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 0

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

        }

    }

    StackView {
        id: stack
        anchors.top: topMenu.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.topMargin: 0
        initialItem: mainView


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
