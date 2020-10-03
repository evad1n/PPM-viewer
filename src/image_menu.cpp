#include <fstream>
#include <cmath>
#include <sstream>
#include "image_menu.h"

// ASSIGNMENT 1

std::string getString(ActionData &action_data, const std::string &prompt)
{
    if (!action_data.getQuiet())
    {
        action_data.getOS() << prompt;
    }
    std::string color;
    action_data.getIS() >> color;
    return color;
}

int getInteger(ActionData &action_data, const std::string &prompt)
{
    action_data.getOS() << prompt;
    int num;
    action_data.getIS() >> num;
    return num;
}

double getDouble(ActionData &action_data, const std::string &prompt)
{
    action_data.getOS() << prompt;
    double num;
    action_data.getIS() >> num;
    return num;
}

int assignment1(std::istream &is, std::ostream &os)
{
    ActionData action_data = ActionData(is, os);
    std::string color = getString(action_data, "What's your favorite color? ");
    int integer = getInteger(action_data, "What's your favorite integer? ");
    double num = getDouble(action_data, "What's your favorite number? ");

    for (int i = 0; i < integer; i++)
    {
        action_data.getOS() << i + 1 << " " << color << " " << num << std::endl;
    }

    return integer;
}

// ASSIGNMENT 2

void writeUserImage(ActionData &action_data)
{
    std::string file_name = getString(action_data, "Output filename? ");

    std::ofstream fout(file_name);
    fout << action_data.getOutputImage();
    fout.close();
}

int assignment2(std::istream &is, std::ostream &os)
{
    ActionData action_data = ActionData(is, os);

    int height = getInteger(action_data, "Image height? ");
    int width = getInteger(action_data, "Image width? ");

    PPM ppm = PPM(height, width);
    int max = (height + width) / 3; // don't make (height + width) > 765
    ppm.setMaxColorValue(max);

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int red = row < (height / 2) ? 0 : max;
            int green = (row + col) % (max + 1);
            int blue = col < (width / 2) ? 0 : max;
            ppm.setPixel(row, col, red, green, blue);
        }
    }

    action_data.getOutputImage() = ppm;
    writeUserImage(action_data);

    return 0;
}

// EXAM 1

int inquisitor(ActionData &action_data)
{
    std::string pokemon_name = getString(action_data, "What is your most powerful Pokemon? ");
    int level = getInteger(action_data, "What is its level? ");
    double health = getDouble(action_data, "What is its health? ");

    action_data.getOS() << pokemon_name << " is level " << level << " and " << health << " HP." << std::endl;

    return level;
}

int four_square(std::istream &is, std::ostream &os)
{
    ActionData action_data = ActionData(is, os);

    int size = getInteger(action_data, "Image size? ");

    PPM ppm = PPM(size, size);
    ppm.setMaxColorValue(100);

    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            // TOP LEFT
            if (row < (size / 2) && col < (size / 2))
            {
                ppm.setPixel(row, col, 100, 0, 66);
            }
            // TOP RIGHT
            if (row < (size / 2) && col >= (size / 2))
            {
                ppm.setPixel(row, col, 0, 100, 33);
            }
            // BOT LEFT
            if (row >= (size / 2) && col < (size / 2))
            {
                ppm.setPixel(row, col, 66, 33, 100);
            }
            // BOT RIGHT
            if (row >= (size / 2) && col >= (size / 2))
            {
                ppm.setPixel(row, col, 33, 66, 0);
            }
        }
    }

    action_data.getOutputImage() = ppm;
    writeUserImage(action_data);

    return 0;
}

// ASSIGNMENT 4

void showMenu(MenuData &menu_data, ActionData &action_data)
{
    action_data.getOS() << std::endl
                        << "Menu Options: " << std::endl
                        << "----------------------------------------------------" << std::endl;
    std::vector<std::string> names = menu_data.getNames();
    for (size_t i = 0; i < names.size(); i++)
    {
        action_data.getOS() << names[i] << ") " << menu_data.getDescription(names[i]) << std::endl;
    }
}

std::string getChoice(ActionData &action_data)
{
    return getString(action_data, "Choice? ");
}

