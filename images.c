/***************************************
* Author: Rui Min *
****************************************/

#include <stdio.h>

 #define TABLESIZE 512

//  #define DEBUG    // uncomment for debug mode
 
 // global variables and functions defined in functions.c
 extern int colorPixelSafe [TABLESIZE];
 extern int colorPixel [TABLESIZE];
 extern int safePixelCount;
 extern int allPixelCount;
 extern char colorDescriptions[TABLESIZE][50];

 void fillDescription(int r, int g, int b, int index);
 void analysis_display();


 
int main(int argc, char *argv[])
{
	int h,  w;  // height width of image
	int safeS, safeW;  // safe start, safe width
	
	int rgb, rgb9;  // rgb for read in color value,  rgb9 for 3+3+3 bits combined value 

	int i; 
	for (i=0; i<TABLESIZE; i++ )
	{
	   colorPixelSafe[i] = colorPixel[i] = 0;
	}

	safePixelCount = 0;	allPixelCount = 0;	// Initialization

 	while ( scanf("%d %d %d %d", &w, &h,&safeS, &safeW) != EOF) // try to read first 4 values of each line
	{
	   printf("scanning pixel data for a new image..... \n");
	   for (i=0; i<w*h; i++)
	   {
 	    // use scanf to read in a color and process
		scanf("%d", &rgb);
		int r,g,b;
		r = (rgb >> 16) & 0xFF;		// shift as 8 bits binary
		g = (rgb >> 8) & 0xFF;		// shift as 8 bits binary
		b = (rgb) & 0xFF;			// shift as 8 bits binary
		rgb9 = (r<<(8-7) & 07<<6) + (g>>(7-5) & 07<<3) + (b>>(7-2) & 07);

   	    fillDescription(r,g,b, rgb9);
		colorPixel[rgb9] ++; allPixelCount ++;
		// if in safe region, increase rgb9 occurrence in safe array
		if ( i%w >= safeS && i%w <= (safeS+safeW-1) ){ 
			colorPixelSafe[rgb9] ++; 
			safePixelCount ++;
		}
				 
	    #ifdef DEBUG //#if defined(DEBUG)
	    { 
	        printf(" processing pixel %d\t%3d %3d %3d (%s)\tConcatenated to [%d].", i, r,g,b,colorDescriptions[rgb9],rgb9);
	       
		// if current pixel is a safe pixel...
			if ( i%w >= safeS && i%w <= (safeS+safeW-1) )
	           printf("\tThis is a safe pixel\n");
	        else printf("\tThis is not a safe pixel\n");
	     }
	     #endif

	    } // end for 
       
           printf("\n");
	 } //  end while
     /****************************************************/
         analysis_display();
         return 0;
   }
 
     
	  
