#include "BlockObject.h"

INT g_pos[] = { 1250, 1500, 1750, 2000, 2250, 2500 };

BlockObject::BlockObject() : is_back_(false) {}

BlockObject::~BlockObject() {}

bool BlockObject::LoadImg(const std::string& path, SDL_Renderer* screen) {
    return BaseObject::LoadImageFile(path, screen);
}

void BlockObject::SetPos(const int& xp, const int& yp) {
    SetRect(xp, yp);
}

void BlockObject::SetXPos(const int& xp) {
    SDL_Rect rect = GetRect();
    SetRect(xp, rect.y);
}

void BlockObject::ShowImg(SDL_Renderer* screen) {
    Render(screen);
}

void BlockObject::DoRun(UINT& x_val) {
    rect_.x += x_val;
    if (rect_.x + rect_.w < 0) {
        is_back_ = true;
    }
}

DoubleBlock::DoubleBlock() : x_val_(-3), is_back_(false), is_pass_(false) {}

DoubleBlock::~DoubleBlock() {}

bool DoubleBlock::InitBlock(SDL_Renderer* screen, const int& xp) {
    int number = SDLCommonFunc::MyRandom(1, 10) * 14;
    bool ret1 = m_Topblock.LoadImg("img//topblock2.png", screen);
    bool ret2 = m_BottomBlock.LoadImg("img//bottomblock2.png", screen);

    if (number % 2 == 0) {
        m_Topblock.SetPos(xp, -300 + number);
        m_BottomBlock.SetPos(xp, GROUND_MAP - 220 + number);
    }
    else {
        m_Topblock.SetPos(xp, -300 - number);
        m_BottomBlock.SetPos(xp, GROUND_MAP - 220 - number);
    }

    return ret1 && ret2;
}

void DoubleBlock::RenderImg(SDL_Renderer* screen) {
    m_Topblock.ShowImg(screen);
    m_BottomBlock.ShowImg(screen);
}

void DoubleBlock::DoMoving() {
    m_Topblock.DoRun(x_val_);
    m_BottomBlock.DoRun(x_val_);
    if (m_Topblock.GetStateBack() || m_BottomBlock.GetStateBack()) {
        is_back_ = true;
    }
}

SDL_Rect DoubleBlock::GetTopRect() {
    return m_Topblock.GetRectPos();
}

void DoubleBlock::SetRectVal(const UINT& xp) {
    m_Topblock.SetXPos(xp);
    m_BottomBlock.SetXPos(xp);
}

void DoubleBlock::SetIsBack(bool isBack) {
    is_back_ = isBack;
    m_Topblock.SetBack(isBack);
    m_BottomBlock.SetBack(isBack);
}

void DoubleBlock::GetRectSlot() {
    SDL_Rect rect_top = m_Topblock.GetRectPos();
    slot_rect_ = { rect_top.x + rect_top.w, rect_top.y + rect_top.h, 5, 160 };
}

void DoubleBlock::DrawBound(SDL_Renderer* des) {
    GeometricFormat outlie_size(slot_rect_.x, slot_rect_.y, slot_rect_.w, slot_rect_.h);
    ColorData color_data1(255, 255, 255);
    Gemometric::RenderOutline(outlie_size, color_data1, des);
}

bool DoubleBlock::CheckPass(SDL_Rect rect) {
    return SDLCommonFunc::CheckCollision(rect, slot_rect_);
}

bool DoubleBlock::CheckCol(SDL_Rect pl_rect) {
    return SDLCommonFunc::CheckCollision(pl_rect, m_Topblock.GetRectPos()) || SDLCommonFunc::CheckCollision(pl_rect, m_BottomBlock.GetRectPos());
}

BlockManager::BlockManager() : xp_max_(0), stop_moving_(false), m_count(0), is_col_(false) {}

BlockManager::~BlockManager() {
    FreeBlock();
}

void BlockManager::FreeBlock() {
    for (auto* pBlock : m_BlockList) {
        delete pBlock;
    }
    m_BlockList.clear();
}

bool BlockManager::InitBlockList(SDL_Renderer* screen) {
    for (int i = 0; i < 6; ++i) {
        auto* block = new DoubleBlock();
        if (!block->InitBlock(screen, g_pos[i])) {
            delete block;
            return false;
        }
        m_BlockList.push_back(block);
    }
    xp_max_ = 5;
    return true;
}

void BlockManager::SetStopMoving(const bool& stop) {
    stop_moving_ = stop;
}

void BlockManager::Render(SDL_Renderer* screen) {
    for (size_t i = 0; i < m_BlockList.size(); ++i) {
        DoubleBlock* pBlock = m_BlockList[i];

        pBlock->GetRectSlot();

        if (!stop_moving_) {
            pBlock->DoMoving();

            if (pBlock->GetIsBack()) {
                DoubleBlock* endBlock = m_BlockList[xp_max_];
                SDL_Rect end_rect = endBlock->GetTopRect();
                UINT xp = end_rect.x + 250;
                pBlock->SetRectVal(xp);
                pBlock->SetIsBack(false);
                pBlock->SetIsPass(false);
                xp_max_ = i;
            }

            if (pBlock->CheckCol(player_rect_)) {
                is_col_ = true;
                Mix_Chunk* beep_sound = Mix_LoadWAV("sound//punch.wav");
                if (beep_sound != NULL)
                    Mix_PlayChannel(-1, beep_sound, 0);
                break;
            }

            if (pBlock->CheckPass(player_rect_)) {
                if (!pBlock->GetIsPass()) {
                    Mix_Chunk* beep_sound = Mix_LoadWAV("sound//ting.wav");
                    if (beep_sound != NULL)
                        Mix_PlayChannel(-1, beep_sound, 0);
                    m_count++;
                    pBlock->SetIsPass(true);
                }
            }
        }

        pBlock->RenderImg(screen);
    }
}
