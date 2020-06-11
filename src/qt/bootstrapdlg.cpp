#include <qt/bootstrapdlg.h>
#include <qt/forms/ui_bootstrapdlg.h>

#include <qt/guiutil.h>
#include <qt/guiconstants.h>
#include <bootstrap.h>
#include <QDesktopServices>

Bootstrapdlg::Bootstrapdlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Bootstrapdlg)
{
    ui->setupUi(this);
    setWindowTitle(tr("Chain Bootstrap"));
    ui->checkBox->setVisible(false);
}

Bootstrapdlg::~Bootstrapdlg()
{
    delete ui;
}

Bootstrapdlg* xfer_callback_instance;
static void xfer_callback(curl_off_t total, curl_off_t now)
{
    xfer_callback_instance->setProgress(total, now);
}

void Bootstrapdlg::on_startButton_clicked()
{
    extern void set_xferinfo_data(void*);

    xfer_callback_instance = this;
    set_xferinfo_data((void*)xfer_callback);

    QMessageBox::information(this, "Bootstrap", "The client will now bootstrap the chain. \n\nThe Verium vault will exit after extracting the bootstrap and need to be restarted.", QMessageBox::Ok, QMessageBox::Ok);
    try {
        DownloadBootstrap();
    } catch (const std::runtime_error& e) {
        QMessageBox::critical(this, tr("Bootstrap failed"), e.what());
    }
    set_xferinfo_data(nullptr);
    xfer_callback_instance = nullptr;
    this->close();
    QApplication::quit();
}

void Bootstrapdlg::setProgress(curl_off_t total, curl_off_t now)
{
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(total - 1);
    ui->progressBar->setValue(now);
}
