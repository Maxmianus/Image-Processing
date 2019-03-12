#ifndef UTILITY_H
#define UTILITY_H

#include "image.h"
#include <sstream>
#include <math.h>
#include "string.h"

class utility
{
	public:
		utility();
		virtual ~utility();
		static std::string intToString(int number);
		static int checkValue(int value);
		static void addGrey(image &src, image &tgt, int value);
		static void colorMod(image &src, image &tgt, int value, int x, int y, int sx, int sy, const int rgb);
		static void scale(image &src, image &tgt, float ratio);
		static void binarize(image &src, image &tgt, int threshold);
		static void cv_gray(cv::Mat &src, cv::Mat &tgt);
		static void cv_avgblur(cv::Mat &src, cv::Mat &tgt, int WindowSize);
		static void displayHistogram(image &src, image &hsm, int x, int y, int sx, int sy, char *fn);
		static void stretching(image &src, image &tgt, int a, int b, int d, int x, int y, int sx, int sy);
		static void biStretching(image &src, image &tgt, int a, int b, int c, int d, int e, int f, int x, int y, int sx, int sy);
		static void hsiStretching(image &src, image &tgt, int a, int b2, int e, int d, int x, int y, int sx, int sy);
		static void hsiToRGB(image &src, float h, float s, float i, int x, int y);
		static int gradientAmp(image &src, int x, int y);
		static int colorAmp(image &src, int x, int y, int rgb);
		static void gradThreshold(image &src, image &tgt, int threshold, int x, int y, int sx, int sy);
		static void gradThresholdDir(image &src, image &tgt,int threshold, int dir, int x, int y, int sx, int sy);
		static void colorGrad(image &src, image &tgt, int threshold, int x, int y, int sx, int sy);
		static int getDY(image &src, int x, int y);
		static int getDX(image &src, int x, int y);
		static int hsiAmp(image &src, int x, int y);
		static void WS(image &src, image &tgt, int value, int x, int y, int sx, int sy);
		static void oneWS(image &src, image &tgt, int value, int x, int y, int sx, int sy);
		static void hsiEdge(image &src, image &tgt, int threshold, int x, int y, int sx, int sy);
};

#endif

