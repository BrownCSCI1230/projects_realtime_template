#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCheckBox>
#include <QPushButton>
#include "glrenderer.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    void initialize();
    void finish();

private:

    void connectUIElements();
    GLRenderer *glRenderer;
    QCheckBox *filter1;
    QCheckBox *filter2;
    QPushButton *uploadFile;

private slots:
    void onPerPixel();
    void onKernelBased();
    void onUploadFile();
};
#endif // MAINWINDOW_H
