//
//  File.cpp
//  Belmont_Reverb
//
//  Created by Derys on 11/10/25.
//


menu.addItem("Echo Plate", 1);
    menu.addItem("A Plate", 2);
    menu.addItem("Jazz Hall", 3);
    menu.addItem("Large Church", 4);
    menu.addItem("Large Room" ,5);
    menu.addItem("Medium Hall", 6);
    menu.addItem("Small Hall", 7);
    menu.addItem("McAfee", 8);
    menu.addItem("MPAC", 9);
    menu.addItem("Classroom", 10);
    
    menu.setTextWhenNothingSelected("None");
    
    menu.onChange = [this]() {
        auto id = menu.getSelectedId();
        audioProcessor.setImpulseResponseFromID(id);
    };