void commentLine(ActionData &action_data)
{
    while (!action_data.getIS().eof())
    {
        char c;
        action_data.getIS().read(&c, 1);
        if (c == '\n')
        {
            break;
        }
    }
}

void setSize(ActionData &action_data)
{
    action_data.getInputImage1().setHeight(getInteger(action_data, "Height? "));
    action_data.getInputImage1().setWidth(getInteger(action_data, "Width? "));
}

void setMaxColorValue(ActionData &action_data)
{
    action_data.getInputImage1().setMaxColorValue(getInteger(action_data, "Max color value? "));
}

void setChannel(ActionData &action_data)
{
    int row = getInteger(action_data, "Row? ");
    int col = getInteger(action_data, "Column? ");
    int channel = getInteger(action_data, "Channel? ");
    int value = getInteger(action_data, "Value? ");
    action_data.getInputImage1().setChannel(row, col, channel, value);
}

void setPixel(ActionData &action_data)
{
    int row = getInteger(action_data, "Row? ");
    int col = getInteger(action_data, "Column? ");
    int r = getInteger(action_data, "Red? ");
    int g = getInteger(action_data, "Green? ");
    int b = getInteger(action_data, "Blue? ");
    action_data.getInputImage1().setPixel(row, col, r, g, b);
}

void clearAll(ActionData &action_data)
{
    for (int row = 0; row < action_data.getInputImage1().getHeight(); row++)
    {
        for (int col = 0; col < action_data.getInputImage1().getWidth(); col++)
        {
            action_data.getInputImage1().setPixel(row, col, 0, 0, 0);
        }
    }
}

void drawDiamond(ActionData &action_data)
{
    int centerRow = getInteger(action_data, "Center Row? ");
    int centerCol = getInteger(action_data, "Center Column? ");
    int size = getInteger(action_data, "Size? ");
    int r = getInteger(action_data, "Red? ");
    int g = getInteger(action_data, "Green? ");
    int b = getInteger(action_data, "Blue? ");

    for (int row = centerRow - size; row <= centerRow + size; row++)
    {
        for (int col = centerCol - size; col <= centerCol + size; col++)
        {
            int dist = std::abs(row - centerRow) + std::abs(col - centerCol);
            if (dist <= size)
            {
                action_data.getInputImage1().setPixel(row, col, r, g, b);
            }
        }
    }
}

void drawCircle(ActionData &action_data)
{
    int centerRow = getInteger(action_data, "Center Row? ");
    int centerCol = getInteger(action_data, "Center Column? ");
    int radius = getInteger(action_data, "Radius? ");
    int r = getInteger(action_data, "Red? ");
    int g = getInteger(action_data, "Green? ");
    int b = getInteger(action_data, "Blue? ");

    for (int row = centerRow - radius; row <= centerRow + radius; row++)
    {
        for (int col = centerCol - radius; col <= centerCol + radius; col++)
        {
            double dist = std::sqrt(std::pow(std::abs(row - centerRow), 2) + std::pow(std::abs(col - centerCol), 2));
            if (dist <= radius)
            {
                action_data.getInputImage1().setPixel(row, col, r, g, b);
            }
        }
    }
}

void drawBox(ActionData &action_data)
{
    int topRow = getInteger(action_data, "Top Row? ");
    int leftCol = getInteger(action_data, "Left Column? ");
    int botRow = getInteger(action_data, "Bottom Row? ");
    int rightCol = getInteger(action_data, "Right Column? ");
    int r = getInteger(action_data, "Red? ");
    int g = getInteger(action_data, "Green? ");
    int b = getInteger(action_data, "Blue? ");

    for (int row = topRow; row <= botRow; row++)
    {
        for (int col = leftCol; col <= rightCol; col++)
        {
            action_data.getInputImage1().setPixel(row, col, r, g, b);
        }
    }
}

void takeAction(const std::string &choice, MenuData &menu_data, ActionData &action_data)
{
    ActionFunctionType func = menu_data.getFunction(choice);
    if (func != 0)
    {
        func(action_data);
    }
    else
    {
        action_data.getOS() << "Unknown action '" << choice << "'." << std::endl;
    }
}

