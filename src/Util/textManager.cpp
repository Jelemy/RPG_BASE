#include "textManager.h"
#include <iostream>

textManager::textManager()
{
    glyphAtlas = NULL;
    line = "";
    currChar = 0;
    string chars = R"(ABCDEFGHIJKLMNOPQRSTUVWXYZ<abcdefghijklmnopqrstuvwxyz>0123456789.,;:$#'!"/?%&()@ )";
    int i = 0;
    int j = 0;
    for (char c : chars) {
        if (i > 8) {
            i = 0;
            j++;
        }
        glyphIndex ij = make_tuple(i, j);
        glyphs.insert({c, ij});
        i++;
    }

}
textManager::~textManager()
{
    
}

void textManager::setFont(const char* fileName, int size, SDL_Color colour)
{
    glyphAtlas = textureManager::loadTexture(fileName);
}
void textManager::displayText(string text, int x, int y)
{
    // Divisions use for tweaking text size
    // For future may need to implement some system for 
    int texW, texH;
    SDL_QueryTexture(glyphAtlas, NULL, NULL, &texW, &texH);
    SDL_Rect src, dst;
    src.x = 0;
    src.y = 0;
    src.w = texW/9;
    src.h = texH/9;
    dst.x = x;
    dst.y = y;
    dst.w = (texW/9)/6;
    dst.h = (texH/9)/6.5;

    for (char c : text) {
        if (c == '@') {
            dst.x = x;
            dst.y += (texH/9)/6;
        } else {
            src.x = get<0>(glyphs[c]) *texW/9;
            src.y = get<1>(glyphs[c]) *texH/9;
            SDL_RenderCopy(game::renderer, glyphAtlas, &src, &dst);
            dst.x += (texW/9)/11;
        }
    }

}
void textManager::setLine(string line)
{

}
void textManager::displayChar()
{

}