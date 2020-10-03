/****************************************************************************
 * Copyright (C) 2015 Dimok
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/
#pragma once

#include <gui/GuiElement.h>
#include <gui/GuiTextureData.h>
#include <gui/video/SDL_FontCache.h>
#include <gui/GuiImage.h>
#include <gui/GuiFont.h>
#include <mutex>
#include <SDL2/SDL_ttf.h>

//!Display, manage, and manipulate text in the GUI
class GuiText : public GuiElement {
public:
    //!\param t Text
    explicit GuiText(const std::string &t);

    //!\param t Text
    //!\param s Font size
    GuiText(const std::string &t, int32_t s);

    //!\param t Text
    //!\param s Font size
    //!\param c Font color
    GuiText(const std::string &t, int32_t s, SDL_Color c);

    //!\param t Text
    //!\param s Font size
    //!\param c Font color
    //!\param font Font
    GuiText(const std::string &t, int32_t s, SDL_Color c, GuiFont *font);

    ~GuiText() override;

    void draw(Renderer *pVideo) override;

    void process() override;

    void setMaxWidth(float width);

    static void setPresetFont(GuiFont *f);

    static void setPresets(int32_t sz, const SDL_Color & c);

    void setFontSize(int32_t size);

protected:
    GuiImage texture;
    GuiTextureData *textureData = nullptr;

    std::string text;
    SDL_Color color;
    FC_Font *fc_font = nullptr;
    bool doUpdateTexture = true;

    uint16_t maxWidth = 0xFFFF;

    void updateSize();

    void updateTexture(Renderer *renderer);

    GuiFont *gFont = nullptr;

    static GuiFont *presetFont;
    static SDL_Color presetColor;
    static int32_t presetSize;
};
