#include "CannyEdgeDetection.h"
#include "ui_CannyEdgeDetection.h"

#include <QDateTime>
#include <QMessageBox>

CannyEdgeDetection::CannyEdgeDetection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CannyEdgeDetection)
{
    ui->setupUi(this);
}

CannyEdgeDetection::CannyEdgeDetection(QWidget *parent, cv::Mat image) :
    QDialog(parent),
    ui(new Ui::CannyEdgeDetection),
    mImage(image)
{
    ui->setupUi(this);
    mThreshold1 = mThreshold2 = 0.0;
    mApertureSize = 3;
    mL2Gradient = false;

    updateImage();
}

CannyEdgeDetection::~CannyEdgeDetection()
{
    delete ui;
}

void CannyEdgeDetection::on_threshold1_valueChanged(double arg1)
{
    mThreshold1 = arg1;
    updateImage();
}

void CannyEdgeDetection::on_threshold2_valueChanged(double arg1)
{
    mThreshold2 = arg1;
    updateImage();
}

void CannyEdgeDetection::on_apertureSize_valueChanged(int arg1)
{
    mApertureSize = arg1;
    updateImage();
}

void CannyEdgeDetection::on_l2Gradient_toggled(bool checked)
{
    mL2Gradient = checked;
    updateImage();
}

void CannyEdgeDetection::updateImage()
{
    cv::Canny(mImage, mResult, mThreshold1, mThreshold2, mApertureSize, mL2Gradient);
    cv::imshow("Canny Edge Detection", mResult);
}

void CannyEdgeDetection::on_pushButton_clicked()
{
    if(!mResult.empty())
    {
        std::string date = QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss").toStdString();
        bool res = cv::imwrite("canny_edge_detection_" + date + ".png", mResult);
        if(res)
        {
            QMessageBox::information(this, "Write", "Image saved successfully.");
        }
        else
        {
            QMessageBox::warning(this, "Write", "Could not save the image.");
        }
    }
}
