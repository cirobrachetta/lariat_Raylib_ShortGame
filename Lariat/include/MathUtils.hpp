#pragma once
#include "raylib.h"
#include "raymath.h"

/** \file MathUtils.hpp
 *  \brief Utilidades matemáticas y de dibujo.
 */
namespace MathU {
    /** \brief Limita un valor dentro de un rango. */
    template<typename T>
    T clamp(T v, T lo, T hi) { return (v < lo) ? lo : (v > hi ? hi : v); }

    /** \brief Dibuja una línea punteada.
     *  \param start Punto inicial.
     *  \param end   Punto final.
     *  \param dash  Largo de cada trazo.
     *  \param gap   Separación entre trazos.
     *  \param color Color a dibujar.
     */
    inline void DrawDashedLine(Vector2 start, Vector2 end, float dash, float gap, Color color) {
        Vector2 v = Vector2Subtract(end, start);
        float len = Vector2Length(v);
        if (len <= 0.0001f) return;
        Vector2 dir = Vector2Scale(Vector2Normalize(v), dash);
        Vector2 step = Vector2Scale(Vector2Normalize(v), dash + gap);
        int steps = (int)(len / (dash + gap));
        Vector2 p = start;
        for (int i = 0; i < steps; ++i) {
            Vector2 p2 = Vector2Add(p, dir);
            DrawLineEx(p, p2, 2.0f, color);
            p = Vector2Add(p, step);
        }
    }
}