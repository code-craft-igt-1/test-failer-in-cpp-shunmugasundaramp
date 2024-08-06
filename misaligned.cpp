#include <assert.h>
#include <iostream>
#include <sstream>
#include <tuple>

int printColorMap() {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    int i = 0, j = 0;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            std::cout << i * 5 + j << " | " << majorColor[i] << " | " << minorColor[i] << "\n";
        }
    }
    return i * j;
}

std::tuple<int, int, int> getCellDetails(std::string row) {
    std::istringstream iss(row);
    std::string cell;
    int columnWidth[3] = { 0 };
    int columnIndex = 0;
    std::tuple<int, int, int> cellDetails = std::make_tuple(-1, -1, -1);
    while (std::getline(iss, cell, '|') && columnIndex < 3) {
        columnWidth[columnIndex] = cell.length();
        if (columnIndex == 2) {
            cellDetails = std::make_tuple(columnWidth[0], columnWidth[1], columnWidth[2]);
            break;
        }
        columnIndex++;
    }
    return cellDetails;
}

bool alignmentCheck(std::stringstream& colormapOutput) {
    std::string str;
    std::tuple<int, int, int> previousCellDetails = std::make_tuple(-1, -1, -1);
    while (std::getline(colormapOutput, str)) {
        std::tuple<int, int, int> cellDetails = getCellDetails(str);
        // invalid cell size or empty columns
        assert(cellDetails != std::make_tuple(-1, -1, -1));
        if (previousCellDetails == std::make_tuple(-1, -1, -1)) {
            previousCellDetails = cellDetails;
        }
        // column size not consistent
        assert(previousCellDetails == cellDetails);
    }
    return true;
}

int main() {
    std::stringstream colormapOutput;
    std::streambuf *coutbuf = std::cout.rdbuf(colormapOutput.rdbuf());
    int result = printColorMap();
    std::cout.rdbuf(coutbuf);

    assert(alignmentCheck(colormapOutput));
    assert(result == 25);

    std::cout << "All is well (maybe!)\n";
    return 0;
}
