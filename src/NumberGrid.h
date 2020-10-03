#ifndef _NUMBERGRID_H_
#define _NUMBERGRID_H_
#include <vector>
#include "PPM.h"
#include "ColorTable.h"

// A class to represent a two-dimensional grid of values
class NumberGrid {

    public:
        // Default contrsuctor
        NumberGrid( );
        // Constructor with specified height and width
        NumberGrid( const int& height, const int& width );
        // Returns the height of the number grid
        int getHeight( ) const;
        // Returns the width of the number grid
        int getWidth( ) const;
        // Returns the maximum value allowed in the number grid
        int getMaxNumber( ) const;
        // Sets height and width of number grid and resizes the storage
        // Only accepts height and width values of at least 2
        virtual void setGridSize( const int& height, const int& width );
        // Sets the maximum allowed value in the number grid
        // Only accepts values of at least 0
        void setMaxNumber( const int& number );
        // Returns a reference to the vector of grid values
        const std::vector< int >& getNumbers( ) const;
        // Returns the index into the grid values using the formula:
        // index = (row * width) + column
        int index( const int& row, const int& column ) const;
        // Returns true if row and column are within range of the number grid
        bool indexValid( const int& row, const int& column ) const;
        // Returns true if the number is non-negative and no larger than the maximum value allowed
        bool numberValid( const int& number ) const;
        // Returns a number from the grid at the position specified.
        // If not valid then returns -1
        int getNumber( const int& row, const int& column ) const;
        // Sets a number in the grid at the position specified
        // Only makes a change if position and number are valid
        void setNumber( const int& row, const int& column, const int& number );
        // Configures metadata of PPM to match height and width of number grid
        // Sets maximum color value to 63
        // Sets each pixel value according to table...
        void setPPM( PPM& ppm ) const;

        // ASSIGNMENT 8

        // Destructor
        virtual ~NumberGrid( );
        // Pure virtual
        virtual int calculateNumber( const int& row, const int& column ) const = 0;
        // For every (row, column) pair, runs calculateNumber to get a number and setNumber to store it
        virtual void calculateAllNumbers( );

        // ASSIGNMENT 10

        // Uses the currently stored grid numbers to configure an image in the PPM object. Sets the width and height of the image to match the width and height of the grid. Sets the maximum color value to the maximum color value of any color in the color table (getMaxChannelValue()). For each pixel in the PPM object, sets the color based on the grid number for the pixel. If the color table does not have at least 3 colors, make no changes to the PPM object. Use the color table item at the last position for any pixels with a maximum number. Use the color table item at the next to last position for any pixels with a 0 grid number. For all other grid numbers, use (number) mod (the size of the color table - 2) as the index into the color table.
        void setPPM( PPM& ppm, const ColorTable& colors ) const;

    private:
        // Height of the number grid
        int mHeight;
        // Width of the number grid
        int mWidth;
        // Maximum value allowed in the number grid
        int mMax_value;
        // Vector of number grid values
        std::vector<int> mValues;
};

// EXAM 3

class ManhattanNumbers : public NumberGrid{
    public:
        // The default constructor, does constructor chaining to the parent class, setting the height to 600 and the width to 800.
        ManhattanNumbers( ); 
        // Does constructor chaining to the parent class, setting the height and width according to the parameters.
        ManhattanNumbers(const int& height, const int& width); 
        // The required but empty destructor.
        virtual ~ManhattanNumbers( ); 
        // Returns the Manhattan distance from the center of the grid (height/2,width/2) to the location at (row,column).
        int calculateNumber( const int& row, const int& column ) const; 

    private:

};

#endif