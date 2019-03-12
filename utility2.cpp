#include "utility.h"

#define MAXRGB 255
#define MINRGB 0

std::string utility::intToString(int number)
{
   std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

int utility::checkValue(int value)
{
	if (value > MAXRGB)
		return MAXRGB;
	if (value < MINRGB)
		return MINRGB;
	return value;
}

/*-----------------------------------------------------------------------**/
void utility::addGrey(image &src, image &tgt, int value)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			tgt.setPixel(i,j,checkValue(src.getPixel(i,j)+value)); 
		}
}

/*-----------------------------------------------------------------------**/
void utility::scale(image &src, image &tgt, float ratio)
{
	int rows = (int)((float)src.getNumberOfRows() * ratio);
	int cols  = (int)((float)src.getNumberOfColumns() * ratio);
	tgt.resize(rows, cols);
	for (int i=0; i<rows; i++)
	{
		for (int j=0; j<cols; j++)
		{	
			/* Map the pixel of new image back to original image */
			int i2 = (int)floor((float)i/ratio);
			int j2 = (int)floor((float)j/ratio);
			if (ratio == 2) {
				/* Directly copy the value */
				tgt.setPixel(i,j,checkValue(src.getPixel(i2,j2)));
			}

			if (ratio == 0.5) {
				/* Average the values of four pixels */
				int value = src.getPixel(i2,j2) + src.getPixel(i2,j2+1) + src.getPixel(i2+1,j2) + src.getPixel(i2+1,j2+1);
				tgt.setPixel(i,j,checkValue(value/4));
			}
		}
	}
}

/*-----------------------------------------------------------------------**/
void utility::binarize(image &src, image &tgt, int threshold)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			if (src.getPixel(i,j) < threshold)
				tgt.setPixel(i,j,MINRGB);
			else
				tgt.setPixel(i,j,MAXRGB);
		}
	}
}

/*-----------------------------------------------------------------------**/
//Try creating a black image then each number of values in the histogram corresponds to a a max RGB value
void utility::displayHistogram(image &src, image &hsm, int x, int y, int sx, int sy, char *fn)
{
	//initializes array
	int array[256];
	hsm.resize(256, 256);
	
	for(int i=0; i<256; ++i)
	{
		array[i] = 0;
	}
	
	//loop through image matrix and add them to 256 size array
	for(int i=0; i<src.getNumberOfColumns(); ++i)
	{
		for(int j=0; j<src.getNumberOfRows(); ++j)
		{
			array[src.getPixel(j,i)] += 1;
		}
	}
	
	for(int x =0; x<256; ++x)
	{
		array[x] = array[x]/100;
		
		for(int y=255; array[x]>0; --y )
		{
			hsm.setPixel(y,x, 255);
			array[x] = array[x]-1;
		}
	}
	
	hsm.save(fn);
}

/*-----------------------------------------------------------------------**/
void utility::biStretching(image &src, image &tgt, int a, int b, int c, int d, int e, int f, int x, int y, int sx, int sy)
{
	tgt.copyImage(src);
	//double for loop to loop through image matrix
	for(int j=x; j<sx; ++j)
	{
		for(int h=y; h<sy; ++h)
		{
			if(src.getPixel(h,j) < a+1)
			{
				tgt.setPixel(h,j, d);
			}
			else if(src.getPixel(h,j) < b && src.getPixel(h,j) > a)
			{
				float temp = (float)(src.getPixel(h,j) - a)*((float)(e-d)/(float)(b-a));
				int con = round(temp + d);
				
				tgt.setPixel(h,j,con);
			}
			else if(src.getPixel(h,j) < c && src.getPixel(h,j) > b)
			{
				float temp = (float)(src.getPixel(h,j) - a)*((float)(f-e)/(float)(b-a));
				int con = round(temp + d);
				
				tgt.setPixel(h,j,con);
			}
			else
			{
				tgt.setPixel(h,j,f);
			}
		}
	}
}

/*-----------------------------------------------------------------------**/
void utility::stretching(image &src, image &tgt, int a, int b, int d, int x, int y, int sx, int sy)
{
	tgt.copyImage(src);
	//double for loop to loop through image matrix
	for(int j=x; j<sx; ++j)
	{
		for(int h=y; h<sy; ++h)
		{
			float temp = (float)(src.getPixel(h,j) - a)*((float)(255-d)/(float)(b-a));
			//printf("%f\n", temp);
			int con = round(temp + d);
			//printf("%d\n", con);
			if(src.getPixel(h,j) < a)
			{
				tgt.setPixel(h,j, d);
			}
			else if(src.getPixel(h,j) > b)
			{
				tgt.setPixel(h,j, 255);
			}
			else
			{
				tgt.setPixel(h,j, con);
			}
		}
	}
}

