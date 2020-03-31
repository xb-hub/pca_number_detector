#include "number_detector/number_detector.h"
using namespace number_detector;

int main()
{
    NumberDetector* number_detector = new NumberDetector();
    number_detector->process();
//    number_detector->detector();
}