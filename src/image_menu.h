#ifndef _IMAGE_MENU_H_
#define _IMAGE_MENU_H_
#include <iostream>
#include <string>
#include <map>
#include "PPM.h"
#include "NumberGrid.h"
#include "JuliaSet.h"
#include "MandelbrotSet.h"

// ASSIGNMENT 11

// A class to store objects that our functions commonly work on
class ActionData
{
public:
    // Initialize all data members. The color table should be size 16, and have the gradient from Color(0,255,0) to Color(255,0,255). This is the same as was created in imageMenu previously. mDone should be initialized to false.
    ActionData(std::istream &is, std::ostream &os);
    // If mGrid is not 0, delete it.
    ~ActionData();
    // Return the data member.
    std::istream &getIS();
    // Return the data member.
    std::ostream &getOS();
    // Return the data member.
    PPM &getInputImage1();
    // Return the data member.
    PPM &getInputImage2();
    // Return the data member.
    PPM &getOutputImage();
    // Return *mGrid, a reference to the object pointed to by mGrid.
    NumberGrid &getGrid();
    // If mGrid is not 0, delete it, then assign mGrid to grid.
    void setGrid(NumberGrid *grid);
    // Return the data member.
    ColorTable &getTable();
    // Return the data member.
    bool getDone() const;
    // Set mDone to true.
    void setDone();
    // Return the data member.
    bool getQuiet() const;
    // Set mQuiet.
    void toggleQuiet();
    // Toggles the quiet state
    void copy(ActionData& rhs);

protected:
    // A reference to the input stream to read user input from.
    std::istream &mIS;
    // A reference to the output stream to display data to user.
    std::ostream &mOS;
    // The “input image 1”.
    PPM mInputImage1;
    // The “input image 2”.
    PPM mInputImage2;
    // The “output image”.
    PPM mOutputImage;
    // A pointer to the current grid-like object. Should be initialized to 0.
    NumberGrid *mGrid;
    // The color table object, should be initialized to the colors as described in the Color Table assignment.
    ColorTable mTable;
    // Is the user done or not.
    bool mDone;
    // Is the menu quieted
    bool mQuiet;
};

typedef void (*ActionFunctionType)(ActionData &action_data);

// Class to represent a menu with stored functions
class MenuData
{
public:
    // Constructor, no initialization required.
    MenuData();
    // Add name to mActionNames, name:func to mActionFunctions, and name:description to mActionDescriptions. If name has already been added, do nothing.
    void addAction(const std::string &name, ActionFunctionType func, const std::string &description);
    // Returns the data member.
    const std::vector<std::string> &getNames() const;
    // If name is registered, return the function pointer. Otherwise, return 0.
    ActionFunctionType getFunction(const std::string &name);
    // If name is registered, return the description. Otherwise, throw an exception. The exception should be a std::string with the value “Action NAME has no description.”, where NAME is the value of name.
    const std::string &getDescription(const std::string &name);

protected:
    // A vector of action names users are allowed to use.
    std::vector<std::string> mActionNames;
    // A map from action names to action function pointers.
    std::map<std::string, ActionFunctionType> mActionFunctions;
    // A map from action names to action descriptions.
    std::map<std::string, std::string> mActionDescriptions;
};

// ASSIGNMENT 1

// Read a string in from the user with the given prompt
std::string getString(ActionData &action_data, const std::string &prompt);
// Read an integer in from the user with the given prompt
int getInteger(ActionData &action_data, const std::string &prompt);
// Read a double in from the user with the given prompt
double getDouble(ActionData &action_data, const std::string &prompt);
// Asks user for favorite color, integer, and double, then prints the color and double out {integer} times
int assignment1(std::istream &is, std::ostream &os);

// ASSIGNMENT 2

// Writes the PPM image to a file with name read in from the user and saves it
void writeUserImage(ActionData &action_data);
// Creates an image with a user given height and width
// Image will have a diagonal color gradient and will be separated into four quadrants
int assignment2(std::istream &is, std::ostream &os);

// EXAM 1

// Asks user for favorite pokemon, and the level and health of said pokemon
// Prints user input in a formatted sentence
int inquisitor(ActionData &action_data);
// Draws a picture divided into four quadrants of a size input from the user
int four_square(std::istream &is, std::ostream &os);

// ASSIGNMENT 3

// Display menu options
void showMenu(MenuData &menu_data, ActionData &action_data);
// Get user input
std::string getChoice(ActionData &action_data);
// Ignore lines starting with #
void commentLine(std::istream &is);
// Sets the size of the image
void setSize(ActionData &action_data);
// Sets the max color value of the image
void setMaxColorValue(ActionData &action_data);
// Sets the channel specified by user input
void setChannel(ActionData &action_data);
// Sets the pixel specified by user input
void setPixel(ActionData &action_data);
// Sets all pixels to black -> rgb(0,0,0)
void clearAll(PPM &src);
// Draws a diamond with user given parameters
void drawDiamond(ActionData &action_data);
// Draws a circle with user given parameters
void drawCircle(ActionData &action_data);
// Draws a box with user given parameters
void drawBox(ActionData &action_data);
// Process user input
void takeAction(const std::string &choice, MenuData &menu_data, ActionData &action_data);
// Image editing loop
int imageMenu(std::istream &is, std::ostream &os);

// ASSIGNMENT 4

// Reads a PPM file into PPM input_image1
void readUserImage1(ActionData &action_data);
// Reads a PPM file into PPM input_image2
void readUserImage2(ActionData &action_data);

