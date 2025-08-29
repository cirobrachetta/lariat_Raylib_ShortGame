#include "Bullet.hpp"
#include "Constants.hpp"

Bullet::Bullet(Vector2 pos, Vector2 vel, Color color, int ownerId)
: position(pos), velocity(vel), radius(Cfg::BulletRadius), tint(color), ownerId(ownerId), alive(true) {}

void Bullet::Update(float dt) {
    if (!alive) return;

    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    // Bounce against window borders
    if (position.x < radius) { position.x = radius; velocity.x *= -1; }
    if (position.x > Cfg::ScreenWidth - radius) { position.x = Cfg::ScreenWidth - radius; velocity.x *= -1; }
    if (position.y < radius) { position.y = radius; velocity.y *= -1; }
    if (position.y > Cfg::ScreenHeight - radius) { position.y = Cfg::ScreenHeight - radius; velocity.y *= -1; }
}

void Bullet::ReflectX() {
    velocity.x *= -1;
    bounceCount++;
    if(bounceCount > maxBounces) Kill();
}

void Bullet::ReflectY() {
    velocity.y *= -1;
    bounceCount++;
    if(bounceCount > maxBounces) Kill();
}

void Bullet::Draw() const {
    if (!alive) return;
    DrawCircleV(position, radius, tint);
}
