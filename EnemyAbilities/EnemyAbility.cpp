//
// Created by Vilém on 10/06/2025.
//

#include "EnemyAbility.h"
#include "Ability_InstantPlayerDamage.h"
#include "Ability_PlayerHeal.h"

EnemyAbility::EnemyAbility(std::string name) {
    m_name = name;
}

EnemyAbility *EnemyAbility::getEnemyAbility(nlohmann::json data) {
    try {
        std::string type = data["effect_type"];
        /**
         *
         * Zde přidávat inicializaci všech nových abilit
         *
         **/
        if (type == "instant_player_damage") {
            std::string abilityName = data["ability_name"];
            int abilitiyActivationChance = data["chance_to_activate"];
            Vector2 abilityDamageRange = Vector2(data["damage_range"][0], data["damage_range"][1]);

            ConsoleManager::printLog("Loaded ability \"" + abilityName + "\"");
            return new Ability_InstantPlayerDamage(abilityName, abilitiyActivationChance, abilityDamageRange);
        }
        if (type == "heal_player") {
            std::string abilityName = data["ability_name"];
            int abilityChance = data["chance_to_activate"];
            int abilityHealAmount = data["amount"];

            return new Ability_PlayerHeal(abilityName, abilityChance, abilityHealAmount);
        }

        ConsoleManager::printError("Schopnost typu \"" + type + "\" nebyla zapsaná do inicializace schopností. Více info v Combatmenu.cpp->getEnemyAbility()");
        return new Ability_PlayerHeal("Neznámá schopnost", 0, 0);
    }
    catch (...) {
        ConsoleManager::printError("Json záznam schopnosti nemá zapsaný typ. Vracím neznámou schopnost.");
        return new Ability_PlayerHeal("Neznámá schopnost", 0, 0);
    }
}

std::string EnemyAbility::getName() {
    try {
        return m_name;
    }
    catch (...) {
        ConsoleManager::printError("Could not read ability name.");
        return "Invalid Ability name";
    }
}

