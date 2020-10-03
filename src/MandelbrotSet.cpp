#include <cmath>
#include "MandelbrotSet.h"

MandelbrotSet::MandelbrotSet( ) 
: ComplexFractal() {

}

MandelbrotSet::MandelbrotSet( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y)
: ComplexFractal(height, width, min_x, max_x, min_y, max_y) {

}

MandelbrotSet::~MandelbrotSet( ) {

}

void MandelbrotSet::calculateNextPoint( const double x0, const double y0, const double& a, const double& b, double& x1, double &y1 ) const {
    x1 = x0*x0 - y0*y0 + a;
    y1 = 2*x0*y0 + b;
}

int MandelbrotSet::calculatePlaneEscapeCount( const double& a, const double& b ) const {
    int count = 0;
    double x1,y1;
    double x2, y2;

    calculateNextPoint(0, 0, a, b, x1, y1);
    
    while ((x1*x1 + y1*y1) <= 4 && count < this->getMaxNumber()) {
        count++;

        calculateNextPoint(x1, y1, a, b, x2, y2);
        x1 = x2;
        y1 = y2;
    }

    return count;
}

int MandelbrotSet::calculateNumber( const int& row, const int& column ) const {
    if (row >= 0 && row < this->getHeight() && column >= 0 && column < this->getWidth()) {
        return this->calculatePlaneEscapeCount(this->calculatePlaneXFromPixelColumn(column), this->calculatePlaneYFromPixelRow(row));
    }
    else {
        return -1;
    }
}
