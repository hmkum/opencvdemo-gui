#ifndef SOBELEDGEDETECTION_H
#define SOBELEDGEDETECTION_H

#include <QMainWindow>
#include <opencv/cv.hpp>

namespace Ui {
class SobelEdgeDetection;
}

class SobelEdgeDetection : public QMainWindow
{
    Q_OBJECT

public:
    explicit SobelEdgeDetection(QWidget *parent = 0);
    SobelEdgeDetection(QWidget *parent, cv::Mat image);
    ~SobelEdgeDetection();

private:
    void updateImage();

private slots:
    void on_sbDx_valueChanged(int arg1);
    void on_sbDy_valueChanged(int arg1);
    void on_sbKernelSize_valueChanged(int arg1);
    void on_sbScale_valueChanged(double arg1);
    void on_sbDelta_valueChanged(double arg1);
    void on_btnSave_clicked();

private:
    Ui::SobelEdgeDetection *ui;

    cv::Mat mImage, mResult;
    int mDepth, mDx, mDy, mKernelSize;
    double mScale, mDelta;
};

#endif // SOBELEDGEDETECTION_H
