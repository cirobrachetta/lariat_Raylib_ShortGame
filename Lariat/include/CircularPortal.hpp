#pragma once
#include "raylib.h"
#include "TicTacToe.hpp"
#include "raymath.h"

/** \file Portal.hpp
 *  \brief Portales superior/inferior que marcan el centro al ser golpeados por balas del color clave.
 */
class CircularPortal {
public:
    /** \brief Crea un portal.
     *  \param rect Rectángulo en pantalla.
     *  \param keyColor Color que habilita el portal (coincidencia exacta).
     *  \param credit Marca a otorgar cuando se activa (coincide con el dueño de ese color).
     */
    CircularPortal(Rectangle rect, Color keyColor, TicTacToe::Mark credit);

    /** \brief Dibuja el portal. */
    void Draw() const;

    /** \brief Intenta consumir una bala: si colisiona y color coincide, marca centro.
     *  \return true si activó y debe destruirse la bala.
     */
    bool TryConsumeBullet(const class Bullet& b, TicTacToe& grid) const;

private:
    Rectangle        rect;
    Color            key;
    TicTacToe::Mark  creditTo;
};
