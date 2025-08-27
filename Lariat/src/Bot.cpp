#include "Bot.hpp"
#include "Constants.hpp"
#include "raymath.h"
#include "MathUtils.hpp"
#include <cstdlib>

Bot::Bot(Vector2 startPos, TicTacToe* gridRef, std::shared_ptr<Entity> playerRef)
: Entity(1, startPos, Cfg::BotColor, Cfg::BotBulletColor, gridRef),
  playerRef(playerRef)
{
    speed = Cfg::BotSpeed;
    shootTimer = GetRandomValue(50, 200) / 100.0f;
    aimDir = {0.0f, 1.0f};
    targetDecisionTimer = GetRandomValue(100, 200) / 100.0f;

    if(auto p = this->playerRef.lock())
        currentTarget = p->GetPosition();
}

void Bot::Update(float dt) {
    if(stunTimer > 0.0f) stunTimer -= dt;

    // Movimiento horizontal aleatorio
    if(!IsStunned()) {
        targetXTimer -= dt;
        if(targetXTimer <= 0.0f) {
            targetX = Cfg::ScreenWidth * 0.5f + GetRandomValue(-120, 120);
            targetXTimer = GetRandomValue(100, 200) / 100.0f;
        }

        Vector2 move = {0,0};
        if(position.x < targetX-4.0f) move.x = 1.0f;
        else if(position.x > targetX+4.0f) move.x = -1.0f;

        if(move.x != 0.0f) {
            move = Vector2Normalize(move);
            position = Vector2Add(position, Vector2Scale(move, speed*dt));
        }
    }

    // Limitar a mitad superior de la pantalla
    position.x = MathU::clamp(position.x, radius, (float)Cfg::ScreenWidth-radius);
    position.y = MathU::clamp(position.y, radius, Cfg::ScreenHeight*0.5f-radius);

    // Colisión con la grilla
    if(grid) {
        Rectangle board = grid->GetBoardRect();
        if(board.width>0 && board.height>0)
            Entity::ResolveCircleRectCollision(position, radius, board);
    }

    // Decisión de objetivo
    targetDecisionTimer -= dt;
    if(targetDecisionTimer <= 0.0f) {
        bool targetGrid = false;
        if(grid && GetRandomValue(0,100)<70) {
            Vector2 cellPos;
            if(grid->GetStrategicCellWorldPos(cellPos)) {
                currentTarget = cellPos;
                targetGrid = true;
            }
        }
        if(!targetGrid) {
            if(auto p = playerRef.lock())
                currentTarget = p->GetPosition();
        }
        targetDecisionTimer = GetRandomValue(100,200)/100.0f;
    }

    // Apuntado suavizado
    Vector2 toTarget = Vector2Subtract(currentTarget, position);
    if(Vector2Length(toTarget) > 0.001f) {
        Vector2 desiredDir = Vector2Normalize(toTarget);
        aimDir = Vector2Lerp(aimDir, desiredDir, dt*5.0f);
    }

    // Disparo
    shootTimer -= dt;
    if(!IsStunned() && shootTimer <= 0.0f) {
        SpawnBullet(aimDir, Cfg::BulletSpeed);
        shootTimer = GetRandomValue(50,200)/100.0f;
    }
}

void Bot::Draw() const {
    DrawCircleV(position, radius, color);
    Vector2 tip = Vector2Add(position, Vector2Scale(aimDir, 120.0f));
    DrawLineEx(position, tip, 2.0f, Fade(WHITE,0.5f));
}

Vector2 Bot::AimTarget() const {
    return Vector2Add(position, Vector2Scale(aimDir,1.0f));
}
