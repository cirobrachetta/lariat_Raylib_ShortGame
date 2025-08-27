#pragma once
#include "raylib.h"
#include "raymath.h"

/** \file Bullet.hpp
 *  \brief Declaración de una bala simple con rebotes en bordes.
 */
class Bullet {
public:
    /** \brief Crea una bala con posición, velocidad, color e id de dueño.
     *  \param pos Posición inicial.
     *  \param vel Velocidad (px/s).
     *  \param color Color de la bala.
     *  \param ownerId 0 = jugador, 1 = bot.
     */
    Bullet(Vector2 pos, Vector2 vel, Color color, int ownerId);

    /** \brief Actualiza la posición y procesa rebotes en paredes. */
    void Update(float dt);

    /** \brief Dibuja la bala. */
    void Draw() const;

    /** \brief Getters y estado de vida. */
    float   Radius()   const { return radius; }
    Vector2 Position() const { return position; }
    int     OwnerId()  const { return ownerId; }
    Color   Tint()     const { return tint; }
    bool    IsAlive()  const { return alive; }
    void    Kill()           { alive = false; }

private:
    Vector2 position;
    Vector2 velocity;
    float   radius;
    Color   tint;
    int     ownerId;
    bool    alive;
};
