#pragma once
#include "Entity.hpp"
#include "TicTacToe.hpp"
#include <memory>

class Bot : public Entity {
public:
    // Constructor recibe un shared_ptr seguro al player
    Bot(Vector2 startPos, TicTacToe* gridRef, std::shared_ptr<Entity> playerRef);

    void Update(float dt) override;
    void Draw() const override;
    Vector2 AimTarget() const override;

private:
    std::weak_ptr<Entity> playerRef; // puntero seguro al player
    Vector2 currentTarget;
    Vector2 aimDir;
    float shootTimer;
    float targetDecisionTimer;
    float targetX;
    float targetXTimer;
};
