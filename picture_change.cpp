#include "picture_change.h"

Animate::Animate(Entity entity, void *attach) {
    belongs_to = attach;
    switch (entity) {
        case _Mtower:
            break;
        case _Cannon:
            break;
        case _Enemy1:
            break;
    }
}

void Animate::walking() {


}
