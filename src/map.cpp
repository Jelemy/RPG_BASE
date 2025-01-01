#include <map.h>
#include <textureManager.h>
#include <overWorldState.h>
#include <fstream>
#include <ECS.h>
#include <components.h>
#include <iostream>
extern Manager manager;

map::map(const char* mfp, int ms, int ts) : mapFilePath(mfp), mapScale(ms), tileSize(ts)
{
}

map::~map()
{
}

void map::loadMap(std::string path, int sizeX, int sizeY)
{
    char c;
    std::fstream mapFile;
    mapFile.open(path);

    int srcX, srcY;


    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            mapFile.get(c);
            srcY = atoi(&c) * tileSize;
            mapFile.get(c);
            srcX = atoi(&c) * tileSize;
            addTile(srcX, srcY, x * (tileSize * mapScale), y * (tileSize * mapScale));
            mapFile.ignore();
        }
    }

    mapFile.ignore();

    for (int y = 0; y < sizeY; y++)
    {
        for(int x = 0; x < sizeX; x++)
        {
            mapFile.get(c);
            if (c == '1')
            {
                auto& tcol(manager.addEntity());
                tcol.addComponent<colliderComponent>("terrain", x * (tileSize * mapScale), y * (tileSize * mapScale), (tileSize * mapScale));
                tcol.addGroup(overWorldState::groupColliders);
            }
            mapFile.ignore();
        }
    }
    mapFile.close();
}

void map::addTile(int srcX, int srcY, int xpos, int ypos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<tileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, mapFilePath);
	tile.addGroup(overWorldState::groupMap);
}
