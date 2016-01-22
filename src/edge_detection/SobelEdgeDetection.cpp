#include "SobelEdgeDetection.h"
#include "ui_SobelEdgeDetection.h"
#include <QDateTime>
#include <QMessageBox>

SobelEdgeDetection::SobelEdgeDetection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SobelEdgeDetection)
{
    ui->setupUi(this);
}

SobelEdgeDetection::SobelEdgeDetection(QWidget *parent, cv::Mat image) :
    QDialog(parent),
    ui(new Ui::SobelEdgeDetection),
    mImage(image)
{
    ui->setupUi(this);

    mDepth = mImage.depth();
    ui->sbDepth->setValue(mDepth);
    mDx = mDy = 1;
    mKernelSize = 3;
    mScale = 1.0;
    mDelta = 0.0;

    updateImage();
}

SobelEdgeDetection::~SobelEdgeDetection()
{
    delete ui;
}

void SobelEdgeDetection::updateImage()
{
    cv::Sobel(mImage, mResult, mDepth, mDx, mDy, mKernelSize, mScale, mDelta);
    cv::imshow("Sobel Edge Detection", mResult);
}

void SobelEdgeDetection::on_sbDx_valueChanged(int arg1)
{
    if(arg1 < mKernelSize)
    {
        mDx = arg1;
        updateImage();
    }
}

void SobelEdgeDetection::on_sbDy_valueChanged(int arg1)
{
    if(arg1 < mKernelSize)
    {
        mDy = arg1;
        updateImage();
    }
}

void SobelEdgeDetection::on_sbKernelSize_valueChanged(int arg1)
{
    mKernelSize = arg1;
    updateImage();
}

void SobelEdgeDetection::on_sbScale_valueChanged(double arg1)
{
    mScale = arg1;
    updateImage();
}

void SobelEdgeDetection::on_sbDelta_valueChanged(double arg1)
{
    mDelta = arg1;
    updateImage();
}

void SobelEdgeDetection::on_btnSave_clicked()
{
    if(!mResult.empty())
    {
        std::string date = QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss").toStdString();
        bool res = cv::imwrite("sobel_edge_detection_" + date + ".png", mResult);
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