/*-----------------------------------------------------------------------**/
void utility::hsiStretching(image &src, image &tgt, int a, int bTwo, int e, int d, int x, int y, int sx, int sy)
{
	float r, g, b, hue, sat, intensity, test;
	tgt.copyImage(src);
	
	for(int h=x; h<sx; ++h)
	{
		for(int j=y; j<sy; ++j)
		{
			r = (float)src.getPixel(h,j,0)/(float)(src.getPixel(h,j,0) + src.getPixel(h,j,1) + src.getPixel(h,j,2));
			g = (float)src.getPixel(h,j,1)/(float)(src.getPixel(h,j,0) + src.getPixel(h,j,1) + src.getPixel(h,j,2));
			b = (float)src.getPixel(h,j,2)/(float)(src.getPixel(h,j,0) + src.getPixel(h,j,1) + src.getPixel(h,j,2));
			
			if(b>g)
			{
				hue = ((2*3.14) - ((acos(((.5)*((r-g)+(r-b)))/(float)pow((pow((r-g),2) + (r-b)*(g-b)),(.5)))))) * 180/ 3.14;
			}
			else
			{
				hue = acos(((.5)*((r-g)+(r-b)))/(float)pow((pow((r-g),2) + (r-b)*(g-b)),(.5))) * 180/ 3.14;
			}
			
			sat = (float)((1 - (3 * min(min(r,b),g)))*100);
			
			intensity = ((float)(src.getPixel(h,j,0) + src.getPixel(h,j,1) + src.getPixel(h,j,2))/(3*255))*255;
			
			if(r == g && r==b)
			{
				hue = 0;
				sat = 0;
			}
			
			if(intensity < a)
			{
				intensity = d;
				hsiToRGB(tgt, hue, sat, intensity, h, j);
			}
			else if(intensity > bTwo)
			{
				intensity = e;
				hsiToRGB(tgt, hue, sat, intensity, h, j);
			}
			else
			{
				intensity = (float)(intensity - a)*((e-d)/(float)(bTwo-a)) + d;
				hsiToRGB(tgt, hue, sat, intensity, h, j);
			}
		}
	}
}

/*-----------------------------------------------------------------------**/
void utility::hsiToRGB(image &src, float h, float s, float i, int x, int y)
{
	float m, n, o;//x, y, z
	
	h = (h*3.14)/180;
	s = s/100;
	i = i/255;
	
	if(h<((2*3.14)/3))
	{
		m = (i * (1-s))*255;
		n = (i * (1+ (s*cos(h))/cos(3.14/3-h)))*255;
		o = ((3*i) - ((m/255) + (n/255)))*255;
		
		
		src.setPixel(x,y,0,(int)n);
		src.setPixel(x,y,1,(int)o);
		src.setPixel(x,y,2,(int)m);
	}
	else if((h == ((2*3.14)/3) || h > ((2*3.14)/3)) && h < ((4*3.14)/3))
	{
		h = h - ((2*3.14)/3);
		m = (i * (1-s))*255;
		n = (i * (1+ (s*cos(h))/cos(3.14/3-h)))*255;
		o = ((3*i) - ((m/255) + (n/255)))*255;
		
		src.setPixel(x,y,0,(int)m);
		src.setPixel(x,y,1,(int)n);
		src.setPixel(x,y,2,(int)o);
	}
	else
	{
		h = h - ((4*3.14)/3);
		m = (i * (1-s))*255; //g
		n = (i * (1+ (s*cos(h))/cos(3.14/3-h)))*255; //b
		o = ((3*i) - ((m/255) + (n/255)))*255; //r
		
		src.setPixel(x,y,0,(int)o);
		src.setPixel(x,y,1,(int)m);
		src.setPixel(x,y,2,(int)n);
	}
}

/*-----------------------------------------------------------------------**/
int utility::gradientAmp(image &src, int x, int y)
{
	
	int grad;
	int dx = abs(src.getPixel(x+1,y-1) + (2*src.getPixel(x+1,y)) + src.getPixel(x+1, y+1) - (src.getPixel(x-1, y-1) + (2*src.getPixel(x-1,y)) + src.getPixel(x-1, y+1)));
	int dy = abs(src.getPixel(x-1,y-1) + (2*src.getPixel(x,y-1) + src.getPixel(x+1,y-1)) - (src.getPixel(x-1,y+1) + (2*src.getPixel(x,y+1)) + src.getPixel(x+1,y+1)));

	
	grad = dx + dy;
	
	return grad;
}

/*-----------------------------------------------------------------------**/
int utility::colorAmp(image &src, int x, int y, int rgb)
{
	int dx = abs(src.getPixel(x+1,y-1,rgb) + (2*src.getPixel(x+1,y,rgb)) + src.getPixel(x+1, y+1,rgb) - (src.getPixel(x-1, y-1,rgb) + (2*src.getPixel(x-1,y,rgb)) + src.getPixel(x-1, y+1,rgb)));
	int dy = abs(src.getPixel(x-1,y-1,rgb) + (2*src.getPixel(x,y-1,rgb) + src.getPixel(x+1,y-1,rgb)) - (src.getPixel(x-1,y+1,rgb) + (2*src.getPixel(x,y+1,rgb)) + src.getPixel(x+1,y+1,rgb)));
	int grad = dx + dy;
	
	return grad;
}

