#include "raylib.h"
#include "CircularPortal.hpp"
#include "Bullet.hpp"

CircularPortal::CircularPortal(Rectangle rect, Color keyColor, TicTacToe::Mark credit)
: rect(rect), key(keyColor), creditTo(credit) {}

void CircularPortal::Draw() const {
    // Calculamos centro y radio del portal
    float cx = rect.x + rect.width * 0.5f;
    float cy = rect.y + rect.height * 0.5f;
    float radius = rect.width * 0.5f; // Suponemos círculo perfecto

    // Fondo del portal (semi-transparente)
    DrawCircle(cx, cy, radius, ColorAlpha(key, 0.35f));

    // Contorno del portal
    DrawCircleLines(cx, cy, radius, RED);
}

bool CircularPortal::TryConsumeBullet(const Bullet& b, TicTacToe& grid) const {
    // Comprobamos colisión: si la bala está dentro del círculo
    float cx = rect.x + rect.width * 0.5f;
    float cy = rect.y + rect.height * 0.5f;
    float radius = rect.width * 0.5f;

    Vector2 pos = b.Position();
    float dist = sqrtf((pos.x - cx)*(pos.x - cx) + (pos.y - cy)*(pos.y - cy));

    if(dist > radius) return false;

    if (ColorToInt(b.Tint()) == ColorToInt(key)) {
        // Marca el centro con la marca asociada al color
        return grid.TryMarkCenter(creditTo);
    }

    return false;
}
