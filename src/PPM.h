#ifndef _PPM_H_
#define _PPM_H_
#include <iostream>
#include <vector>

// A class to represent images in portable pixmap format
class PPM {

public:
    // Default constructor
    PPM();
    // Constructor with height and width
    PPM(const int& height, const int& width);
    // Returns height of image
    int getHeight() const;
    // Returns width of image
    int getWidth() const;
    // Returns the max color value for this image
    int getMaxColorValue() const;
    // Returns color channel value for specified row and column
    // Red = 0, Green = 1, Blue = 2
    int getChannel(const int& row, const int& column, const int& channel) const;
    // Returns true if specificied parameters are valid
    bool indexValid(const int& row, const int& column, const int& channel) const;
    // Returns the index into the one dimensional vector of pixel channels
    int index(const int& row, const int& column, const int& channel) const;
    // Returns true if the value is within legal range [0, max_color_value]
    bool valueValid(const int& value) const;
    // Sets the height of the image
    // Must be non-negative
    void setHeight(const int& height);
    // Sets the width of the image
    // Must be non-negative
    void setWidth(const int& width);
    // Sets the max color value of the image [0, 255]
    void setMaxColorValue(const int& max_color_value);
    // Sets color channel value at specified row and column [0, max_color_value]
    // Red = 0, Green = 1, Blue = 2
    void setChannel(const int& row, const int& column, const int& channel, const int& value);
    // Sets pixel color at specified row and column [0, max_color_value]
    void setPixel(const int& row, const int& column, const int& red, const int& green, const int& blue);

    // EXAM 1

    // Sets all pixels in the given row to the specified color
    void setRow(const int& row, const int& red, const int& green, const int& blue);

    // ASSIGNMENT 4

    // Create gray values from specific channel
    void grayFromChannel( PPM& dst, const int& src_channel ) const;
    // Create gray values from red channel
    void grayFromRed( PPM& dst ) const;
    // Create gray values from green channel
    void grayFromGreen( PPM& dst ) const;
    // Create gray values from blue channel
    void grayFromBlue( PPM& dst ) const;
    // Calculates the linear colorimetric value for the pixel at row, column, and returns it.
    double linearColorimetricPixelValue( const int& row, const int& column ) const;
    // Sets all pixels to have gray value as calculated by linear colorimetric formula for corresponding pixels
    void grayFromLinearColorimetric( PPM& dst ) const;

    // ASSIGNMENT 5

    // Returns true if the PPMs have the same number of pixels
    bool operator==( const PPM& rhs ) const;
    // Returns true if the PPMs have a different number of pixels
    bool operator!=( const PPM& rhs ) const;
    // Returns true if *this has less pixels than rhs
    bool operator<( const PPM& rhs ) const;
    // Returns true if *this has less than or an equal number of pixels as rhs
    bool operator<=( const PPM& rhs ) const;
    // Returns true if *this has more pixels than rhs
    bool operator>( const PPM& rhs ) const;
    // Returns true if *this has more than or an equal number of pixels as rhs
    bool operator>=( const PPM& rhs ) const;
    // Adds the channel values from rhs into the channel values for *this
    PPM& operator+=( const PPM& rhs );
    // Subtracts the channel values from rhs from the channel values for *this
    PPM& operator-=( const PPM& rhs );
    // Multiplies the channel values of *this by the double rhs
    PPM& operator*=( const double& rhs );
    // Divides the channel values of *this by the double rhs
    PPM& operator/=( const double& rhs );
    // Modulo the channel values of *this by the double rhs
    PPM& operator%=( const int& rhs );
    // Creates a new PPM with identical meta data as *this with channel values of the sum of *this and rhs
    PPM operator+( const PPM& rhs ) const;
    // Creates a new PPM with identical meta data as *this with channel values of *this minus rhs
    PPM operator-( const PPM& rhs ) const;
    // Creates a new PPM with identical meta data as *this with channel values of *this multiplied by double rhs
    PPM operator*( const double& rhs ) const;
    // Creates a new PPM with identical meta data as *this with channel values of *this divided by double rhs
    PPM operator/( const double& rhs ) const;
    // Creates a new PPM with identical meta data as *this with channel values of the remainder of *this divided by rhs
    PPM operator%( const int& rhs ) const;

    // ASSIGNMENT 6

    // Uses the linearColorimetricPixelValue of the two pixels. If the difference is at least {threshold}% of the maximum color value, returns the maximum color value. Otherwise, returns 0. Used by the find*Edges methods.
    int edgePixelValue( const int& row1, const int& column1, const int& row2, const int& column) const;
    // Sets dst to have the same meta data as the current PPM object. Then sets each pixel to the correct value using the edgePixelValue method.
    void findVerticalEdges( PPM& dst) const;
    // Sets dst to have the same meta data as the current PPM object. Then sets each pixel to the correct value using the edgePixelValue method.
    void findHorizontalEdges( PPM& dst) const; 
    // Sets dst to have the same meta data as the current PPM object. Then sets each pixel to the correct value using the edgePixelValue method.
    void findDiagonalEdges( PPM& dst) const;

    // Optional threshold values

    int edgePixelValue( const int& row1, const int& column1, const int& row2, const int& column2, const double& threshold ) const;
    void findVerticalEdges( PPM& dst, const double& threshold ) const;
    void findHorizontalEdges( PPM& dst, const double& threshold ) const; 
    void findDiagonalEdges( PPM& dst, const double& threshold ) const;


    // EXAM 2

    // Swap red, green, and blue values
    void rotateColorFilter( PPM& dst ) const;

    // EXAM 4

    // Anti-aliasing
    void antiAlias(const int& n, PPM& dst) const;

private:
    int mHeight;
    int mWidth;
    int mMax_color_value;
    // The one dimensional vector of pixel channels
    std::vector<int> mPixels;
};

// Writes the image data into PPM format
std::ostream& operator<<(std::ostream& os, const PPM& rhs);
// Reads an image into a PPM object
std::istream& operator>>(std::istream& is, PPM& rhs);

#endif 