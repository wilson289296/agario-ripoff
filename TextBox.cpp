#include "TextBox.h"
#include <iostream>

TextBox::TextBox(
        const char* text,
        float x,
        float y,
        void* font,
        float r,
        float g,
        float b,
        int width
    ):

    Shape(),
    text(text),
    x(x),
    y(y),
    font(font),
    r(r),
    g(g),
    b(b),
    width(width)
    {}

void TextBox::draw() const {
    glColor3f(r, g, b);
    float offset = 0;
    for (int i = 0; i < text.length(); i++) {
        glRasterPos2f(x+offset, y);
        glutBitmapCharacter(font, text[i]);
        int w = glutBitmapWidth(font, text[i]);
        offset += ((float)w / width)*2;
    }
}

void TextBox::setText(std::string temp){
	text = temp;
}
void TextBox::setX(float newX){
	x = newX;
}
void TextBox::setY(float newY){
	y = newY;
}
void TextBox::setR(float newR){
	r = newR;
}
void TextBox::setG(float newG){
	g = newG;
}
void TextBox::setB(float newB){
	b = newB;
}
float TextBox::getX(){
	return x;
}
float TextBox::getY(){
	return y;
}
float TextBox::getR(){
	return r;
}
float TextBox::getG(){
	return g;
}
float TextBox::getB(){
	return b;
}
