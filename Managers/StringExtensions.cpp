//
// Created by Vilém on 10/05/2025.
//

#include "StringExtensions.h"

#include "ConsoleManager.h"
#include "JsonManager.h"

std::string StringExtensions::truncateFloat(float value, unsigned int decimalPlaces) {
    std::string valueAsString = std::to_string(value);
    int dotPosition = valueAsString.find('.');

    if (decimalPlaces == 0)
        return valueAsString.substr(0, dotPosition);

    return valueAsString.substr(0, dotPosition + 1 + decimalPlaces);
}

/*
 * Poznámka od Viléma:
 *
 * Potřeboval jsem překonvertovat std::string na std::wstring aby mohla konzole vypisovat UTF-8 speciální znaky.
 * Nemohl jsem přijít na řešení a tak jsem se zeptal ChatGPT a tohle na mě vyplivl.
 * Vypadá to že prochází každej znak a snaží se přijít jak ho konvertovat a pak to slepí zpět (možná se mýlím) ale funguje to takže to tak zatím nechám.
 */
std::wstring StringExtensions::stringToWideString(std::string text) {
    if (text.empty()) return L"";

    int sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, nullptr, 0);
    std::wstring wstr(sizeNeeded, 0);
    MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, &wstr[0], sizeNeeded);
    wstr.pop_back();
    return wstr;
}

std::string StringExtensions::colorizeString(std::string text, ForegroundConsoleColor foregroundColor, BackgroundConsoleColor backgroundColor) {
    if (text.empty()) return text;

    std::string foregroundCode = std::to_string(int(foregroundColor));
    std::string backgroundCode = backgroundColor == BackgroundConsoleColor::Default ? "" : ";" + std::to_string(int(backgroundColor));

    return "\033[" + foregroundCode + backgroundCode + "m" + text + "\033[0m";
}
/*
std::string StringExtensions::colorizeString(std::string text, int foregroundColor, int backgroundColor) {
    if (text.empty()) return text;

    std::string foregroundCode = std::to_string(foregroundColor );
    std::string backgroundCode = backgroundColor == -1 ? "" : ";" + std::to_string(backgroundColor);

    return "\033[" + foregroundCode + backgroundCode + "m" + text + "\033[0m";
}
*/
size_t utf8_length(const std::string str) {
    size_t len = 0;
    for (size_t i = 0; i < str.size();) {
        unsigned char c = str[i];
        if      ((c & 0x80) == 0x00) i += 1; // 1-byte
        else if ((c & 0xE0) == 0xC0) i += 2; // 2-byte
        else if ((c & 0xF0) == 0xE0) i += 3; // 3-byte
        else if ((c & 0xF8) == 0xF0) i += 4; // 4-byte
        else i += 1; // Invalid byte, skip
        ++len;
    }
    return len;
}

std::string StringExtensions::centerString(std::string text, int width, std::string fillingString) {
    std::regex ansiRegex(R"(\x1b\[[0-9;]*m)");
    std::string textWithoutAnsi = std::regex_replace(text, ansiRegex, "");

    size_t visibleLength = utf8_length(textWithoutAnsi);
    if (width <= visibleLength) return text;

    size_t padding = width - visibleLength;
    size_t paddingLeft = padding / 2;
    size_t paddingRight = padding - paddingLeft;

    return repeatString(fillingString, paddingLeft) + text + repeatString(fillingString, paddingRight);
}

std::string StringExtensions::alignStringLeft(std::string text, int width, char fillingCharacter) {
    std::regex ansiRegex(R"(\x1b\[[0-9;]*m)");
    std::string textWithoutAnsi = std::regex_replace(text, ansiRegex, "");

    size_t visibleLength = utf8_length(textWithoutAnsi);
    if (width <= visibleLength) return cutoffString(text, width);

    size_t padding = width - visibleLength;

    return text + std::string(padding, fillingCharacter);
}

