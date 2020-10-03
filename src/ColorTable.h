#ifndef _COLORTABLE_H_
#define _COLORTABLE_H_
#include <vector>
#include <iostream>

class Color {
    public:
        // Sets all color channels to value 0.
        Color( ); 
        // Sets the color channels to the values provided here. No range checking is applied.
        Color( const int& red, const int& green, const int& blue ); 
        // Returns the value of the red channel.
        int getRed( ) const; 
        // Returns the value of the green channel.
        int getGreen( ) const; 
        // Returns the value of the blue channel.
        int getBlue( ) const; 
        // Returns the value of the channelth channel. 0 == red, 1 == green, 2 == blue. Returns -1 if the channel is out of range.
        int getChannel( const int& channel ) const; 
        // Changes the red channel to value. If value is less than 0, do not make any changes.
        void setRed( const int& value ); 
        // Changes the green channel to value. If value is less than 0, do not make any changes.
        void setGreen( const int& value ); 
        // Changes the blue channel to value. If value is less than 0, do not make any changes.
        void setBlue( const int& value ); 
        // Changes the channelth channel to value. If value is less than 0, do not make any changes. 0 == red, 1 == green, 2 == blue. Does not make changes if channel is out of range.
        void setChannel( const int& channel, const int& value ); 
        // Inverts the red, green and blue channels, using max_color_value. If max_color_value is less than any of the current color channels (red, green or blue), then make no changes. The inversion is completed by subtracting the current value from max_color_value. For example: red = max_color_value - red. This only makes sense if red is >= max_color_value. That’s why we make no changes if any channel (red, green or blue) is larger than max_color_value.
        void invert( const int& max_color_value ); 
        // Returns true if *this and rhs have the same color values. Otherwise, returns false.
        bool operator==( const Color& rhs ) const; 

    private:
        int mRed, mGreen, mBlue;
};

// Displays the color to os in the following format: “red:green:blue”. For example, if the color has red = 13, green = 2 and blue = 45, then the output would be “13:2:45”.
std::ostream& operator<<( std::ostream& os, const Color& color ); 

class ColorTable {
    public:
        // Sizes the Color collection to num_color items.
        ColorTable( const size_t& num_color ); 
        // Returns the number of Colors stored.
        size_t getNumberOfColors( ) const; 
        // Resizes the collection to hold num_color items. Previous Color contents may or may not be preserved.
        void setNumberOfColors( const size_t& num_color ); 
        // Returns the ith Color in the collection. If i is out of range, returns a static memory Color object with all three channels set to -1. See an example below.
        const Color& operator[]( const int& i ) const; 
        // Returns the ith Color in the collection. If i is out of range, returns a static memory Color object with all three channels set to -1.
        Color& operator[]( const int& i ); 
        
        // Assigns the positionth color random values for all three channels. The random values are between 0 and max_color_value, inclusive. If position is out of range, no change is made. If max_color_value is less than 0, no change is made.
        void setRandomColor( const int& max_color_value, const size_t& position ); 
        // Change the colors from position1 to position2, inclusive, to be gradients from color1 to color2. If position1 is not less than position2, no change is made. If either position is out of range, no change is made.
        void insertGradient( const Color& color1, const Color& color2, const size_t& position1, const size_t& position2 ); 
        // Finds the largest value of any RGB value in any color in the table.
        int getMaxChannelValue( ) const; 

        // EXAM 3

        // Creates the second color by inverting color1 with max_color_value of 255. Calls insertGradient() to do the rest of the work.
        void insertInvertedGradient( const Color& color1, const size_t& position1, const size_t& position2 );

    private:
        // A linear collection of colors
        std::vector<Color> mColors;
};

#endif