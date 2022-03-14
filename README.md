# PixelValuesProcessing Documentation
Scan pixel values from .dat files(they can be opened & edited as .txt files) and calculate positional probabilities. Sample running can be done with following terminal command lines:
  1. >gcc images.c functions.c -Wall     
  2. >a.out < image1.dat
or in Bash Shell run the script file:
$ datScript.sh
and then follow instructions after invoking the shell script. Below is **demo of how the script works**:
![demoScript](/demo_script.JPG)

# Safe and Unsafe Region
The images may have different sizes, but each image consists of a safe region surrounded by two unsafe regions, as illustrated below where shaded areas in the images are safe regions, whereas white areas are unsafe regions. (A safe region can represent, for example, a bridge, and unsafe regions are rivers, or, a safe region represents a path where no landmines are placed and unsafe regions are full of landmines.)
![safe](/safeRegion.JPG)

# ARGB color model and its compression
Each pixel value is an integer of 32 bits, which has the RGB value and other information compressed and stored in such a way that, counting from the right most bit, B values occupies the first 8 bits, G occupies the next 8 bits, and R occupies the next 8 bits. This is shown below. (The left-most 8 bits store other information about the image, which we are not interested here.)

We use arrays to store occurrences of each possible colors, but potentially any combination of R,G and B is possible, and thus there are 256 ×256 × 256 = 16777216 possible colors! It would be cumbersome to use an array of size 16777216 to store the colors. One feasible approach is to take the 3 most significant bits of each of the R, G and B bits, concatenate them, and then put as the lower 9 bits of an integer (other bits are 0), as shown below. This integer will represent a group of very similar colors. Thus, we have totally 8×8×8 = 512 colors (from binary 00…000000000 ~ 00…111111111) for which we need to store occurrence information.

![ARGB](/ARGBcompression.JPG)

# A comprehensive example
![images](/sampleImages.JPG)

You may have multiple images as data source. In such cases, we can simply take the sum for each occurrence, and compute as before. Consider the two images shown above. The first image is the same as above. For the second image, assume it has 4× 3 pixels, and that the pixels in the middle 2 columns (i.e, pixel 1,2,5,6,9,10) represent the safe region in the image. Others represent unsafe region. For this example, after scanning all the pixel data, you should correctly calculate that: there are totally 12 + 12 pixels, among them, 4 + 6 = 10 are ‘safe pixels’. There are 3 + 4 = 7 red pixels, which are all ‘safe pixels’. There are 2 +3 = 5 green pixels, among them 1+ 2 = 3 are safe pixels.
Based on this information, function analysis_display() should calculate and conclude that
* have scanned/encountered black, white, green and red color
* the probability that a black color represents a safe region in the images is 0
* the probability that a white color represents a safe region in the images is 0
* the probability that a red color represents a safe region in the images is 100%
* the probability that a green color represents a safe region in the images is 60%

# Sample input and output
red 99% gcc images.c functions.c -Wall

red 100% a.out < image1.dat

`scanning pixel data for a new image.....`

`------------- display database ---------------`

`[0]: concatenated by 000***** 000***** 000***** (e.g., BLACK, which has r,g,b value 00000000 00000000 00000000)`

`probability that this color represents safe region is (0/4) * (4/12) / (3/12) --> 0.000 * 0.333 / 0.250 = 0.000`

`[56]: concatenated by 000***** 111***** 000***** (e.g., GREEN, which has r,g,b value 00000000 11111111 00000000)`

`probability that this color represents safe region is (1/4) * (4/12) / (2/12) --> 0.250 * 0.333 / 0.167 = 0.500`

`[448]: concatenated by 111***** 000***** 000***** (e.g., RED, which has r,g,b value 11111111 00000000 00000000)`

`probability that this color represents safe region is (3/4) * (4/12) / (3/12) --> 0.750 * 0.333 / 0.250 = 1.000`

`[511]: concatenated by 111***** 111***** 111***** (e.g., WHITE, which has r,g,b value 11111111 11111111 11111111)`

`probability that this color represents safe region is (0/4) * (4/12) / (4/12) --> 0.000 * 0.333 / 0.333 = 0.000`

`Totally 4 colors are stored in database`
