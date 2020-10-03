#ifndef _JULIASET_H_
#define _JULIASET_H_
#include "ComplexFractal.h"

class JuliaSet : public ComplexFractal {

public:
    // Default constructor
    JuliaSet( );
    // Constructor with specified parameters
    JuliaSet( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y, const double& a, const double& b );
    // Destructor
    virtual ~JuliaSet( );
    // Returns the a parameter for the Julia set
    double getA( ) const;
    // Returns the b parameter for the Julia set
    double getB( ) const;
    // Sets a and b Julia set parameters (must be between -2.0 and 2.0 inclusive)
    void setParameters( const double& a, const double& b );
    // Calculate the next escape point after (x0, y0) and store in (x1, y1)
    virtual void calculateNextPoint( const double x0, const double y0, double& x1, double &y1 ) const;
    // Calculate number of iterations required for (x0, y0) to escape.
    int calculatePlaneEscapeCount( const double& x0, const double& y0 ) const;
    // Calculate number of iterations required for (row, column) to escape
    virtual int calculateNumber( const int& row, const int& column ) const;


private:
    // The a parameter for the Julia set
    double mA;
    // The b parameter for the Julia set
    double mB;

};

#endif