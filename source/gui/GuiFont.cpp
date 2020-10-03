#include <gui/GuiFont.h>

GuiFont::GuiFont(const uint8_t *buffer, size_t buffer_size, Renderer *renderer) {
    this->rw = SDL_RWFromMem((void *) buffer, buffer_size);
    this->renderer = renderer;
}

GuiFont::~GuiFont() {
    for (auto const&[key, val] : font_cache) {
        FC_FreeFont(val);
    }
    for (auto const&[key, val] : ttf_font_cache) {
        TTF_CloseFont(val);
    }
    SDL_RWclose(rw);
}

FC_Font *GuiFont::getFont(int32_t size) {
    if (font_cache.count(size) > 0) {
        return font_cache[size];
    }

    TTF_Font *font = TTF_OpenFontRW(rw, 0, size);
    if (!font) {
        return nullptr;
    }

    FC_Font *fc_font = FC_CreateFont();
    if (!fc_font) {
        TTF_CloseFont(font);
        font = nullptr;
        return nullptr;
    }

    auto res = FC_LoadFontFromTTF(fc_font, renderer->getRenderer(), font, {255, 255, 255, 255});
    if (!res) {
        TTF_CloseFont(font);
        font = nullptr;
        return nullptr;
    }

    font_cache[size] = fc_font;
    ttf_font_cache[size] = font;

    return fc_font;
}