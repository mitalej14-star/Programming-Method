#include "tetromino.h"
#include "rotation_shapes.h"
#include <iostream>

const int W = 10;
const int H = 20;

// class Tetromino
Tetromino::Tetromino(Shape shape) : shape_(shape) {
    initTetromino();
}
Tetromino::~Tetromino() {}

void Tetromino::initTetromino() {
    shapeNow_ = RotationShapes[0][shape_];
    setPosition(4, 0);
    rotationState_ = 0;
    color_ = Colors[shape_];
    isTSRS = false;
}


void Tetromino::rotateCCW() {
    rotationState_ = (4 + --rotationState_) % 4;
    shapeNow_ = RotationShapes[rotationState_][shape_];
}
void Tetromino::rotateCW() {
    rotationState_ = (++rotationState_) % 4;
    shapeNow_ = RotationShapes[rotationState_][shape_];
}
void Tetromino::moveLeft() {
    x_--;
}
void Tetromino::moveRight() {
    x_++;
}
void Tetromino::moveDown() {
    y_++;
}
void Tetromino::moveUp() {
    y_--;
}

// set
void Tetromino::setPosition(int x, int y) {x_ = x; y_ = y;}
void Tetromino::setColor(Color color) {color_ = color;}

// get
Shape Tetromino::getShape() const {return shape_;}
const std::array<std::array<int,4>,4>& Tetromino::getCurrentMatrix() const {return shapeNow_;}
int Tetromino::getRotationState() const {return rotationState_;}
int Tetromino::getX() const {return x_;}
int Tetromino::getY() const {return y_;}
Color Tetromino::getColor() const {return color_;}

// operator overloading
bool operator==(const Tetromino& tet1, const Tetromino& tet2) {
    return (tet1.shapeNow_ == tet2.shapeNow_) && (tet1.x_ == tet2.x_) && (tet1.y_ == tet2.y_);
}
bool operator!=(const Tetromino& tet1, const Tetromino& tet2) {
    return !(tet1 == tet2);
}


//derived classes--------------------------------------------------------------------------------------
//Tetromino_I() : Tetromino(I) {}
//~Tetromino_I() {}