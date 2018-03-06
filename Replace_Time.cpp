/**
 * @file compareHist_Demo.cpp
 * @brief Sample code to use the function compareHist
 * @author OpenCV team
 */

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

float abs_diff (float a, float b)
{
if(a>b)
return a-b;
return b-a;
}

using namespace std;
using namespace cv;

/**
 * @function main
 */
int main( int argc, char** argv )
{
    Mat src_base, hsv_base;
    Mat src_test1, hsv_test1;

    /// Load three images with different environment settings
    if( argc < 3 )
    {
        printf("** Error. Usage: ./compareHist_Demo <image_settings0> <image_setting1> <image_settings2>\n");
        return -1;
    }

    src_base = imread( argv[1], 1 );
    src_test1 = imread( argv[2], 1 );

    /// Convert to HSV
    cvtColor( src_base, hsv_base, COLOR_BGR2HSV );
    cvtColor( src_test1, hsv_test1, COLOR_BGR2HSV );


    /// Using 50 bins for hue and 60 for saturation
    int h_bins = 50; int s_bins = 60;
    int histSize[] = { h_bins, s_bins };

    // hue varies from 0 to 179, saturation from 0 to 255
    float h_ranges[] = { 0, 180 };
    float s_ranges[] = { 0, 256 };

    const float* ranges[] = { h_ranges, s_ranges };

    // Use the o-th and 1-st channels
    int channels[] = { 0, 1 };


    /// Histograms
    MatND hist_base;
    MatND hist_test1;

    /// Calculate the histograms for the HSV images
    calcHist( &hsv_base, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false );
    normalize( hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat() );

    calcHist( &hsv_test1, 1, channels, Mat(), hist_test1, 2, histSize, ranges, true, false );
    normalize( hist_test1, hist_test1, 0, 1, NORM_MINMAX, -1, Mat() );

    /// Apply the histogram comparison methods
        int compare_method = 2;
        double base_initial = compareHist( hist_base, hist_base, compare_method );
        double base_final = compareHist( hist_base, hist_test1, compare_method );
        int degree;

        float rust = abs_diff( base_initial, base_final);

        if (rust < 5)
        { 
           degree = 0;
        }
        else if (rust < 12.45)
        {
           degree = 1;
        }
        else if ( rust < 12.7)
        {
           degree = 2;
        }
        else if ( rust < 13.05 )
        {
           degree = 3;
        }
        else if ( rust < 13.4)
        {
           degree = 4;
        }
        else if ( rust < 13.7 )
        {
           degree = 5;
        }
        else if ( rust < 14.5 )
        {
           degree = 6;
        }
        else 
        {
           printf("\n\nImproper image\n\n\n");
           return 0;
        }
    
    float replace;
    if (degree == 0)
    {
        printf("\n\nNot corroded. Standard replacement period is 2.5 years\n\n\n");
        return 0;
    }

    switch (degree)
    {
      case 1: replace = 12 ;
      break;
      case 2: replace = 9 ;
      break;
      case 3: replace = 7 ;
      break;
      case 4: replace = 5 ;
      break;
      case 5: replace = 1.5 ;
      break;
      case 6: replace = 0.5 ;
      break;
      default: { printf("\n\nNo suitable replacement period found\n\n\n"); return 0; }
    }
    
    printf( "\n\nThe degree of corrosion is :\t\t %d\n\n", degree);
    printf ("\n\nThe replacement period is:\t\t %.01f months\n\n", replace); 

    printf( "\n" );

    return 0;
}
