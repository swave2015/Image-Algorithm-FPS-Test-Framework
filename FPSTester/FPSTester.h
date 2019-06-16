#ifndef FPSTESTER_H
#define FPSTESTER_H

#include "FPSTesterThread.h"
#include "ImgGetterThread.h"
#include <QObject>

namespace cv {
class Mat;
}

namespace fpsTest {

class FPSTester : public QObject
{
    Q_OBJECT
public:
    explicit FPSTester(QObject *parent = nullptr);

    void setTestTime(qint64 time);
    void setImgGetter(ImgGetter *igt);
    void setAlgorithm(Algorithm *alg);
    void setSavePath(const QString &path);

    void start();
    void stop();

signals:
    void stopped();
    void errorMsg(const QString& msg);

private slots:
    /**
     * @brief onTesterUpdated
     *   测试线程更新时触发
     * @param t 算法计时
     * @param count 算法已处理的帧数
     */
    void onTesterUpdated(qint64 t, qint64 count);
    void onTesterStopped();
    void onImgGetterStopped();

    void onStopped();

    void onErrorMsg(const QString& msg);

private:
    ImgGetterThread mImgGetThread;
    FPSTesterThread mFPSTestThread;

    QString mSavePath;

    qint64 mTestTime;
    qint64 mTestCount;
};


class ImgGetter
{
public:
    ImgGetter() {}
    virtual ~ImgGetter() {}

    virtual bool init() = 0;
    virtual cv::Mat getImg() = 0;
};

class Algorithm
{
public:
    Algorithm() {}
    virtual ~Algorithm() {}

    virtual bool init() = 0;
    virtual void update(cv::Mat& img) = 0;
};
}

#endif // FPSTESTER_H
