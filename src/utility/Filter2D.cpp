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

void Filter2D::updateTable()
{
    for(int i = 0; i < KernelSize; ++i)
    {
        for(int j = 0; j < KernelSize; ++j)
        {
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(QString::number(mKernel.at<float>(i, j))));
        }
    }
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

void Filter2D::on_comboBox_currentIndexChanged(int index)
{
    ui->tableWidget->setEnabled(false);
    switch (index)
    {
    case (int)Kernels::Custom:
        ui->tableWidget->setEnabled(true);
        break;
    case (int)Kernels::Identity:
        mKernel = 0.0;
        mKernel.at<float>(1, 1) = 1.0;

        updateTable();
        updateImage();
        break;
    case (int)Kernels::GauissianBlur:
        mKernel.at<float>(0, 0) = 1.0f / 16.0f;
        mKernel.at<float>(0, 2) = 1.0f / 16.0f;
        mKernel.at<float>(2, 0) = 1.0f / 16.0f;
        mKernel.at<float>(2, 2) = 1.0f / 16.0f;
        mKernel.at<float>(0, 1) = 2.0f / 16.0f;
        mKernel.at<float>(1, 0) = 2.0f / 16.0f;
        mKernel.at<float>(1, 2) = 2.0f / 16.0f;
        mKernel.at<float>(2, 1) = 2.0f / 16.0f;
        mKernel.at<float>(1, 1) = 4.0f / 16.0f;
        updateTable();
        updateImage();
        break;
    case (int)Kernels::BottomSobel:
        mKernel = 0.0;
        mKernel.at<float>(0, 0) = -1.0f;
        mKernel.at<float>(0, 1) = -2.0f;
        mKernel.at<float>(0, 2) = -1.0f;
        mKernel.at<float>(2, 0) =  1.0f;
        mKernel.at<float>(2, 1) =  2.0f;
        mKernel.at<float>(2, 2) =  1.0f;

        updateTable();
        updateImage();
        break;
    case (int)Kernels::TopSobel:
        mKernel = 0.0;
        mKernel.at<float>(0, 0) =  1.0f;
        mKernel.at<float>(0, 1) =  2.0f;
        mKernel.at<float>(0, 2) =  1.0f;
        mKernel.at<float>(2, 0) = -1.0f;
        mKernel.at<float>(2, 1) = -2.0f;
        mKernel.at<float>(2, 2) = -1.0f;

        updateTable();
        updateImage();
        break;
    case (int)Kernels::LeftSobel:
        mKernel = 0.0;
        mKernel.at<float>(0, 0) =  1.0f;
        mKernel.at<float>(1, 0) =  2.0f;
        mKernel.at<float>(2, 0) =  1.0f;
        mKernel.at<float>(0, 2) = -1.0f;
        mKernel.at<float>(1, 2) = -2.0f;
        mKernel.at<float>(2, 2) = -1.0f;

        updateTable();
        updateImage();
        break;
    case (int)Kernels::RightSobel:
        mKernel = 0.0;
        mKernel.at<float>(0, 0) = -1.0f;
        mKernel.at<float>(1, 0) = -2.0f;
        mKernel.at<float>(2, 0) = -1.0f;
        mKernel.at<float>(0, 2) =  1.0f;
        mKernel.at<float>(1, 2) =  2.0f;
        mKernel.at<float>(2, 2) =  1.0f;

        updateTable();
        updateImage();
        break;
    case (int)Kernels::Outline:
        mKernel = -1.0f;
        mKernel.at<float>(1, 1) = 8.0f;

        updateTable();
        updateImage();
        break;
    case (int)Kernels::Sharpen:
        mKernel = 0.0f;
        mKernel.at<float>(1, 1) =  5.0f;
        mKernel.at<float>(0, 1) = -1.0f;
        mKernel.at<float>(1, 0) = -1.0f;
        mKernel.at<float>(1, 2) = -1.0f;
        mKernel.at<float>(2, 1) = -1.0f;

        updateTable();
        updateImage();
        break;
    default:
        break;
    }
}
