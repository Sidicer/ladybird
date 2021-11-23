/*
 * Copyright (c) 2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "Game.h"
#include <LibGUI/Application.h>
#include <LibGUI/Icon.h>
#include <LibGUI/Menu.h>
#include <LibGUI/Menubar.h>
#include <LibGUI/Window.h>
#include <LibGfx/Bitmap.h>
#include <LibMain/Main.h>
#include <LibSystem/Wrappers.h>

ErrorOr<int> serenity_main(Main::Arguments arguments)
{
    TRY(System::pledge("stdio recvfd sendfd rpath unix", nullptr));

    auto app = GUI::Application::construct(arguments);

    TRY(System::pledge("stdio recvfd sendfd rpath", nullptr));

    TRY(System::unveil("/res", "r"));
    TRY(System::unveil(nullptr, nullptr));

    auto window = GUI::Window::construct();
    window->resize(Breakout::Game::game_width, Breakout::Game::game_height);
    window->set_resizable(false);
    window->set_double_buffering_enabled(false);
    window->set_title("Breakout");
    auto app_icon = GUI::Icon::default_icon("app-breakout");
    window->set_icon(app_icon.bitmap_for_size(16));
    auto& game = window->set_main_widget<Breakout::Game>();

    auto& game_menu = window->add_menu("&Game");
    game_menu.add_action(GUI::Action::create_checkable("&Pause", { {}, Key_P }, [&](auto& action) {
        game.set_paused(action.is_checked());
    }));

    game_menu.add_separator();

    game_menu.add_action(GUI::CommonActions::make_quit_action([](auto&) {
        GUI::Application::the()->quit();
    }));

    auto& help_menu = window->add_menu("&Help");
    help_menu.add_action(GUI::CommonActions::make_about_action("Breakout", app_icon, window));

    window->show();

    return app->exec();
}
