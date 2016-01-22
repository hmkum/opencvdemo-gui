#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "edge_detection/CannyEdgeDetection.h"
#include "edge_detection/SobelEdgeDetection.h"
#include "edge_detection/LaplacianEdgeDetection.h"
#include "utility/Filter2D.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showModifiedImage()
{
    if(!mModifiedImage.empty())
    {
        cv::imshow("Modified", mModifiedImage);
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Firstly, open an image!");
    }
}

void MainWindow::on_pushButton_clicked()
{
    QFileDialog *fileDialog = new QFileDialog(this, "Select Image");
    fileDialog->setNameFilter("Images (*.png)");
    ui->lblImageName->setText(fileDialog->getOpenFileName());
    mModifiedImage = cv::imread(ui->lblImageName->text().toStdString());
    if(mModifiedImage.empty())
    {
        ui->lblImageName->setText("");
        QMessageBox::critical(this, "Fatal Error", "Please select proper image");
    }

    mOrgImage = mModifiedImage.clone();
    ui->statusBar->showMessage("Image opened successfully.");
}

// Show modified image
void MainWindow::on_pushButton_2_clicked()
{
    showModifiedImage();
}

// Show original image
void MainWindow::on_pushButton_3_clicked()
{
    if(!mOrgImage.empty())
    {
        cv::imshow("Original", mOrgImage);
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Firstly, open an image!");
    }
}

void MainWindow::on_actionTo_Gray_triggered()
{
    try
    {
        cv::cvtColor(mOrgImage, mModifiedImage, CV_BGR2GRAY);
    } catch(cv::Exception &ex)
    {
        std::string err = "Exception: ";
        err += ex.err.c_str();
        ui->statusBar->showMessage(err.c_str());

        return;
    }

    ui->statusBar->showMessage("Image converted to gray.");
    showModifiedImage();
}

void MainWindow::on_actionTo_RGB_triggered()
{
    try
    {
        cv::cvtColor(mOrgImage, mModifiedImage, CV_BGR2RGB);
    } catch(cv::Exception &ex)
    {
        std::string err = "Exception: ";
        err += ex.err.c_str();
        ui->statusBar->showMessage(err.c_str());

        return;
    }

    ui->statusBar->showMessage("Image converted to RGB.");
    showModifiedImage();
}

void MainWindow::on_actionTo_Lab_triggered()
{
    try
    {
        cv::cvtColor(mOrgImage, mModifiedImage, CV_BGR2Lab);
    } catch(cv::Exception &ex)
    {
        std::string err = "Exception: ";
        err += ex.err.c_str();
        ui->statusBar->showMessage(err.c_str());

        return;
    }

    ui->statusBar->showMessage("Image converted to Lab.");
    showModifiedImage();
}

void MainWindow::on_actionTo_HSV_triggered()
{
    try
    {
        cv::cvtColor(mOrgImage, mModifiedImage, CV_BGR2HSV);
    } catch(cv::Exception &ex)
    {
        std::string err = "Exception: ";
        err += ex.err.c_str();
        ui->statusBar->showMessage(err.c_str());

        return;
    }

    ui->statusBar->showMessage("Image converted to HSV.");
    showModifiedImage();
}

void MainWindow::on_actionFrom_RGB_triggered()
{
    try
    {
        cv::cvtColor(mModifiedImage, mModifiedImage, CV_RGB2BGR);
    } catch(cv::Exception &ex)
    {
        std::string err = "Exception: ";
        err += ex.err.c_str();
        ui->statusBar->showMessage(err.c_str());

        return;
    }

    ui->statusBar->showMessage("Image converted from RGB to BGR.");
    showModifiedImage();
}

void MainWindow::on_actionFrom_Lab_triggered()
{
    try
    {
        cv::cvtColor(mModifiedImage, mModifiedImage, CV_Lab2BGR);
    } catch(cv::Exception &ex)
    {
        std::string err = "Exception: ";
        err += ex.err.c_str();
        ui->statusBar->showMessage(err.c_str());

        return;
    }

    ui->statusBar->showMessage("Image converted from Lab to BGR.");
    showModifiedImage();
}

void MainWindow::on_actionFrom_HSV_triggered()
{
    try
    {
        cv::cvtColor(mModifiedImage, mModifiedImage, CV_HSV2BGR);
    } catch(cv::Exception &ex)
    {
        std::string err = "Exception: ";
        err += ex.err.c_str();
        ui->statusBar->showMessage(err.c_str());

        return;
    }

    ui->statusBar->showMessage("Image converted from HSV to BGR.");
    showModifiedImage();
}


void MainWindow::on_actionSplit_channels_triggered()
{
    std::vector<cv::Mat> channels;
    cv::split(mModifiedImage, channels);
    for(size_t i = 0; i < channels.size(); ++i)
    {
        cv::imshow((QString("Channel %1").arg(QString::number(i + 1))).toStdString().c_str(), channels[i]);
    }
}

void MainWindow::on_actionCanny_triggered()
{
    CannyEdgeDetection *ced = new CannyEdgeDetection(this, mModifiedImage);
    ced->exec();
}

void MainWindow::on_actionSobel_triggered()
{
    SobelEdgeDetection *sed = new SobelEdgeDetection(this, mModifiedImage);
    sed->exec();
}

void MainWindow::on_actionLaplacian_triggered()
{
    LaplacianEdgeDetection *led = new LaplacianEdgeDetection(this, mModifiedImage);
    led->exec();
}

void MainWindow::on_actionFilter_triggered()
{
    Filter2D *filter = new Filter2D(this, mModifiedImage);
    filter->exec();
}
