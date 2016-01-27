#ifndef FILTER2D_H
#define FILTER2D_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <opencv/cv.hpp>

namespace Ui {
class Filter2D;
}

enum class Kernels : short {Custom, Identity, GauissianBlur, BottomSobel, TopSobel,
                            LeftSobel, RightSobel, Outline, Sharpen};

const int KernelSize = 3;

class Filter2D : public QMainWindow
{
    Q_OBJECT

public:
    explicit Filter2D(QWidget *parent = 0);
    Filter2D(QWidget *parent, cv::Mat image);
    ~Filter2D();

private slots:
    void on_btnSave_clicked();
    void on_tableWidget_itemChanged(QTableWidgetItem *item);
    void on_comboBox_currentIndexChanged(int index);
    void on_tbScale_textChanged(const QString &arg1);

private:
    void updateImage();
    void updateTable();

private:
    Ui::Filter2D *ui;

    cv::Mat mImage, mResult, mKernel;
    float mScale;
};

#endif // FILTER2D_H
