#include "game.h"

#include "core/application.h"
#include "scenes/main_menu_scene.h"
#include "scenes/level_one.h"

int game()
{
    Engine::Application app;
    if (!app.Initialize({ 1920, 1080 }, "Aneka")) return -1;

    app.GetSceneManager().LoadScene(std::make_unique<LevelOne>());

    app.Run();
    app.Shutdown();

    return 0;
}