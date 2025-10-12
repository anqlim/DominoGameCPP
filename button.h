#ifndef BUTTON_H
#define BUTTON_H
#include <string>
#include "raylib.h"
#include "parameters.h"

class Button {
private:
    Rectangle rec;
    Color color;
    std::string text;
    Color textColor;
public:
    Button(Rectangle _rec, Color _color, const std::string& _text, Color _textColor);
    bool isClicked(float mouseX, float mouseY);
    void draw();
};

#endif
