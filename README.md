# PixelValuesProcessing Documentation
 Scan pixel values from .dat files(they can be opened & edited as .txt files) and calculate positional probabilities. Sample running can be done with following terminal command lines:
  1. >gcc images.c functions.c -Wall     
  2. >a.out < image1.dat

# 
 
# Safe and Unsafe Region
The images may have different sizes, but each image consists of a safe region surrounded by two unsafe regions, as illustrated below where shaded areas in the images are safe regions, whereas white areas are unsafe regions. (A safe region can represent, for example, a bridge, and unsafe regions are rivers, or, a safe region represents a path where no landmines are placed and unsafe regions are full of landmines.)


# A comprehensive example
![images](/sampleImages.JPG)

You may have multiple images as data source. In such cases, we can simply take the sum for each occurrence, and compute as before. Consider the two images shown above. The first image is the same as above. For the second image, assume it has 4× 3 pixels, and that the pixels in the middle 2 columns (i.e, pixel 1,2,5,6,9,10) represent the safe region in the image. Others represent unsafe region. For this example, after scanning all the pixel data, you should correctly calculate that: there are totally 12 + 12 pixels, among them, 4 + 6 = 10 are ‘safe pixels’. There are 3 + 4 = 7 red pixels, which are all ‘safe pixels’. There are 2 +3 = 5 green pixels, among them 1+ 2 = 3 are safe pixels.
Based on this information, function analysis_display() should calculate and conclude that
* have scanned/encountered black, white, green and red color
* the probability that a black color represents a safe region in the images is 0
* the probability that a white color represents a safe region in the images is 0
* the probability that a red color represents a safe region in the images is 100%
* the probability that a green color represents a safe region in the images is 60%
