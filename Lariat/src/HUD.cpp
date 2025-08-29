#include "HUD.hpp"
#include "Constants.hpp"
#include <string>

void HUD::DrawTop(const Entity& bot, std::optional<TicTacToe::Mark> win) const {
    DrawText(Cfg::GameTitle.c_str(), 16, 8, 24, WHITE);

    std::string botLives = "Bot Lives: " + std::to_string(bot.Lives());
    DrawText(botLives.c_str(), Cfg::ScreenWidth - 200, 8, 20, Cfg::BotColor);

    if (win.has_value()) {
        const char* txt = (win.value() == TicTacToe::Mark::Player) ? "¡Ganó el Jugador!" : "¡Ganó el Bot!";
        int w = MeasureText(txt, 28);
        DrawText(txt, (Cfg::ScreenWidth - w) / 2, 10, 28, YELLOW);
    }
}

void HUD::DrawBottom(const Entity& player) const {
    std::string pl = "Player Lives: " + std::to_string(player.Lives());
    DrawText(pl.c_str(), 16, Cfg::ScreenHeight - 28, 20, Cfg::PlayerColor);
    DrawText("ESC: Menu", Cfg::ScreenWidth - 120, Cfg::ScreenHeight - 24, 18, GRAY);
}

void HUD::DrawTextCentered(const char* text, int x, int y, int fontSize, Color color) const {
    int textWidth = MeasureText(text, fontSize);
    DrawText(text, x - textWidth/2, y, fontSize, color);
}

void HUD::DrawMenu() const {
    const char* title = Cfg::GameTitle.c_str();
    int tw = MeasureText(title, 42);
    DrawText(title, (Cfg::ScreenWidth - tw) / 2, 120, 42, WHITE);

    const char* play = "Jugar (ENTER)";
    const char* exit = "Salir (ESC)";
    int pw = MeasureText(play, 28);
    int ew = MeasureText(exit, 28);

    DrawText(play, (Cfg::ScreenWidth - pw) / 2, 240, 28, GREEN);
    DrawText(exit, (Cfg::ScreenWidth - ew) / 2, 290, 28, RED);
}
