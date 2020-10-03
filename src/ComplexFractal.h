#ifndef _COMPLEXFRACTAL_H_
#define _COMPLEXFRACTAL_H_
#include "ThreadedGrid.h"

class ComplexFractal : public ThreadedGrid
{

public:
    // Default constructor
    ComplexFractal();
    // Constructor with specified parameters
    ComplexFractal(const int &height, const int &width, const double &min_x, const double &max_x, const double &min_y, const double &max_y);
    // Destructor
    virtual ~ComplexFractal();
    // Returns the minimum X value for the plane
    double getMinX() const;
    // Returns the maximum X value for the plane
    double getMaxX() const;
    // Returns the minimum Y value for the plane
    double getMinY() const;
    // Returns the maximum Y value for the plane
    double getMaxY() const;
    // Overrides NumberGrid
    // Only make changes if height and width >= 2
    virtual void setGridSize(const int &height, const int &width);
    // Sets plane coordinates (must be between -2.0 and 2.0 inclusive)
    void setPlaneSize(const double &min_x, const double &max_x, const double &min_y, const double &max_y);
    // Returns the vertical delta value
    double getDeltaX() const;
    // Returns the horizontal delta value
    double getDeltaY() const;
    // Sets the delta data members (must be positive)
    void setDeltas(const double &delta_x, const double &delta_y);
    // Calculate the vertical plane distance between neighboring pixel rows
    double calculateDeltaX() const;
    // Calculate the horizontal plane distance between neighboring pixel columns
    double calculateDeltaY() const;
    // Calculate the plane y value for a given row
    // Return 0 if row is out of range
    double calculatePlaneYFromPixelRow(const int &row) const;
    // Calculate the plane x value for a given column
    // Return 0 if column is out of range
    double calculatePlaneXFromPixelColumn(const int &column) const;
    // Sets x and y to the plane coordinates for the row and column
    void calculatePlaneCoordinatesFromPixelCoordinates(const int &row, const int &column, double &x, double &y) const;

    // EXAM 3

    // This method calculates new values for minimum and maximum x and y, and calls setPlaneSize(), as described above.
    void zoomPlane(const double &zoom_factor);

    // ASSIGNMENT 13

    // Add this method to the class. It has the same behavior as setPlaneSize, except that it does not force the plane coordinates to be between -2.0 and 2.0.
    void setPlaneSizeNoLimits(const double &min_x, const double &max_x, const double &min_y, const double &max_y);

private:
    // Minimum X value for plane coordinates
    double mMinX;
    // Maximum X value for plane coordinates
    double mMaxX;
    // Minimum Y value for plane coordinates
    double mMinY;
    // Maximum Y value for plane coordinates
    double mMaxY;
    // Horizontal delta value
    double mDeltaX;
    // Vertical delta value
    double mDeltaY;
};

#endif
