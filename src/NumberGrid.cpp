#include <vector>
#include "NumberGrid.h"

NumberGrid::NumberGrid( ) 
: mHeight(300), mWidth(400), mMax_value(255), mValues(std::vector<int>(300 * 400)) {

}

NumberGrid::NumberGrid( const int& height, const int& width ) 
: mHeight(height), mWidth(width), mMax_value(255), mValues(std::vector<int>(height * width)) {
    
}

int NumberGrid::getHeight( ) const {
    return this->mHeight;
}

int NumberGrid::getWidth( ) const {
    return this->mWidth;
}

int NumberGrid::getMaxNumber( ) const {
    return this->mMax_value;
}

void NumberGrid::setGridSize( const int& height, const int& width ) {
    if (height >= 2 && width >= 2) {
        this->mHeight = height;
        this->mWidth = width;
        this->mValues = std::vector<int>(height * width);
    }
}

void NumberGrid::setMaxNumber( const int& number ) {
    if(number >= 0) {
        this->mMax_value = number;
    }
}

const std::vector< int >& NumberGrid::getNumbers( ) const {
    return this->mValues;
}

int NumberGrid::index( const int& row, const int& column ) const {
    return (row * this->mWidth) + column;
}

bool NumberGrid::indexValid( const int& row, const int& column ) const {
    if (row < 0 || row >= this->mHeight) {
        return false;
    }
    if (column < 0 || column >= this->mWidth) {
        return false;
    }
    return true;
}

bool NumberGrid::numberValid( const int& number ) const {
    return (number >= 0 && number <= this->mMax_value);
}

int NumberGrid::getNumber( const int& row, const int& column ) const {
    return indexValid(row, column) ? this->mValues[index(row, column)] : -1;
}

void NumberGrid::setNumber( const int& row, const int& column, const int& number ) {
    if(indexValid(row, column) && numberValid(number)) {
        this->mValues[index(row, column)] = number;
    }
}

void NumberGrid::setPPM( PPM& ppm ) const {
    ppm.setHeight(this->mHeight);
    ppm.setWidth(this->mWidth);
    ppm.setMaxColorValue(63);

    // table formula
    for (int row = 0; row < this->mHeight; row++) {
        for (int col = 0; col < this->mWidth; col++) {
            int num = getNumber(row, col);

            if (num == 0) {
                ppm.setPixel(row, col, 0, 0, 0);
            }
            else if (num == this->mMax_value) {
                ppm.setPixel(row, col, 63, 31, 31);
            }
            else if (num % 8 == 0) {
                ppm.setPixel(row, col, 63, 63, 63);
            }
            else if (num % 8 == 1) {
                ppm.setPixel(row, col, 63, 31, 31);
            }
            else if (num % 8 == 2) {
                ppm.setPixel(row, col, 63, 63, 31);
            }
            else if (num % 8 == 3) {
                ppm.setPixel(row, col, 31, 63, 31);
            }
            else if (num % 8 == 4) {
                ppm.setPixel(row, col, 0, 0, 0);   
            }
            else if (num % 8 == 5) {
                ppm.setPixel(row, col, 31, 63, 63);
            }
            else if (num % 8 == 6) {
                ppm.setPixel(row, col, 31, 31, 63);
            }
            else if (num % 8 == 7) {
                ppm.setPixel(row, col, 63, 31, 63);
            }   
        }
    }
}

// ASSIGNMENT 8

NumberGrid::~NumberGrid( ) {

}

void NumberGrid::calculateAllNumbers( ) {
    for (int row = 0; row < this->mHeight; row++) {
        for (int col = 0; col < this->mWidth; col++) {
            setNumber(row, col, calculateNumber(row, col));
        }
    }
}

// ASSIGNMENT 10

void NumberGrid::setPPM( PPM& ppm, const ColorTable& colors ) const {
    if (colors.getNumberOfColors() >= 3) {
        ppm.setWidth(this->mWidth);
        ppm.setHeight(this->mHeight);
        ppm.setMaxColorValue(colors.getMaxChannelValue());

        for (int row = 0; row < this->mHeight; row++) {
            for (int col = 0; col < this->mWidth; col++) {
                int num = this->mValues[index(row, col)];
                Color c;
                if (num == 0) {
                    c = colors[colors.getNumberOfColors() - 2];
                }
                else if (num == this->mMax_value) {
                    c = colors[colors.getNumberOfColors() - 1];
                }
                else {
                    c = colors[num % (colors.getNumberOfColors() - 2)];
                }

                for (size_t channel = 0; channel < 3; channel++)
                {
                    ppm.setChannel(row, col, channel, c.getChannel(channel));
                }
                
            }
        }
    } 
}

// EXAM 3

ManhattanNumbers::ManhattanNumbers( ) 
: NumberGrid(600, 800) {

}

ManhattanNumbers::ManhattanNumbers(const int& height, const int& width)
: NumberGrid(height, width) {

}

ManhattanNumbers::~ManhattanNumbers( ) {

}

int ManhattanNumbers::calculateNumber( const int& row, const int& column ) const {
    int centerX = this->getWidth()/2;
    int centerY = this->getHeight()/2;

    int x = abs(centerX - column);
    int y = abs(centerY - row);

    return x + y;
}
