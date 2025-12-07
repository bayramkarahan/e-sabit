#ifndef BACKUPPROGRESSDIALOG_H
#define BACKUPPROGRESSDIALOG_H

#include <QDialog>
#include <QProcess>
#include <QProgressBar>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTimer>
#include <QDateTime>
class BackupProgressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BackupProgressDialog(const QString &source,
                                  const QString &dest,
                                  QWidget *parent = nullptr)
        : QDialog(parent),
        m_source(source),
        m_dest(dest)
    {
        setWindowTitle("Yedekleme İşlemi");

        progress = new QProgressBar(this);
        progress->setRange(0, 100);
        progress->setValue(0);

        lblStatus = new QLabel("Başlatılıyor...", this);
        lblSpeed = new QLabel("-", this);
        lblEta = new QLabel("-", this);

        btnCancel = new QPushButton("İptal", this);
        connect(btnCancel, &QPushButton::clicked, this, &BackupProgressDialog::cancelBackup);

        auto *layout = new QVBoxLayout(this);
        layout->addWidget(lblStatus);
        layout->addWidget(progress);
        layout->addWidget(lblSpeed);
        layout->addWidget(lblEta);
        layout->addWidget(btnCancel);

        // rsync başlat
        startBackup();
    }

private slots:
    void startBackup()
    {
        proc = new QProcess(this);

        connect(proc, &QProcess::readyReadStandardError, this, &BackupProgressDialog::readRsyncOutput);
        connect(proc, SIGNAL(finished(int,QProcess::ExitStatus)),
                this, SLOT(backupFinished(int,QProcess::ExitStatus)));

        QStringList args;
        args << "-a" << "--info=progress2" << "--delete"
             << m_source << m_dest;

        startTime = QDateTime::currentDateTime();

        proc->start("rsync", args);
    }

    void readRsyncOutput()
    {
        QByteArray data = proc->readAllStandardError();
        QString text = QString::fromUtf8(data);

        // progress2 örnek çıktı:
        //  123,456,789  45%   25.48MB/s    00:02:11

        QRegExp rx("(\\d+)[ ]+(\\d+)%[ ]+([0-9\\.]+)([A-Z]+)/s[ ]+([0-9:]+)");
        // Gruplar:
        // 1 = kopyalanan byte
        // 2 = yüzde
        // 3 = hız sayısı
        // 4 = hız birimi (K,M,G)
        // 5 = ETA

        if (rx.indexIn(text) != -1) {
            QString bytesStr = rx.cap(1);
            QString percentStr = rx.cap(2);
            QString speedNum = rx.cap(3);
            QString speedUnit = rx.cap(4);
            QString eta = rx.cap(5);

            int percent = percentStr.toInt();
            progress->setValue(percent);

            lblStatus->setText(QString("Kopyalanıyor: %1%").arg(percent));
            lblSpeed->setText(QString("Hız: %1 %2/s").arg(speedNum, speedUnit));
            lblEta->setText(QString("Tahmini Süre: %1").arg(eta));
        }
    }

    void backupFinished(int code, QProcess::ExitStatus status)
    {
        if (status == QProcess::NormalExit && code == 0) {
            progress->setValue(100);
            lblStatus->setText("Tamamlandı.");
            btnCancel->setText("Kapat");
        } else {
            lblStatus->setText("Hata oluştu!");
        }
    }

    void cancelBackup()
    {
        if (proc) {
            proc->kill();
            lblStatus->setText("İptal edildi.");
            btnCancel->setText("Kapat");
        }
    }

private:
    QString m_source, m_dest;
    QProcess *proc = nullptr;

    QProgressBar *progress;
    QLabel *lblStatus;
    QLabel *lblSpeed;
    QLabel *lblEta;
    QPushButton *btnCancel;

    QDateTime startTime;
};

#endif // BACKUPPROGRESSDIALOG_H
