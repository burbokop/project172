#include "guibutton.h"

GUIButton::GUIButton(Controller *player) : GUILabel (player) {
}

GUIButton::GUIButton(Controller *player, std::string label) : GUILabel (player, label) {
}


#include <iostream>

void GUIButton::press() {
    //std::cout << "PRESSED: " << label << "\n";
}

void GUIButton::update() {
    Ship *playerShip = dynamic_cast<Ship*>(player->getParent());
    WarpDrive *warpDrive = playerShip->getFirstWarp();
    int mode = warpDrive->getState();
    std::string chargingBar;
    if(mode == WarpDrive::WARP_RECHARGING) {
        chargingBar = StringFormer::line(static_cast<unsigned int>((1 - playerShip->getFirstWarp()->getCharging()) * 4));
    //    chargingBar = std::to_string((1 - playerShip->getFirstWarp()->getCharging()) * 4);
    } else if (mode == WarpDrive::WARP_LOADING) {
        chargingBar = StringFormer::line(static_cast<unsigned int>((playerShip->getFirstWarp()->getReady() * 4)));
    //    chargingBar = std::to_string(playerShip->getFirstWarp()->getReady() * 4);
    } else if (mode == WarpDrive::WARP_DISABLED) {
        chargingBar = "";
    } else if (mode == WarpDrive::WARP_EXECUTING) {
        chargingBar = "****";
    } else if (mode == WarpDrive::WARP_READY) {
        chargingBar = "----";
    }

    label = "WD: " + chargingBar + " " + playerShip->getFirstWarp()->getStateAsIcon();
}
