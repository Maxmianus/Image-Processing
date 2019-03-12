Image Processing - Christopher Dixon
--------------------------------------------------------
Text File Parameters:
	The general format of parameter files are: "inputFile.pgm" "outputFile.pgm" #ofROIs #x1 #y1 #sx1 #sy1 "functionName" 
	(various inputs depending on which function is called) (parameters depending on which function) with x1 and y1 being the starting point
	of the region of interest and sx1 and sy1 being the ending points.
	
	For greyscale images I have included a black colored picture called "histogram.pgm", which I use to base the output of the histograms on
	
	
	
	Example Parameters:
		pen.ppm pen_125.ppm 1 0 0 286 490 hsiStretch 20 100 200 0
		slope.pgm slope_126.pgm 1 0 0 300 300 greyStretch 100 200 50 histogram.pgm histogramA.pgm histogramB.pgm
--------------------------------------------------------
How To Run:
	Running the makefile provided from the project directory should compile all the nessecary programs then in the command line typing main "parameters.txt" will create the new, edited picture
	(parameters.txt being any text file not necessarily that exact name).

--------------------------------------------------------
Functions:

  Each function has the arguments of the region of interests in it, x, y, sx, sy, except for displayHistogram.
	
	hsiStretching - Converts the colored image from RGB to HSI then performs contrast stretching on the intensity, afterwards it converts
		the image back to RGB and outputs it the directed file.
	
	stretching - Performs contrast stretching on a greyscale image
	
	displayHistogram - Creates a histogram of a greyscale image based on its current pixels values, outputs it to the directed file
	
	biStretching - Contrast stretching function that takes in six different inputs instead of three and spreads the pixels out across
		a wider range of distribution.
    
  	colorGrad: Computes the gradient magnitude for each color channel of a color image then makes the pixel either black or white 
		depending on the given threshold.
	
	gradThreshDir: Computes the gradient magnitude then depending on the edge orientation given by the user makes a pixel either black
		or white.
	
	gradThreshold: Computes the gradient magnitude then decides whether the pixel is black or white depending on the threshold
	
	hsiEdge: Performs edge detection on the intensity after converting from RGB to HSI. Converts back afterwards.
  
 	 binarize - Binarizes the function depending on the threshold levels, any pixel lower than the lowest threshold or higher than the highest threshold makes the pixel
	turn black, while any pixel between the two thresholds turn white.
	
	colorMod - Function that either increases or decreases the intensity of any of the channels (red, blue, green).
	Has three integer arguments, dR (red), dB (blue), dG (green), the values being the amount to change each color intenstity.
	
	WS - Uniform smoothing operation is a function that takes the average of neighboring pixels and sets the value as the new pixel. 
	Has one argument N, which is the window size which must be odd.
	
