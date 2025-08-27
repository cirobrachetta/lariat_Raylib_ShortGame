#include "Game.hpp"

/** \mainpage
 *  \brief Juego "Tank TicTacToe" con Raylib y C++.
 *
 *  \section descripcion Descripción
 *  Híbrido entre "tres en raya" y tanques 2D. El jugador (WASD + ratón + click) y un bot
 *  compiten por marcar la grilla central; ambos pueden sobreescribir marcas conforme a las
 *  restricciones por filas (superior sólo Player, inferior sólo Bot, central libre).
 *  Las balas rebotan y, si golpean a una entidad, la inhabilitan por 3 s y le quitan una vida
 *  (ambos comienzan con 5). Portales coloreados marcan el centro si los golpea una bala del
 *  color que les corresponde (color del lado opuesto). Menú: Enter = jugar, Esc = salir/volver.
 */
int main() {
    Game game;
    game.Run();
    return 0;
}
