
#ifndef WORK_H
#define WORK_H

#include <QByteArray>

class Work
{
public:
    Work();

    int failed_times;
    QByteArray data;

    bool CheckResponse(quint8 * return_pkg);

};

#endif // WORK_H
