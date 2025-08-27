#include "Player.hpp"
#include "Constants.hpp"
#include "MathUtils.hpp"
#include "raymath.h"

Player::Player(Vector2 startPos, TicTacToe* gridRef)
: Entity(0, startPos, Cfg::PlayerColor, Cfg::PlayerBulletColor, gridRef)
{
    speed = Cfg::PlayerSpeed;
}

void Player::Update(float dt) {
    if (stunTimer > 0.0f) stunTimer -= dt;

    Vector2 move = {0,0};
    if (!IsStunned()) {
        if (IsKeyDown(KEY_W)) move.y -= 1.0f;
        if (IsKeyDown(KEY_S)) move.y += 1.0f;
        if (IsKeyDown(KEY_A)) move.x -= 1.0f;
        if (IsKeyDown(KEY_D)) move.x += 1.0f;
    }
    if (move.x != 0.0f || move.y != 0.0f) move = Vector2Normalize(move);

    position = Vector2Add(position, Vector2Scale(move, speed * dt));

    float minY = Cfg::ScreenHeight * 0.5f + radius;
    float maxY = Cfg::ScreenHeight - radius;
    position.x = MathU::clamp(position.x, radius, (float)Cfg::ScreenWidth - radius);
    position.y = MathU::clamp(position.y, minY, maxY);

    if (grid) {
        Rectangle board = grid->GetBoardRect();
        if (board.width > 0 && board.height > 0)
            Entity::ResolveCircleRectCollision(position, radius, board);
    }

    if (!IsStunned() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 aim = GetMousePosition();
        Vector2 dir = Vector2Subtract(aim, position);
        if (Vector2Length(dir) > 0.001f) SpawnBullet(dir, Cfg::BulletSpeed);
    }
}

void Player::Draw() const {
    DrawCircleV(position, radius, color);

    const float maxDist = 150.0f;
    Vector2 mouse = GetMousePosition();
    Vector2 dir = Vector2Subtract(mouse, position);
    float len = Vector2Length(dir);
    if (len > 0.001f) {
        Vector2 nd = Vector2Normalize(dir);
        Vector2 end = Vector2Add(position, Vector2Scale(nd, (len > maxDist ? maxDist : len)));
        MathU::DrawDashedLine(position, end, 8.0f, 6.0f, Fade(WHITE, 0.75f));
    }
}

Vector2 Player::AimTarget() const {
    return GetMousePosition();
}
