#include "LaplacianEdgeDetection.h"
#include "ui_LaplacianEdgeDetection.h"

#include <QDateTime>
#include <QMessageBox>

LaplacianEdgeDetection::LaplacianEdgeDetection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LaplacianEdgeDetection)
{
    ui->setupUi(this);
}

LaplacianEdgeDetection::LaplacianEdgeDetection(QWidget *parent, cv::Mat image) :
    QDialog(parent),
    ui(new Ui::LaplacianEdgeDetection),
    mImage(image)
{
    ui->setupUi(this);

    mDepth = mImage.depth();
    ui->sbDepth->setValue(mDepth);
    mKernelSize = 3;
    mScale = 1.0;
    mDelta = 0.0;

    updateImage();
}

LaplacianEdgeDetection::~LaplacianEdgeDetection()
{
    delete ui;
}

void LaplacianEdgeDetection::updateImage()
{
    cv::Laplacian(mImage, mResult, mDepth, mKernelSize, mScale, mDelta);
    cv::imshow("Laplacian Edge Detection", mResult);

}

void LaplacianEdgeDetection::on_sbKernelSize_valueChanged(int arg1)
{
    mKernelSize = arg1;
    updateImage();
}

void LaplacianEdgeDetection::on_sbScale_valueChanged(double arg1)
{
    mScale = arg1;
    updateImage();
}

void LaplacianEdgeDetection::on_sbDelta_valueChanged(double arg1)
{
    mDelta = arg1;
    updateImage();
}

void LaplacianEdgeDetection::on_btnSave_clicked()
{
    if(!mResult.empty())
    {
        std::string date = QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss").toStdString();
        bool res = cv::imwrite("laplacian_edge_detection_" + date + ".png", mResult);
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
