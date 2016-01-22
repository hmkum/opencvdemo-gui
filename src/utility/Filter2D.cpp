#include "Filter2D.h"
#include "ui_Filter2D.h"

#include <QDateTime>
#include <QMessageBox>

Filter2D::Filter2D(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Filter2D)
{
    ui->setupUi(this);
}

Filter2D::Filter2D(QWidget *parent, cv::Mat image) :
    QDialog(parent),
    ui(new Ui::Filter2D),
    mImage(image)
{
    ui->setupUi(this);

    mKernel.create(3, 3, CV_32F);
    mKernel = 0.0;
    mKernel.at<float>(1,1) = 1.0;

    updateImage();
}

Filter2D::~Filter2D()
{
    delete ui;
}

void Filter2D::updateImage()
{

    cv::filter2D(mImage, mResult, mImage.depth(), mKernel);
    cv::imshow("Filter", mResult);
}

void Filter2D::on_btnSave_clicked()
{
    if(!mResult.empty())
    {
        std::string date = QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss").toStdString();
        bool res = cv::imwrite("filter2d_" + date + ".png", mResult);
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

void Filter2D::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    int row = item->row();
    int col = item->column();
    mKernel.at<float>(row, col) = item->text().toFloat();
    updateImage();
}
