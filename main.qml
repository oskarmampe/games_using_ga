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
            fillMode: Image.PreserveAspectFit

        }
    }

    Button {
        id: button
        x: 100
        y: 850
        width: 124
        height: 48
        text: qsTr("Simulate")
        onClicked: lattice.run_simulation()
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

    Label {
        id: statusLabel
        x: 658
        y: 900
        width: 7
        height: 17
        clip:false
        text: lattice.text
    }
}

