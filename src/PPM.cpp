#include <cmath>
#include "PPM.h"

PPM::PPM()
    : mHeight(0), mWidth(0), mMax_color_value(0), mPixels(std::vector<int>(0))
{
}

PPM::PPM(const int &height, const int &width)
    : mHeight(height), mWidth(width), mMax_color_value(0), mPixels(std::vector<int>(width * height * 3))
{
}

int PPM::getHeight() const
{
    return this->mHeight;
}

int PPM::getWidth() const
{
    return this->mWidth;
}

int PPM::getMaxColorValue() const
{
    return this->mMax_color_value;
}

int PPM::getChannel(const int &row, const int &column, const int &channel) const
{
    return this->indexValid(row, column, channel) ? this->mPixels[this->index(row, column, channel)] : -1;
}

bool PPM::indexValid(const int &row, const int &column, const int &channel) const
{
    if (channel < 0 || channel > 2)
    {
        return false;
    }
    if (row < 0 || row >= this->mHeight)
    {
        return false;
    }
    if (column < 0 || column >= this->mWidth)
    {
        return false;
    }
    return true;
}

int PPM::index(const int &row, const int &column, const int &channel) const
{
    return (row * this->mWidth * 3 + column * 3) + channel;
}

bool PPM::valueValid(const int &value) const
{
    if (value < 0 || value > this->mMax_color_value)
    {
        return false;
    }
    return true;
}

void PPM::setHeight(const int &height)
{
    if (height >= 0)
    {
        // RESIZE
        std::vector<int> newSize(this->mWidth * height * 3);
        this->mPixels = newSize;
        this->mHeight = height;
    }
    else
    {
        std::cout << "Height must be non-negative. No changes made." << std::endl;
    }
}

void PPM::setWidth(const int &width)
{
    if (width >= 0)
    {
        // RESIZE
        this->mPixels = std::vector<int>(width * this->mHeight * 3);
        ;
        this->mWidth = width;
    }
    else
    {
        std::cout << "Width must be non-negative. No changes made." << std::endl;
    }
}

// must be between 0 and 255
void PPM::setMaxColorValue(const int &max_color_value)
{
    if (max_color_value >= 0 && max_color_value <= 255)
    {
        this->mMax_color_value = max_color_value;
    }
    else
    {
        std::cout << "Max color value must be between 0 and 255 inclusive. No changes made." << std::endl;
    }
}

void PPM::setChannel(const int &row, const int &column, const int &channel, const int &value)
{
    if (this->indexValid(row, column, channel))
    {
        if (this->valueValid(value))
        {
            this->mPixels[this->index(row, column, channel)] = value;
        }
        else
        {
            std::cout << "Invalid value. No changes made." << std::endl;
        }
    }
    else
    {
        std::cout << "Invalid index. No changes made." << std::endl;
    }
}

void PPM::setPixel(const int &row, const int &column, const int &red, const int &green, const int &blue)
{
    this->setChannel(row, column, 0, red);
    this->setChannel(row, column, 1, green);
    this->setChannel(row, column, 2, blue);
}

// EXAM 1

void PPM::setRow(const int &row, const int &red, const int &green, const int &blue)
{
    for (int col = 0; col < this->mWidth; col++)
    {
        this->setPixel(row, col, red, green, blue);
    }
}

// ASSIGNMENT 4

void PPM::grayFromChannel(PPM &dst, const int &src_channel) const
{
    dst.setHeight(this->getHeight());
    dst.setWidth(this->getWidth());
    dst.setMaxColorValue(this->getMaxColorValue());

    for (int row = 0; row < this->getHeight(); row++)
    {
        for (int col = 0; col < this->getWidth(); col++)
        {
            int val = this->getChannel(row, col, src_channel);
            dst.setPixel(row, col, val, val, val);
        }
    }
}

void PPM::grayFromRed(PPM &dst) const
{
    this->grayFromChannel(dst, 0);
}

void PPM::grayFromGreen(PPM &dst) const
{
    this->grayFromChannel(dst, 1);
}

void PPM::grayFromBlue(PPM &dst) const
{
    this->grayFromChannel(dst, 2);
}

double PPM::linearColorimetricPixelValue(const int &row, const int &column) const
{
    int r = this->getChannel(row, column, 0);
    int g = this->getChannel(row, column, 1);
    int b = this->getChannel(row, column, 2);
    double brightness = 0.2126 * r + 0.7152 * g + 0.0722 * b;
    return brightness;
}

void PPM::grayFromLinearColorimetric(PPM &dst) const
{
    dst.setHeight(this->getHeight());
    dst.setWidth(this->getWidth());
    dst.setMaxColorValue(this->getMaxColorValue());

    for (int row = 0; row < this->getHeight(); row++)
    {
        for (int col = 0; col < this->getWidth(); col++)
        {
            int value = this->linearColorimetricPixelValue(row, col);
            dst.setPixel(row, col, value, value, value);
        }
    }
}

