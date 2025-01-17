#include <collision.h>
#include <cCollider.h>


bool collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
    if (
        recA.x + recA.w >= recB.x &&
        recB.x + recB.w >= recA.x &&
        recA.y + recA.h >= recB.y &&
        recB.y + recB.h >= recA.y
    )
    {
        return true;
    }

    return false;
}

bool collision::AABB(const colliderComponent& colA, const colliderComponent& colB)
{
    if(AABB(colA.collider, colB.collider))
    {
        //std::cout << colA.tag << " hit: " << colB.tag << std::endl;
        return true;
    }
    return false;
}