int imageMenu(std::istream &is, std::ostream &os)
{
    ActionData action_data = ActionData(is, os);
    MenuData menu_data = MenuData();
    configureMenu(menu_data);
    action_data.setGrid(new JuliaSet());

    std::string input = "";

    while (action_data.getIS().good() && !action_data.getDone())
    {
        if (!action_data.getQuiet())
        {
            showMenu(menu_data, action_data);
        }
        input = getChoice(action_data);

        if (input.size() > 0 && input[0] == '#')
        {
            input = "#";
        }
        takeAction(input, menu_data, action_data);
    }

    return 0;
}

// ASSIGNMENT 4

void readUserImage1(ActionData &action_data)
{
    std::string file_name = getString(action_data, "Input filename? ");
    std::ifstream fin(file_name);
    fin >> action_data.getInputImage1();
    fin.close();
}

void readUserImage2(ActionData &action_data)
{
    std::string file_name = getString(action_data, "Input filename? ");

    std::ifstream fin(file_name);
    fin >> action_data.getInputImage2();
    fin.close();
}

// ASSIGNMENT 5

void plusEquals(ActionData &action_data)
{
    action_data.getInputImage1() += action_data.getInputImage2();
}

void minusEquals(ActionData &action_data)
{
    action_data.getInputImage1() -= action_data.getInputImage2();
}

void timesEquals(ActionData &action_data)
{
    double factor = getDouble(action_data, "Factor? ");
    action_data.getInputImage1() *= factor;
}

void divideEquals(ActionData &action_data)
{
    double factor = getDouble(action_data, "Factor? ");
    action_data.getInputImage1() /= factor;
}

void plus(ActionData &action_data)
{
    action_data.getOutputImage() = action_data.getInputImage1() + action_data.getInputImage2();
}

void minus(ActionData &action_data)
{
    action_data.getOutputImage() = action_data.getInputImage1() - action_data.getInputImage2();
}

void times(ActionData &action_data)
{
    double factor = getDouble(action_data, "Factor? ");
    action_data.getOutputImage() = action_data.getInputImage1() * factor;
}

void divide(ActionData &action_data)
{
    double factor = getDouble(action_data, "Factor? ");
    action_data.getOutputImage() = action_data.getInputImage1() / factor;
}

// ASSIGNMENT 6

void runFile(ActionData &action_data)
{
    MenuData menu_data = MenuData();
    configureMenu(menu_data);
    std::string file_name = getString(action_data, "File? ");

    std::ifstream fin(file_name);
    std::stringstream ss;
    std::string input = "";

    ActionData action_data_tmp(fin, action_data.getOS());
    action_data_tmp.copy(action_data);
    while (action_data.getIS().good() && !action_data.getDone())
    {
        if (!action_data.getQuiet())
        {
            showMenu(menu_data, action_data);
        }
        input = getChoice(action_data);
        if (input.size() > 0 && input[0] == '#')
        {
            input = "#";
        }
        takeAction(input, menu_data, action_data);
    }

    fin.close();
    action_data.copy(action_data_tmp);

    return;
}

// EXAM 2

void drawSquare(ActionData &action_data)
{
    int centerRow = getInteger(action_data, "Row? ");
    int centerCol = getInteger(action_data, "Column? ");
    int size = getInteger(action_data, "Size? ");
    int r = getInteger(action_data, "Red? ");
    int g = getInteger(action_data, "Green? ");
    int b = getInteger(action_data, "Blue? ");

    for (int row = centerRow - (size / 2); row <= centerRow + (size / 2); row++)
    {
        for (int col = centerCol - (size / 2); col <= centerCol + (size / 2); col++)
        {
            action_data.getInputImage1().setPixel(row, col, r, g, b);
        }
    }
}

void blendImages(ActionData &action_data)
{
    double ratio = getDouble(action_data, "Ratio? ");
    action_data.getOutputImage() = (action_data.getInputImage1() * ratio) + (action_data.getInputImage2() * (1 - ratio));
}

