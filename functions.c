/***************************************
* Author: Rui Min *
****************************************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TABLESIZE 512

 /* some global variables 
 used to store occurence information */
 int colorPixelSafe [TABLESIZE]; 
 int colorPixel [TABLESIZE];
 int safePixelCount;  // total safe pixel
 int allPixelCount;
 char colorDescriptions[TABLESIZE][50]; // table to store description of one of the 512 possible colors

 // fill in arr, which a array of string, the example color, its binary representation, and name
 void fillDescription(int r, int g, int b, int index){
   
   //int index = concat(r,g,b);
   
   if (r == 0 && g== 0 && b == 0)
	 strcpy(colorDescriptions[index], "00000000 00000000 00000000 BLACK"); 
   else if (r == 255 && g== 255 && b == 255)
	 strcpy(colorDescriptions[index], "11111111 11111111 11111111 WHITE");
   else	if (r == 128 && g== 128 && b == 128)
	 strcpy(colorDescriptions[index], "10000000 10000000 10000000 GRAY");
   else	if (r == 255 && g== 0 && b == 0)
	 strcpy(colorDescriptions[index], "11111111 00000000 00000000 RED");
   else	if (r == 255 && g== 255 && b == 0)
	 strcpy(colorDescriptions[index], "11111111 11111111 00000000 YELLOW");
   else	if (r == 0 && g== 255 && b == 0)
	 strcpy(colorDescriptions[index], "00000000 11111111 00000000 GREEN"); 
   else	if (r == 0 && g== 0 && b == 255)
	 strcpy(colorDescriptions[index], "00000000 00000000 11111111 BLUE");
   else	if (r == 0 && g== 255 && b == 255)
	 strcpy(colorDescriptions[index], "00000000 11111111 11111111 CYAN");
   else
	 strcpy(colorDescriptions[index], "OTHER");//"other"); //arr[index] = "OTHER";
 }




void subString(char dest[], char src[], int start, int howmany){
    int length = strlen(src);
    if (length - start < howmany)
       howmany = length - start;
	
    strncpy(dest, &src[start], howmany);	// untaught usage of strncpy
    dest[howmany] = '\0';
}


 void fillBinary(char outstr[],int val, int size){

     int i;
     for (i=0;i<size;i++) {
       if (val & 1)
          outstr[size-1-i] = '1';
       else
          outstr[size-1-i] = '0';

       val >>= 1; // shift right to test next bit

     }
     outstr[i] = '\0';
 }



  void analysis_display()
 {
	printf("------------- display database --------------- \n");
	int i, countColor=0, kk;

       	for (i = 0; i<TABLESIZE; i++ )
       	{
       	  int occurrenceColor_i = colorPixel[i];
		   
	  if (occurrenceColor_i > 0)  // this color has been encountered
	  {
	     countColor ++;
	  
	     int occurrenceColorSafe_i = colorPixelSafe[i];
	     // complete the 3 lines below	 
	     double probCol_Safe = (double) occurrenceColorSafe_i/safePixelCount; // probability that this color is observed, given that the safe region is observed   
   	     double prob_Safe = (double) safePixelCount/allPixelCount;   // probability of observing safe region in the image 
	     double probCol = (double) occurrenceColor_i/allPixelCount;	//  probability of observing this color in the image 
		     
             double probSafe_Col = probCol_Safe  * prob_Safe/ probCol;  // probability this color in safe region

	     char fillR[10], fillG[10], fillB[10];
	     fillBinary(fillR, i >> 6 << 5,8);

             fillBinary(fillG,i >> 3 << 5,8);	// all left & right "non-G" bits disappear
            
    	     fillBinary(fillB, i << 5,8);  

	     int k;
	     for (k=3; k<=7; k++)
	        fillR[k] =  fillG[k]= fillB[k] = '*'; 
						 
	     //now retrieve the descriptions of the color (group)
	      if ( ! strcmp(colorDescriptions[i], "OTHER"))  // descriptions is  OTHER
	      {
	         printf("[%d]: OTHER\n",i);
    	      }
  	      else{
	         char nameSubString[10]; char valueSubString[30];
	         subString(nameSubString, colorDescriptions[i],27,10);
                 subString(valueSubString, colorDescriptions[i],0,26);
             
	         kk =0;
	         while (nameSubString[kk] != '\0')	// nameSubString already has an end '\0'
		 {
		     nameSubString[kk] = toupper(nameSubString[kk]);	//"toupper" itself
		     kk ++;
		 }

		    printf("[%d]: concatenated by %s %s %s (e.g., %s, which has r,g,b value %s)\n", i, fillR, fillG, fillB, nameSubString, valueSubString);
	      }
              printf("probability that this color represents safe region is (%d/%d) * (%d/%d) / (%d/%d) --> %.3f * %.3f / %.3f = %.3f \n\n", occurrenceColorSafe_i, safePixelCount, safePixelCount, allPixelCount, occurrenceColor_i, allPixelCount, probCol_Safe, prob_Safe, probCol, probSafe_Col ); 
 
     	      }
 
	  } printf("Totally %d colors are stored in database\n", countColor);
      }
		  
