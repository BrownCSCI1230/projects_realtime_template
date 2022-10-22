#include "mainwindow.h"
#include "settings.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QSettings>

void MainWindow::initialize() {
    realtime = new Realtime;

    QHBoxLayout *hLayout = new QHBoxLayout; // horizontal alignment
    QVBoxLayout *vLayout = new QVBoxLayout(); // vertical alignment
    vLayout->setAlignment(Qt::AlignTop);
    hLayout->addLayout(vLayout);
    hLayout->addWidget(realtime, 1);
    this->setLayout(hLayout);

    // Create toggle for showing wireframe / normals
    filter1 = new QCheckBox();
    filter1->setText(QStringLiteral("Per-Pixel Filter"));
    filter1->setChecked(false);

    // Create toggle for showing wireframe / normals
    filter2 = new QCheckBox();
    filter2->setText(QStringLiteral("Kernel-Based Filter"));
    filter2->setChecked(false);

    // Create file uploader for scene file
    uploadFile = new QPushButton();
    uploadFile->setText(QStringLiteral("Upload Scene File"));

    vLayout->addWidget(uploadFile);
    vLayout->addWidget(filter1);
    vLayout->addWidget(filter2);

    connectUIElements();
}

void MainWindow::finish() {
    realtime->finish();
    delete(realtime);
}

void MainWindow::connectUIElements() {
    connect(filter1, &QCheckBox::clicked, this, &MainWindow::onPerPixelFilter); // invert colors cb
    connect(filter2, &QCheckBox::clicked, this, &MainWindow::onKernelBasedFilter); // sharpen image cb
    connect(uploadFile, &QPushButton::clicked, this, &MainWindow::onUploadFile); // upload file button
}

void MainWindow::onPerPixelFilter() {
    settings.perPixelFilter = !settings.perPixelFilter;
    realtime->settingsChange();
}

void MainWindow::onKernelBasedFilter() {
    settings.kernelBasedFilter = !settings.kernelBasedFilter;
    realtime->settingsChange();
}

void MainWindow::onUploadFile() {
    // Get abs path of config file
    QString configFilePath = QFileDialog::getOpenFileName(this, tr("Upload File"), QDir::homePath(), tr("Config Files (*.ini)"));
    if (configFilePath.isNull()) { return; }

    // Parse .ini config file
    QSettings qsettings(configFilePath, QSettings::IniFormat);
    settings.sceneFilePath = qsettings.value("IO/scene").toString().toStdString();
    settings.shapeParameter1 = qsettings.value("tesselation_param_1").toInt();
    settings.shapeParameter2 = qsettings.value("tesselation_param_2").toInt();
    realtime->sceneChange();
}
