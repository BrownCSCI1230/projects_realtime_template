#pragma once

#include <QMainWindow>
#include <QCheckBox>
#include <QPushButton>
#include "realtime.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    void initialize();
    void finish();

private:

    void connectUIElements();
    Realtime *realtime;
    QCheckBox *filter1;
    QCheckBox *filter2;
    QPushButton *uploadFile;

private slots:
    void onPerPixelFilter();
    void onKernelBasedFilter();
    void onUploadFile();
};
