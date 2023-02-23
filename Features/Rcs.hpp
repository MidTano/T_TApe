#pragma once
#include "../Game/LocalPlayer.hpp"
#include "Settings.hpp"
#include "../Math/QAngle.hpp"

class Rcs
{
private:
    QAngle _previousPunch;

    Rcs() : _previousPunch(QAngle::zero()) {}
    ~Rcs() {}

    void recoilControl(RcsSettings& settings, QAngle& weponPunch) const {
        QAngle playerAngle = LocalPlayer::getInstance().getViewAngle();

        QAngle punchValue = weponPunch - _previousPunch;
        punchValue.x *= settings.getVerticalPower(); 
        punchValue.y *= settings.getHorizontalPower();

        LocalPlayer::getInstance().setViewAngle(playerAngle - punchValue);
    }

public:

    static Rcs& getInstance() {
        static Rcs instance;
        return instance;
    }

    Rcs(const Rcs&) = delete;
    Rcs& operator=(const Rcs&) = delete;

    void update() {
        auto settings = Settings::getInstance().getRcsSettings();
        QAngle weponPunch = LocalPlayer::getInstance().getWeaponPunch();

        if(settings.isEnabled() && LocalPlayer::getInstance().isInAttack()) {
            recoilControl(settings, weponPunch);
        }

        _previousPunch = weponPunch;
    }
};