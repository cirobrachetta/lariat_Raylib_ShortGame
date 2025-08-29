#pragma once
#include "raylib.h"
#include "raymath.h"

/** \file Bullet.hpp
 *  \brief Declaración de una bala simple con rebotes en bordes.
 */
class Bullet {
public:
    Bullet(Vector2 pos, Vector2 vel, Color color, int ownerId);

    void Update(float dt);
    void Draw() const;

    float   Radius()   const { return radius; }
    Vector2 Position() const { return position; }
    int     OwnerId()  const { return ownerId; }
    Color   Tint()     const { return tint; }
    bool    IsAlive()  const { return alive; }
    void    Kill()           { alive = false; }

    void ReflectX();
    void ReflectY();

    // ✅ Nuevos getters para rebotes
    int  BounceCount() const { return bounceCount; }
    int  MaxBounces()  const { return maxBounces; }

private:
    Vector2 position;
    Vector2 velocity;
    float   radius;
    Color   tint;
    int     ownerId;
    bool    alive;

    int bounceCount{0};                  // contador de rebotes
    static constexpr int maxBounces{3};  // máximo permitido
};