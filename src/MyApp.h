#ifndef _MYAPP_H_
#define _MYAPP_H_
#include "image_menu.h"

class MyApp {
public:
  enum Mode { MODE_DISPLAY_OUTPUT_IMAGE, MODE_JULIA_PARAMETERS };

// Initializes the data members as follows: mHeight to height and mWidth to width, mMaxNumber to 300, mMinX to -2.0, mMaxX to 2.0, mMinY to -2.0, mMaxY to 2.0, mA to -0.8, mB to 0.156, mZoomFactor to 0.9, mGrid to 0, mTable to size 16, mMode to MODE_DISPLAY_OUTPUT_IMAGE, mFileNumber to 1, and mWhichColor to 0.
// Also inserts a gradient into the color table, the same as the imageMenu() function did; sets mJuliaParameterGrid to a heap allocated MandelbrotSet with height and width from the parameters, and plane boundaries set to the -2.0, 2.0 range; sets the mJuliaParameterGrid maximum number to 100, tells it to calculate all numbers, and calls setPPM on it to set mJuliaParameterImage, using mTable; Additionally uses setGrid to set a new MandelbrotSet with height, width and plane parameters set from the data members; finally calls setMaxNumber and setSize with the data member values as parameters. All of this work is necessary to set up the initial default display.
MyApp(int height, int width); 
// Returns the data member.
int getHeight() const; 
// Returns the data member.
int getWidth() const; 
// If height and width are both at least 2, updates the data members, calls setGridSize on mGrid, calls fixFractalPlaneSize, calculateFractal, and applyColorTable. Additionally calls setGridSize, calculateAllNumbers, and setPPM on mJuliaParameterGrid.
void setSize(int height, int width); 
// Returns the data member.
int getMaxNumber() const; 
// If max_number is positive, sets the data member, calls setMaxNumber on mGrid, and calls setColorTable with mWhichColor as the parameter.
void setMaxNumber(int max_number); 
// If mGrid can be dynamic_cast to ComplexFractal*, call setPlaneSizeNoLimits on the cast pointer with this function’s parameters as arguments, then call fixFractalPlaneSize, calculateFractal, and applyColorTable.
void setFractalPlaneSize(double min_x, double max_x, double min_y, double max_y); 
// If mGrid can be dynamic_cast to ComplexFractal*, Get the min/max/delta x/y values from the cast pointer. If mWidth is bigger than mHeight, calculate mid_y as the average of min_y and max_y. Update min_y to be mid_y - dx*mHeight/2.0. max_y is updated the same, but with a + instead of -. If mWidth is not greater than mHeight, instead calculate mid_x as the average of min_x and max_x, then update min_x and max_x from similar formulas. Note that the y values are updated using dx (the delta x value), and x values are updated using the dy value. Finally, call setPlaneSizeNoLimits on the cast pointer, using the min/max x/y values, two of which should have been updated, and the other two should not have been changed.
void fixFractalPlaneSize(); 
// Calls calculateAllNumbers on mGrid.
void calculateFractal(); 
// Calls setPPM on mGrid, passing mOutputImage and mTable as parameters.
void applyColorTable(); 
// Returns the data member.
PPM& getOutputImage(); 
// Returns *mGrid.
NumberGrid& getGrid(); 
// Much like ActionData::setGrid. If mGrid is not 0, delete it. Then sets mGrid to the parameter.
void setGrid(NumberGrid *grid); 
// Returns the data member.
ColorTable& getTable(); 
// If mMode is MODE_DISPLAY_OUTPUT_IMAGE, returns mOutputImage, if it is MODE_JULIA_PARAMTERS, returns mJuliaParameterImage.
PPM& getDisplayPPM(); 
// If mGrid can be dynamic_cast to ComplexFractal*, The x and y parameters are the column and row of the image clicked by the user. To calculate the new plane size values: calculate the column and row shifts to center with x-mGrid->getWidth()/2 and similar for the y coordinate. To find the shift distance in the plane, multiply these results by delta x and delta y, respectively. These can be fetched from the cast pointer with getDeltaX() and getDelataY(). The new minimum x value is mMinX + dx. Similar values can be found for maximum x, and min/max y. All use addition. Call setPlaneSizeNoLimits on the cast pointer, using the min/max x/y values calculated. Finally, calls fixFractalPlaneSize, calculateFractal, and applyColorTable.
void setCenter(int x, int y); 
// x and y are the column and row clicked by the user in the image. If mJuliaParameterGrid can be dynamic_cast to ComplexFractal*, call calculatePlaneCoordinatesFromPixelCoordinates on the cast pointer, passing y and x as row and column parameters, and mA and mB as the location parameters. If mGrid can be dynamic_cast to JuliaSet*, call setParameters on it with mA and mB as parameters. Also call calculateFractal, and applyColorTable. Finally if mMode is MODE_JULIA_PARAMETERS, then call setMode to set it to MODE_DISPLAY_OUTPUT_IMAGE.
void setJuliaParameters(int x, int y); 
// Like other methods, dynamic cast mGrid to a ComplexFractal*. If successful, Set dx to (mMaxX-mMinX) * (1-mZoomFactor)/2. Use a similar formula for dy. The new minimum x and y values are calculated by adding dx and dy to the current ones. Subtract dx or dy from the maximum to get the new maximum. Call setPlaneSizeNoLimits on the cast pointer, with the newly calculated limits as parameters, then call fixFractalPlaneSize, calculateFractal, and applyColorTable.
void zoomIn(); 
// This looks the same as zoomIn, with the difference of dividing by (1-mZoomFactor) instead of multiplying by it.
void zoomOut(); 
// Calls setGrid with a new JuliaSet initialized with mHeight, mWidth, mMinX, …. Calls setMaxNumber and setSize, using the data members as parameters.
void julia(); 
// Calls setGrid with a new MandelbrotSet initialized with mHeight, mWidth, mMinX, …. Calls setMaxNumber and setSize, using the data members as parameters.
void mandelbrot(); 
// Assigns the parameter to mMode.
void setMode(Mode mode); 
// Returns the data member.
Mode getMode() const; 
// Constructs a filename using std::stringstream gui_image_ and mFileNumber. Writes mOutputImage to the file, then increments mFileNumber.
void writePPMFile(); 
// Sets the data member to the parameter. If the value is 0, sets the color table to the one configured in the constructor. If the value is 1, 2, or 3, configure a different color table. You choose what these 3 extra color tables will look like. Make them interesting as possible. Finally, calls applyColorTable.
void setColorTable(int which); 
// If mAntiAliasFactor is 1, then change it to be 3. Otherwise, set it to 1. After setting the value of the data member, call setSize(mHeight,mWidth).
void toggleAntiAlias();

protected:
  int mHeight, mWidth;
  int mMaxNumber;
  double mMinX, mMaxX, mMinY, mMaxY;
  double mA, mB;
  double mZoomFactor;
  PPM mOutputImage;
  PPM mJuliaParameterImage;
  NumberGrid *mGrid;
  MandelbrotSet *mJuliaParameterGrid;
  ColorTable mTable;
  Mode mMode;
  int mFileNumber;
  int mWhichColor;
  int mAntiAliasFactor;
};

#endif