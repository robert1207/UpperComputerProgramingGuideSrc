
#ifndef WORK_H
#define WORK_H

#include <QByteArray>

namespace HYKT {
class Work
{
public:
    Work();

    int failed_times;
    QByteArray data;

    bool CheckResponse(quint8 * return_pkg);

};
} //namespace HYKT

#endif // WORK_H
