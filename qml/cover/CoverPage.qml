/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

import QtQuick 2.0
import Sailfish.Silica 1.0
import "../pages/components"
import "../pages/scripts/HelperVariables.js" as HV

CoverBackground {

    property bool active: status === Cover.Active

    Image {
        id: icon
        horizontalAlignment: Image.AlignHCenter
        source: "qrc:/images/images/harbour-unitconverter.png"
        smooth: true
        anchors {
            top: parent.top
            topMargin: Theme.paddingLarge
            horizontalCenter: parent.horizontalCenter
        }
        scale: Screen.width > 540 ? 1.7 : 1
    }

    Label {
        id: label
        anchors {
            left: parent.left
            bottom: parent.bottom
        }

        text: "UnitConverter"
        color: Theme.secondaryHighlightColor
        font.pixelSize: Theme.fontSizeLarge * 1.55

        transform: Rotation {
            angle: -60
        }
    }

    Resultpanel {
        id: resultpanel
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: Theme.paddingLarge
        visible: false
        scale: 0.5
        // z: 2
        unittype_text: ""
        unit1_text: ""
        unit2_text: ""
        unit3_text: ""
        unit4_text: ""
        unit1_value: ""
        unit2_value: ""
        unit3_value: ""
        unit4_value: ""
    }

    onActiveChanged: {
        if (active && HV.COVER_UNIT1 !== null && HV.COVER_UNIT2 !== null
                && (HV.COVER_VALUE1 !== "0" || HV.COVER_VALUE2 !== "0")) {
            label.opacity = icon.opacity = 0.25
            resultpanel.visible = true
            resultpanel.unittype_text = HV.UNITTYPE
            resultpanel.unit1_text = HV.COVER_UNIT1
            resultpanel.unit2_text = HV.COVER_UNIT2
            resultpanel.unit3_text = HV.COVER_UNIT3
            resultpanel.unit4_text = HV.COVER_UNIT4
            resultpanel.unit1_value = HV.COVER_VALUE1
            resultpanel.unit2_value = HV.COVER_VALUE2
            resultpanel.unit3_value = HV.COVER_VALUE3
            resultpanel.unit4_value = HV.COVER_VALUE4
        } else if (active && HV.COVER_UNIT1 === null && HV.COVER_UNIT2 === null
                   || (HV.COVER_VALUE1 === "0" && HV.COVER_VALUE2 === "0")) {
            resultpanel.visible = false
            label.opacity = icon.opacity = 1.0
        }
    }
}
