#include "game.h"

#include "core/application.h"
#include "main_menu_scene.h"
#include "level_one.h"

int game()
{
    Engine::Application app;
    if (!app.Initialize({ 1600, 900 }, "Smoke Game")) return -1;


    app.GetSceneManager().LoadScene(std::make_unique<LevelOne>());

    app.Run();
    app.Shutdown();

    return 0;
}