// HELPER

// P6 WIDTH HEIGHT MAX_COLOR_VALUE\n
// BINARY REPRESENTATION OF COLORS FOR EACH PIXEL IN THE SAME ORDER AS THE COLOR FILE

std::ostream &operator<<(std::ostream &os, const PPM &rhs)
{
    os << "P6 " << rhs.getWidth() << " " << rhs.getHeight() << " " << rhs.getMaxColorValue() << "\n";
    for (int row = 0; row < rhs.getHeight(); row++)
    {
        for (int col = 0; col < rhs.getWidth(); col++)
        {
            for (int channel = 0; channel < 3; channel++)
            {
                int x = rhs.getChannel(row, col, channel);
                unsigned char c = x;
                os.write((char *)&c, 1);
            }
        }
    }

    return os;
}

std::istream &operator>>(std::istream &is, PPM &rhs)
{
    // Skip "P6"
    std::string p6;
    is >> p6;

    int width, height, max_color_value;
    is >> width;
    is >> height;
    is >> max_color_value;
    rhs.setWidth(width);
    rhs.setHeight(height);
    rhs.setMaxColorValue(max_color_value);

    // Skip \n character
    char c;
    is.read(&c, 1);

    // Read values
    for (int row = 0; row < rhs.getHeight(); row++)
    {
        for (int col = 0; col < rhs.getWidth(); col++)
        {
            for (int channel = 0; channel < 3; channel++)
            {
                unsigned char c;
                is.read((char *)&c, 1);
                rhs.setChannel(row, col, channel, c);
            }
        }
    }

    return is;
}

// ASSIGNMENT 5

// Helper method

// Keeps the value between low and high (inclusive)
int clamp(const int &val, const int &low, const int &high)
{
    return (val < low) ? low : (val > high) ? high : val;
}

bool PPM::operator==(const PPM &rhs) const
{
    return (this->getWidth() * this->getHeight()) == (rhs.getWidth() * rhs.getHeight());
}

bool PPM::operator!=(const PPM &rhs) const
{
    return (this->getWidth() * this->getHeight()) != (rhs.getWidth() * rhs.getHeight());
}

bool PPM::operator<(const PPM &rhs) const
{
    return (this->getWidth() * this->getHeight()) < (rhs.getWidth() * rhs.getHeight());
}

bool PPM::operator<=(const PPM &rhs) const
{
    return (this->getWidth() * this->getHeight()) <= (rhs.getWidth() * rhs.getHeight());
}

bool PPM::operator>(const PPM &rhs) const
{
    return (this->getWidth() * this->getHeight()) > (rhs.getWidth() * rhs.getHeight());
}

bool PPM::operator>=(const PPM &rhs) const
{
    return (this->getWidth() * this->getHeight()) >= (rhs.getWidth() * rhs.getHeight());
}

PPM &PPM::operator+=(const PPM &rhs)
{
    for (int row = 0; row < this->getHeight(); row++)
    {
        for (int col = 0; col < this->getWidth(); col++)
        {
            for (int channel = 0; channel < 3; channel++)
            {
                int x = this->getChannel(row, col, channel);
                x += rhs.getChannel(row, col, channel);
                x = std::min(x, this->getMaxColorValue());
                this->setChannel(row, col, channel, x);
            }
        }
    }
    return *this;
}

PPM &PPM::operator-=(const PPM &rhs)
{
    for (int row = 0; row < this->getHeight(); row++)
    {
        for (int col = 0; col < this->getWidth(); col++)
        {
            for (int channel = 0; channel < 3; channel++)
            {
                int x = this->getChannel(row, col, channel);
                x -= rhs.getChannel(row, col, channel);
                x = std::max(x, 0);
                this->setChannel(row, col, channel, x);
            }
        }
    }
    return *this;
}

PPM &PPM::operator*=(const double &rhs)
{
    for (int row = 0; row < this->getHeight(); row++)
    {
        for (int col = 0; col < this->getWidth(); col++)
        {
            for (int channel = 0; channel < 3; channel++)
            {
                int x = this->getChannel(row, col, channel);
                x *= rhs;
                x = clamp(x, 0, this->getMaxColorValue());
                this->setChannel(row, col, channel, x);
            }
        }
    }
    return *this;
}

PPM &PPM::operator/=(const double &rhs)
{
    for (int row = 0; row < this->getHeight(); row++)
    {
        for (int col = 0; col < this->getWidth(); col++)
        {
            for (int channel = 0; channel < 3; channel++)
            {
                int x = this->getChannel(row, col, channel);
                x /= rhs;
                x = clamp(x, 0, this->getMaxColorValue());
                this->setChannel(row, col, channel, x);
            }
        }
    }
    return *this;
}

