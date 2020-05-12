#include "opencv2/core.hpp"
#include "opencv2/video.io.hpp"
#include "opencv2/highgui.hpp"
#include "iostream"
#include "stdio.h"

using namespace cv;
using namespace std;


int main(int argc, char* argv[])
{
   //VideoCapture capture(0);
   //VideoCapture capture(1);
   VideoCapture capture("./src/test_200508.mp4");
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
            cvtColor(edges, contours_img, CV_GRAY2BGR);
            for (idx = 0; idx < contours.size(); idx++)
            {
               RotatedRect rect = minAreaRect(contours[idx]);
               double areaRatio = abs(contourArea(contours[idx])) / (rect.size.height);
               drawContours(contours_img, contours, idx, (0,0,255) , 2);
            }

            vector<Point> poly;
            Mat poly_img, ratangle_img;
            cvtColor(edges,poly_img, CV_GRAY2BGR);
            cvtColor(edges, ratangle_img, CV_GRAY2BGR);

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