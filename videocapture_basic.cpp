#include "opencv2/core.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <stdio.h>

#ifndef ANDROID_DOXCAPTUREUI_OPENCV4_COMPAT_H
#define ANDROID_DOXCAPTUREUI_OPENCV4_COMPAT_H

#include <opencv2/opencv.hpp>
#include <cmath>

#if CV_MAJOR_VERSION > 3

// namespace cv;
//{
#ifndef CV_TERMCRIT_ITER
#define CV_TERMCRIT_ITER cv::TermCriteria::MAX_ITER
#endif

#ifndef CV_BGR2GRAY
#define CV_BGR2GRAY cv::COLOR_BGR2GRAY
#endif

#ifndef CV_BGR2RGB
#define CV_BGR2RGB cv::COLOR_BGR2RGB
#endif

#ifndef CV_RGB2GRAY
#define CV_RGB2GRAY cv::COLOR_RGB2GRAY
#endif

#ifndef CV_BGRA2GRAY
#define CV_BGRA2GRAY cv::COLOR_BGRA2GRAY
#endif

#ifndef CV_GRAY2RGBA
#define CV_GRAY2RGBA cv::COLOR_GRAY2RGBA
#endif

#ifndef CV_GRAY2RGB
#define CV_GRAY2RGB cv::COLOR_GRAY2RGB
#endif

#ifndef CV_GRAY2BGRA
#define CV_GRAY2BGRA cv::COLOR_GRAY2BGRA
#endif

#ifndef CV_GRAY2BGR565
#define CV_GRAY2BGR565 cv::COLOR_GRAY2BGR565
#endif

#ifndef CV_RGBA2BGR565
#define CV_RGBA2BGR565 cv::COLOR_RGBA2BGR565
#endif

#ifndef CV_RGBA2RGB
#define CV_RGBA2RGB cv::COLOR_RGBA2RGB
#endif

#ifndef CV_RGB2RGBA
#define CV_RGB2RGBA cv::COLOR_RGB2RGBA
#endif

#ifndef CV_RGB2BGR565
#define CV_RGB2BGR565 cv::COLOR_RGB2BGR565
#endif

#ifndef CV_RGBA2BGR
#define CV_RGBA2BGR cv::COLOR_RGBA2BGR
#endif

#ifndef CV_RGBA2GRAY
#define CV_RGBA2GRAY cv::COLOR_RGBA2GRAY
#endif

#ifndef CV_ADAPTIVE_THRESH_GAUSSIAN_C
#define CV_ADAPTIVE_THRESH_GAUSSIAN_C cv::ADAPTIVE_THRESH_GAUSSIAN_C
#endif

#ifndef CV_THRESH_BINARY
#define CV_THRESH_BINARY cv::THRESH_BINARY
#endif

#ifndef CV_BGR2HSV
#define CV_BGR2HSV cv::COLOR_BGR2HSV
#endif

#ifndef CV_BGR2Lab
#define CV_BGR2Lab cv::COLOR_BGR2Lab
#endif

#ifndef CV_RGB2HSV
#define CV_RGB2HSV cv::COLOR_RGB2HSV
#endif

#ifndef CV_HSV2RGB
#define CV_HSV2RGB cv::COLOR_HSV2RGB
#endif

#ifndef CV_THRESH_OTSU
#define CV_THRESH_OTSU cv::THRESH_OTSU
#endif


#ifndef CV_THRESH_BINARY
#define CV_THRESH_BINARY THRESH_BINARY
#endif

#ifndef CV_MOP_CLOSE
#define CV_MOP_CLOSE cv::MORPH_CLOSE
#endif

#ifndef CV_RETR_CCOMP
#define CV_RETR_CCOMP cv::RETR_CCOMP
#endif

#ifndef CV_RETR_LIST
#define CV_RETR_LIST cv::RETR_LIST
#endif

#ifndef CV_RETR_TREE
#define CV_RETR_TREE cv::RETR_TREE
#endif

#ifndef CV_RETR_FLOODFILL
#define CV_RETR_FLOODFILL cv::RETR_FLOODFILL
#endif

#ifndef CV_RETR_EXTERNAL
#define CV_RETR_EXTERNAL cv::RETR_EXTERNAL
#endif

