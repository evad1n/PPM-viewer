#include <random>
#include <algorithm>
#include <iostream>
#include "ColorTable.h"

// COLOR CLASS

Color::Color( ) 
: mRed(0), mGreen(0), mBlue(0) {

}

Color::Color( const int& red, const int& green, const int& blue ) 
: mRed(red), mGreen(green), mBlue(blue) {

}

int Color::getRed( ) const {
    return this->mRed;
}

int Color::getGreen( ) const {
    return this->mGreen;
}

int Color::getBlue( ) const {
    return this->mBlue;
}

int Color::getChannel( const int& channel ) const {
    switch (channel)
    {
    case 0:
        return this->mRed;
        break;
    case 1:
        return this->mGreen;
        break;
    case 2:
        return this->mBlue;
        break;
    
    default:
        return -1;
        break;
    }
}

void Color::setRed( const int& value ) {
    if (value >= 0) {
        this->mRed = value;
    }
}

void Color::setGreen( const int& value ) {
    if (value >= 0) {
        this->mGreen = value;
    }
}

void Color::setBlue( const int& value ) {
    if (value >= 0) {
        this->mBlue = value;
    }
}

void Color::setChannel( const int& channel, const int& value ) {
    if (value < 0) {
        return;
    }

    switch (channel)
    {
    case 0:
        this->mRed = value;
        break;
    case 1:
        this->mGreen = value;
        break;
    case 2:
        this->mBlue = value;
        break;
    
    default:
        break;
    }
}

void Color::invert( const int& max_color_value ) {
    if (max_color_value >= this->mRed && max_color_value >= this->mGreen && max_color_value >= this->mBlue) {
        this->mRed = max_color_value - this->mRed;
        this->mGreen = max_color_value - this->mGreen;
        this->mBlue = max_color_value - this->mBlue;
    }
}

bool Color::operator==( const Color& rhs ) const {
    return this->mRed == rhs.getRed() && this->mGreen == rhs.getGreen() && this->mBlue == rhs.getBlue();
}

std::ostream& operator<<( std::ostream& os, const Color& color ) {
    os << color.getRed() << ":" << color.getGreen() << ":" << color.getBlue();
    return os;
} 



// -------------------------- COLOR TABLE CLASS --------------------------------

ColorTable::ColorTable( const size_t& num_color ) 
: mColors(std::vector<Color>(num_color)) {

}

size_t ColorTable::getNumberOfColors( ) const {
    return this->mColors.size();
}

void ColorTable::setNumberOfColors( const size_t& num_color ) {
    this->mColors = std::vector<Color>(num_color);
}

const Color& ColorTable::operator[]( const int& i ) const {
    static Color ec( -1, -1, -1 );
    if (i >= 0 && i < (int)this->mColors.size()) {
        return this->mColors[i];
    }
    else {
        static Color c(-1, -1, -1);
        c = ec;
        return c;
    }
}

Color& ColorTable::operator[]( const int& i ) {
    static Color ec( -1, -1, -1 );
    if (i >= 0 && i < (int)this->mColors.size()) {
        return this->mColors[i];
    }
    else {
        static Color c(-1, -1, -1);
        c = ec;
        return c;
    }
}

void ColorTable::setRandomColor( const int& max_color_value, const size_t& position ) {
    if (max_color_value >= 0 && (int)position >= 0 && position < this->mColors.size()) {
        for (size_t i = 0; i < 3; i++)
        {
            this->mColors[position].setChannel(i, std::rand() % (max_color_value + 1));
        }
    }
}

void ColorTable::insertGradient( const Color& color1, const Color& color2, const size_t& position1, const size_t& position2 ) {
    if (position1 < position2 && position1 < this->mColors.size() && position2 < this->mColors.size()) {
        for (size_t i = position1; i <= position2; i++)
        {                
            double percent = ((double)(i - position1) / (double)(position2 - position1));
            for (size_t j = 0; j < 3; j++)
            {
                int val = ((color2.getChannel(j) - color1.getChannel(j)) * percent) + color1.getChannel(j);
                
                this->mColors[i].setChannel(j, val);
            }
        }
        
    }
}

int ColorTable::getMaxChannelValue( ) const {
    int max = -1;
    for (size_t i = 0; i < this->mColors.size(); i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            if (this->mColors[i].getChannel(j) > max) {
                max = this->mColors[i].getChannel(j);
            }
        }
    }
    return max;
}

// EXAM 3

void ColorTable::insertInvertedGradient( const Color& color1, const size_t& position1, const size_t& position2 ) {
    Color invertedColor = color1;
    invertedColor.invert(255);

    this->insertGradient(color1, invertedColor, position1, position2);
}
