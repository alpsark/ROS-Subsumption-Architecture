/*
 * image_helper.h
 *
 *  Created on: Apr 20, 2013
 *      Author: okan
 */

#ifndef IMAGE_HELPER_H_
#define IMAGE_HELPER_H_

#include <sensor_msgs/Image.h>

class ImageHelper {
public:
	ImageHelper();
	virtual ~ImageHelper();

	void processImage(const sensor_msgs::ImageConstPtr& imageConstPtr);

	bool isBallKnown;
	int centerx;
	int centery;
	int redCount;
};

#endif /* IMAGE_HELPER_H_ */