#ifndef CV_CHAIN_APPROX_SIMPLE
#define CV_CHAIN_APPROX_SIMPLE cv::CHAIN_APPROX_SIMPLE
#endif

#ifndef CV_CHAIN_APPROX_TC89_KCOS
#define CV_CHAIN_APPROX_TC89_KCOS cv::CHAIN_APPROX_TC89_KCOS
#endif

#ifndef CV_FILLED
#define CV_FILLED cv::FILLED
#endif


#ifndef CV_REDUCE_SUM
#define CV_REDUCE_SUM cv::REDUCE_SUM
#endif

#ifndef CV_StsBadArg
#define CV_StsBadArg cv::Error::StsBadArg
#endif
//}

#ifndef cvFastArctan
#define cvFastArctan( Y, X )  ( std::atan2( (Y), (X) ) )
#endif

#endif //endif CV_MAJOR_VERSION

#endif //ANDROID_DOXCAPTUREUI_OPENCV4_COMPAT_H

using namespace cv;
using namespace std;


int main(int argc, char* argv[])
{
   VideoCapture capture(-1);
   //VideoCapture capture(1);
   //VideoCapture capture("./src/test_04.mp4");
   //VideoCapture capture("s.mp4");
   //VideoCapture capture = VideoCapture("http://172.30.1.13:8090/?action=stream");

   if (!capture.isOpened())
   {
      cerr << "Could not open camera" << endl;
      return 0;
   }

   //namedWindow("testcam", );

   while (true) {
      bool frame_valid = true;
      Mat frame;

      try {
         capture >> frame;
      }
      catch (Exception& e) {
         cerr << "Exception occurred. Ignoring frame..." << e.err
            << endl;
         frame_valid = false;
      }

      if (frame_valid) {
         try {
            Mat edges;
            cvtColor(frame, edges, COLOR_BGR2GRAY);
            GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
            Canny(edges, edges, 50, 100);
            //Canny(edges, edges, 20, 70);
            Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(16, 16));
            Mat morph;
            morphologyEx(edges, morph, CV_MOP_CLOSE, kernel);


            // 이진화 영상 검출 시작
            int M, N;

            M = morph.rows;
            N = morph.cols;

            N = 240;

            int row1 = 240, row2 = 240;

            
            for (int x = row1; x <= row2; x++)
            {

               printf("<col %d> \n", x);

               for (int j = 0; j < M; j++)

               {

                  printf("%d ", morph.at<uchar>(j, x));

               }

               printf("\n\n");

            }

         // 검출 
            


            size_t idx, i;
            vector<vector<Point>> contours;
            vector<Vec4i> hierarchy;
            findContours(morph, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, Point(0,0));

            Mat contours_img;
            cvtColor(edges, contours_img, CV_GRAY2BGRA);
            for (idx = 0; idx < contours.size(); idx++)
            {
               RotatedRect rect = minAreaRect(contours[idx]);
               double areaRatio = abs(contourArea(contours[idx])) / (rect.size.height);
               drawContours(contours_img, contours, idx, (0,0,255) , 2);
            }

            vector<Point> poly;
            Mat poly_img, ratangle_img;
            cvtColor(edges,poly_img, CV_GRAY2BGRA);
            cvtColor(edges, ratangle_img, CV_GRAY2BGRA);

            for (idx = 0; idx < contours.size(); idx++)
            {
               approxPolyDP(contours[idx], poly, 1, true);
               for (i = 0; i < poly.size(); i++)
               {
                  line(poly_img, poly[i], poly[(i + 1) % poly.size()], (255, 0, 0), 2);
                  if (poly.size() == 4)
                  {
                     line(ratangle_img, poly[i], poly[(i + 1) % poly.size()], (255, 0, 0));
                  }
               }
            }

            imshow("testcam", frame);
            //imshow("original", down_stairs.mp4);
            imshow("contours", morph);
            //imshow("test", ratangle_img);
            //imshow("morphcam", contours_img);
         }

         catch (Exception& e) {
            cerr << "Exception occurred. Ignoring frame..." << e.err
               << endl;
         }
      }
      if (waitKey(30) >= 0) break;
   } // VideoCapture automatically deallocate camera object 
   return 0;
   
}
