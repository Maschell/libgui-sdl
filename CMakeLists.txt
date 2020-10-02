cmake_minimum_required(VERSION 3.17)
project(gui-sdl)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)
include_directories(include/gui-sdl)

add_library(${PROJECT_NAME}
        include/gui-sdl/gui/GuiButton.h
        include/gui-sdl/gui/GuiController.h
        include/gui-sdl/gui/GuiElement.h
        include/gui-sdl/gui/GuiFrame.h
        include/gui-sdl/gui/GuiImage.h
        include/gui-sdl/gui/GuiSound.h
        include/gui-sdl/gui/GuiText.h
        include/gui-sdl/gui/GuiTextureData.h
        include/gui-sdl/gui/GuiTrigger.h
        include/gui-sdl/gui/sigslot.h
        include/gui-sdl/gui/input/SDLController.h
        include/gui-sdl/gui/input/SDLControllerMouse.h
        include/gui-sdl/gui/input/SDLControllerWiiUGamepad.h
        include/gui-sdl/gui/input/SDLControllerXboxOne.h
        include/gui-sdl/gui/input/SDLControllerJoystick.h
        include/gui-sdl/gui/input/SDLControllerWiiUProContoller.h
        include/gui-sdl/gui/video/SDL_FontCache.h
        include/gui-sdl/gui/video/Renderer.h
        include/gui-sdl/gui/system/libgui_log.h
        include/gui-sdl/gui/system/SDLSystem.h
        source/gui/GuiButton.cpp
        source/gui/GuiElement.cpp
        source/gui/GuiFrame.cpp
        source/gui/GuiImage.cpp
        source/gui/GuiSound.cpp
        source/gui/GuiText.cpp
        source/gui/GuiTextureData.cpp
        source/gui/GuiTrigger.cpp
        source/gui/input/ControllerManager.cpp
        source/gui/system/SDLSystem.cpp
        source/gui/video/SDL_FontCache.cpp
        )
