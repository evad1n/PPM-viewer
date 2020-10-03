#include <cmath>
#include "ComplexFractal.h"

ComplexFractal::ComplexFractal()
    : ThreadedGrid(200, 300), mMinX(-1.5), mMaxX(1.5), mMinY(-1), mMaxY(1), mDeltaX(0.01), mDeltaY(0.01)
{
}

ComplexFractal::ComplexFractal(const int &height, const int &width, const double &min_x, const double &max_x, const double &min_y, const double &max_y)
    : ThreadedGrid(height, width), mMinX(min_x), mMaxX(max_x), mMinY(min_y), mMaxY(max_y)
{
}

ComplexFractal::~ComplexFractal()
{
}

double ComplexFractal::getMinX() const
{
    return this->mMinX;
}

double ComplexFractal::getMaxX() const
{
    return this->mMaxX;
}

double ComplexFractal::getMinY() const
{
    return this->mMinY;
}

double ComplexFractal::getMaxY() const
{
    return this->mMaxY;
}

void ComplexFractal::setGridSize(const int &height, const int &width)
{
    if (height >= 2 && width >= 2)
    {
        NumberGrid::setGridSize(height, width);
        this->mDeltaX = calculateDeltaX();
        this->mDeltaY = calculateDeltaY();
    }
}

void ComplexFractal::setPlaneSize(const double &min_x, const double &max_x, const double &min_y, const double &max_y)
{
    if (min_x >= -2.0 && min_x <= 2.0 && max_x >= -2.0 && max_x <= 2.0 && min_y >= -2.0 && min_y <= 2.0 && max_y >= -2.0 && max_y <= 2.0)
    {
        if (min_x != max_x && min_y != max_y)
        {
            if (min_x > max_x)
            {
                this->mMinX = max_x;
                this->mMaxX = min_x;
            }
            else
            {
                this->mMinX = min_x;
                this->mMaxX = max_x;
            }
            if (min_y > max_y)
            {
                this->mMinY = max_y;
                this->mMaxY = min_y;
            }
            else
            {
                this->mMinY = min_y;
                this->mMaxY = max_y;
            }
            this->mDeltaX = calculateDeltaX();
            this->mDeltaY = calculateDeltaY();
        }
    }
}

double ComplexFractal::getDeltaX() const
{
    return this->mDeltaX;
}

double ComplexFractal::getDeltaY() const
{
    return this->mDeltaY;
}

void ComplexFractal::setDeltas(const double &delta_x, const double &delta_y)
{
    if (delta_x >= 0 && delta_y >= 0)
    {
        this->mDeltaX = delta_x;
        this->mDeltaY = delta_y;
    }
}

double ComplexFractal::calculateDeltaX() const
{
    return (this->mMaxX - this->mMinX) / (this->getWidth() - 1);
}

double ComplexFractal::calculateDeltaY() const
{
    return (this->mMaxY - this->mMinY) / (this->getHeight() - 1);
}

double ComplexFractal::calculatePlaneYFromPixelRow(const int &row) const
{
    if (row >= 0 && row < this->getHeight())
    {
        return (this->mMaxY - (row * this->mDeltaY));
    }
    return 0;
}

double ComplexFractal::calculatePlaneXFromPixelColumn(const int &column) const
{
    if (column >= 0 && column < this->getWidth())
    {
        return (this->mMinX + (column * this->mDeltaX));
    }
    return 0;
}

void ComplexFractal::calculatePlaneCoordinatesFromPixelCoordinates(const int &row, const int &column, double &x, double &y) const
{
    if (row >= 0 && row < this->getHeight() && column >= 0 && column < this->getWidth())
    {
        x = this->calculatePlaneXFromPixelColumn(column);
        y = this->calculatePlaneYFromPixelRow(row);
        return;
    }
    x = 0;
    y = 0;
}

// EXAM 3

void ComplexFractal::zoomPlane(const double &zoom_factor)
{
    double currentX = this->mMaxX - this->mMinX;
    double currentY = this->mMaxY - this->mMinY;

    double desiredX = currentX * zoom_factor;
    double desiredY = currentY * zoom_factor;

    double xChange = (currentX - desiredX) / 2;
    double yChange = (currentY - desiredY) / 2;

    double newMinx = this->mMinX + xChange;
    newMinx = std::max(newMinx, -2.0);

    double newMaxX = this->mMaxX - xChange;
    newMaxX = std::min(newMaxX, 2.0);

    double newMinY = this->mMinY + yChange;
    newMinY = std::max(newMinY, -2.0);

    double newMaxY = this->mMaxY - yChange;
    newMaxY = std::min(newMaxY, 2.0);

    this->setPlaneSize(newMinx, newMaxX, newMinY, newMaxY);
}

// ASSIGNMENT 13

void ComplexFractal::setPlaneSizeNoLimits(const double &min_x, const double &max_x, const double &min_y, const double &max_y)
{
    if (min_x != max_x && min_y != max_y)
    {
        if (min_x > max_x)
        {
            this->mMinX = max_x;
            this->mMaxX = min_x;
        }
        else
        {
            this->mMinX = min_x;
            this->mMaxX = max_x;
        }
        if (min_y > max_y)
        {
            this->mMinY = max_y;
            this->mMaxY = min_y;
        }
        else
        {
            this->mMinY = min_y;
            this->mMaxY = max_y;
        }
        this->mDeltaX = calculateDeltaX();
        this->mDeltaY = calculateDeltaY();
    }
}