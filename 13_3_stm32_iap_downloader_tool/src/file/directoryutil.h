/*
 * @Name       core
 * @Author    Robert Zhang
 * @E-mail    zhangzhiguo1207@163.com
 * @Date       2019-08-03
 */

#ifndef DIRECTORYUTIL_H
#define DIRECTORYUTIL_H

#include <QString>



class DirectoryUtil
{
private:
    DirectoryUtil();

public:

    static bool IsDirExist(QString fullPath);
    static bool IsFileExist(QString fullFilePath);
    static bool CreatePath(QString dir);
    static bool RemoveFolderContent(const QString &folderDir);


};



#endif // DIRECTORYUTIL_H
