#ifndef _MANDELBROTSET_H_
#define _MANDELBROTSET_H_
#include "ComplexFractal.h"

class MandelbrotSet : public ComplexFractal {

public:
    // Default constructor
    MandelbrotSet( );
    // Constructor with specified parameters
    MandelbrotSet( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y);
    // Destructor
    virtual ~MandelbrotSet( );
    // Calculate the next escape point after (x0, y0) and store in (x1, y1)
    virtual void calculateNextPoint( const double x0, const double y0, const double& a, const double& b, double& x1, double &y1 ) const;
    // Calculate number of iterations required for (a, b) to escape.
    int calculatePlaneEscapeCount( const double& a, const double& b ) const;
    // Calculate number of iterations required for (row, column) to escape
    virtual int calculateNumber( const int& row, const int& column ) const;

};

#endif