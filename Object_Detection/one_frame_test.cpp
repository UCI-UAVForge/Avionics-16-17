//
//  one_frame_test.cpp
//  object_detection_project_1
//
//  Created by Phillip Lai on 10/28/17.
//  Copyright © 2017 Phillip Lai. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"


int main(int argc, char* argv[])
{
    
    if( argc != 2)
    {
        std::cout <<" Usage: ./executable imagename" << std::endl;
        return -1;
    }
    
    cv::Mat mat_image;
    mat_image = cv::imread(argv[1]);   // Read the file
    
    if( !mat_image.data )                              // Check for invalid input
    {
        std::cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    int width,height,step; // parameters of image
    int t1min=0,t1max=0,t2min=0,t2max=0,t3min=0,t3max=0; // threshold variables
    
    CvMat* threshold_matrix  = cvCreateMat(2,3,CV_32FC1);
    
    // Create a window in which the image will be presented
    cvNamedWindow( "Original", CV_WINDOW_AUTOSIZE );
    cvNamedWindow( "HSV", CV_WINDOW_AUTOSIZE );
    cvNamedWindow( "F1", CV_WINDOW_AUTOSIZE );
    cvNamedWindow( "F2", CV_WINDOW_AUTOSIZE );
    cvNamedWindow( "F3", CV_WINDOW_AUTOSIZE );
    //cvNamedWindow( "EdgeDetection", CV_WINDOW_AUTOSIZE );
    
    CvScalar hsv_min = cvScalar(0, 0, 0, 0);
    CvScalar hsv_max = cvScalar(0, 0, 0, 0);
    
    // convert to IplImage because easier to work with
    IplImage* ipl_image;
    ipl_image = cvCreateImage(cvSize(mat_image.cols,mat_image.rows),8,3);
    IplImage ipl_temp = mat_image;
    cvCopy(&ipl_temp,ipl_image);
    
    // get the image data
    height    = ipl_image->height;
    width     = ipl_image->width;
    step      = ipl_image->widthStep;
    
    // image size -
    CvSize size = cvSize(width,height);
    
    
    // Initialize different images that are going to be used in the program
    //cv::Mat frame_blur;
    IplImage*  hsv_frame    = cvCreateImage(size, IPL_DEPTH_8U, 3); // image converted to HSV plane
    IplImage*  thresholded   = cvCreateImage(size, IPL_DEPTH_8U, 1); // final thresholded image
    IplImage*  thresholded1   = cvCreateImage(size, IPL_DEPTH_8U, 1); // Component image threshold
    IplImage*  thresholded2   = cvCreateImage(size, IPL_DEPTH_8U, 1);
    IplImage*  thresholded3   = cvCreateImage(size, IPL_DEPTH_8U, 1);
    IplImage*  filtered   = cvCreateImage(size, IPL_DEPTH_8U, 1);  //smoothed image
    

    // Load threshold values in these 2 parameters
    
    /*just red for now*/
    hsv_min = cvScalar(113,61,61, 0);
    hsv_max = cvScalar(140,255,255, 0);
   
    /* Ignore Blur for now
    
            //converting to Mat format because function wont take temporaries
            frame_blur = cv::cvarrToMat(ipl_image);
            
            //Add blurring to filter out salt and pepper noise
            cv::medianBlur(frame_blur,frame_blur,3);
            
            //Convert back to IplImage
            IplImage ipl_temp=frame_blur;
            cvCopy(&ipl_temp,hsv_frame);
     
    */
    
    // Covert color space to HSV as it is much easier to filter colors in the HSV color-space.
    cvCvtColor(ipl_image, hsv_frame, CV_BGR2HSV);
    
    // Filter out colors which are out of range.
    cvInRangeS(hsv_frame, hsv_min, hsv_max, thresholded);
    
    // the below lines of code is for visual purpose only remove after calibration
    //--------------FROM HERE-----------------------------------
    //Split image into its 3 one dimensional images
    cvSplit( hsv_frame,thresholded1, thresholded2, thresholded3, NULL );
    
    // Filter out colors which are out of range.
    cvInRangeS(thresholded1,cvScalar(t1min,0,0,0) ,cvScalar(t1max,0,0,0) ,thresholded1);
    cvInRangeS(thresholded2,cvScalar(t2min,0,0,0) ,cvScalar(t2max,0,0,0) ,thresholded2);
    cvInRangeS(thresholded3,cvScalar(t3min,0,0,0) ,cvScalar(t3max,0,0,0) ,thresholded3);
    
    //-------------REMOVE OR COMMENT AFTER CALIBRATION TILL HERE ------------------
    
    
    // Memory for hough circles
    CvMemStorage* storage = cvCreateMemStorage(0);
    
    // hough detector works better with some smoothing of the image
    cvSmooth( thresholded, thresholded, CV_GAUSSIAN, 9, 9 );
    
    //hough transform to detect circle
    CvSeq* circles = cvHoughCircles(thresholded, storage, CV_HOUGH_GRADIENT, 2,
                                    thresholded->height/4, 100, 50, 10, 400);
    
    for (int i = 0; i < circles->total; i++)
    {   //get the parameters of circles detected
        float* p = (float*)cvGetSeqElem( circles, i );
        printf("Ball! x=%f y=%f r=%f\n\r",p[0],p[1],p[2] );
        
        // draw a circle with the centre and the radius obtained from the hough transform
        cvCircle(ipl_image, cvPoint(cvRound(p[0]),cvRound(p[1])),  //plot centre
                 2, CV_RGB(255,255,255),-1, 8, 0 );
        cvCircle(ipl_image, cvPoint(cvRound(p[0]),cvRound(p[1])),  //plot circle
                 cvRound(p[2]), CV_RGB(0,255,0), 2, 8, 0 );
    }
    
    
    
    /* for testing purpose you can show all the images but when done with calibration
     only show frame to keep the screen clean  */
    
    cvShowImage( "Original", ipl_image ); // Original stream with detected ball overlay
    cvShowImage( "HSV", hsv_frame); // Original stream in the HSV color space
    cvShowImage( "After Color Filtering", thresholded ); // The stream after color filtering
    cvShowImage( "F1", thresholded1 ); // individual filters
    cvShowImage( "F2", thresholded2 );
    cvShowImage( "F3", thresholded3 );
    
    //cvShowImage( "filtered", thresholded );
    
    
    
    cvReleaseMemStorage(&storage);
    
    cv::waitKey(0);
    
    return 0;
}



