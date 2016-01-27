#ifndef NOISEGENERATOR_H
#define NOISEGENERATOR_H

#include <QDialog>

#include <opencv/cv.hpp>

namespace Ui {
class NoiseGenerator;
}

class NoiseGenerator : public QDialog
{
    Q_OBJECT

public:
    explicit NoiseGenerator(QWidget *parent = 0);
    NoiseGenerator(QWidget *parent, const cv::Mat &image);
    ~NoiseGenerator();

private slots:
    void on_btnSPShow_clicked();

    void on_btnSPSave_clicked();

    void on_btnGShow_clicked();

    void on_btnGSave_clicked();

private:
    Ui::NoiseGenerator *ui;

    cv::Mat mImage;
    cv::Mat mResult;
};

#endif // NOISEGENERATOR_H