// ASSIGNMENT 7

void configureGrid(ActionData &action_data)
{
    int height = getInteger(action_data, "Grid Height? ");
    int width = getInteger(action_data, "Grid Width? ");
    int max_value = getInteger(action_data, "Grid Max Value? ");
    action_data.getGrid().setGridSize(height, width);
    action_data.getGrid().setMaxNumber(max_value);
}

void setGrid(ActionData &action_data)
{
    int row = getInteger(action_data, "Grid Row? ");
    int col = getInteger(action_data, "Grid Column? ");
    int value = getInteger(action_data, "Grid Value? ");
    action_data.getGrid().setNumber(row, col, value);
}

void applyGrid(ActionData &action_data)
{
    action_data.getGrid().setPPM(action_data.getOutputImage());
}

// ASSIGNMENT 8

void setFractalPlaneSize(ActionData &action_data)
{
    double minX = getDouble(action_data, "Min X? ");
    double maxX = getDouble(action_data, "Max X? ");
    double minY = getDouble(action_data, "Min Y? ");
    double maxY = getDouble(action_data, "Max Y? ");

    ComplexFractal *fptr = dynamic_cast<ComplexFractal *>(&action_data.getGrid());
    if (fptr != 0)
    {
        fptr->setPlaneSize(minX, maxX, minY, maxY);
    }
    else
    {
        action_data.getOS() << "Not a ComplexFractal object. Can't set plane size." << std::endl;
    }
}

void calculateFractal(ActionData &action_data)
{
    action_data.getGrid().calculateAllNumbers();
}

void setJuliaParameters(ActionData &action_data)
{
    double a_param = getDouble(action_data, "Parameter a? ");
    double b_param = getDouble(action_data, "Parameter b? ");

    JuliaSet *jptr = dynamic_cast<JuliaSet *>(&action_data.getGrid());
    if (jptr != 0)
    {
        jptr->setParameters(a_param, b_param);
    }
    else
    {
        action_data.getOS() << "Not a JuliaSet object. Can't set parameters." << std::endl;
    }
}

// ASSIGNMENT 9

void setJuliaFractal(ActionData &action_data)
{
    action_data.setGrid(new JuliaSet());
}

void setMandelbrotFractal(ActionData &action_data)
{
    action_data.setGrid(new MandelbrotSet());
}

// ASSIGNMENT 10

void applyGridColorTable(ActionData &action_data)
{
    action_data.getGrid().setPPM(action_data.getOutputImage(), action_data.getTable());
}

void setColorTableSize(ActionData &action_data)
{
    int size = getInteger(action_data, "Size? ");
    action_data.getTable().setNumberOfColors(size);
}

void setColor(ActionData &action_data)
{
    int position = getInteger(action_data, "Position? ");
    int r = getInteger(action_data, "Red? ");
    int g = getInteger(action_data, "Green? ");
    int b = getInteger(action_data, "Blue? ");

    action_data.getTable()[position].setRed(r);
    action_data.getTable()[position].setGreen(g);
    action_data.getTable()[position].setBlue(b);
}

void setRandomColor(ActionData &action_data)
{
    int position = getInteger(action_data, "Position? ");

    action_data.getTable().setRandomColor(255, position);
}

void setColorGradient(ActionData &action_data)
{
    int firstPosition = getInteger(action_data, "First position? ");
    int firstRed = getInteger(action_data, "First red? ");
    int firstGreen = getInteger(action_data, "First green? ");
    int firstBlue = getInteger(action_data, "First blue? ");

    int secondPosition = getInteger(action_data, "Second position? ");
    int secondRed = getInteger(action_data, "Second red? ");
    int secondGreen = getInteger(action_data, "Second green? ");
    int secondBlue = getInteger(action_data, "Second blue? ");

    Color color1 = Color(firstRed, firstGreen, firstBlue);
    Color color2 = Color(secondRed, secondGreen, secondBlue);

    action_data.getTable().insertGradient(color1, color2, firstPosition, secondPosition);
}

// EXAM 3

void setManhattanNumbers(ActionData &action_data)
{
    action_data.setGrid(new ManhattanNumbers());
}

