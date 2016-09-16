#include <cv.h>
#include <highgui.h>
#include <ml.h>
#include <stdio.h>

int
main (int argc, char **argv)
{
  int i, j;
  int width = 28, height = 30;  /* サンプル画像サイズ */
  int image_dim = width * height;
  CvMat m;
  float a[image_dim];
  float ret = -1.0;
  float scale;
  IplImage *src, *src_color, *src_tmp;
  int sx, sy, tw, th;
  int stepx = 3, stepy = 3;
  double steps = 1.2;
  int iterate;
  CvSVM svm = CvSVM ();

  // (1)画像の読み込み
  if (argc < 2 ||
      (src = cvLoadImage (argv[1], CV_LOAD_IMAGE_GRAYSCALE)) == 0 ||
      (src_color = cvLoadImage (argv[1], CV_LOAD_IMAGE_COLOR)) == 0) {
    return -1;
  }

  // (2)SVMデータの読み込み
  svm.load ("svm_image.xml");

  /* 読み込んだ画像を部分画像毎に処理 */
  cvInitMatHeader (&m, 1, image_dim, CV_32FC1, NULL);
  tw = src->width;
  th = src->height;

  for (iterate = 0; iterate < 1; iterate++) {
    // (3)画像を縮小し，現在の部分画像を行列へ変更
    src_tmp = cvCreateImage (cvSize ((int) (tw / steps), (int) (th / steps)), IPL_DEPTH_8U, 1);
    cvResize (src, src_tmp);
    tw = src_tmp->width;
    th = src_tmp->height;
    for (sy = 0; sy <= src_tmp->height - height; sy += stepy) {
      for (sx = 0; sx <= src_tmp->width - width; sx += stepx) {
        for (i = 0; i < height; i++) {
          for (j = 0; j < width; j++) {
            a[i * width + j] =
              float ((int) ((uchar) (src_tmp->imageData[(i + sy) * src_tmp->widthStep + (j + sx)])) / 255.0);
          }
        }
        cvSetData (&m, a, sizeof (float) * image_dim);

        // (4)SVMによる判定と結果の描画
        ret = svm.predict (&m);
        if ((int) ret == 1) {
          scale = (float) src->width / tw;
          cvRectangle (src_color, cvPoint ((int) (sx * scale), (int) (sy * scale)),
                       cvPoint ((int) ((sx + width) * scale), (int) ((sy + height) * scale)), CV_RGB (255, 0, 0), 2);
        }
      }
    }
    cvReleaseImage (&src_tmp);
  }

  // (5)検出結果画像の表示
  cvNamedWindow ("svm_predict", CV_WINDOW_AUTOSIZE);
  cvShowImage ("svm_predict", src_color);
  cvWaitKey (0);

  cvDestroyWindow ("svm_predict");
  cvReleaseImage (&src);
  cvReleaseImage (&src_color);
  cvReleaseImage (&src_tmp);

  return 0;
}
