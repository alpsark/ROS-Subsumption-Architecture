/*
 * MapHelper.cpp
 *
 *  Created on: Apr 11, 2013
 *      Author: okan
 */

#include "map_helper.h"
#define PI 3.1415926535897932384626433f

MapHelper::MapHelper()
{
	 
}

MapHelper::MapHelper(const nav_msgs::OccupancyGrid& _grid) {
	occupancyGrid = _grid;

	// debug tests
	std::cout << "origin.x=" << occupancyGrid.info.origin.position.x << " origin.y="
			<< occupancyGrid.info.origin.position.y << std::endl;
	std::cout << "resolution=" << occupancyGrid.info.resolution << std::endl;
	std::cout << "width=" << occupancyGrid.info.width << " height=" << occupancyGrid.info.height << std::endl;

	resolution = occupancyGrid.info.resolution;
	width = occupancyGrid.info.width;
	height = occupancyGrid.info.height;
	originx = occupancyGrid.info.origin.position.x;
	originy = occupancyGrid.info.origin.position.y;

	// validate linear indexing
	//		double startx = -2.5;
	//		double starty = -2.5;
	//		for (int i = 0; i < 120; i++)
	//		{
	//			for (int j = 0; j < 120; j++)
	//			{
	//				double px = startx + resolution*j;
	//				double py = starty + resolution*i;
	//				if (isOccupied(px, py)) {
	//					std::cout << "X";
	//				} else {
	//					std::cout << ".";
	//				}
	//			}
	//			std::cout << std::endl;
	//		}

	//		double pointx = -1.5;
	//		double pointy = 0;
	//
	//		pointx = pointx - originx;
	//		pointy = pointy - originy;
	//
	//		std::cout << "pointx=" << pointx << " pointy=" << pointy << std::endl;
	//
	//		int row = floor(pointy/resolution);
	//		int col = floor(pointx/resolution);
	//
	//		std::cout <<"row=" << row << " col=" << col << std::endl;
	//		int linearIndex = row * width + col;
	//		std::cout << "linearIndex=" << linearIndex << std::endl;
	//		std::cout << (int)occupancyGrid.data[linearIndex] << std::endl;

	//	std::cout << "occupied=" << isOccupied(-2.5, 1, 2.0, 1.2) << std::endl;
	//	std::cout << "occupied=" << isOccupied(0, 1, 0.0, 0.0) << std::endl;
	std::cout << "occupied=" << isOccupied(0.0, -5.5) << std::endl;

}

MapHelper::~MapHelper()
{
}

bool MapHelper::isOccupied(int rowIndex, int colIndex)
{
	
	int linearIndex = rowIndex * width + colIndex;
	int occupancy = (int)occupancyGrid.data[linearIndex];
        linearIndex = (rowIndex) * width + (colIndex);
	occupancy = (int)occupancyGrid.data[linearIndex];
	if (occupancy > 0 || occupancy == -1 ) //
	{
		return true;
	}
		
	
return false;
}

bool MapHelper::isOccupied(double pointx, double pointy)
{		
			//std::cout << "point: "  << pointx << std::endl ; 
		pointx = pointx - originx;
		pointy = pointy - originy;
		int row = floor(pointy/resolution);
		int col = floor(pointx/resolution);
		int linearIndex = row * width + col;
		int occupancy = (int)occupancyGrid.data[linearIndex];
                linearIndex = (row) * width + (col);
		occupancy = (int)occupancyGrid.data[linearIndex];
		//std::cout <<  occupancy << " " ; 
		if (occupancy > 0 || occupancy == -1 )//
		{	
			return true;
		}
		
	
return false;
}

bool MapHelper::isOccupied(double startx, double starty, double endx, double endy)
{
	int startrow = getRowIndex(starty);
	int startcol = getColIndex(startx);
	int endrow = getRowIndex(endy);
	int endcol = getColIndex(endx);

	if(startrow == endrow && startcol == endcol)
		return true;

	//		std::cout << "startrow=" << startrow << " startcol=" << startcol << std::endl;
	//		std::cout << "endrow=" << endrow << " endcol=" << endcol << std::endl;
	double diffrow =  (endrow - startrow);
	double diffcol = (endcol - startcol);
	double rowStep, colStep;
	bool greatRowDiff = false;
	if (fabs(diffrow) > fabs(diffcol)) {
		rowStep = diffrow / fabs(diffrow);
		colStep = diffcol / fabs(diffrow);
		for (int i = 0; i < fabs(diffrow)+1; i++) {
			int newrow = round(startrow + rowStep*i);
			int newcol = round(startcol + colStep*i);
			//				std::cout << "newrow=" << newrow << " newcol=" << newcol << std::endl;
			if (isOccupied(newrow, newcol)) {
				return true;
			}
		}
	} else {
		rowStep = diffrow / fabs(diffcol);
		colStep = diffcol / fabs(diffcol);
		for (int i = 0; i < fabs(diffcol)+1; i++) {
			int newrow = round(startrow + rowStep*i);
			int newcol = round(startcol + colStep*i);
			if (isOccupied(newrow, newcol)) {
				return true;
			}
			//				std::cout << "newrow=" << newrow << " newcol=" << newcol << std::endl;
		}
	}
	//		std::cout <<"diffrow=" << diffrow << std::endl;
	//		std::cout << "diffcol=" << diffcol << std::endl;
	//
	//		std::cout <<"rowStep=" << rowStep << std::endl;
	//		std::cout << "colStep=" << colStep << std::endl;
	return false;
}

int MapHelper::getRowIndex(double py) {
	py = py - originy;
	int row = floor(py/resolution);
	return row;
}

int MapHelper::getColIndex(double px) {
	px = px - originx;
	int col = floor(px/resolution);
	return col;
}

void MapHelper::processMap(const nav_msgs::OccupancyGridConstPtr& occupancyGridConstPtr)
{
	//std::cout << "origin.x=" << occupancyGridConstPtr->info.origin.position.x << " origin.y="
	//			<< occupancyGridConstPtr->info.origin.position.y << std::endl;
//	std::cout << "resolution=" << occupancyGridConstPtr->info.resolution << std::endl;
//	std::cout << "width=" << occupancyGridConstPtr->info.width << " height=" << occupancyGridConstPtr->info.height << std::endl;

	resolution = occupancyGridConstPtr->info.resolution;
	width = occupancyGridConstPtr->info.width;
	height = occupancyGridConstPtr->info.height;
	originx = occupancyGridConstPtr->info.origin.position.x;
	originy = occupancyGridConstPtr->info.origin.position.y;
	occupancyGrid = *occupancyGridConstPtr;

	
			//    0  +x 0 
	  //3 +y PI/2	       1 -y -PI/2
		 //   2 -x PI
	

}
