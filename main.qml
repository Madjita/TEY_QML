import QtQuick 2.9
import QtQuick.Controls 2.2

import QtQuick.Layouts 1.3
import QtQuick.Window 2.3
import QtQuick.Controls.Styles 1.4

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


                onClicked: stack.pop()

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

                onClicked: menu.open()

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

//        Column {
//            spacing: 10

            Page1Form {
                colorBackground: colorBackground
                colorTittle:  colorTittle
                anchors.fill: parent

            }

//            Button {
//                text: "Push"
//                onClicked: stack.push(mainView)
//            }
//            Button {
//                text: "Pop"
//                enabled: stack.depth > 1
//                onClicked: stack.pop()

//            }
//            Text {
//                text: stack.depth
//            }
 //       }
    }


//    SwipeView {
//        id: swipeView
//        anchors.fill: parent
//        currentIndex: tabBar.currentIndex

//        Page1Form {
//        }

//        Page2Form {
//        }
//    }
}
