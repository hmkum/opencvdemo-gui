#ifndef CANNYEDGEDETECTION_H
#define CANNYEDGEDETECTION_H

#include <QMainWindow>
#include <opencv/cv.hpp>

namespace Ui {
class CannyEdgeDetection;
}

class CannyEdgeDetection : public QMainWindow
{
    Q_OBJECT

public:
    explicit CannyEdgeDetection(QWidget *parent = 0);
    CannyEdgeDetection(QWidget *parent, cv::Mat image);
    ~CannyEdgeDetection();

    void updateImage();

private slots:
    void on_threshold1_valueChanged(double arg1);
    void on_threshold2_valueChanged(double arg1);
    void on_apertureSize_valueChanged(int arg1);
    void on_l2Gradient_toggled(bool checked);
    void on_pushButton_clicked();

private:
    Ui::CannyEdgeDetection *ui;
    cv::Mat mImage, mResult;

    double mThreshold1, mThreshold2;
    int mApertureSize;
    bool mL2Gradient;
};

#endif // CANNYEDGEDETECTION_H
