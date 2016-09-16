#include <cv.h>
#include <highgui.h>

int
main (int argc, char **argv)
{
  IplImage *src_img = 0, *dst_img;
  IplImage *src_img_gray = 0;
  IplImage *tmp_img1, *tmp_img2, *tmp_img3;

  if (argc >= 2)
    src_img = cvLoadImage (argv[1], CV_LOAD_IMAGE_COLOR);
  if (src_img == 0)
    return -1;

  tmp_img1 = cvCreateImage (cvGetSize (src_img), IPL_DEPTH_8U, 1);
  tmp_img2 = cvCreateImage (cvGetSize (src_img), IPL_DEPTH_8U, 1);
  tmp_img3 = cvCreateImage (cvGetSize (src_img), IPL_DEPTH_8U, 1);
  src_img_gray = cvCreateImage (cvGetSize (src_img), IPL_DEPTH_8U, 1);
  cvCvtColor (src_img, src_img_gray, CV_BGR2GRAY);
  dst_img = cvCloneImage (src_img);

  cvSmooth (src_img_gray, src_img_gray, CV_GAUSSIAN, 5);

  cvThreshold (src_img_gray, tmp_img1, 90, 255, CV_THRESH_BINARY);

  cvAdaptiveThreshold (src_img_gray, tmp_img2, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 11, 10);

  cvAnd (tmp_img1, tmp_img2, tmp_img3);
  cvCvtColor (tmp_img3, dst_img, CV_GRAY2BGR);

  cvSmooth (src_img, src_img, CV_GAUSSIAN, 11);
  cvAnd (dst_img, src_img, dst_img);

//  cvNamedWindow ("Threshold", CV_WINDOW_AUTOSIZE);
//  cvShowImage ("Threshold", tmp_img1);
//  cvNamedWindow ("AdaptiveThreshold", CV_WINDOW_AUTOSIZE);
//  cvShowImage ("AdaptiveThreshold", tmp_img2);
//  cvNamedWindow ("Image", CV_WINDOW_AUTOSIZE);
//  cvShowImage ("Image", dst_img);
//  cvWaitKey (0);

  cvSaveImage("threshold.JPG", tmp_img1);
  cvSaveImage("adaptivethreshold.JPG", tmp_img2);

//  cvDestroyWindow ("Threshold");
//  cvDestroyWindow ("AdaptiveThreshold");
//  cvDestroyWindow ("Image");
  cvReleaseImage (&src_img);
  cvReleaseImage (&dst_img);
  cvReleaseImage (&src_img_gray);
  cvReleaseImage (&tmp_img1);
  cvReleaseImage (&tmp_img2);
  cvReleaseImage (&tmp_img3);

  return 0;
}
