#pragma once

struct Input {
    SDL_Event mainevent;
    unsigned char mousebuffer[256] = {0};
    int mouseX;
    int mouseY;
    int my;
    int mx;
    int screenW;
    int screenH;
    float camspeed = 0.5f;
    float rotspeed = 0.01f;
    unsigned char keybuffer[256] = {0}; // 0b00000000 is the binary representation. The last byte
                                        // is "clicked", the second to last is "pressed", the third
                                        // to last is "released"
    bool Clicked(unsigned char key);
    bool Pressed(unsigned char key);
    bool Released(unsigned char key);
    bool MouseClicked(unsigned char button);
    bool MousePressed(unsigned char button);
    bool MouseReleased(unsigned char button);

    void GetInput();
    void CheckEvents();
};
