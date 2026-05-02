//
// Created by alaf4 on 12.05.2025.
//

#ifndef HALLROOM_H
#define HALLROOM_H

#include "Room.h"

class HallRoom : public Room{
private:
    void gen_generateWalls();
public:
    HallRoom(Vector2 positionOnMap, ForceGenerateState northDoor, ForceGenerateState southDoor, ForceGenerateState eastDoor, ForceGenerateState westDoor);
};




#endif //HALLROOM_H