std::string StringExtensions::cutoffString(std::string text, int width) {
    std::string output;
    size_t count = 0;

    for (size_t i = 0; i < text.size();) {
        if (text[i] == '\033') {
            // Start of ANSI escape sequence
            size_t esc_end = i + 1;
            while (esc_end < text.size() && text[esc_end] != 'm') ++esc_end;
            if (esc_end < text.size()) ++esc_end; // Include 'm'

            output += text.substr(i, esc_end - i);
            i = esc_end;
        } else {
            // Parse UTF-8 character
            unsigned char c = text[i];
            size_t char_len = 1;
            if      ((c & 0x80) == 0x00) char_len = 1;
            else if ((c & 0xE0) == 0xC0) char_len = 2;
            else if ((c & 0xF0) == 0xE0) char_len = 3;
            else if ((c & 0xF8) == 0xF0) char_len = 4;
            else break; // Invalid UTF-8, stop

            if (count >= width) break;

            output += text.substr(i, char_len);
            i += char_len;
            ++count;
        }
    }

    return output;
}

std::string StringExtensions::startColor(ForegroundConsoleColor foregroundColor, BackgroundConsoleColor backgroundColor) {
    std::string foregroundCode = std::to_string(int(foregroundColor));
    std::string backgroundCode = backgroundColor == BackgroundConsoleColor::Default ? "" : ";" + std::to_string(int(backgroundColor));

    return "\033[" + foregroundCode + backgroundCode + "m";
}

std::string StringExtensions::endColor() {
    return "\033[0m";
}

bool StringExtensions::isEmpty(std::string text) {
    std::regex ansiRegex(R"(\x1b\[[0-9;]*m)");
    std::string textWithoutAnsi = std::regex_replace(text, ansiRegex, "");
    return textWithoutAnsi == "  ";
}

std::vector<std::string> StringExtensions::createBoxView(std::vector<std::string> lines, std::string title, int width, ForegroundConsoleColor edgeForegroundColor, ForegroundConsoleColor titleForegroundColor) {
    std::vector<std::string> output;
    nlohmann::json boxViewJson = JsonManager::UIElements["box_view"];

    std::string edgeHorizontal = boxViewJson["elements"]["edge_horizontal"];
    std::string edgeVertical = boxViewJson["elements"]["edge_vertical"];

    std::string currentLine = "";
    //První řádek

    currentLine += startColor(edgeForegroundColor);
    currentLine += boxViewJson["elements"]["corner_top_left"];

    currentLine += centerString(
        colorizeString(boxViewJson["elements"]["title_start"], edgeForegroundColor) +
        colorizeString(title, titleForegroundColor) +
        colorizeString(boxViewJson["elements"]["title_end"], edgeForegroundColor),
        width - 2,
        colorizeString(edgeHorizontal, edgeForegroundColor));

    currentLine += startColor(edgeForegroundColor);
    currentLine += boxViewJson["elements"]["corner_top_right"];

    output.push_back(currentLine);

    //Kontent
    currentLine = "";
    for (std::string line : lines) {
        currentLine += startColor(edgeForegroundColor);
        currentLine += edgeVertical;
        currentLine += endColor();

        currentLine += alignStringLeft(line, width - 2);

        currentLine += startColor(edgeForegroundColor);
        currentLine += edgeVertical;
        currentLine += endColor();

        output.push_back(currentLine);
        currentLine = "";
    }

    //Spodní řádek

    currentLine = "";
    currentLine += startColor(edgeForegroundColor);
    currentLine += boxViewJson["elements"]["corner_bottom_left"];

    currentLine += repeatString(colorizeString(edgeHorizontal, edgeForegroundColor), width - 2);

    currentLine += startColor(edgeForegroundColor);
    currentLine += boxViewJson["elements"]["corner_bottom_right"];

    currentLine += endColor();
    output.push_back(currentLine);
    return output;
}

std::string StringExtensions::list2String(std::vector<std::string> lines) {
    std::string output;
    for (int i = 0; i < lines.size(); ++i) {
        output += lines[i];
        if (i < lines.size() - 1) output += "\n";
    }
    return output;
}

std::string StringExtensions::chainBoxViews(std::vector<std::vector<std::string>> boxViews) {
    std::vector<std::string> outputList;

    for (std::vector<std::string> boxView : boxViews) {
        for (int i = 0; i < boxView.size(); ++i) {
            if (outputList.size() < i + 1) outputList.push_back("");
            outputList[i] += boxView[i];
        }
    }

    return list2String(outputList);
}

std::string StringExtensions::repeatString(std::string text, int amount) {
    std::string finalText = "";
    for (int i = 0; i < amount; i++) {
        finalText += text;
    }
    return finalText;
}
