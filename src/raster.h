//
// Ulises Olivares
// uolivares@unam.mx
// June 13, 2020.
//

#ifndef SRC_RASTER_H
#define SRC_RASTER_H

#endif //SRC_RASTER_H

#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/mat.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <memory>
#include <stdexcept>
#include <cstdio>
#include <algorithm>
#include <map>
#include <set>
#include "gdal.h"
#include "gdal_priv.h"
#include "ogr_spatialref.h"

using namespace std;
using namespace cv;

// Struct definition
struct Point2D {
    int x, y;
    Point2D () {};
    Point2D(int x, int y) : x(x), y(y) {}
    bool operator () (Point2D const &e) const {
        return (x == e.x && y == e.y);
    }
};

struct Grid {
    vector<Point2D> elements;
    int noElements = 0;
    int invalidCells = 0;
    int id;
    float sum = 0.0;
    float biomass = 0;
    float friction = 0;
    float value;
    float biomassAvg = 0;

    Grid() {}

    Grid(vector<Point2D> elements, int noElements, int invalidCells, float sum) :
            elements(elements),noElements(noElements), invalidCells(invalidCells), sum(sum) {}

};

struct cellVecinos {
    int x, y;
    float distance;
    cellVecinos(int x, int y, float distance) :
            x(x), y(y), distance(distance) {}
};


class Raster{
public:



    // Method definition
    bool isInsideGrid(int i, int j);
    float** tiff_to_matrix_gdal(string file, bool flag);
    void write_image(float** output_raster, int rows, int cols, string heuristic, int stop, string map, string algName);
    void define_intervals(int stop, int &xIntervals, int &yIntervals);
    map<float,Grid> define_grids(int rows, int cols, const int &xIntervals, const int &yIntervals, float** biomass, float** friction);
    Point2D find_centroid(map<float,Grid> grids, float** biomass, float** friction);
    set<cellVecinos>vecinos2(int origen_x, int origen_y);
    set<cellVecinos> vecinos3(set<cellVecinos> vecinos);
    void matrix_to_tiff(float** output_raster, int rows, int cols, string heuristic, int stop, string map, string algName);
    void check_npa(float** npa_matrix, float** &biomass_matrix);
    void check_waterbodies(float** water_matrix, float** &biomass_matrix);
    void reproject_coords(string map_biomass);

    // Get methods
    int getCols();
    int getRows();
    int getValidPoints();
    int getIntervals();
    double getProjection();
    int getTotalGrids();
    int getXMin();
    int getYMin();
    int getXMax();
    int getYMax();


private:
    float avg_biomasa, pixels_necesarios = 0, xMax = FLT_MIN, xMin = FLT_MAX, yMax = FLT_MIN, yMin = FLT_MAX;
    int ROWS, COLS, intervals = 0, totValidGrids = 0, totGridsAvg = 0, valid_points = 0;
    bool flag = true;
    double projection, adfGeoTransform[6];
    string proj, epsg;
    vector<Point2D> active_raster;
    float** costos;
    map<float,Grid> gridsMap;
    vector<float> tokens;


};