#pragma once

struct GameModifiers {
    bool rainActive = false;
    bool windActive = false;
    bool thunderActive = false;
    bool wifiActive = false;
    bool smallerRocksActive = false;
    bool tooStrongActive = false;

    void updateModifiersForRound(int round) {
        rainActive = (round >= 2);
        windActive = (round >= 4);
        thunderActive = (round >= 6);
        wifiActive = (round >= 8);
        smallerRocksActive = (round >= 10);
        tooStrongActive = (round >= 12);
    }
};