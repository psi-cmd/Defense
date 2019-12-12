#ifndef START_PICTURE_CHANGE_H
#define START_PICTURE_CHANGE_H

#include <vector>

enum Entity
{
    _Mtower,
    _Cannon,
    _Enemy1
};

enum Movement
{
    Walk,
    Shoot,
    Dead,
    Battle
};

class Animate
{
public:
    Animate(Entity entity, void *attach);
    void walking();

private:
    void *belongs_to;
};

#endif //START_PICTURE_CHANGE_H