PPM &PPM::operator%=(const int &rhs)
{
    for (int row = 0; row < this->getHeight(); row++)
    {
        for (int col = 0; col < this->getWidth(); col++)
        {
            for (int channel = 0; channel < 3; channel++)
            {
                int x = this->getChannel(row, col, channel);
                x %= rhs;
                x = clamp(x, 0, this->getMaxColorValue());
                this->setChannel(row, col, channel, x);
            }
        }
    }
    return *this;
}

PPM PPM::operator+(const PPM &rhs) const
{
    PPM ppm = PPM(this->getHeight(), this->getWidth());
    ppm.setMaxColorValue(this->getMaxColorValue());

    for (int row = 0; row < this->getHeight(); row++)
    {
        for (int col = 0; col < this->getWidth(); col++)
        {
            for (int channel = 0; channel < 3; channel++)
            {
                int x = this->getChannel(row, col, channel);
                x += rhs.getChannel(row, col, channel);
                x = std::min(x, this->getMaxColorValue());
                ppm.setChannel(row, col, channel, x);
            }
        }
    }
    return ppm;
}

PPM PPM::operator-(const PPM &rhs) const
{
    PPM ppm = PPM(this->getHeight(), this->getWidth());
    ppm.setMaxColorValue(this->getMaxColorValue());

    for (int row = 0; row < this->getHeight(); row++)
    {
        for (int col = 0; col < this->getWidth(); col++)
        {
            for (int channel = 0; channel < 3; channel++)
            {
                int x = this->getChannel(row, col, channel);
                x -= rhs.getChannel(row, col, channel);
                x = std::max(x, 0);
                ppm.setChannel(row, col, channel, x);
            }
        }
    }
    return ppm;
}

PPM PPM::operator*(const double &rhs) const
{
    PPM ppm = PPM(this->getHeight(), this->getWidth());
    ppm.setMaxColorValue(this->getMaxColorValue());

    for (int row = 0; row < this->getHeight(); row++)
    {
        for (int col = 0; col < this->getWidth(); col++)
        {
            for (int channel = 0; channel < 3; channel++)
            {
                int x = this->getChannel(row, col, channel);
                x *= rhs;
                x = clamp(x, 0, this->getMaxColorValue());
                ppm.setChannel(row, col, channel, x);
            }
        }
    }
    return ppm;
}

PPM PPM::operator/(const double &rhs) const
{
    PPM ppm = PPM(this->getHeight(), this->getWidth());
    ppm.setMaxColorValue(this->getMaxColorValue());

    for (int row = 0; row < this->getHeight(); row++)
    {
        for (int col = 0; col < this->getWidth(); col++)
        {
            for (int channel = 0; channel < 3; channel++)
            {
                int x = this->getChannel(row, col, channel);
                x /= rhs;
                x = clamp(x, 0, this->getMaxColorValue());
                ppm.setChannel(row, col, channel, x);
            }
        }
    }
    return ppm;
}

PPM PPM::operator%(const int &rhs) const
{
    PPM ppm = PPM(this->getHeight(), this->getWidth());
    ppm.setMaxColorValue(this->getMaxColorValue());

    for (int row = 0; row < this->getHeight(); row++)
    {
        for (int col = 0; col < this->getWidth(); col++)
        {
            for (int channel = 0; channel < 3; channel++)
            {
                int x = this->getChannel(row, col, channel);
                x %= rhs;
                x = clamp(x, 0, this->getMaxColorValue());
                ppm.setChannel(row, col, channel, x);
            }
        }
    }
    return ppm;
}

// ASSIGNMENT 6
int PPM::edgePixelValue(const int &row1, const int &column1, const int &row2, const int &column2) const
{
    double l1 = linearColorimetricPixelValue(row1, column1);
    double l2 = linearColorimetricPixelValue(row2, column2);

    int ret = std::abs(l1 - l2) >= (0.10 * (double)this->getMaxColorValue()) ? this->getMaxColorValue() : 0;

    return ret;
}

void PPM::findVerticalEdges(PPM &dst) const
{
    dst.setWidth(this->getWidth());
    dst.setHeight(this->getHeight());
    dst.setMaxColorValue(this->getMaxColorValue());

    for (int row = 0; row < this->getHeight(); row++)
    {
        for (int col = 1; col < this->getWidth(); col++)
        {
            for (int channel = 0; channel < 3; channel++)
            {
                int x = edgePixelValue(row, col - 1, row, col);
                dst.setChannel(row, col, channel, x);
            }
        }
    }
}