/*-----------------------------------------------------------------------**/
int utility::getDX(image &src, int x, int y)
{
	int dx = src.getPixel(x+1,y-1) + (2*src.getPixel(x+1,y)) + src.getPixel(x+1, y+1) - (src.getPixel(x-1, y-1) + (2*src.getPixel(x-1,y)) + src.getPixel(x-1, y+1));

	return dx;
}

/*-----------------------------------------------------------------------**/
int utility::getDY(image &src, int x, int y)
{
	int dy = src.getPixel(x-1,y-1) + (2*src.getPixel(x,y-1) + src.getPixel(x+1,y-1)) - (src.getPixel(x-1,y+1) + (2*src.getPixel(x,y+1)) + src.getPixel(x+1,y+1));
	
	return dy;
}

/*-----------------------------------------------------------------------**/
void utility::gradThreshold(image &src, image &tgt, int threshold, int x, int y, int sx, int sy)
{
	tgt.copyImage(src);
	int gradTemp;
	
	for (int i=y; i<sy; i++)
	{
		for (int j=x; j<sx; j++)
		{
			gradTemp = gradientAmp(src,j,i);
			
			if(gradTemp > threshold-1)
			{
				tgt.setPixel(j,i,MAXRGB);
			}
			else
			{
				tgt.setPixel(j,i,MINRGB);
			}
		}
	}
}

/*-----------------------------------------------------------------------**/
void utility::gradThresholdDir(image &src, image &tgt,int threshold, int dir, int x, int y, int sx, int sy)
{
	//tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	tgt.copyImage(src);
	double gradTemp;
	int temp;
	
	for (int i=y; i<sy; i++)
	{
		for (int j=x; j<sx; j++)
		{
			if(getDX(src,j,i) == 0)
			{
				gradTemp = 90;
			}
			else
			{
				gradTemp = (atan(getDY(src,j,i)/getDX(src,j,i)) * 180)/3.14;
			}
			
			temp = gradientAmp(src,j,i);
			
			if(gradTemp > dir-10 && gradTemp < dir+10)
			{
				if(temp > threshold-1)
				{
					tgt.setPixel(j,i,MAXRGB);
				}
				else
				{
					tgt.setPixel(j,i,MINRGB);
				}
			}
			else
			{
				tgt.setPixel(j,i,MINRGB);
			}
		}
	}
}

/*-----------------------------------------------------------------------**/
void utility::colorGrad(image &src, image &tgt, int threshold, int x, int y, int sx, int sy)
{
	tgt.copyImage(src);
	int gradTemp;
	
	for (int i=x; i<sx; i++)
	{
		for (int j=y; j<sy; j++)
		{
			for(int t=0; t<3; ++t)//t = rgb values
			{
				gradTemp = colorAmp(src,i,j,t);
				
				if(gradTemp > threshold-1)
				{
					for(int h=0; h<3; ++h)
					{
						tgt.setPixel(i,j,h,MAXRGB);
					}
					break;
				}
				else
				{
					tgt.setPixel(i,j,t,MINRGB);
				}
			}
		}
	}
	
}

/*-----------------------------------------------------------------------**/
void utility::cv_gray(Mat &src, Mat &tgt)
{
	cvtColor(src, tgt, CV_BGR2GRAY);
}

/*-----------------------------------------------------------------------**/
void utility::cv_avgblur(Mat &src, Mat &tgt, int WindowSize)
{
	blur(src,tgt,Size(WindowSize,WindowSize));
}

/*________________________________________________________________________________________________**/
void utility::WS(image &src, image &tgt, int value, int x, int y, int sx, int sy)
{
	tgt.copyImage(src);
	
	//First two for loops for iterating through x and y, last two for loops for iterating through size of window square size
	for(int i=y; i<sy; i++)
	{
		for(int j=x; j<sx; j++)
		{
			int t = 0;
			int p = 0;
			int sum = 0;
			
			for(int m = i-1; t<value; m++)
			{
				for(int n = j-1; p<value; n++)
				{
					if((n || m) < 0)
					{
						sum = sum + MAXRGB;
					}
					else
					{
						sum = sum + src.getPixel(n, m);
					}
					
					p++;
				}
				
				t++;
			}
			
			int q = sum/(value);
			
			tgt.setPixel(j, i, q);
		}
	
	}
}

/*________________________________________________________________________________________________**/
void utility::oneWS(image &src, image &tgt, int value, int x, int y, int sx, int sy)
{
	tgt.copyImage(src);
	
	for(int i=y; i<sy; i++)
	{
		for(int j=x; j<sx; j++)
		{
			int t = 0;
			int p = 0;
			int sum = 0;
			
			for(int m = i-1; t<value; m++)
			{
				for(int n = j-1; p<value; n++)
				{
					if((n || m) < 0)
					{
						sum = sum + MAXRGB;
					}
					else
					{
						sum = sum + src.getPixel(n, m);
					}
					
					p++;
				}
				
				t++;
			}
			
			int q = sum/(value);
			tgt.setPixel(j, i, q);
		}
	
	}
}
