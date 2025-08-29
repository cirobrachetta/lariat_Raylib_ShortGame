#pragma once
#include "Entity.hpp"
#include "TicTacToe.hpp"
#include <optional>

/** \file HUD.hpp
 *  \brief Interfaz de usuario: vidas, ganador, instrucciones y menú.
 */
class HUD {
public:
    enum class Screen { Menu, Playing };

    void DrawTextCentered(const char* text, int x, int y, int fontSize, Color color) const;

    HUD() = default;

    /** \brief Dibuja la banda superior: título, vidas del bot y ganador. */
    void DrawTop(const Entity& bot, std::optional<TicTacToe::Mark> win) const;

    /** \brief Dibuja la banda inferior: vidas del jugador y tips. */
    void DrawBottom(const Entity& player) const;

    /** \brief Dibuja el menú principal. */
    void DrawMenu() const;
};
