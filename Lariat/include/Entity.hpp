#pragma once
#include "raylib.h"
#include <vector>
#include "Bullet.hpp"
#include "raymath.h"
#include "TicTacToe.hpp"

class Entity {
public:
    virtual ~Entity() = default;

    virtual void Update(float dt) = 0;
    virtual void Draw() const = 0;

    std::vector<Bullet> FlushSpawnedBullets();

    Vector2 GetPosition() const { return position; }
    float   GetRadius()   const { return radius; }
    Color   GetColor()    const { return color;  }
    int     Lives()       const { return lives;  }
    int     Id()          const { return id;     }

    void OnHit();
    bool IsStunned() const { return stunTimer > 0.0f; }

    virtual Vector2 AimTarget() const = 0;

    static bool ResolveCircleRectCollision(Vector2 &circlePos, float radius, const Rectangle &rect);

    TicTacToe* grid; ///< puntero a la grilla para evitar atravesarla

    Vector2 position;

    float   radius;
protected:
    Entity(int id, Vector2 startPos, Color color, Color bulletColor, TicTacToe* gridRef = nullptr);

    void SpawnBullet(Vector2 dir, float speed);

    // --- datos ---
    int     id;
    
    Color   color;
    Color   bulletColor;
    float   speed;
    int     lives;
    float   stunTimer;

    std::vector<Bullet> spawnedBullets;

    
};