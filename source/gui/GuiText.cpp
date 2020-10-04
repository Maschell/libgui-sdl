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
#include <cstdarg>
#include <SDL2/SDL_surface.h>
#include <gui/GuiText.h>

GuiFont *GuiText::presetFont = nullptr;
int32_t GuiText::presetSize = 28;
SDL_Color GuiText::presetColor = (SDL_Color) {
        255, 255, 255, 255
};

GuiText::GuiText(const std::string &t)
        : GuiText(t, presetSize) {
}

GuiText::GuiText(const std::string &t, int32_t s)
        : GuiText(t, s, presetColor) {
}

GuiText::GuiText(const std::string &t, int32_t s, SDL_Color c)
        : GuiText(t, s, c, presetFont) {
}

GuiText::GuiText(const std::string &text, int32_t size, SDL_Color c, GuiFont *gFont) :
        text(text),
        color(c) {
    this->gFont = gFont;
    this->fc_font = gFont->getFont(size);
    this->doUpdateTexture = true;
    this->texture.setParent(this);
    this->updateSize();
}

GuiText::~GuiText() {
    delete textureData;
}

void GuiText::setFontSize(int32_t size) {
    this->fc_font = this->gFont->getFont(size);
    updateSize();
    this->doUpdateTexture = true;
}

void GuiText::setMaxWidth(float width) {
    this->maxWidth = width;

    // Rebuild the texture cache on next draw
    updateSize();
    doUpdateTexture = true;
}

void GuiText::updateSize() {
    auto height = FC_GetColumnHeight(fc_font, maxWidth, text.c_str());
    auto width = FC_GetWidth(fc_font, text.c_str());
    width = width > maxWidth ? maxWidth : width;
    this->setSize(width, height);
}

void GuiText::updateTexture(Renderer *renderer) {
    if(doUpdateTexture) {
        updateSize();
        int tex_width = width == 0 ? 1 : (int) width;
        int tex_height = height == 0 ? 1 : (int)height;

        SDL_Texture *temp = SDL_CreateTexture(renderer->getRenderer(), renderer->getPixelFormat(), SDL_TEXTUREACCESS_TARGET, tex_width, tex_height);
        if (temp) {
            texture.setTexture(nullptr);
            delete textureData;
            textureData = new GuiTextureData(temp);
            textureData->setBlendMode(SDL_BLENDMODE_BLEND);
            texture.setTexture(textureData);

            // Set render target to texture
            SDL_SetRenderTarget(renderer->getRenderer(), temp);

            // Clear texture.
            SDL_SetRenderDrawColor(renderer->getRenderer(), 0, 0, 0, 0);
            SDL_RenderClear(renderer->getRenderer());

            // Draw text to texture
            FC_DrawColumnColor(fc_font, renderer->getRenderer(), 0, 0, maxWidth, color, text.c_str());

            // Restore render target
            SDL_SetRenderTarget(renderer->getRenderer(), nullptr);
        } else {
            LG_Log("Failed to create texture");
        }
        doUpdateTexture = false;
    }
}

void GuiText::draw(Renderer *renderer) {
    if (!this->isVisible()) {
        return;
    }

    updateTexture(renderer);

    texture.draw(renderer);
}

void GuiText::process() {
    GuiElement::process();
}

void GuiText::setPresets(int32_t sz, const SDL_Color &c) {
    GuiText::presetSize = sz;
    GuiText::presetColor = c;
}

void GuiText::setPresetFont(GuiFont *f) {
    GuiText::presetFont = f;
}
