#pragma once
#include "Entity.hpp"
#include "TicTacToe.hpp"

class Player : public Entity {
public:
    Player(Vector2 startPos, TicTacToe* gridRef);

    void Update(float dt) override;
    void Draw() const override;
    Vector2 AimTarget() const override;
};
