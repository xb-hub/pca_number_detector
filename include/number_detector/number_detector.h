#ifndef _NUMBER_DETECTOR_H_
#define _NUMBER_DETECTOR_H_

#include <iostream>
#include <vector>
#include <Eigen/Dense>
using namespace std;

namespace number_detector
{

class NumberDetector
{
private:
    int th, total, image_width_, image_height_, dim_;
    const string train_path_, test_path_;

    Eigen::MatrixXd train_Matrix_;
    Eigen::MatrixXd test_Matrix_;
    Eigen::MatrixXd train_mean_;

    vector<int> train_label_;
    vector<int> test_label_;

    vector<double> pre_P, post_P;
    vector<vector<double> > in_P;
public:
    NumberDetector();
    ~NumberDetector();

    void process();
    void detector();
    void classfiy();

    void setTrainMatrix(const string train_path);
    void setTestMatrix(const string test_path);
};
    
} // namespace number_detector

#endif /* _NUMBER_DETECTOR_H_ */