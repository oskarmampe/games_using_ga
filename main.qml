import QtQuick 2.4
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 1680
    height: 1050
    title: qsTr("Evolutionary Games")

    GridLayout {
        id: grid
        columns: 10
        anchors.fill: parent
        columnSpacing: 10

        Image {
            id: img
            width: 480
            height: 360
            Layout.row: 2
            Layout.column: 0
            Layout.rowSpan: 3
            Layout.columnSpan: 9
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: 4

            source: lattice.image_path
            cache: false
            fillMode: Image.PreserveAspectFit
            Layout.alignment: Qt.AlignCenter
        }

        Button {
            id: simulateButton
            width: 124
            height: 48
            text: qsTr("Simulate")
            onClicked: lattice.run_simulation()
            Layout.row: 6
            Layout.column: 0
            Layout.leftMargin: 4
        }

        Button {
            id: cancelButton
            width: 124
            height: 48
            text: qsTr("Cancel")
            onClicked: lattice.cancel()
        }

        TextField {
            id: tTF
            onTextChanged: lattice.set_t(text)
            text: lattice.get_t()
            Layout.row: 6
            Layout.column: 5
            width: 40
        }

        Label {
            id: tLabel
            text: qsTr("T:")
            Layout.row: 6
            Layout.column: 4
            Layout.alignment: Qt.AlignRight
            width: 40
        }

        Label {
            id: dimensionLabel
            text: qsTr("Dimension:")
            Layout.row: 6
            Layout.column: 2
            Layout.alignment: Qt.AlignRight
        }

        TextField {
            id: dimensionTF
            x: 332
            y: 850
            onEditingFinished: lattice.set_dimension(text)
            text: lattice.get_dimension()
            Layout.row: 6
            Layout.column: 3
        }

        TextField {
            id: eTF
            x: 686
            y: 850
            onTextChanged: lattice.set_e(text)
            text: lattice.get_e()
            Layout.row: 6
            Layout.column: 7
        }

        Label {
            id: eLabel
            x: 658
            y: 850
            width: 7
            height: 17
            text: qsTr("e:")
            Layout.row: 6
            Layout.column: 6
            Layout.alignment: Qt.AlignRight
        }

        TextField {
            id: bTF
            x: 879
            y: 850
            onTextChanged: lattice.set_b(text)
            text: lattice.get_b()
            Layout.row: 6
            Layout.column: 9
        }

        Label {
            id: bLabel
            x: 851
            y: 850
            width: 7
            height: 17
            text: qsTr("b:")
            Layout.alignment: Qt.AlignRight
            Layout.row: 6
            Layout.column: 8

        }

        Button {
            id: changeButton
            width: 124
            height: 48
            text: qsTr("Change Cell")
            onClicked: lattice.change_lattice(xTF.text, yTF.text, cTF.text)
            Layout.row: 7
            Layout.column: 1
            Layout.leftMargin: 4
        }

        Button {
            id: showButton
            width: 124
            height: 48
            text: qsTr("Show")
            onClicked: lattice.show_lattice()
            Layout.row: 7
            Layout.column: 0
            Layout.leftMargin: 4
        }

        TextField {
            id: cTF
            x: 1129
            y: 800
            text: qsTr("c")
            Layout.row: 7
            Layout.column: 3
        }

        Label {
            id: cLabel
            x: 1129
            y: 790
            width: 7
            height: 17
            text: qsTr("Strategy:")
            Layout.row: 7
            Layout.column: 2
            Layout.alignment: Qt.AlignRight
        }

        TextField {
            id: xTF
            x: 1129
            y: 850
            text: qsTr("0")
            Layout.row: 7
            Layout.column: 5
        }

        Label {
            id: xLabel
            x: 1129
            y: 840
            width: 7
            height: 17
            text: qsTr("Row:")
            Layout.row: 7
            Layout.column: 4
            Layout.alignment: Qt.AlignRight
        }

        TextField {
            id: yTF
            x: 1129
            y: 900
            text: qsTr("0")
            Layout.row: 7
            Layout.column: 7
        }

        Label {
            id: yLabel
            x: 1129
            y: 890
            width: 7
            height: 17
            text: qsTr("Column:")
            Layout.row: 7
            Layout.column: 6
            Layout.alignment: Qt.AlignRight
        }


        Label {
            id: statusLabel
            x: 458
            y: 900
            width: 7
            height: 17
            clip:false
            text: lattice.text
            Layout.row: 5
            Layout.column: 0
            Layout.columnSpan: 2
            Layout.leftMargin: 4
        }

        Label {
            id: imageStatusLabel
            x: 240
            y: 925
            width: 7
            height: 17
            clip:false
            text: qsTr("Image saved to: ")+lattice.image_path
            Layout.row: 5
            Layout.column: 2
            Layout.columnSpan: 6
        }


        Button {
            id: updateButton
            width: 124
            height: 48
            text: qsTr("Update Params")
            onClicked: lattice.change_ga(encodingCMB.currentText, childrenTF.text, parentTF.text, neighbourSwitch.checked, mutationSwitch.checked)
            Layout.row: 8
            Layout.column: 0
            Layout.leftMargin: 4
        }

        Label {
            id: encodingLabel
            x: 1129
            y: 840
            width: 7
            height: 17
            text: qsTr("Encoding:")
            Layout.row: 8
            Layout.column: 1
            Layout.alignment: Qt.AlignRight
        }

        ComboBox {
          id: encodingCMB
          model: [ "CELLSTATE", "AUTOMATA", "ATTRIBUTE" ]
          currentIndex: lattice.get_encoding()
          Layout.row: 8
          Layout.column: 2
          font.pointSize: 10
          editable: false
        }

        Label {
            id: childrenLabel
            x: 1129
            y: 840
            width: 7
            height: 17
            text: qsTr("Children:")
            Layout.row: 8
            Layout.column: 3
            Layout.alignment: Qt.AlignRight
        }

        TextField {
            id: childrenTF
            x: 1129
            y: 800
            text: lattice.get_children()
            Layout.row: 8
            Layout.column: 4
        }

        Label {
            id: parentsLabel
            x: 1129
            y: 840
            width: 7
            height: 17
            text: qsTr("Parents:")
            Layout.row: 8
            Layout.column: 5
            Layout.alignment: Qt.AlignRight
        }

        TextField {
            id: parentTF
            x: 1129
            y: 800
            text: lattice.get_parent()
            Layout.row: 8
            Layout.column: 6
        }


        Switch {
            id: neighbourSwitch
            x: 165
            y: 180
            text: qsTr("Global")
            Layout.row: 8
            Layout.column: 7
            checked: lattice.get_global_pop()
        }

        Switch {
            id: mutationSwitch
            x: 165
            y: 180
            text: qsTr("Mutation")
            Layout.row: 8
            Layout.column: 8
            checked: lattice.get_mutation()
        }

    }
}

