#include <opencv2/opencv.hpp>
#include <Eigen/Dense>
#include "number_detector/number_detector.h"
using namespace number_detector;
using namespace cv;
using namespace Eigen;
using namespace std;

NumberDetector::NumberDetector() :
    th(127),
    total(0),
    image_height_(28),
    image_width_(28),
    dim_(100),
    train_path_("../image/num_train/link.txt"),
    test_path_("../image/num_test/link.txt")
{ 
}

NumberDetector::~NumberDetector()
{

}

void NumberDetector::process()
{
    setTrainMatrix(train_path_);
    setTestMatrix(test_path_);

    cout << "finished load set..." << endl;

    // 计算每一维的均值
    train_mean_ = train_Matrix_.colwise().mean();
    RowVectorXd mean_vec_row = train_mean_;

    cout << "finished mean..." << endl;

    // 零均值化
    MatrixXd train_zero_Matrix = train_Matrix_;
    train_zero_Matrix.rowwise() -= mean_vec_row;

    cout << "finished zero..." << endl;

    // 计算协方差矩阵
    MatrixXd C = train_zero_Matrix.transpose() * train_zero_Matrix;

    cout << "finished compute Cov..." << endl;

    // 计算协方差矩阵的特征值和特征向量，使用selfadjont可以让产生的特征值和特征向量有序排列
    SelfAdjointEigenSolver<MatrixXd> eigen_solver(C);
    MatrixXd vec = eigen_solver.eigenvectors().rightCols(dim_);  // 特征向量
    MatrixXd val = eigen_solver.eigenvalues();   // 特征值

    cout << "train_zero_Matrix: " << train_zero_Matrix.rows() << " * " << train_zero_Matrix.cols() << endl;
    cout << "vec: " << vec.rows() << " * " << vec.cols() << endl;

    MatrixXd Y = train_zero_Matrix * vec;
    th = (Y.minCoeff() + Y.maxCoeff()) / 2;
    cout << "th：" << th << endl;
    cout << "降维矩阵维数：" << Y.rows() << " " << Y.cols() << endl;
//    cout << "矩阵：" << Y << endl;
}

void NumberDetector::classfiy()
{

}

void NumberDetector::detector()
{ 
}

void NumberDetector::setTrainMatrix(const string train_path)
{
    string content;
    fstream file(train_path);
    if(!file.is_open())
    {
        cout << "Open File Failed" << endl;
    }
    vector<Mat> image_data;
    while (getline(file, content))
    {
        string path = content.substr(0, content.size() - 2);
        int label = content.back() - '0';
        Mat image = imread(path, IMREAD_GRAYSCALE);
        Mat reshape_image = image.reshape(0, 1);
        image_data.push_back(reshape_image);
        train_label_.push_back(label);
        total++;
    }
    train_Matrix_ = MatrixXd::Zero(image_data.size(), image_width_ * image_height_);
    for(int i = 0; i < image_data.size(); i++)
    {
        for(int j = 0; j < image_width_ * image_height_; j++)
        {
            train_Matrix_.coeffRef(i, j) = image_data[i].data[j];
        }
    }
}

void NumberDetector::setTestMatrix(const string test_path)
{
    string content;
    fstream file(test_path);
    if(!file.is_open())
    {
        cout << "Open File Failed" << endl;
    }
    vector<Mat> image_data;
    while (getline(file, content))
    {
        string path = content.substr(0, content.size() - 2);
        int label = content.back() - '0';
        Mat image = imread(path, IMREAD_GRAYSCALE);
        Mat reshape_image = image.reshape(0, 1);
        image_data.push_back(reshape_image);
        test_label_.push_back(label);
    }
    test_Matrix_ = MatrixXd::Zero(image_data.size(), image_width_ * image_height_);
    for(int i = 0; i < image_data.size(); i++)
    {
        for(int j = 0; j < image_width_ * image_height_; j++)
        {
            test_Matrix_.coeffRef(i, j) = image_data[i].data[j];
        }
    }
}