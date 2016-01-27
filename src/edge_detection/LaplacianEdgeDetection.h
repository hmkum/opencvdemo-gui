#ifndef LAPLACIANEDGEDETECTION_H
#define LAPLACIANEDGEDETECTION_H

#include <QMainWindow>
#include <opencv/cv.hpp>

namespace Ui {
class LaplacianEdgeDetection;
}

class LaplacianEdgeDetection : public QMainWindow
{
    Q_OBJECT

public:
    explicit LaplacianEdgeDetection(QWidget *parent = 0);
    LaplacianEdgeDetection(QWidget *parent, cv::Mat image);
    ~LaplacianEdgeDetection();

private:
    void updateImage();

private slots:
    void on_sbKernelSize_valueChanged(int arg1);
    void on_sbScale_valueChanged(double arg1);
    void on_sbDelta_valueChanged(double arg1);
    void on_btnSave_clicked();

private:
    Ui::LaplacianEdgeDetection *ui;

    cv::Mat mImage, mResult;

    int mDepth, mKernelSize;
    double mScale, mDelta;
};

#endif // LAPLACIANEDGEDETECTION_H