void zoomPlane(ActionData &action_data)
{
    double zoomFactor = getDouble(action_data, "Zoom Factor? ");

    ComplexFractal *cptr = dynamic_cast<ComplexFractal *>(&action_data.getGrid());
    if (cptr != 0)
    {
        cptr->zoomPlane(zoomFactor);
    }
    else
    {
        action_data.getOS() << "Not a ComplexFractal object. Can't zoom." << std::endl;
    }
}

void setInvertedColorGradient(ActionData &action_data)
{
    int firstPosition = getInteger(action_data, "First position? ");
    int firstRed = getInteger(action_data, "First red? ");
    int firstGreen = getInteger(action_data, "First green? ");
    int firstBlue = getInteger(action_data, "First blue? ");

    int secondPosition = getInteger(action_data, "Second position? ");

    Color color1 = Color(firstRed, firstGreen, firstBlue);

    action_data.getTable().insertInvertedGradient(color1, firstPosition, secondPosition);
}

// ASSIGNMENT 11

ActionData::ActionData(std::istream &is, std::ostream &os)
    : mIS(is), mOS(os), mInputImage1(PPM(500, 500)), mInputImage2(PPM()), mOutputImage(PPM()), mGrid(0), mTable(ColorTable(16)), mDone(false), mQuiet(false)
{
    this->mTable.insertGradient(Color(0, 255, 0), Color(255, 0, 255), 0, 15);
}

ActionData::~ActionData()
{
}

std::istream &ActionData::getIS()
{
    return this->mIS;
}

std::ostream &ActionData::getOS()
{
    return this->mOS;
}

PPM &ActionData::getInputImage1()
{
    return this->mInputImage1;
}

PPM &ActionData::getInputImage2()
{
    return this->mInputImage2;
}

PPM &ActionData::getOutputImage()
{
    return this->mOutputImage;
}

NumberGrid &ActionData::getGrid()
{
    return *this->mGrid;
}

void ActionData::setGrid(NumberGrid *grid)
{
    if (this->mGrid != 0)
    {
        delete this->mGrid;
    }

    this->mGrid = grid;
}

ColorTable &ActionData::getTable()
{
    return this->mTable;
}

bool ActionData::getDone() const
{
    return this->mDone;
}

void ActionData::setDone()
{
    this->mDone = true;
}

bool ActionData::getQuiet() const
{
    return this->mQuiet;
}

void ActionData::toggleQuiet()
{
    this->mQuiet = !(this->mQuiet);
}

void ActionData::copy(ActionData &rhs)
{
    this->mInputImage1 = rhs.mInputImage1;
    this->mInputImage2 = rhs.mInputImage2;
    this->mOutputImage = rhs.mOutputImage;
    // careful with mGrid
    if (this->mGrid != 0)
    {
        delete this->mGrid;
    }
    this->mGrid = rhs.mGrid;
    rhs.mGrid = 0;
    // careful with mGrid
    this->mTable = rhs.mTable;
    // don't copy mDone; //this->mDone = rhs.mDone;
    this->mQuiet = rhs.mQuiet;
}

MenuData::MenuData()
{
}

void MenuData::addAction(const std::string &name, ActionFunctionType func, const std::string &description)
{
    if (mActionFunctions.find(name) == mActionFunctions.end())
    {
        this->mActionNames.push_back(name);
        this->mActionFunctions[name] = func;
        this->mActionDescriptions[name] = description;
    }
}

const std::vector<std::string> &MenuData::getNames() const
{
    return this->mActionNames;
}

ActionFunctionType MenuData::getFunction(const std::string &name)
{
    if (mActionFunctions.find(name) != mActionFunctions.end())
    {
        return mActionFunctions[name];
    }
    else
    {
        return 0;
    }
}

const std::string &MenuData::getDescription(const std::string &name)
{
    if (mActionDescriptions.find(name) != mActionDescriptions.end())
    {
        return mActionDescriptions[name];
    }
    else
    {
        throw std::string("Action" + name + "has no description.");
    }
}

void quit(ActionData &action_data)
{
    action_data.setDone();
}

