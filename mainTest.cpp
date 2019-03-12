#include "utility.h"
#include <strings.h>
#include <string.h>

using namespace std;

#define MAXLEN 256

int main (int argc, char** argv)
{
	image src, tgt, hsm;
	FILE *fp;
	char str[MAXLEN];
	char outfile[MAXLEN];
	char *pch;
	char *tch;
	char *gch;
	char *vch;
	char *ech;
	char *bch;
	char *ach;
	char *dch;
	char *fch;
	int roi, x, y, sx, sy, dR, dG, dB;
	
	if ((fp = fopen(argv[1],"r")) == NULL) {
		fprintf(stderr, "Can't open file: %s\n", argv[1]);
		exit(1);
	}

	while(fgets(str,MAXLEN,fp) != NULL) 
	{
		pch = strtok(str, " ");
		src.read(pch);

		pch = strtok(NULL, " ");
		strcpy(outfile, pch);

		pch = strtok(NULL, " "); // # of ROIS
		roi = atoi(pch);
		
		for(int i=0; i<roi; ++i)
		{
			
			pch = strtok(NULL, " "); //x
			x = atoi(pch);
			
			pch = strtok(NULL, " "); //y
			y = atoi(pch);
			
			pch = strtok(NULL, " "); //sx
			sx = atoi(pch);
			
			pch = strtok(NULL, " "); //sy
			sy = atoi(pch);
			
			pch = strtok(NULL, " ");
			if (strncasecmp(pch,"gThreshDir",MAXLEN)==0) 
			{
				pch = strtok(NULL, " ");
				tch = strtok(NULL, " ");
				
				utility::gradThresholdDir(src,tgt,atoi(pch),atoi(tch)-90,x,y,sx,sy);
			}
			else if(strncasecmp(pch,"gThresh",MAXLEN)==0) //
			{
				pch = strtok(NULL, " ");
				
				utility::gradThreshold(src,tgt,atoi(pch),x,y,sx,sy);
			}
			else if(strncasecmp(pch,"colorThresh",MAXLEN)==0)
			{
				pch = strtok(NULL, " "); //a
				
				utility::colorGrad(src,tgt,atoi(pch),x,y,sx,sy);
			}
			else if (strncasecmp(pch,"binarize",MAXLEN)==0) 
			{
				/* Thresholding */
				pch = strtok(NULL, " ");
				tch = strtok(NULL, " ");
				
				utility::binarize(src,tgt,atoi(pch),atoi(tch),x,y,sx,sy);
				src.copyImage(tgt);
			}
			else if(strncasecmp(pch,"colorMod",MAXLEN)==0)
			{
				pch = strtok(NULL, " ");
				dR = atoi(pch);
				
				pch = strtok(NULL, " ");
				dG = atoi(pch);
				
				pch = strtok(NULL, " ");
				dB = atoi(pch);
				
				utility::colorMod(src,tgt,dR,x,y,sx,sy,0);
				src.copyImage(tgt);
				
				utility::colorMod(src,tgt,dB,x,y,sx,sy,2);
				src.copyImage(tgt);
				
				utility::colorMod(src,tgt,dG,x,y,sx,sy,1);
				src.copyImage(tgt);
			}
			else if(strncasecmp(pch,"WS",MAXLEN)==0)
			{
				pch = strtok(NULL, " ");
				
				utility::WS(src, tgt, atoi(pch), x, y, sx, sy);
				src.copyImage(tgt);
			}
			else if(strncasecmp(pch,"oneWS",MAXLEN)==0)
			{
				pch = strtok(NULL, " ");
				
				utility::oneWS(src, tgt, atoi(pch), x, y, sx, sy);
				src.copyImage(tgt);
			}
			else 
			{
				printf("No function: %s\n", pch);
				continue;
			}
			
		}
		tgt.save(outfile);
	}
	
	fclose(fp);
	return 0;
}
