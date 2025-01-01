#pragma once
#include <string>
class map
{
public:

    map(const char* mfp, int ms, int ts);
    ~map();

    void loadMap(std::string path, int sizeX, int sizeY);
    void addTile(int srcX, int srcY, int xpos, int ypos);


private:
    const char* mapFilePath;
    int mapScale;
    int tileSize;
};