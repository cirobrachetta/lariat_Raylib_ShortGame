#pragma once
#include <memory>
#include <vector>
#include <optional>
#include "raylib.h"
#include "Bullet.hpp"
#include "TicTacToe.hpp"
#include "HUD.hpp"
#include "Player.hpp"           // <-- incluir definición completa
#include "Bot.hpp" 
#include "CircularPortal.hpp"

/** \file Game.hpp
 *  \brief Orquesta el bucle principal, estados, colisiones y dibujo.
 */
class Game {
public:
    void Run();

private:
    enum class State { Menu, Playing };

    State state{ State::Menu };

    // Punteros a entidades
    std::shared_ptr<Player> player;
    std::unique_ptr<Bot> bot;

    std::vector<Bullet> bullets;
    TicTacToe grid;

    // Portales circulares
    std::unique_ptr<CircularPortal> portalTop;
    std::unique_ptr<CircularPortal> portalBottom;

    HUD hud;

    void StartMatch();
    void UpdatePlaying(float dt);
    void DrawPlaying(std::optional<TicTacToe::Mark> win);
};
