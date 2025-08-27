#include "TicTacToe.hpp"
#include "Constants.hpp"
#include <algorithm>

TicTacToe::TicTacToe() : cells{} {
    float w = Cfg::ScreenWidth  * 0.36f;
    float h = Cfg::ScreenHeight * 0.36f;
    boardRect = { (Cfg::ScreenWidth - w) * 0.5f, (Cfg::ScreenHeight - h) * 0.5f, w, h };
    cellW = w / 3.0f;
    cellH = h / 3.0f;
    Reset();
}

void TicTacToe::Draw() const {
    // Filas coloreadas:
    // - Fila superior (r=0): sólo puede marcar Player (opuesto a su mitad)
    // - Fila media (r=1): libre
    // - Fila inferior (r=2): sólo puede marcar Bot
    Color topRow = ColorAlpha(Cfg::PlayerBulletColor, 0.25f);
    Color midRow = ColorAlpha(WHITE, 0.08f);
    Color botRow = ColorAlpha(Cfg::BotBulletColor, 0.25f);

    for (int r=0; r<3; ++r) {
        for (int c=0; c<3; ++c) {
            Rectangle cell{ boardRect.x + c*cellW, boardRect.y + r*cellH, cellW, cellH };
            Color bg = (r==0? topRow : (r==1? midRow : botRow));
            DrawRectangleRec(cell, bg);
        }
    }

    // Líneas de la grilla
    DrawRectangleLinesEx(boardRect, 3, WHITE);
    DrawLineEx({boardRect.x + cellW,        boardRect.y}, {boardRect.x + cellW,        boardRect.y + boardRect.height}, 3, WHITE);
    DrawLineEx({boardRect.x + 2.0f*cellW,   boardRect.y}, {boardRect.x + 2.0f*cellW,   boardRect.y + boardRect.height}, 3, WHITE);
    DrawLineEx({boardRect.x, boardRect.y + cellH},      {boardRect.x + boardRect.width, boardRect.y + cellH},            3, WHITE);
    DrawLineEx({boardRect.x, boardRect.y + 2.0f*cellH}, {boardRect.x + boardRect.width, boardRect.y + 2.0f*cellH},       3, WHITE);

    // Marcas
    for (int i=0; i<9; ++i) {
        int r = i/3, c = i%3;
        Rectangle cell{ boardRect.x + c*cellW, boardRect.y + r*cellH, cellW, cellH };
        Vector2 center{ cell.x + cell.width/2.0f, cell.y + cell.height/2.0f };
        float s = std::min(cell.width, cell.height) * 0.28f;

        if (cells[i] == Mark::Player) {
            DrawCircleLinesV(center, s, Cfg::PlayerBulletColor);
        } else if (cells[i] == Mark::Bot) {
            DrawLineEx({center.x - s, center.y - s}, {center.x + s, center.y + s}, 4, Cfg::BotBulletColor);
            DrawLineEx({center.x - s, center.y + s}, {center.x + s, center.y - s}, 4, Cfg::BotBulletColor);
        }
    }
}

bool TicTacToe::TryMarkCenter(Mark who) {
    int idx = 4;
    // Centro libre de restricción especial; permitir sobreescritura también
    cells[idx] = who;
    return true;
}

int TicTacToe::PosToIndex(Vector2 p) const {
    if (!CheckCollisionPointRec(p, boardRect)) return -1;
    int c = (int)((p.x - boardRect.x)/cellW);
    int r = (int)((p.y - boardRect.y)/cellH);
    c = std::clamp(c, 0, 2);
    r = std::clamp(r, 0, 2);
    return r*3 + c;
}

bool TicTacToe::RestrictionAllows(int idx, Mark who) const {
    if (idx < 0 || idx >= 9) return false;
    // Fila superior (0..2) sólo Player
    if (idx <= 2 && who != Mark::Player) return false;
    // Fila inferior (6..8) sólo Bot
    if (idx >= 6 && who != Mark::Bot) return false;
    // Fila central (3..5) libre
    return true;
}

bool TicTacToe::TryMarkFromPoint(Vector2 p, Mark who) {
    int idx = PosToIndex(p);
    if (idx < 0) return false;
    if (!RestrictionAllows(idx, who)) return false;

    // Overwrite permitido
    cells[idx] = who;
    return true;
}

std::optional<TicTacToe::Mark> TicTacToe::CheckWinner() const {
    const int lines[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };
    for (auto &ln : lines) {
        Mark a = cells[ln[0]], b = cells[ln[1]], c = cells[ln[2]];
        if (a != Mark::None && a == b && b == c) return a;
    }
    return std::nullopt;
}

bool TicTacToe::GetStrategicCellWorldPos(Vector2 &outPos) const {
    std::vector<Vector2> emptyCells;

    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            int idx = r * 3 + c;
            if (cells[idx] == Mark::None) { // <-- usamos tu enum Mark
                // Calculamos centro en coordenadas del mundo
                float cx = boardRect.x + c * cellW + cellW * 0.5f;
                float cy = boardRect.y + r * cellH + cellH * 0.5f;
                emptyCells.push_back({cx, cy});
            }
        }
    }

    if (emptyCells.empty()) return false;

    int idx = GetRandomValue(0, (int)emptyCells.size() - 1);
    outPos = emptyCells[idx];
    return true;
}

void TicTacToe::Reset() {
    cells.fill(Mark::None);
}
