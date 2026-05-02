//
// Created by Vilém on 10/06/2025.
//

#ifndef EMPTYTILE_H
#define EMPTYTILE_H
#include "StaticTile.h"


class EmptyTile : public StaticTile{
public:
    EmptyTile(Vector2 position);
    ~EmptyTile();
    StaticTile *clone() const override;
};



#endif //EMPTYTILE_H
