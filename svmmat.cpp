#include <cv.h>
#include <highgui.h>
#include <ml.h>
#include <time.h>

int main(){

const int NUM_POS=10;//�|�W�e�B�u�f�[�^��.�@P����

const int NUM_NEG=10;//�l�K�e�B�u���@NEG

const int NUM_ALL=NUM_POS+NUM_NEG;//�S�f�[�^��

const int USE_FEATURE_COUNT =2;//1�̃f�[�^�̎�����

Mat trainingData;//�����Ƀf�[�^�����Ă����܂��D

Mat trainingLabels;//+�P��-1�����x��������܂��D

trainingData.create(NUM_ALL,USE_FEATURE_COUNT,CV_32FC1);//�S�f�[�^���C��������Mat�^��p��

trainingLabels.create(NUM_ALL,1,CV_32FC1);//���x�������Ȃ̂ŁC��������1�ł����ł��D

const double data[NUM_ALL][USE_FEATURE_COUNT]={

{0.83,0.23},

{1.01,0.67},

{0.89,0.24},

{0.96,0.52},

{1.28,0.11},

{1.01,0.3},

{0.7,0.1},

{0.88,0.24},

{0.76,0.4},

{0.6,0.3},

////////////////////////////���|�W�e�B�u�f�[�^ ��NG�f�[�^�Ƃ��܂�.

{0.21,0.96},

{0.32,0.99},

{0.14,1.21},

{0.21,1.01},

{0.26,0.74},

{0.51,0.96},

{0.02,0.69},

{0.34,1.21},

{0.11,1.1},

{0.3,0.55}

};

const double check_data[CHECK_DATA_COUNT][USE_FEATURE_COUNT]={

{0.1,0.8},

{0.2,0.6},

{0.4,0.4},

{0.6,0.2},

{1.0,0.15}

};

////POS�f�[�^�̐ݒ�ł��D

for(int i=0;i<NUM_POS;i++){

for(int j=0;j<USE_FEATURE_COUNT;j++)

trainingData.at<float>(i,j)=data[i][j];//(i�Ԗ�,i�Ԗڂ�j�v�f)=���

trainingLabels.at<float>(i,0)=1;//(i�Ԗ�,0�i�z���0����͂��܂邽��)�j=������郉�x��

std::cout<<�g.�h;

}



////NG�̐ݒ�

//���ӁI�@trainingData���g���܂킷�̂ŁCi+NUM_POS�Ƃ��Ȃ���POS���㏑�����Ă��܂��܂��D

for(int i=0;i<NUM_NEG;i++){

for(int j=0;j<USE_FEATURE_COUNT;j++)

trainingData.at<float>(i+NUM_POS,j)=data[i+NUM_POS][j]; 

trainingLabels.at<float>(i+NUM_POS,0)=-1;

std::cout<<�g.�h;

}

CvSVM svm = CvSVM ();

  CvSVMParams svm_param;

  CvTermCriteria criteria;

   criteria = cvTermCriteria (CV_TERMCRIT_EPS, 1000, FLT_EPSILON);

  svm_param = CvSVMParams (CvSVM::C_SVC, CvSVM::RBF, 10.0, 8.0, 1.0, 10.0, 0.5, 0.1, NULL, criteria);

  svm.train(trainingData,trainingLabels,cv::Mat(),cv::Mat(),svm_param);

  svm.save(�gSVM.xml�h);//train�����f�[�^�����������D

///////////////////���w�K�I��//////////////////

////////////////�����ʊJ�n///////////////////

Mat result;

result.create(1,USE_FEATURE_COUNT,CV_32FC1);//�m�F�������f�[�^��,�������@



for(int i=0;i<CHECK_DATA_COUNT;i++){

for(int j=0;j<USE_FEATURE_COUNT;j++)

result.at<float>(0,j)=check_data[i][j];// 0.8 0.2�Ƃ����ƁC1�ɂȂ� �����̒l�����낢��ς��āCpredict�̗l�q�����Ă�������

cv::SVM svm_predict;

svm_predict.load(�gSVM.xml�h);

std::cout<<�gSVM�f�f����:�h<<svm_predict.predict(result)<<�g\n�h;//predict�Őf�f���܂��D�@1or-1���߂�l

}