void copyImage(ActionData &action_data)
{
    action_data.getOutputImage() = action_data.getInputImage1();
}

void grayFromRed(ActionData &action_data)
{
    action_data.getInputImage1().grayFromRed(action_data.getOutputImage());
}

void grayFromGreen(ActionData &action_data)
{
    action_data.getInputImage1().grayFromGreen(action_data.getOutputImage());
}

void grayFromBlue(ActionData &action_data)
{
    action_data.getInputImage1().grayFromBlue(action_data.getOutputImage());
}

void grayFromLinearColorimetric(ActionData &action_data)
{
    action_data.getInputImage1().grayFromLinearColorimetric(action_data.getOutputImage());
}

void rotateColorFilter(ActionData &action_data)
{
    action_data.getInputImage1().rotateColorFilter(action_data.getOutputImage());
}

void verticalEdgeFilter(ActionData &action_data)
{
    action_data.getInputImage1().findVerticalEdges(action_data.getOutputImage());
}

void horizontalEdgeFilter(ActionData &action_data)
{
    action_data.getInputImage1().findHorizontalEdges(action_data.getOutputImage());
}

void diagonalEdgeFilter(ActionData &action_data)
{
    action_data.getInputImage1().findDiagonalEdges(action_data.getOutputImage());
}

void verticalEdgeFilterThreshold(ActionData &action_data)
{
    double threshold = getDouble(action_data, "Threshold? ");
    action_data.getInputImage1().findVerticalEdges(action_data.getOutputImage(), threshold);
}

void horizontalEdgeFilterThreshold(ActionData &action_data)
{
    double threshold = getDouble(action_data, "Threshold? ");
    action_data.getInputImage1().findHorizontalEdges(action_data.getOutputImage(), threshold);
}

void diagonalEdgeFilterThreshold(ActionData &action_data)
{
    double threshold = getDouble(action_data, "Threshold? ");
    action_data.getInputImage1().findDiagonalEdges(action_data.getOutputImage(), threshold);
}

void quiet(ActionData &action_data)
{
    action_data.toggleQuiet();
}

void calculateFractalSingleThread(ActionData &action_data)
{
    action_data.getGrid().NumberGrid::calculateAllNumbers();
}
// EXAM 4

void antiAliasFilter(ActionData& action_data) 
{
    double n = getInteger(action_data, "Reduction count? ");
    action_data.getInputImage1().antiAlias(n, action_data.getOutputImage());
}

