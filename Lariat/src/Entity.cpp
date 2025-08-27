#include "Entity.hpp"
#include "Constants.hpp"
#include "raymath.h"
#include <algorithm>

Entity::Entity(int id, Vector2 startPos, Color color, Color bulletColor, TicTacToe* gridRef)
: id(id), position(startPos), radius(Cfg::EntityRadius),
  color(color), bulletColor(bulletColor), speed(Cfg::PlayerSpeed),
  lives(Cfg::MaxLives), stunTimer(0.0f), grid(gridRef) {}

/** \brief Genera una bala desplazada hacia fuera de la entidad. */
void Entity::SpawnBullet(Vector2 dir, float speedBullet) {
    const Vector2 nd = Vector2Normalize(dir);
    Vector2 spawnPos = Vector2Add(position, Vector2Scale(nd, radius + Cfg::BulletRadius + 2.0f));
    Vector2 vel = Vector2Scale(nd, speedBullet);
    spawnedBullets.emplace_back(spawnPos, vel, bulletColor, id);
}

std::vector<Bullet> Entity::FlushSpawnedBullets() {
    std::vector<Bullet> out;
    out.swap(spawnedBullets);
    return out;
}

void Entity::OnHit() {
    if (stunTimer > 0.0f) return;
    if (lives > 0) lives--;
    stunTimer = Cfg::StunSeconds;
}

// --- función de colisión círculo vs rectángulo ---
bool Entity::ResolveCircleRectCollision(Vector2 &circlePos, float radius, const Rectangle &rect) {
    if (radius <= 0.0f) return false; // sanity check
    if (rect.width <= 0.0f || rect.height <= 0.0f) return false;
    float closestX = fmaxf(rect.x, fminf(circlePos.x, rect.x + rect.width));
    float closestY = fmaxf(rect.y, fminf(circlePos.y, rect.y + rect.height));
    Vector2 closestPoint = { closestX, closestY };

    Vector2 delta = Vector2Subtract(circlePos, closestPoint);
    float dist = Vector2Length(delta);

    if (dist < radius) {
        if (dist < 0.001f) {
            circlePos.y = rect.y - radius;
        } else {
            Vector2 push = Vector2Scale(Vector2Normalize(delta), radius - dist);
            circlePos = Vector2Add(circlePos, push);
        }
        return true;
    }
    return false;
}