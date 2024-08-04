#include "CommonFunc.h"
#include "PlayerObject.h"
#include "ImpTimer.h"
#include "BlockObject.h"
#include "Geometric.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 640

BaseObject g_background;
BaseObject g_ground;

TTF_Font* g_font_text = NULL;
TTF_Font* g_font_MENU = NULL;

bool is_paused = false;

bool show_start_screen = true;
int countdown_timer = 0;



bool InitData() {
    BOOL bSucess = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
        return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("PlappyBird - Phattrienphanmem123AZ",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_OPENGL);

    if (g_window != NULL) {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen != NULL) {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR,
                RENDER_DRAW_COLOR,
                RENDER_DRAW_COLOR,
                RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
                bSucess = false;
        }

        if (TTF_Init() == -1) {
            bSucess = false;
        }

        if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
            bSucess = false;
        }

        g_font_text = TTF_OpenFont("font//ARCADE.ttf", 38);
        if (g_font_text == NULL) {
            return false;
        }

        g_font_MENU = TTF_OpenFont("font//ARCADE.ttf", 80);
        if (g_font_MENU == NULL) {
            return false;
        }
    }

    return bSucess;
}

bool LoadBackground() {
    bool ret = g_background.LoadImageFile("img//bkgn.png", g_screen);
    return ret;
}

void close() {
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[]) {

    if (InitData() == false) {
        return -1;
    }

    ShowStartScreen(g_screen, g_font_MENU);

    ImpTimer fps;
    bool quit = false;

    int ret_menu = SDLCommonFunc::ShowMenu(g_screen, g_font_MENU, "Play Game", "Exit", "img//MENU.png");
    if (ret_menu == 1)
        quit = true;

    if (!LoadBackground()) {
        return -1;
    }

    bool ret = g_ground.LoadImageFile("img//ground2.png", g_screen);
    if (ret == false) {
        return -1;
    }
    g_ground.SetRect(0, GROUND_MAP);

again_label:

    TextObject text_count_;
    text_count_.setColor(TextObject::WHITE_TEXT);

    PlayerObject player;
    ret = player.LoadImg("img//fl_bird.png", g_screen);
    player.SetRect(100, 100);
    if (ret == false) {
        return -1;
    }

    BlockManager manage_block;
    ret = manage_block.InitBlockList(g_screen);
    if (ret == false)
        return -1;

    while (!quit) {
        if (show_start_screen) {
            ShowStartScreen(g_screen, g_font_MENU);
            show_start_screen = false; 
        }

        fps.start();
        while (SDL_PollEvent(&g_event) != 0) {
            if (g_event.type == SDL_QUIT) {
                quit = true;
            }

            if (g_event.type == SDL_KEYDOWN && g_event.key.keysym.sym == SDLK_SPACE) {
                is_paused = !is_paused; 
            }

            if (!is_paused) {
                player.HandleInputAction(g_event, g_screen);
            }

            player.HandleInputAction(g_event, g_screen);
        }

        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR,
            RENDER_DRAW_COLOR,
            RENDER_DRAW_COLOR,
            RENDER_DRAW_COLOR);

        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);

        manage_block.SetPlayerRect(player.GetRect());

        bool is_falling = player.GetFalling();
        if (is_falling == true) {
            manage_block.SetStopMoving(true);
        }

        manage_block.Render(g_screen);

        bool end_game = manage_block.GetColState();
        if (end_game == true) {
            player.SetFalling(true);
        }
        player.DoFalling(g_screen);
        player.Show(g_screen);

        GeometricFormat rectange_size(0, 0, SCREEN_WIDTH, 30);
        ColorData color_data(36, 36, 36);
        Gemometric::RenderRectange(rectange_size, color_data, g_screen);

        GeometricFormat outlie_size(1, 1, SCREEN_WIDTH - 1, 28);
        ColorData color_data1(255, 255, 255);
        Gemometric::RenderOutline(outlie_size, color_data1, g_screen);

        int count = manage_block.GetCount();
        std::string count_str = std::to_string(count);
        text_count_.SetText(count_str);
        text_count_.loadFromRenderedText(g_font_text, g_screen);
        text_count_.RenderText(g_screen, SCREEN_WIDTH * 0.5, 2);

        g_ground.Render(g_screen);
        SDL_RenderPresent(g_screen);

        bool game_over = player.GetIsDie();
        if (game_over == true) {
            Sleep(500);
            int ret_menu = SDLCommonFunc::ShowMenu(g_screen, g_font_MENU,
                "Player Again", "Exit",
                "img//MENU END.png");
            if (ret_menu == 1) {
                quit = true;
                continue;
            }
            else {
                quit = false;
                manage_block.FreeBlock();
                goto again_label;
            }
        }

        if (!is_paused) {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            SDL_RenderClear(g_screen);

            g_background.Render(g_screen, NULL);

            manage_block.SetPlayerRect(player.GetRect());

            bool is_falling = player.GetFalling();
            if (is_falling == true) {
                manage_block.SetStopMoving(true);
            }

            manage_block.Render(g_screen);

            bool end_game = manage_block.GetColState();
            if (end_game == true) {
                player.SetFalling(true);
            }
            player.DoFalling(g_screen);
            player.Show(g_screen);

            GeometricFormat rectange_size(0, 0, SCREEN_WIDTH, 30);
            ColorData color_data(36, 36, 36);
            Geometric::RenderRectangle(rectange_size, color_data, g_screen);

            GeometricFormat outlie_size(1, 1, SCREEN_WIDTH - 1, 28);
            ColorData color_data1(255, 255, 255);
            Geometric::RenderOutline(outlie_size, color_data1, g_screen);

            int count = manage_block.GetCount();
            std::string count_str = std::to_string(count);
            text_count_.SetText(count_str);
            text_count_.loadFromRenderedText(g_font_text, g_screen);
            text_count_.RenderText(g_screen, SCREEN_WIDTH * 0.5, 2);

            g_ground.Render(g_screen);
            SDL_RenderPresent(g_screen);

            bool game_over = player.GetIsDie();
            if (game_over == true) {
                Sleep(500);
                int ret_menu = SDLCommonFunc::ShowMenu(g_screen, g_font_MENU, "Player Again", "Exit", "img//MENU END.png");
                if (ret_menu == 1) {
                    quit = true;
                    continue;
                }
                else {
                    quit = false;
                    manage_block.FreeBlock();
                    goto again_label;
                }
            }
        }
        else {
            SDL_SetRenderDrawColor(g_screen, 0, 0, 0, 255); 
            SDL_RenderClear(g_screen);

            SDL_Color text_color = { 255, 0, 0 }; 
            TextObject pause_text;
            pause_text.SetText("PAUSE GAME");
            pause_text.setColor(text_color.r, text_color.g, text_color.b);
            pause_text.loadFromRenderedText(g_font_MENU, g_screen);
            pause_text.RenderText(g_screen, SCREEN_WIDTH * 0.5 - pause_text.getWidth() / 2, SCREEN_HEIGHT * 0.5 - pause_text.getHeight() / 2);

            SDL_RenderPresent(g_screen);
        }



        int val1 = fps.get_ticks();
        if (fps.get_ticks() < 1000 / FRAMES_PER_SECOND) {
            SDL_Delay((1000 / FRAMES_PER_SECOND) - fps.get_ticks());
        }
    }

    close();
    return 0;
}
