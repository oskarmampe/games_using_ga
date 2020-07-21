import QtQuick 2.4
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 1280
    height: 960
    title: qsTr("Evolutionary Games")

    Frame {
        id: latticeframe
        x: 150
        y: 20
        width: 960
        height: 750

        Image {
            id: img
            x: 0
            y: 0
            width: 960
            height: 720
            source: lattice.image_path
            cache: false
            fillMode: Image.PreserveAspectFit

        }
    }

    Button {
        id: simulateButton
        x: 100
        y: 850
        width: 124
        height: 48
        text: qsTr("Simulate")
        onClicked: lattice.run_simulation()
    }

    Button {
        id: cancelButton
        x: 100
        y: 900
        width: 124
        height: 48
        text: qsTr("Cancel")
        onClicked: lattice.cancel()
    }

    TextField {
        id: tTF
        x: 504
        y: 850
        onTextChanged: lattice.set_t(text)
        text: lattice.get_t()
    }

    Label {
        id: tLabel
        x: 476
        y: 850
        text: qsTr("T:")
    }

    Label {
        id: dimensionLabel
        x: 256
        y: 850
        text: qsTr("Dimension:")
    }

    TextField {
        id: dimensionTF
        x: 332
        y: 850
        onTextChanged: lattice.set_dimension(text)
        text: lattice.get_dimension()
    }

    TextField {
        id: eTF
        x: 686
        y: 850
        onTextChanged: lattice.set_e(text)
        text: lattice.get_e()
    }

    Label {
        id: eLabel
        x: 658
        y: 850
        width: 7
        height: 17
        text: qsTr("e:")
    }

    TextField {
        id: bTF
        x: 879
        y: 850
        onTextChanged: lattice.set_b(text)
        text: lattice.get_b()
    }

    Label {
        id: bLabel
        x: 851
        y: 850
        width: 7
        height: 17
        text: qsTr("b:")
    }

    Button {
        id: changeButton
        x: 1029
        y: 875
        width: 80
        height: 48
        text: qsTr("Change")
        onClicked: lattice.change_lattice(xTF.text, yTF.text, cTF.text)
    }

    Button {
        id: showButton
        x: 1029
        y: 825
        width: 80
        height: 48
        text: qsTr("Show")
        onClicked: lattice.show_lattice()
    }

    TextField {
        id: cTF
        x: 1129
        y: 800
        text: qsTr("c")
    }

    Label {
        id: cLabel
        x: 1129
        y: 790
        width: 7
        height: 17
        text: qsTr("Strategy:")
    }

    TextField {
        id: xTF
        x: 1129
        y: 850
        text: qsTr("0")
    }

    Label {
        id: xLabel
        x: 1129
        y: 840
        width: 7
        height: 17
        text: qsTr("Row:")
    }

    TextField {
        id: yTF
        x: 1129
        y: 900
        text: qsTr("0")
    }

    Label {
        id: yLabel
        x: 1129
        y: 890
        width: 7
        height: 17
        text: qsTr("Column:")
    }


    Label {
        id: statusLabel
        x: 458
        y: 900
        width: 7
        height: 17
        clip:false
        text: lattice.text
    }

    Label {
        id: imageStatusLabel
        x: 240
        y: 925
        width: 7
        height: 17
        clip:false
        text: qsTr("Image saved to: ")+lattice.image_path
    }
}

