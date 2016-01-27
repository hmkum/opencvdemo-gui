#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <vector>
#include <QMainWindow>
#include <opencv/cv.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void showModifiedImage();
    std::vector<cv::Mat> calculateHistogram() const;
    void showHistogram(const std::vector<cv::Mat> &hists) const;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

    void on_actionTo_Gray_triggered();
    void on_actionTo_RGB_triggered();
    void on_actionTo_Lab_triggered();
    void on_actionTo_HSV_triggered();
    void on_actionFrom_RGB_triggered();
    void on_actionFrom_Lab_triggered();
    void on_actionFrom_HSV_triggered();

    void on_actionSplit_channels_triggered();
    void on_actionCanny_triggered();
    void on_actionSobel_triggered();
    void on_actionLaplacian_triggered();
    void on_actionFilter_triggered();
    void on_actionHistogram_triggered();
    void on_actionNoiseGenerator_triggered();

private:
    Ui::MainWindow *ui;
    cv::Mat mOrgImage;
    cv::Mat mModifiedImage;
};

#endif // MAINWINDOW_H
