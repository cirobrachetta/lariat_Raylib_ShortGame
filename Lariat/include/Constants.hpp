#pragma once
#include "raylib.h"
#include <string>
#include "raymath.h"

/** \file Constants.hpp
 *  \brief Constantes globales de configuración del juego.
 */
namespace Cfg {
    // Window
    inline constexpr int ScreenWidth  = 960;
    inline constexpr int ScreenHeight = 540;
    inline constexpr int TargetFPS    = 60;

    // Gameplay
    inline constexpr float PlayerSpeed = 220.0f;   ///< Velocidad del jugador
    inline constexpr float BotSpeed    = 200.0f;   ///< Velocidad del bot
    inline constexpr float BulletSpeed = 340.0f;   ///< Las balas son más rápidas que las entidades
    inline constexpr float BulletRadius = 5.0f;
    inline constexpr float EntityRadius = 14.0f;
    inline constexpr float StunSeconds  = 3.0f;    ///< Inhabilitación al ser golpeado
    inline constexpr int   MaxLives     = 5;

    // Colors
    inline const Color PlayerColor        = BLUE;
    inline const Color PlayerBulletColor  = SKYBLUE;
    inline const Color BotColor           = RED;
    inline const Color BotBulletColor     = ORANGE;

    // UI
    inline const std::string GameTitle = "Tank TicTacToe";
}