void configureMenu(MenuData &menu_data)
{
    menu_data.addAction("read1", readUserImage1, "Read file into input image 1.");
    menu_data.addAction("read2", readUserImage2, "Read file into input image 1.");
    menu_data.addAction("write", writeUserImage, "Write output image to file.");
    menu_data.addAction("copy", copyImage, "Copy input image 1 to output image.");
    menu_data.addAction("anti-alias", antiAliasFilter, "Set output image from Anti-alias filter on input image 1.");
    menu_data.addAction("grid", configureGrid, "Configure the grid.");
    menu_data.addAction("grid-set", setGrid, "Set a single value in the grid.");
    menu_data.addAction("grid-apply", applyGrid, "Use the grid values to set colors in the output image.");
    menu_data.addAction("manhattan", setManhattanNumbers, "Choose to make a Manhattan daction_data.getIS()tance grid.");
    menu_data.addAction("fractal-plane-size", setFractalPlaneSize, "Set the dimensions of the grid in the complex plane.");
    menu_data.addAction("fractal-calculate", calculateFractal, "Calculate the escape values for the fractal, multi-thread.");
    menu_data.addAction("fractal-calculate-single-thread", calculateFractalSingleThread, "Calculate the escape values for the fractal, single-thread.");
    menu_data.addAction("fractal-zoom", zoomPlane, "Zoom in or out of the complex plane.");
    menu_data.addAction("julia", setJuliaFractal, "Choose to make a Julia set.");
    menu_data.addAction("mandelbrot", setMandelbrotFractal, "Choose to make a Mandelbrot set.");
    menu_data.addAction("julia-parameters", setJuliaParameters, "Set the parameters of the Julia Set function.");
    menu_data.addAction("grid-apply-color-table", applyGridColorTable, "Use the grid values to set colors in the output image using the color table.");
    menu_data.addAction("set-color-table-size", setColorTableSize, "Change the number of slots in the color table.");
    menu_data.addAction("set-color", setColor, "Set the RGB values for one slot in the color table.");
    menu_data.addAction("set-random-color", setRandomColor, "Randomly set the RGB values for one slot in the color table.");
    menu_data.addAction("set-color-gradient", setColorGradient, "Smoothly set the RGB values for a range of slots in the color table.");
    menu_data.addAction("set-inverted-color-gradient", setInvertedColorGradient, "Smoothly set the values for a range of slots in the color table, using a color and its inverse.");
    menu_data.addAction("red-gray", grayFromRed, "Set output image from input image 1's grayscale from red.");
    menu_data.addAction("green-gray", grayFromGreen, "Set output image from input image 1's grayscale from green.");
    menu_data.addAction("blue-gray", grayFromBlue, "Set output image from input image 1's grayscale from blue.");
    menu_data.addAction("linear-gray", grayFromLinearColorimetric, "Set output image from input image 1's grayscale from linear colorimetric.");
    menu_data.addAction("rotate-color", rotateColorFilter, "Set output image from input image 1's rotate color filter.");
    menu_data.addAction("v-edge", verticalEdgeFilter, "Set output image from input image 1's vertical edge detection.");
    menu_data.addAction("h-edge", horizontalEdgeFilter, "Set output image from input image 1's horizontal edge detection.");
    menu_data.addAction("d-edge", diagonalEdgeFilter, "Set output image from input image 1's diagonal edge detection.");
    menu_data.addAction("v-edge-threshold", verticalEdgeFilterThreshold, "Set output image from input image 1's vertical edge detection with specified threshold.");
    menu_data.addAction("h-edge-threshold", horizontalEdgeFilterThreshold, "Set output image from input image 1's horizontal edge detection with specified threshold.");
    menu_data.addAction("d-edge-threshold", diagonalEdgeFilterThreshold, "Set output image from input image 1's diagonal edge detection with specified threshold.");
    menu_data.addAction("+", plus, "Set output image from sum of input image 1 and input image 2");
    menu_data.addAction("+=", plusEquals, "Set input image 1 by adding in input image 2");
    menu_data.addAction("-", minus, "Set output image from difference of input image 1 and input image 2");
    menu_data.addAction("-=", minusEquals, "Set input image 1 by subtracting input image 2");
    menu_data.addAction("*", times, "Set output image from input image 1 multiplied by a number");
    menu_data.addAction("*=", timesEquals, "Set input image 1 by multiplying by a number");
    menu_data.addAction("/", divide, "Set output image from input image 1 divided by a number");
    menu_data.addAction("/=", divideEquals, "Set input image 1 by dividing by a number");
    menu_data.addAction("blend", blendImages, "Blend input image 1 and input image 2 into the output image.");
    menu_data.addAction("size", setSize, "Set the size of input image 1");
    menu_data.addAction("max", setMaxColorValue, "Set the max color value of input image 1");
    menu_data.addAction("channel", setChannel, "Set a channel value in input image 1");
    menu_data.addAction("pixel", setPixel, "Set a pixel's 3 values in input image 1");
    menu_data.addAction("clear", clearAll, "Set all pixels to 0,0,0 in input image 1");
    menu_data.addAction("diamond", drawDiamond, "Draw a diamond shape in input image 1");
    menu_data.addAction("circle", drawCircle, "Draw a circle shape in input image 1");
    menu_data.addAction("box", drawBox, "Draw a box shape in input image 1");
    menu_data.addAction("square", drawSquare, "Draw a square shape in input image 1");
    menu_data.addAction("quiet", quiet, "Toggle output quieting");
    menu_data.addAction("quit", quit, "Quit");
    menu_data.addAction("run", runFile, "Run the commands in another file.");
    menu_data.addAction("#", commentLine, "Comment lines.");
}