// ASSIGNMENT 5

// Modifies src1 by adding src2 to it
void plusEquals(ActionData &action_data);
// Modifies src1 by subtracting src2 from it
void minusEquals(ActionData &action_data);
// Modifies src by multiplying it by a user input double
void timesEquals(ActionData &action_data);
// Modifies src by dividing it by a user input double
void divideEquals(ActionData &action_data);
// Sets dst to be the sum of src1 and src2
void plus(ActionData &action_data);
// Sets dst to be the subtraction of src2 from src1
void minus(ActionData &action_data);
// Sets dst to be src multiplied by a user input double
void times(ActionData &action_data);
// Sets dst to be src divided by a user input double
void divide(ActionData &action_data);

// ASSIGNMENT 6

// Opens a file and runs commands from that file
void runFile(ActionData &action_data);

// EXAM 2

// Draws a square with the given parameters
void drawSquare(ActionData &action_data);
// Blend two images by scaling the brightness and then adding them together
void blendImages(ActionData &action_data);

// ASSIGNMENT 7

// Configures grid using user input values
void configureGrid(ActionData &action_data);
// Sets a number in the grid using user input values
void setGrid(ActionData &action_data);
// Sets a PPM from a grid
void applyGrid(ActionData &action_data);

// ASSIGNMENT 8

// Sets the plane size of a JuliaSet object
void setFractalPlaneSize(ActionData &action_data);
// Calculates all numbers for the grid
void calculateFractal(ActionData &action_data);
// Sets a and b parameters of a JuliaSet object
void setJuliaParameters(ActionData &action_data);

// ASSIGNMENT 9

// If grid isn’t 0, delete it. Set grid to be a new JuliaSet object from the heap, default constructed
void setJuliaFractal(ActionData &action_data);
// If grid isn’t 0, delete it. Set grid to be a new MandelbrotSet object from the heap, default constructed
void setMandelbrotFractal(ActionData &action_data);

// ASSIGNMENT 10

// Uses the new setPPM method to set the PPM using the grid and color table. Note this is not a replacement for applyGrid, this is in addition to that function.
void applyGridColorTable(ActionData &action_data);
// Asks the user for the “Size? “, then applies it to the table.
void setColorTableSize(ActionData &action_data);
// Asks the user for “Position? “, “Red? “, “Green? “, and “Blue? “. The uses them to set a color at the specified position in the color table.
void setColor(ActionData &action_data);
// Asks the user for “Position? “, then uses setRandomColor() to set a random color at that position. Use 255 for the maximum color value.
void setRandomColor(ActionData &action_data);
// Asks the user for “First position? “, “First red? “, “First green? “, “First blue? “, “Second position? “, “Second red? “, “Second green? ” and “Second blue? “. The uses them to insertGradient() in the color table.
void setColorGradient(ActionData &action_data);

// EXAM 3

// Will make the grid pointer point to a ManhattanNumbers object allocated from the heap. Be sure to delete any memory already pointed to by grid.
void setManhattanNumbers(ActionData &action_data);
// Will make the grid zoom in or out. Prompts the user for “Zoom Factor? “. Only does this work if the grid can be dynamically cast into a ComplexFractal pointer.
void zoomPlane(ActionData &action_data);
// Will set an inverted gradient in the color table, using the insertInvertedGradient() method. Prompts the user for “First position? “, “First red? “, “First green? “, “First blue? “, and “Second position? “.
void setInvertedColorGradient(ActionData &action_data);

// ASSIGNMENT 11

// Calls setDone()
void quit(ActionData &action_data);
// Copies input image 1 to output image.
void copyImage(ActionData &action_data);
// Sets output image to the red gray filter of input image 1.
void grayFromRed(ActionData &action_data);
// Sets output image to the green gray filter of input image 1.
void grayFromGreen(ActionData &action_data);
// Sets output image to the blue gray filter of input image 1.
void grayFromBlue(ActionData &action_data);
// Sets output image to the linear colorimetric gray filter of input image 1.
void grayFromLinearColorimetric(ActionData &action_data);
// Sets output image to the sepia filter of input image 1.
void sepiaFilter(ActionData &action_data);
// Sets output image to the rotate color filter of input image 1.
void rotateColorFilter(ActionData &action_data);
// Sets output image to the teal filter of input image 1.
void tealFilter(ActionData &action_data);
// Sets output image to the vertical edge filter of input image 1.
void verticalEdgeFilter(ActionData &action_data);
// Sets output image to the horizontal edge filter of input image 1.
void horizontalEdgeFilter(ActionData &action_data);
// Calls addAction for all functions that need to be callable from takeMenu(). For the actions use the user action as the name, such as “copy” or “julia”. For the function use the correct function, such as copyImage or setJuliaFractal. For the description, use the string that used to be displayed in showMenu(), without the “name) ” piece. For example “Copy input image 1 to output image.” or “Choose to make a Julia set.”.
void configureMenu(MenuData &menu_data);

// ASSIGNMENT 12

// This function calls the NumberGrid version of calculateAllNumbers instead of the ThreadedGrid version, which would be the default. This is accomplished with this syntax: grid.NumberGrid::calculateAllNumbers( ), assuming grid is a reference to a polymorphic NumberGrid object.
void calculateFractalSingleThread( ActionData& action_data ); 

// EXAM 4

// Prompts the user for the integer “Reduction count? “, and calls the antiAlias method on the input image 1 of action_data, storing the result in the output image of action_data.
void antiAliasFilter(ActionData& action_data);

#endif
