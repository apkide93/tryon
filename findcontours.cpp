#include <cv.h>
#include <highgui.h>

int
main (int argc, char *argv[])
{
  int i;
  IplImage *src_img = 0, **dst_img;
  IplImage *src_img_gray = 0;
  IplImage *tmp_img;
  CvMemStorage *storage = cvCreateMemStorage (0);
  CvSeq *contours = 0;
  int levels = 0;

  if (argc >= 2)
    src_img = cvLoadImage (argv[1], CV_LOAD_IMAGE_COLOR);
  if (src_img == 0)
    return -1;

  src_img_gray = cvCreateImage (cvGetSize (src_img), IPL_DEPTH_8U, 1);
  cvCvtColor (src_img, src_img_gray, CV_BGR2GRAY);
  tmp_img = cvCreateImage (cvGetSize (src_img), IPL_DEPTH_8U, 1);
  dst_img = (IplImage **) cvAlloc (sizeof (IplImage *) * 3);
  for (i = 0; i < 3; i++) {
    dst_img[i] = cvCloneImage (src_img);
  }

// (1)画像の二値化
  cvThreshold (src_img_gray, tmp_img, 120, 255, CV_THRESH_BINARY);

// (2)輪郭の検出
  cvFindContours (tmp_img, storage, &contours, sizeof (CvContour), CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

// (3)輪郭の描画
  cvDrawContours (dst_img[0], contours, CV_RGB (255, 0, 0), CV_RGB (0, 255, 0), levels - 1, 2, CV_AA, cvPoint (0, 0));
  cvDrawContours (dst_img[1], contours, CV_RGB (255, 0, 0), CV_RGB (0, 255, 0), levels, 2, CV_AA, cvPoint (0, 0));
  cvDrawContours (dst_img[2], contours, CV_RGB (255, 0, 0), CV_RGB (0, 255, 0), levels + 1, 2, CV_AA, cvPoint (0, 0));

// (4)画像の表示
//  cvNamedWindow ("Level:-1", CV_WINDOW_AUTOSIZE);
//  cvShowImage ("Level:-1", dst_img[0]);
//  cvNamedWindow ("Level:0", CV_WINDOW_AUTOSIZE);
//  cvShowImage ("Level:0", dst_img[1]);
//  cvNamedWindow ("Level:1", CV_WINDOW_AUTOSIZE);
//  cvShowImage ("Level:1", dst_img[2]);
//  cvWaitKey (0);

  cvSaveImage("findcontours.JPG",dst_img[2]);

//  cvDestroyWindow ("Level:-1");
//  cvDestroyWindow ("Level:0");
//  cvDestroyWindow ("Level:1");
  cvReleaseImage (&src_img);
  cvReleaseImage (&src_img_gray);
  cvReleaseImage (&tmp_img);
  for (i = 0; i < 3; i++) {
    cvReleaseImage (&dst_img[i]);
  }
  cvFree (dst_img);
  cvReleaseMemStorage (&storage);


  return 0;
}
