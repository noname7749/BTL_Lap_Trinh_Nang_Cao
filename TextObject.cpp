
#include "TextObject.h"
#include "HighScoreManager.h"
          

TextObject::TextObject() : texture_(NULL), width_(0), height_(0) {
    text_color_.r = 255;
    text_color_.g = 255;
    text_color_.b = 255;
}

TextObject::~TextObject()
{
    Free();
}

void TextObject::SetText(const string& text) {
    str_val_ = text;
}


bool TextObject::loadFromRenderedText(TTF_Font* gFont, SDL_Renderer* screen)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, str_val_.c_str(), text_color_);
    if (textSurface != NULL)
    {
        texture_ = SDL_CreateTextureFromSurface(screen, textSurface);
        if (texture_ != NULL)
        {
            width_ = textSurface->w;
            height_ = textSurface->h;
        }

        SDL_FreeSurface(textSurface);
    }

    return texture_ != NULL;
}

void TextObject::Free()
{
    if (texture_ != NULL)
    {
        SDL_DestroyTexture(texture_);
        texture_ = NULL;
    }
}

void TextObject::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    text_color_.r = red;
    text_color_.g = green;
    text_color_.b = blue;
}

void TextObject::setColor(int type)
{
    if (type == RED_TEXT)
    {
        SDL_Color color = { 255, 0, 0 };
        text_color_ = color;
    }
    else if (type == WHITE_TEXT)
    {
        SDL_Color color = { 255, 255, 255 };
        text_color_ = color;
    }
    else
    {
        SDL_Color color = { 0, 0, 0 };
        text_color_ = color;
    }
}
void TextObject::RenderText(SDL_Renderer* screen, int x, int y, SDL_Rect* clip /* = NULL */, double angle /* = 0.0 */, SDL_Point* center /* = NULL */, SDL_RendererFlip flip /* = SDL_FLIP_NONE */)
{

    SDL_Rect renderQuad = { x, y, width_, height_ };

    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(screen, texture_, clip, &renderQuad, angle, center, flip);
}

void TextObject::RenderHighScore(SDL_Renderer* screen, TTF_Font* font, int high_score, int current_score) {
    string best_score_text = "Best Score: " + to_string(high_score);
    SetText(best_score_text);
    loadFromRenderedText(font, screen);
    RenderText(screen, 100, 150);

    string your_score_text = "Your Score is: " + to_string(current_score);
    SetText(your_score_text);
    loadFromRenderedText(font, screen);
    RenderText(screen, 100, 100);
}

