#include "game.h"

#include "core/application.h"
#include "main_menu_scene.cpp"
#include "level_one.cpp"

int game()
{
    Engine::Application app;
    if (!app.Initialize({ 1600, 900 }, "Smoke Game")) return -1;


    app.GetSceneManager().LoadScene(std::make_unique<MainMenuScene>());

    app.Run();
    app.Shutdown();

    return 0;
}