#pragma once

#include <cstdint>
#include <SDL2/SDL_rwops.h>
#include <map>
#include <gui/video/SDL_FontCache.h>
#include <gui/video/Renderer.h>

class GuiFont {
public:
    GuiFont(const uint8_t *buffer, size_t buffer_size, Renderer *renderer);
    ~GuiFont();

    FC_Font *getFont(int32_t size);


private:
    std::map<int32_t, FC_Font *> font_cache;
    std::map<int32_t, TTF_Font *> ttf_font_cache;
    SDL_RWops *rw;
    Renderer *renderer;
};
