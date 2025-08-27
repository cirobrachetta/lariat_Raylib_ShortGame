#pragma once
#include "raylib.h"
#include <array>
#include <vector>
#include <optional>
#include "raymath.h"

/** \file TicTacToe.hpp
 *  \brief Lógica y render de la grilla de tres en raya.
 */
class TicTacToe {
public:
    /** \brief Marca de celda. */
    enum class Mark { None, Player, Bot };

    /** \brief Crea una grilla centrada en pantalla. */
    TicTacToe();

    /** \brief Dibuja la grilla, fondos por filas y marcas. */
    void Draw() const;

    /** \brief Marca el centro si está permitido y devuelve éxito. */
    bool TryMarkCenter(Mark who);

    /** \brief Intenta marcar según un punto (impacto de bala) con restricción por filas.
     *  \note Se permite sobreescritura: si hay marca previa, se reemplaza.
     */
    bool TryMarkFromPoint(Vector2 p, Mark who);

    /** \brief Retorna el ganador si existe. */
    std::optional<Mark> CheckWinner() const;

    /** \brief Reinicia la grilla. */
    void Reset();

    bool GetStrategicCellWorldPos(Vector2 &outPos) const;

    /** \brief Devuelve el rectángulo que ocupa la grilla en el mundo. */
    Rectangle GetBoardRect() const { return boardRect; }

private:
    Rectangle      boardRect;
    float          cellW, cellH;
    std::array<Mark,9> cells;

    int  PosToIndex(Vector2 p) const;
    bool RestrictionAllows(int idx, Mark who) const; ///< Fila superior: sólo Player; fila inferior: sólo Bot; fila media: libre.
};
