#pragma once

struct Input {
    unsigned char mousebuffer[256] = {0};
    int mouseX;
    int mouseY;
    int screenW;
    int screenH;
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
}
