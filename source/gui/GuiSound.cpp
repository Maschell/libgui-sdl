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
#include <gui/GuiSound.h>

GuiSound::GuiSound(void *buffer, uint32_t filesize, bool freeSrc) {
    LoadBuffer(buffer, filesize, freeSrc);
}

GuiSound::GuiSound(const char *filepath) {
    Load(filepath);
}

GuiSound::~GuiSound() {
    Cleanup();
}

void GuiSound::Cleanup() {
    if (music) {
        Mix_FreeChunk(music);
        music = nullptr;
    }
}

bool GuiSound::Load(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if(file != NULL) {
        off_t i = ftello(file);
        if(fseek(file, 0, SEEK_END) == 0) {
            off_t size = ftello(file);
            if(size != -1) {
                void *buffer = malloc(size);
                if(buffer != NULL) {
                    fseeko(file, i, SEEK_SET);
                    if(fread(buffer, size, 1, file) == 1)
                        return LoadBuffer(buffer, size, true);

                    free(buffer);
                }
            }
        }

        fclose(file);
    }

    return false;
}

bool GuiSound::LoadBuffer(void *buffer, uint32_t size, bool freeSrc) {
    Cleanup();
    SDL_RWops *rw = SDL_RWFromMem(buffer, size);
    music = Mix_LoadWAV_RW(rw, freeSrc);
    return music != nullptr;
}

void GuiSound::Play() {
    if (music) {
        playedOn = Mix_PlayChannel(-1, music, loops);
    }
}

void GuiSound::Stop() const {
    Pause();
}

void GuiSound::Pause() const {
    if (playedOn != -1) {
        Mix_HaltChannel(playedOn);
    }
}

void GuiSound::Resume() {
    Play();
}

bool GuiSound::IsPlaying() const {
    if (playedOn == -1) {
        return false;
    }
    return Mix_Playing(playedOn);
}

void GuiSound::SetVolume(uint32_t vol) const {
    if (music) { Mix_VolumeChunk(music, vol); }
}

void GuiSound::SetLoop(bool l) {
    // < 0 == infinitive loop
    loops = l ? -1 : 1;
}

void GuiSound::Rewind() const {
    // TODO: how to rewind?
    Stop();
}
