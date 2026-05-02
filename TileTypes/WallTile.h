//
// Created by Vilém on 07/06/2025.
//

#ifndef WALLTILE_H
#define WALLTILE_H

#include "StaticTile.h"

class WallTile : public StaticTile{
public:
    WallTile(Vector2 position);
    ~WallTile();
    StaticTile *clone() const override;
};



#endif //WALLTILE_H
