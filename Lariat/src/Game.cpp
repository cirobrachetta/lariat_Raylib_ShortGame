#include "Game.hpp"
#include "Player.hpp"
#include "Bot.hpp"
#include "CircularPortal.hpp" // incluimos la versión circular
#include "Constants.hpp"
#include <algorithm>
#include <iostream>

void Game::StartMatch() {
    // 1️⃣ Reset de la grilla y balas
    grid.Reset();
    bullets.clear();

    // 2️⃣ Inicializar player con shared_ptr
    player = std::make_shared<Player>(
        Vector2{Cfg::ScreenWidth*0.5f, Cfg::ScreenHeight*0.75f},
        &grid
    );

    // 3️⃣ Inicializar bot con weak_ptr seguro
    bot = std::make_unique<Bot>(
        Vector2{Cfg::ScreenWidth*0.5f, Cfg::ScreenHeight*0.25f},
        &grid,
        player // std::shared_ptr se pasa automáticamente al weak_ptr del bot
    );

    // 4️⃣ Inicializar portales circulares
    float r = 25.0f; // radio de ejemplo
    Rectangle rectTop{ Cfg::ScreenWidth/2.0f - r, 50 - r, r*2, r*2 };
    portalTop = std::make_unique<CircularPortal>(rectTop, Cfg::PlayerBulletColor, TicTacToe::Mark::Player);

    Rectangle rectBottom{ Cfg::ScreenWidth/2.0f - r, Cfg::ScreenHeight - 50 - r, r*2, r*2 };
    portalBottom = std::make_unique<CircularPortal>(rectBottom, Cfg::BotBulletColor, TicTacToe::Mark::Bot);

    // 5️⃣ Validaciones extra (opcional, útil para debug)
    if (!player)      { std::cerr << "Player no inicializado!\n"; }
    if (!bot)         { std::cerr << "Bot no inicializado!\n"; }
    if (!portalTop)   { std::cerr << "PortalTop no inicializado!\n"; }
    if (!portalBottom){ std::cerr << "PortalBottom no inicializado!\n"; }
}

void Game::Run() {
    InitWindow(Cfg::ScreenWidth, Cfg::ScreenHeight, Cfg::GameTitle.c_str());
    SetTargetFPS(Cfg::TargetFPS);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        if (state == State::Menu) {
            if (IsKeyPressed(KEY_ENTER)) { StartMatch(); state = State::Playing; }
            if (IsKeyPressed(KEY_ESCAPE)) break;

            BeginDrawing();
            ClearBackground(BLACK);
            hud.DrawMenu();
            EndDrawing();
            continue;
        }

        if (IsKeyPressed(KEY_ESCAPE)) { state = State::Menu; continue; }

        UpdatePlaying(dt);

        auto win = grid.CheckWinner();

        BeginDrawing();
        ClearBackground(DARKGRAY);
        DrawPlaying(win);
        EndDrawing();
    }

    CloseWindow();
}

void Game::UpdatePlaying(float dt) {
    if(player) player->Update(dt);
    if(bot) bot->Update(dt);

    // Recolectar balas nuevas en vector temporal
    std::vector<Bullet> newBullets;
    if(player) {
        auto pb = player->FlushSpawnedBullets();
        newBullets.insert(newBullets.end(), pb.begin(), pb.end());
    }
    if(bot) {
        auto bb = bot->FlushSpawnedBullets();
        newBullets.insert(newBullets.end(), bb.begin(), bb.end());
    }

    // Actualizar balas existentes
    for(auto &b : bullets) b.Update(dt);

    // Portales y colisiones
    for(auto &b : bullets) {
        if(!b.IsAlive()) continue;
        if(portalTop && portalTop->TryConsumeBullet(b,grid)) b.Kill();
        if(portalBottom && portalBottom->TryConsumeBullet(b,grid)) b.Kill();

        if(player && Vector2Distance(b.Position(), player->GetPosition()) <= b.Radius()+player->GetRadius())
            if(b.OwnerId()!=player->Id()) player->OnHit(), b.Kill();

        if(bot && Vector2Distance(b.Position(), bot->GetPosition()) <= b.Radius()+bot->GetRadius())
            if(b.OwnerId()!=bot->Id()) bot->OnHit(), b.Kill();

        TicTacToe::Mark who = (b.OwnerId() == 0 ? TicTacToe::Mark::Player : TicTacToe::Mark::Bot);
        if (grid.TryMarkFromPoint(b.Position(), who)) b.Kill();
    }

    // Eliminar balas muertas
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [](const Bullet& b){ return !b.IsAlive(); }), bullets.end());

    // Añadir balas nuevas después
    bullets.insert(bullets.end(), newBullets.begin(), newBullets.end());
}

void Game::DrawPlaying(std::optional<TicTacToe::Mark> win) {
    grid.Draw();

    portalTop->Draw();
    portalBottom->Draw();

    DrawLine(0, Cfg::ScreenHeight/2, Cfg::ScreenWidth, Cfg::ScreenHeight/2, Fade(WHITE, 0.2f));

    for (auto &b : bullets) b.Draw();

    player->Draw();
    bot->Draw();

    hud.DrawTop(*bot, win);
    hud.DrawBottom(*player);
}