void PPM::findHorizontalEdges(PPM &dst) const
{
    dst.setWidth(this->getWidth());
    dst.setHeight(this->getHeight());
    dst.setMaxColorValue(this->getMaxColorValue());

    for (int row = 1; row < this->getHeight(); row++)
    {
        for (int col = 0; col < this->getWidth(); col++)
        {
            for (int channel = 0; channel < 3; channel++)
            {
                int x = edgePixelValue(row - 1, col, row, col);
                dst.setChannel(row, col, channel, x);
            }
        }
    }
}

void PPM::findDiagonalEdges(PPM &dst) const
{
    dst.setWidth(this->getWidth());
    dst.setHeight(this->getHeight());
    dst.setMaxColorValue(this->getMaxColorValue());

    for (int row = 1; row < this->getHeight(); row++)
    {
        for (int col = 1; col < this->getWidth() - 1; col++)
        {
            for (int channel = 0; channel < 3; channel++)
            {
                int x = edgePixelValue(row - 1, col - 1, row, col);
                int y = edgePixelValue(row - 1, col + 1, row, col);
                int z = (x == 0 && y == 0) ? 0 : this->getMaxColorValue();
                dst.setChannel(row, col, channel, z);
            }
        }
    }
}

// THRESHOLD PARAMETERS

int PPM::edgePixelValue(const int &row1, const int &column1, const int &row2, const int &column2, const double &threshold) const
{
    double l1 = linearColorimetricPixelValue(row1, column1);
    double l2 = linearColorimetricPixelValue(row2, column2);

    double correct_threshold = (double)clamp(threshold, 0, 100);

    int ret = std::abs(l1 - l2) >= ((correct_threshold / 100.0) * (double)this->getMaxColorValue()) ? this->getMaxColorValue() : 0;

    return ret;
}

void PPM::findVerticalEdges(PPM &dst, const double &threshold) const
{
    dst.setWidth(this->getWidth());
    dst.setHeight(this->getHeight());
    dst.setMaxColorValue(this->getMaxColorValue());

    for (int row = 0; row < this->getHeight(); row++)
    {
        for (int col = 1; col < this->getWidth(); col++)
        {
            for (int channel = 0; channel < 3; channel++)
            {
                int x = edgePixelValue(row, col - 1, row, col, threshold);
                dst.setChannel(row, col, channel, x);
            }
        }
    }
}

void PPM::findHorizontalEdges(PPM &dst, const double &threshold) const
{
    dst.setWidth(this->getWidth());
    dst.setHeight(this->getHeight());
    dst.setMaxColorValue(this->getMaxColorValue());

    for (int row = 1; row < this->getHeight(); row++)
    {
        for (int col = 0; col < this->getWidth(); col++)
        {
            for (int channel = 0; channel < 3; channel++)
            {
                int x = edgePixelValue(row - 1, col, row, col, threshold);
                dst.setChannel(row, col, channel, x);
            }
        }
    }
}

void PPM::findDiagonalEdges(PPM &dst, const double &threshold) const
{
    dst.setWidth(this->getWidth());
    dst.setHeight(this->getHeight());
    dst.setMaxColorValue(this->getMaxColorValue());

    for (int row = 1; row < this->getHeight(); row++)
    {
        for (int col = 1; col < this->getWidth() - 1; col++)
        {
            for (int channel = 0; channel < 3; channel++)
            {
                int x = edgePixelValue(row - 1, col - 1, row, col, threshold);
                int y = edgePixelValue(row - 1, col + 1, row, col, threshold);
                int z = (x == 0 && y == 0) ? 0 : this->getMaxColorValue();
                dst.setChannel(row, col, channel, z);
            }
        }
    }
}

// EXAM 2

void PPM::rotateColorFilter(PPM &dst) const
{
    dst.setWidth(this->getWidth());
    dst.setHeight(this->getHeight());
    dst.setMaxColorValue(this->getMaxColorValue());

    for (int row = 0; row < this->getHeight(); row++)
    {
        for (int col = 0; col < this->getWidth(); col++)
        {
            int old_r = this->getChannel(row, col, 0);
            int old_g = this->getChannel(row, col, 1);
            int old_b = this->getChannel(row, col, 2);
            dst.setPixel(row, col, old_g, old_b, old_r);
        }
    }
}

// EXAM 4

void PPM::antiAlias(const int &n, PPM &dst) const
{
    dst.setHeight(this->mHeight / n);
    dst.setWidth(this->mWidth / n);
    dst.setMaxColorValue(this->mMax_color_value);

    for (int row = 0; row < this->mHeight; row+=n) {
        for (int col = 0; col < this->mWidth; col+=n) {
            int red = 0;
            int green = 0;
            int blue = 0;

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    red += this->getChannel(row + i, col + j, 0);
                    green += this->getChannel(row + i, col + j, 1);
                    blue += this->getChannel(row + i, col + j, 2);
                }
            }

            red /= (n*n);
            green /= (n*n);
            blue /= (n*n);

            dst.setPixel((row / n), (col / n), red, green, blue);
        }
    }
}