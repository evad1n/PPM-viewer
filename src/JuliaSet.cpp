#include <cmath>
#include "JuliaSet.h"

JuliaSet::JuliaSet( ) 
: ComplexFractal(), mA(-0.650492), mB(-0.478235) {

}

JuliaSet::JuliaSet( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y, const double& a, const double& b )
: ComplexFractal(height, width, min_x, max_x, min_y, max_y), mA(a), mB(b) {

}

JuliaSet::~JuliaSet( ) {

}

double JuliaSet::getA( ) const {
    return this->mA;
}

double JuliaSet::getB( ) const {
    return this->mB;
}

void JuliaSet::setParameters( const double& a, const double& b ) {
    if(a >= -2.0 && a <= 2.0 && b >= -2.0 && b <= 2.0) {
        this->mA = a;
        this->mB = b;
    }
}

void JuliaSet::calculateNextPoint( const double x0, const double y0, double& x1, double &y1 ) const {
    x1 = x0*x0 - y0*y0 + this->mA;
    y1 = 2*x0*y0 + this->mB;
}

int JuliaSet::calculatePlaneEscapeCount( const double& x0, const double& y0 ) const {
    int count = 0;
    double x1,y1;
    double x2, y2;

    x1 = x0;
    y1 = y0;
    
    while ((x1*x1 + y1*y1) <= 4 && count < this->getMaxNumber()) {
        count++;

        calculateNextPoint(x1, y1, x2, y2);
        x1 = x2;
        y1 = y2;
    }

    return count;
}

int JuliaSet::calculateNumber( const int& row, const int& column ) const {
    if (row >= 0 && row < this->getHeight() && column >= 0 && column < this->getWidth()) {
        return this->calculatePlaneEscapeCount(this->calculatePlaneXFromPixelColumn(column), this->calculatePlaneYFromPixelRow(row));
    }
    else {
        return -1;
    }
}
