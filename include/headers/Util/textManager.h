#pragma once

#include "game.h"
#include <vector>
#include <unordered_map>
#include <tuple>

class textManager;
#define GLYPH_MAX 81
#define FONT_TEXTURE_SIZE 256
typedef tuple<int, int> glyphIndex;

class textManager {
private:

    
    SDL_Texture* glyphAtlas;
    string line;
    int currChar;
    std::unordered_map<char, glyphIndex> glyphs;


public:
    textManager();
    ~textManager();
    void setFont(const char* fileName, int size, SDL_Color colour);
    void displayText(string line, int x, int y);
    void setLine(string line);
    void displayChar();

};