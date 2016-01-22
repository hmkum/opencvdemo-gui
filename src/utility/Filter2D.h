#ifndef FILTER2D_H
#define FILTER2D_H

#include <QDialog>
#include <QTableWidgetItem>
#include <opencv/cv.hpp>

namespace Ui {
class Filter2D;
}

class Filter2D : public QDialog
{
    Q_OBJECT

public:
    explicit Filter2D(QWidget *parent = 0);
    Filter2D(QWidget *parent, cv::Mat image);
    ~Filter2D();

private slots:
    void on_btnSave_clicked();
    void on_tableWidget_itemChanged(QTableWidgetItem *item);

private:
    void updateImage();

private:
    Ui::Filter2D *ui;

    cv::Mat mImage, mResult, mKernel;
};

#endif // FILTER2D_H