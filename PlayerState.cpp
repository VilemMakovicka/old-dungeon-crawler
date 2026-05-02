//
// Created by alaf4 on 11.05.2025.
//

#include "PlayerState.h"
#include "Room.h"
#include "Managers/ConsoleManager.h"
#include <format>

PlayerState::PlayerState() {
    m_health = 100;
    m_maximumHealth = 100;
    m_positionOnMap = {0, 0};
    m_currentWeapon = nullptr;
}

PlayerState::~PlayerState() {
    //delete m_currentWeapon;
}


void PlayerState::damagePlayer(int damage) {
    m_health -= damage;
}

void PlayerState::heal(unsigned int amount) {
    if (m_health + amount > m_maximumHealth)
        m_health = m_maximumHealth;
    else
        m_health += amount;
}

int PlayerState::GetHealth() {
    return m_health;
}

std::string PlayerState::getHealthAsString() {
    return std::to_string(GetHealth());
}

Vector2 PlayerState::GetPositionOnMap() {
    return m_positionOnMap;
}

std::string PlayerState::getPositionOnMapAsString() {
    return m_positionOnMap.toString();
}

void PlayerState::travel(Vector2 direction) {
    m_positionOnMap += direction;
}
std::string PlayerState::toString() {
    return "";
}

std::string PlayerState::getHealthVisualized() {
    std::string playerHealthVisualized = "";
    for (int i = 0 ; i < int(m_health / 10) ; i++ ) {
        playerHealthVisualized += "♥";
    }
    playerHealthVisualized = "[" + StringExtensions::colorizeString(playerHealthVisualized, ForegroundConsoleColor::Red) + "]";
    return playerHealthVisualized;
}

std::string PlayerState::getWeaponStatus() {
    return
        m_currentWeapon == nullptr
        ? "You have no weapon."
        : m_currentWeapon->toString();
}

void PlayerState::print() {
    std::vector<std::string> lines = {
        StringExtensions::centerString("Position " + getPositionOnMapAsString(), 35),
        StringExtensions::centerString("Health " + getHealthAsString(), 35),
        StringExtensions::centerString(getHealthVisualized(), 35),
        "",
        StringExtensions::centerString("Your weapon", 35),
        StringExtensions::centerString(getWeaponStatus(), 35)
    };

    ConsoleManager::printBoxView(lines, "Your Status", 35);
}

Weapon *PlayerState::getWeapon() {
    return m_currentWeapon;
}

void PlayerState::setWeapon(Weapon *newWeapon) {
    m_currentWeapon = newWeapon;
}

std::vector<std::string> PlayerState::getBoxView(int width, int height) {
    ForegroundConsoleColor frameColor = ConsoleColor::getForegroundConsoleColor(JsonManager::UIElements["color_themes"]["player_status"]["frame"]);
    ForegroundConsoleColor titleColor = ConsoleColor::getForegroundConsoleColor(JsonManager::UIElements["color_themes"]["player_status"]["headings"]);
    std::string title = "Your Status";

    int interiorWidth = width - 2;

    int healthWidth = interiorWidth / 3;
    int weaponWidth = interiorWidth - healthWidth;

    std::vector<std::string> lines = {
        StringExtensions::centerString("Health " + getHealthAsString(), healthWidth) + StringExtensions::colorizeString("│", ForegroundConsoleColor::Blue) + StringExtensions::centerString("Your weapon", weaponWidth),
        StringExtensions::centerString(getHealthVisualized(), healthWidth) + StringExtensions::colorizeString("│", ForegroundConsoleColor::Blue)  + StringExtensions::centerString(getWeaponStatus(), weaponWidth)
    };

    return StringExtensions::createCutoffBoxView(
        lines,
        title,
        width,
        height,
        frameColor,
        titleColor
        );
}

