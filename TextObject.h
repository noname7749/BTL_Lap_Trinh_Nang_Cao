


#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_

#include "CommonFunc.h"
#include "HighScoreManager.h"

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>


class TextObject
{
public:
    TextObject();
    ~TextObject();

    bool loadFromRenderedText(TTF_Font* gFont, SDL_Renderer* screen);
    void Free();
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setColor(int type);
    void RenderText(SDL_Renderer* screen, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void RenderHighScore(SDL_Renderer* screen, TTF_Font* font, int high_score);

    string GetText() const;
    void SetText(const string& text); 

    int getWidth() const { return width_; }
    int getHeight() const { return height_; }

    static const int RED_TEXT = 1;
    static const int WHITE_TEXT = 2;
    static const int BLACK_TEXT = 3;

    

private:
    string str_val_;
    SDL_Color text_color_;
    SDL_Texture* texture_;
    int width_;
    int height_;

   
};

#endif

