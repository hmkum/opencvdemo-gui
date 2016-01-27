#include "NoiseGenerator.h"
#include "ui_NoiseGenerator.h"

#include <QMessageBox>
#include <QDateTime>

NoiseGenerator::NoiseGenerator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NoiseGenerator)
{
    ui->setupUi(this);
}

NoiseGenerator::NoiseGenerator(QWidget *parent, const cv::Mat &image) :
    QMainWindow(parent),
    ui(new Ui::NoiseGenerator),
    mImage(image)
{
    ui->setupUi(this);

    mResult = mImage.clone();
}

NoiseGenerator::~NoiseGenerator()
{
    delete ui;
}

void NoiseGenerator::on_btnSPShow_clicked()
{
    // Every time clean the image
    mResult = mImage.clone();

    const int nc = mImage.channels();
    int saltCount = ui->tbSaltCount->text().toInt();
    int pepperCount = ui->tbPepperCount->text().toInt();

    int w = mImage.cols;
    int h = mImage.rows;

    // Add salt
    for(int i = 0; i < saltCount; ++i)
    {
        int x = rand() % w;
        int y = rand() % h;

        if(nc == 1)
        {
            mResult.at<uchar>(x, y) = 255;
        }
        else
        {
            mResult.at<cv::Vec3b>(x, y) = cv::Vec3b(255, 255, 255);
        }
    }

    // Add pepper
    for(int i = 0; i < pepperCount; ++i)
    {
        int x = rand() % w;
        int y = rand() % h;

        if(nc == 1)
        {
            mResult.at<uchar>(x, y) = 0;
        }
        else
        {
            mResult.at<cv::Vec3b>(x, y) = cv::Vec3b(0, 0, 0);
        }
    }

    cv::imshow("Salt & Pepper", mResult);
}

void NoiseGenerator::on_btnSPSave_clicked()
{
    if(!mResult.empty())
    {
        std::string date = QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss").toStdString();
        bool res = cv::imwrite("noise_sp_" + date + ".png", mResult);
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

void NoiseGenerator::on_btnGShow_clicked()
{
    // Every time clean the image
    mResult = mImage.clone();

    int sigma = ui->tbSigma->text().toInt();

    cv::Mat noise(mImage.size(), mImage.type());
    cv::randn(noise, cv::Scalar(0), cv::Scalar(1));

    noise *= sigma;

    mResult = mResult + noise;

    cv::imshow("Gaussian", mResult);
}

void NoiseGenerator::on_btnGSave_clicked()
{
    if(!mResult.empty())
    {
        std::string date = QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss").toStdString();
        bool res = cv::imwrite("noise_gaussian_" + date + ".png", mResult);
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
