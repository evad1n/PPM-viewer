#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "MyApp.h"

MyApp::MyApp(int height, int width)
    : mHeight(height), mWidth(width), mMaxNumber(300), mMinX(-2.0), mMaxX(2.0), mMinY(-2.0), mMaxY(2.0), mA(-0.8), mB(0.156),
      mZoomFactor(0.9), mOutputImage(), mJuliaParameterImage(), mGrid(0),
      mJuliaParameterGrid(), mTable(ColorTable(16)), mMode(MODE_DISPLAY_OUTPUT_IMAGE), mFileNumber(1), mWhichColor(0), mAntiAliasFactor(1)
{
    this->mTable.insertGradient(Color(0, 255, 0), Color(255, 0, 255), 0, 15);
    this->mJuliaParameterGrid = new MandelbrotSet(height, width, -2.0, 2.0, -2.0, 2.0);
    this->mJuliaParameterGrid->setMaxNumber(100);
    this->mJuliaParameterGrid->calculateAllNumbers();
    this->mJuliaParameterGrid->setPPM(mJuliaParameterImage, mTable);
    this->setGrid(new MandelbrotSet(height, width, mMinX, mMaxX, mMinY, mMaxY));
}

int MyApp::getHeight() const
{
    return this->mHeight;
}

int MyApp::getWidth() const
{
    return this->mWidth;
}

void MyApp::setSize(int height, int width)
{
    if (height >= 2 && width >= 2)
    {
        this->mGrid->setGridSize(height * mAntiAliasFactor, width * mAntiAliasFactor);
        this->fixFractalPlaneSize();
        this->calculateFractal();
        this->applyColorTable();
        this->mJuliaParameterGrid->setGridSize(height, width);
        this->mJuliaParameterGrid->calculateAllNumbers();
        this->mJuliaParameterGrid->setPPM(mJuliaParameterImage, mTable);
    }
}

int MyApp::getMaxNumber() const
{
    return this->mMaxNumber;
}

void MyApp::setMaxNumber(int max_number)
{
    if (max_number > 0)
    {
        this->mMaxNumber = max_number;
        this->mGrid->setMaxNumber(max_number);
        this->setColorTable(this->mWhichColor);
    }
}

void MyApp::setFractalPlaneSize(double min_x, double max_x, double min_y, double max_y)
{
    ComplexFractal *fptr = dynamic_cast<ComplexFractal *>(this->mGrid);
    if (fptr != 0)
    {
        fptr->setPlaneSizeNoLimits(min_x, max_x, min_y, max_y);
        fixFractalPlaneSize();
        calculateFractal();
        applyColorTable();
    }
    else
    {
        std::cout << "Not a ComplexFractal object. Can't set plane size." << std::endl;
    }
}

void MyApp::fixFractalPlaneSize()
{
    ComplexFractal *fptr = dynamic_cast<ComplexFractal *>(this->mGrid);
    if (fptr != 0)
    {
        double min_x = fptr->getMinX();
        double max_x = fptr->getMaxX();
        double min_y = fptr->getMinY();
        double max_y = fptr->getMaxY();
        double delta_x = fptr->getDeltaX();
        double delta_y = fptr->getDeltaY();

        if (mGrid->getWidth() > mGrid->getHeight())
        {
            double mid_y = (min_y + max_y) / 2;
            min_y = mid_y - delta_x * mGrid->getHeight() / 2.0;
            max_y = mid_y + delta_x * mGrid->getHeight() / 2.0;
        }
        else
        {
            double mid_x = (min_x + max_x) / 2;
            min_x = mid_x - delta_y * mGrid->getWidth() / 2.0;
            max_x = mid_x + delta_y * mGrid->getWidth() / 2.0;
        }

        fptr->setPlaneSizeNoLimits(min_x, max_x, min_y, max_y);
    }
    else
    {
        std::cout << "Not a ComplexFractal object. Can't fix plane size." << std::endl;
    }
}

void MyApp::calculateFractal()
{
    this->mGrid->calculateAllNumbers();
}

void MyApp::applyColorTable()
{
    PPM tmp;
    this->mGrid->setPPM(tmp, mTable);
    tmp.antiAlias(mAntiAliasFactor, mOutputImage);
}

PPM &MyApp::getOutputImage()
{
    return this->mOutputImage;
}

NumberGrid &MyApp::getGrid()
{
    return *this->mGrid;
}

void MyApp::setGrid(NumberGrid *grid)
{
    if (this->mGrid != 0)
    {
        delete this->mGrid;
    }

    this->mGrid = grid;
}

ColorTable &MyApp::getTable()
{
    return this->mTable;
}

PPM &MyApp::getDisplayPPM()
{
    return this->mMode == MODE_DISPLAY_OUTPUT_IMAGE ? this->mOutputImage : this->mJuliaParameterImage;
}

void MyApp::setCenter(int x, int y)
{
    ComplexFractal *fptr = dynamic_cast<ComplexFractal *>(this->mGrid);
    if (fptr != 0)
    {
        double new_x = x - (this->mGrid->getWidth() / 2);
        double new_y = y - (this->mGrid->getHeight() / 2);
        new_x *= fptr->getDeltaX();
        new_y *= fptr->getDeltaY();

        double min_x = this->mMinX + new_x;
        double max_x = this->mMaxX + new_x;
        double min_y = this->mMinY + new_y;
        double max_y = this->mMaxY + new_y;

        fptr->setPlaneSizeNoLimits(min_x, max_x, min_y, max_y);
        fixFractalPlaneSize();
        calculateFractal();
        applyColorTable();
    }
    else
    {
        std::cout << "Not a ComplexFractal object. Can't set center." << std::endl;
    }
}

