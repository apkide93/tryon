#include <cv.h>
#include <highgui.h>
#include <ctype.h>
#include <stdio.h>

int
main (int argc, char **argv)
{
  int i, c, counter;
  int INIT_TIME = 100;
  int w = 0, h = 0;
  double B_PARAM = 1.0 / 50.0;
  double T_PARAM = 1.0 / 200.0;
  double Zeta = 10.0;
  CvCapture *capture = 0;
  IplImage *frame = 0;
  IplImage *av_img, *sgm_img;
  IplImage *lower_img, *upper_img, *tmp_img;
  IplImage *dst_img, *msk_img;

  CvFont font;
  char str[64];

  if (argc == 1 || (argc == 2 && strlen (argv[1]) == 1 && isdigit (argv[1][0])))
    capture = cvCreateCameraCapture (argc == 2 ? argv[1][0] - '0' : 0);

  frame = cvQueryFrame (capture);
  w = frame->width;
  h = frame->height;

  av_img = cvCreateImage (cvSize (w, h), IPL_DEPTH_32F, 3);
  sgm_img = cvCreateImage (cvSize (w, h), IPL_DEPTH_32F, 3);
  tmp_img = cvCreateImage (cvSize (w, h), IPL_DEPTH_32F, 3);
  lower_img = cvCreateImage (cvSize (w, h), IPL_DEPTH_32F, 3);
  upper_img = cvCreateImage (cvSize (w, h), IPL_DEPTH_32F, 3);

  dst_img = cvCreateImage (cvSize (w, h), IPL_DEPTH_8U, 3);
  msk_img = cvCreateImage (cvSize (w, h), IPL_DEPTH_8U, 1);

  printf ("Background statistics initialization start\n");

  cvSetZero (av_img);
  for (i = 0; i < INIT_TIME; i++) {
    frame = cvQueryFrame (capture);
    cvAcc (frame, av_img);
  }
  cvConvertScale (av_img, av_img, 1.0 / INIT_TIME);

  cvSetZero (sgm_img);
  for (i = 0; i < INIT_TIME; i++) {
    frame = cvQueryFrame (capture);
    cvConvert (frame, tmp_img);
    cvSub (tmp_img, av_img, tmp_img);
    cvPow (tmp_img, tmp_img, 2.0);
    cvConvertScale (tmp_img, tmp_img, 2.0);
    cvPow (tmp_img, tmp_img, 0.5);
    cvAcc (tmp_img, sgm_img);
  }
  cvConvertScale (sgm_img, sgm_img, 1.0 / INIT_TIME);

  printf ("Background statistics initialization finish\n");

  cvInitFont (&font, CV_FONT_HERSHEY_COMPLEX, 0.7, 0.7);
  cvNamedWindow ("Input", CV_WINDOW_AUTOSIZE);
  cvNamedWindow ("Substraction", CV_WINDOW_AUTOSIZE);

  counter = 0;
  while (1) {
    frame = cvQueryFrame (capture);
    cvConvert (frame, tmp_img);

    cvSub (av_img, sgm_img, lower_img);
    cvSubS (lower_img, cvScalarAll (Zeta), lower_img);
    cvAdd (av_img, sgm_img, upper_img);
    cvAddS (upper_img, cvScalarAll (Zeta), upper_img);
    cvInRange (tmp_img, lower_img, upper_img, msk_img);

    cvSub (tmp_img, av_img, tmp_img);
    cvPow (tmp_img, tmp_img, 2.0);
    cvConvertScale (tmp_img, tmp_img, 2.0);
    cvPow (tmp_img, tmp_img, 0.5);

    cvRunningAvg (frame, av_img, B_PARAM, msk_img);
    cvRunningAvg (tmp_img, sgm_img, B_PARAM, msk_img);

    cvNot (msk_img, msk_img);
    cvRunningAvg (tmp_img, sgm_img, T_PARAM, msk_img);

    cvSetZero (dst_img);
    cvCopy (frame, dst_img, msk_img);

    snprintf (str, 64, "%03d[frame]", counter);
    cvPutText (dst_img, str, cvPoint (10, 20), &font, CV_RGB (0, 255, 100));
    cvShowImage ("Input", frame);
    cvShowImage ("Substraction", dst_img);

    counter++;

    c = cvWaitKey (10);
    if (c == '\x1b')
      break;
  }

//  cvSaveImage("cvacc.MP4",dst_img);

  cvDestroyWindow ("Input");
  cvDestroyWindow ("Substraction");
  cvReleaseImage (&frame);
  cvReleaseImage (&dst_img);
  cvReleaseImage (&av_img);
  cvReleaseImage (&sgm_img);
  cvReleaseImage (&lower_img);
  cvReleaseImage (&upper_img);
  cvReleaseImage (&tmp_img);
  cvReleaseImage (&msk_img);

  return 0;
}
