#include "button.h"

Button::Button(Rectangle _rec, Color _color, const std::string& _text, Color _textColor):
rec(_rec), color(_color), text(_text), textColor(_textColor){
    rec.y = WINDOW_HEIGHT - rec.y;
}

bool Button::isClicked(float mouseX, float mouseY){
    return (mouseX >= rec.x && mouseX <= rec.x + rec.width) && (mouseY >= rec.y && mouseY <= rec.y + rec.height);
}

std::tuple<int, int, int> buttonTextSize(int width, int height, int textLen){
    int size = (float)width / (textLen + 2) * 2;
    int x = size / 2;
    int y = (float)(height - size) / 2;
    return {x, y, size};
}

void Button::draw(){
    DrawRectangle(rec.x, rec.y, rec.width, rec.height, color);
    DrawRectangleLines(rec.x, rec.y, rec.width, rec.height, textColor);
    auto [x, y, size] = buttonTextSize(rec.width, rec.height, text.length());
    DrawText(text.data(), x + rec.x, y + rec.y, size, textColor);
}