void MyApp::setJuliaParameters(int x, int y)
{
    ComplexFractal *fptr = dynamic_cast<ComplexFractal *>(this->mJuliaParameterGrid);
    if (fptr != 0)
    {
        fptr->calculatePlaneCoordinatesFromPixelCoordinates(y, x, mA, mB);
    }
    else
    {
        std::cout << "Not a ComplexFractal object. Can't calculate plane coordinates." << std::endl;
    }

    JuliaSet *jptr = dynamic_cast<JuliaSet *>(this->mGrid);
    if (jptr != 0)
    {
        jptr->setParameters(mA, mB);
        calculateFractal();
        applyColorTable();
    }
    else
    {
        std::cout << "Not a JuliaSet object. Can't set julia parameters." << std::endl;
    }

    if (mMode == MODE_JULIA_PARAMETERS)
    {
        setMode(MODE_DISPLAY_OUTPUT_IMAGE);
    }
}

void MyApp::zoomIn()
{
    ComplexFractal *fptr = dynamic_cast<ComplexFractal *>(this->mGrid);
    if (fptr != 0)
    {
        double dx = (mMaxX - mMinX) * (1 - mZoomFactor) / 2;
        double dy = (mMaxY - mMinY) * (1 - mZoomFactor) / 2;

        mMinX = this->mMinX + dx;
        mMaxX = this->mMaxX - dx;
        mMinY = this->mMinY + dy;
        mMaxY = this->mMaxY - dy;

        fptr->setPlaneSizeNoLimits(mMinX, mMaxX, mMinY, mMaxY);
        fixFractalPlaneSize();
        calculateFractal();
        applyColorTable();
    }
    else
    {
        std::cout << "Not a ComplexFractal object. Can't set zoom in." << std::endl;
    }
}

void MyApp::zoomOut()
{
    ComplexFractal *fptr = dynamic_cast<ComplexFractal *>(this->mGrid);
    if (fptr != 0)
    {
        double dx = (mMaxX - mMinX) * (1 - mZoomFactor) / 2;
        double dy = (mMaxY - mMinY) * (1 - mZoomFactor) / 2;

        mMinX = this->mMinX - dx;
        mMaxX = this->mMaxX + dx;
        mMinY = this->mMinY - dy;
        mMaxY = this->mMaxY + dy;

        fptr->setPlaneSizeNoLimits(mMinX, mMaxX, mMinY, mMaxY);
        fixFractalPlaneSize();
        calculateFractal();
        applyColorTable();
    }
    else
    {
        std::cout << "Not a ComplexFractal object. Can't set zoom out." << std::endl;
    }
}

void MyApp::julia()
{
    this->setGrid(new JuliaSet(mHeight, mWidth, mMinX, mMaxX, mMinY, mMaxY, mA, mB));
    this->setMaxNumber(mMaxNumber);
    this->setSize(mHeight, mWidth);
}

void MyApp::mandelbrot()
{
    this->setGrid(new MandelbrotSet(mHeight, mWidth, mMinX, mMaxX, mMinY, mMaxY));
    this->setMaxNumber(mMaxNumber);
    this->setSize(mHeight, mWidth);
}

void MyApp::setMode(Mode mode)
{
    this->mMode = mode;
}

MyApp::Mode MyApp::getMode() const
{
    return this->mMode;
}

void MyApp::writePPMFile()
{
    std::string base = "gui_image_";
    std::string extension = ".ppm";
    //std::string filename = base + number + extension;

    std::stringstream ss;
    ss << base << std::setw(4) << std::setfill('0') << mFileNumber << extension;
    std::string filename = ss.str();

    std::cout << filename << std::endl;

    std::ofstream fout(filename);
    fout << mOutputImage;
    fout.close();

    mFileNumber++;
}

void MyApp::setColorTable(int which)
{
    mWhichColor = which;
    
    switch (which)
    {
    case 0:
        this->mTable = ColorTable(16);
        this->mTable.insertGradient(Color(0, 255, 0), Color(255, 0, 255), 0, 15);
        break;
    case 1:
        this->mTable = ColorTable(16);
        this->mTable.insertInvertedGradient(Color(252, 73, 3), 0, 15);
        break;
    case 2:
        this->mTable = ColorTable(16);
        this->mTable.insertGradient(Color(0, 0, 0), Color(255, 255, 255), 0, 15);
        break;
    case 3:
        this->mTable = ColorTable(16);
        this->mTable.insertGradient(Color(0, 0, 0), Color(0, 255, 0), 0, 7);
        this->mTable.insertGradient(Color(0, 255, 0), Color(255, 255, 255), 8, 15);
        break;

    default:
        break;
    }

    applyColorTable();
}

void MyApp::toggleAntiAlias()
{
    this->mAntiAliasFactor = (this->mAntiAliasFactor == 1 ? 3 : 1);
    this->setSize(mHeight, mWidth);
}
