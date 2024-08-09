
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "stdafx.h"
#include "CommonFunc.h"

class PlayerObject : public BaseObject
{
public:
	PlayerObject();
	~PlayerObject();

	bool LoadImg(string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandleInputAction(SDL_Event events, SDL_Renderer* screen, Mix_Chunk* flySound);

	void Reset();

	void DoFalling(SDL_Renderer* des);
	bool GetFalling() const { return is_falling_; }
	void SetFalling(bool falling) { is_falling_ = falling; }
	void DoGround(SDL_Renderer* screen);
	bool GetIsDie() const { return is_die_; }

	Mix_Chunk* flySound;
private:
	bool is_falling_;
	double x_val_;
	double y_val_;
	bool is_die_;
};


#endif
