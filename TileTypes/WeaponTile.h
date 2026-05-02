//
// Created by adaze on 11.05.2025.
//

#ifndef WEAPONTILE_H
#define WEAPONTILE_H

#include "InteractableTile.h"
#include "../RoomChoice.h"
#include "../Managers/Vector2.h"
#include "../Managers/Random.h"
#include "../Weapon.h"
#include <nlohmann/json.hpp>

#include <iostream>
#include <vector>


class WeaponTile : public InteractableTile {
private:
    Weapon* m_weapon;
public:
    WeaponTile(Weapon* weapon, Vector2 position);
    Weapon* getWeapon();
    RoomChoice getInteractionProperties() override;
    WeaponTile *clone() const override;
    static WeaponTile *getBasicSwordTile(Vector2 position);
};



#endif //WEAPONTILE_H
