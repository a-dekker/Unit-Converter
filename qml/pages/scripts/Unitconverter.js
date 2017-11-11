function onActivation(unit, unit_abb) {
    if (unitWindowBox.fromUnitField_text !== "" && unitWindowBox.toUnitField_text !==
        "") {
        unit_from = ""
        unit_to = ""
        unitWindowBox.fromUnitField_text = "";
        unitWindowBox.toUnitField_text = "";
    }
    if (unitWindowBox.fromUnitField_text === "" && unitWindowBox.toUnitField_text ===
        "") {
        unitWindowBox.fromUnitField_text = unit
        unit_from = unit_abb

    } else if (unitWindowBox.fromUnitField_text !== "") {
        unit_to = unit !== unitWindowBox.fromUnitField_text ? unit_abb : ""
        unitWindowBox.toUnitField_text = unit !== unitWindowBox.fromUnitField_text ?
            unit : "";
    }
}
