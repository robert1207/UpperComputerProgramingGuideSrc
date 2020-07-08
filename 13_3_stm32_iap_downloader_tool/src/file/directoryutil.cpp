/*
 * @Name       core
 * @Author    Robert Zhang
 * @E-mail    zhangzhiguo1207@163.com
 * @Date       2019-08-03
 */

#include "directoryutil.h"

#include <QStandardPaths>
#include <QDir>
#include <QFileInfo>
#include <QDebug>



DirectoryUtil::DirectoryUtil()
{

}

bool DirectoryUtil::IsDirExist(QString fullPath)
{
    QDir dir(fullPath);
    if(dir.exists())
    {
      return true;
    }
    return false;
}

bool DirectoryUtil::IsFileExist(QString fullFilePath)
{
    QFileInfo fileInfo(fullFilePath);
    if(fileInfo.exists())
    {
        return true;
    }
    return false;
}

bool DirectoryUtil::CreatePath(QString dir) {
    QDir qdir;
    return qdir.mkpath(dir);
}

bool DirectoryUtil::RemoveFolderContent(const QString &folderDir) {
    QDir dir(folderDir);
    QFileInfoList fileList;
    QFileInfo curFile;
    if(!dir.exists())  {return false;}
    fileList=dir.entryInfoList(QDir::Dirs|QDir::Files
                               |QDir::Readable|QDir::Writable
                               |QDir::Hidden|QDir::NoDotAndDotDot
                               ,QDir::Name);
    while(fileList.size()>0) {
        int infoNum=fileList.size();
        for(int i=infoNum-1;i>=0;i--) {
            curFile=fileList[i];
            if(curFile.isFile()) {
                QFile fileTemp(curFile.filePath());
                fileTemp.remove();
                fileList.removeAt(i);
            }
            if(curFile.isDir()) {
                QDir dirTemp(curFile.filePath());
                QFileInfoList fileList1=dirTemp.entryInfoList(QDir::Dirs|QDir::Files
                                                              |QDir::Readable|QDir::Writable
                                                              |QDir::Hidden|QDir::NoDotAndDotDot
                                                              ,QDir::Name);
                if(fileList1.size()==0) {
                    dirTemp.rmdir(".");
                    fileList.removeAt(i);
                }
                else {
                    for(int j=0; j<fileList1.size(); j++) {
                        if(!(fileList.contains(fileList1[j])))
                            fileList.append(fileList1[j]);
                    }
                }
            }
        }
    }
   return true;
}


