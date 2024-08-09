#include "stdafx.h"
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
TTF_Font* g_font_countdown = NULL;
Mix_Music* g_background_music = NULL;
Mix_Chunk* flap_sound = NULL;
Mix_Chunk* game_over_sound = NULL;

bool InitData()
{
	bool bSucess = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0)
		return false;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	g_window = SDL_CreateWindow("FLAPPY BIRD",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_OPENGL);

	if (g_window != NULL)
	{
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen != NULL)
		{
			SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR,
				RENDER_DRAW_COLOR,
				RENDER_DRAW_COLOR,
				RENDER_DRAW_COLOR);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags))
				bSucess = false;
		}

		if (TTF_Init() == -1)
		{
			bSucess = false;
		}

		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		{
			bSucess = false;
		}

		g_font_countdown = TTF_OpenFont("font//ARCADE.ttf", 300);
		if (g_font_countdown == NULL)
		{
			return false;
		}

		if (Mix_Init(MIX_INIT_OGG) == -1) {
			bSucess = false;
		}

		g_font_text = TTF_OpenFont("font//ARCADE.ttf", 50);
		if (g_font_text == NULL)
		{
			return false;
		}

		g_font_MENU = TTF_OpenFont("font//ARCADE.ttf", 80);
		if (g_font_MENU == NULL)
		{
			return false;
		}
	}

	return bSucess;
}


bool LoadBackground()
{
	g_background_music = Mix_LoadMUS("sound//nhacnen.mp3");
	if (g_background_music == NULL)
	{
		printf(Mix_GetError());
		return false;
	}
	bool ret = g_background.LoadImageFile("img//bkgn.png", g_screen);
	return ret;
}


void close()
{
	g_background.Free();
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;

	SDL_DestroyWindow(g_window);
	g_window = NULL;

	IMG_Quit();
	SDL_Quit();
}


int main(int argc, char* argv[])
{
	if (InitData() == false)
	{
		return -1;
	}

	ImpTimer fps;
	bool quit = false;

	int ret_menu = SDLCommonFunc::ShowMenu(g_screen, g_font_MENU, "Start Game", "Quit", "img//MENU.png");
	if (ret_menu == 1)
		quit = true;

	if (!LoadBackground())
	{
		return -1;
	}



	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(g_background_music, -1);
	}

	Mix_Chunk* flap_sound = Mix_LoadWAV("sound//flap.ogg");
	if (flap_sound == NULL)
	{
		printf(Mix_GetError());
		return 1;
	}

	game_over_sound = Mix_LoadWAV("sound//gameover.mp3");
	if (game_over_sound == NULL) {
		printf(Mix_GetError());
	}

	bool ret = g_ground.LoadImageFile("img//ground2.png", g_screen);
	if (ret == false)
	{
		return -1;
	}
	g_ground.SetRect(0, GROUND_MAP);

again_label:

	TextObject text_count_;
	text_count_.setColor(TextObject::WHITE_TEXT);

	TextObject countdown_text;
	countdown_text.setColor(TextObject::RED_TEXT);

	countdown_text.SetText("3");
	countdown_text.loadFromRenderedText(g_font_countdown, g_screen);

	PlayerObject player;
	ret = player.LoadImg("img//fl_bird.png", g_screen);
	player.SetRect(100, 100);
	if (ret == false)
	{
		return -1;
	}

	BlockManager manage_block;
	ret = manage_block.InitBlockList(g_screen);
	if (ret == false)
		return -1;

	TextObject score_text;
	score_text.setColor(TextObject::RED_TEXT);

	bool game_started = false;

	bool is_paused = false;


	while (!quit)
	{
		fps.start();
		while (SDL_PollEvent(&g_event) != 0)
		{
			if (g_event.type == SDL_QUIT)
			{
				quit = true;
			}

			if (g_event.type == SDL_KEYDOWN) {
				if (g_event.key.keysym.sym == SDLK_SPACE) {
					is_paused = !is_paused;
				}
			}

			player.HandleInputAction(g_event, g_screen, flap_sound);
		}

		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR,
			RENDER_DRAW_COLOR,
			RENDER_DRAW_COLOR,
			RENDER_DRAW_COLOR);

		if (!is_paused) {


			g_background.Render(g_screen, NULL);
			g_ground.Render(g_screen, NULL);


			if (!game_started) {
				g_background.Render(g_screen, NULL);
				g_ground.Render(g_screen, NULL);
				for (int i = 3; i >= 1; i--) {
					std::string count_str = std::to_string(i);
					countdown_text.SetText(count_str);
					countdown_text.loadFromRenderedText(g_font_countdown, g_screen);
					countdown_text.RenderText(g_screen, SCREEN_WIDTH * 0.45, SCREEN_HEIGHT * 0.3);
					SDL_RenderPresent(g_screen);
					SDL_Delay(1000);
					g_background.Render(g_screen, NULL);
				}
				countdown_text.SetText("Ready");
				countdown_text.loadFromRenderedText(g_font_countdown, g_screen);
				countdown_text.RenderText(g_screen, SCREEN_WIDTH * 0.3 - 100, SCREEN_HEIGHT * 0.3);
				SDL_RenderPresent(g_screen);
				SDL_Delay(1000);
				SDL_RenderClear(g_screen);
				g_background.Render(g_screen, NULL);

				countdown_text.SetText("GO!");
				countdown_text.loadFromRenderedText(g_font_countdown, g_screen);
				countdown_text.RenderText(g_screen, SCREEN_WIDTH * 0.45 - 100, SCREEN_HEIGHT * 0.3);
				SDL_RenderPresent(g_screen);
				SDL_Delay(1000);
				SDL_RenderClear(g_screen);
				g_background.Render(g_screen, NULL);

				game_started = true;
			}

			manage_block.SetPlayerRect(player.GetRect());

			bool is_falling = player.GetFalling();
			if (is_falling == true)
			{
				manage_block.SetStopMoving(true);
			}

			manage_block.Render(g_screen);





			bool end_game = manage_block.GetColState();
			if (end_game == true)
			{
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
			string score_str = "Score: " + to_string(count);
			score_text.SetText(score_str);
			score_text.loadFromRenderedText(g_font_text, g_screen);

			score_text.RenderText(g_screen, 20, 40);
			SDL_RenderPresent(g_screen);

			bool game_over = player.GetIsDie();
			if (game_over == true)
			{
				Mix_PlayChannel(-1, game_over_sound, 0);
				Sleep(500);
				int ret_menu = SDLCommonFunc::ShowMenu(g_screen, g_font_MENU,
					"Player Again", "Exit",
					"img//MENU END.png");
				if (ret_menu == 1)
				{
					quit = true;
					continue;
				}
				else
				{
					quit = false;
					manage_block.FreeBlock();
					player.Reset();
					game_started = false;
					goto again_label;
				}
			}

			int val1 = fps.get_ticks();
			if (fps.get_ticks() < 1000 / FRAMES_PER_SECOND)
			{
				SDL_Delay((1000 / FRAMES_PER_SECOND) - fps.get_ticks());
			}
		}
	}
	Mix_FreeChunk(game_over_sound);
	game_over_sound = NULL;
	close();
	return 0;
}
