/*
 *  Copyright (C) 2009 Aleksey Palazhchenko
 *  Copyright (C) 2014 Sergey Shambir
 *  Copyright (C) 2016 Alexander Makarov
 *
 * This file is a part of Breakpad-qt library.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 */

#include <QDir>
#include <QProcess>
#include <QCoreApplication>

#include "BreakpadHandler.h"
#include "BreakpadHttpUploader.h"


static BreakpadHandler* breakpad_static_p = nullptr;

BreakpadHandler* BreakpadHandler::instance = nullptr;
QMutex BreakpadHandler::mutex_;

/**************************** exception handler for each OS ********************/
#if defined(Q_OS_MAC)
#include "client/mac/handler/exception_handler.h"
#elif defined(Q_OS_LINUX)
#include "client/linux/handler/exception_handler.h"
#elif defined(Q_OS_WIN32)
#include "client/windows/handler/exception_handler.h"
#endif


/**************************** DumpCallback for each OS ********************/
#if defined(Q_OS_WIN32)
bool DumpCallback(const wchar_t* dump_dir,
                                    const wchar_t* minidump_id,
                                    void* context,
                                    EXCEPTION_POINTERS* exinfo,
                                    MDRawAssertionInfo* assertion,
                                    bool succeeded)
#elif defined(Q_OS_MAC)
bool DumpCallback(const char *dump_dir,
                                    const char *minidump_id,
                                    void *context, bool succeeded)
#else
bool DumpCallback(const google_breakpad::MinidumpDescriptor& descriptor,
                                    void* context,
                                    bool succeeded)
#endif
{
#ifdef Q_OS_LINUX
    Q_UNUSED(descriptor)
#endif
    Q_UNUSED(context)
#if defined(Q_OS_WIN32)
    Q_UNUSED(assertion)
    Q_UNUSED(exinfo)
#endif
    /*
        NO STACK USE, NO HEAP USE THERE !!!
        Creating QString's, using qDebug, etc. - everything is crash-unfriendly.
    */

#if defined(Q_OS_WIN32)
    QString path = QString::fromWCharArray(dump_dir) + QLatin1String("/") + QString::fromWCharArray(minidump_id);
    qDebug("%s, dump path: %s\n", succeeded ? "Succeed to write minidump" : "Failed to write minidump", qPrintable(path));

    if(breakpad_static_p != nullptr) {
        breakpad_static_p->CallOnCrash(succeeded, QString::fromWCharArray(dump_dir), QString::fromWCharArray(minidump_id));
    }

#elif defined(Q_OS_MAC)
    QString path = QString::fromUtf8(dump_dir) + QLatin1String("/") + QString::fromUtf8(minidump_id);
    qDebug("%s, dump path: %s\n", succeeded ? "Succeed to write minidump" : "Failed to write minidump", qPrintable(path));

    if(breakpad_static_p != nullptr) {
        breakpad_static_p->CallOnCrash(succeeded,  QString::fromUtf8(dump_dir),  QString::fromUtf8(minidump_id));
    }

#else
    qDebug("%s, dump path: %s\n", succeeded ? "Succeed to write minidump" : "Failed to write minidump", descriptor.path());

    if(breakpad_static_p != nullptr) {
        breakpad_static_p->CallOnCrash(succeeded, dump_dir, minidump_id);
    }
#endif

    return succeeded;
}


class BreakpadHandlerPrivate
{
public:
    google_breakpad::ExceptionHandler* pExptHandler;
    QString dumpPath;
    QUrl uploadUrl;
};


BreakpadHandler::BreakpadHandler() :
    d(new BreakpadHandlerPrivate())
{
    breakpad_static_p = this;
}

BreakpadHandler::~BreakpadHandler()
{
    delete d;
    breakpad_static_p = nullptr;
}

BreakpadHandler *BreakpadHandler::GetInstance() {
    if(instance == nullptr) {
        mutex_.lock();
        if(instance == nullptr) {
            instance = new BreakpadHandler();
        }
        mutex_.unlock();
    }
    return instance;
}

void BreakpadHandler::SetupBreakPad(const QString& path)
{
    QString absPath = path;
    if(!QDir::isAbsolutePath(absPath)) {
        absPath = QDir::cleanPath(qApp->applicationDirPath() + "/" + path);
    }
    Q_ASSERT(QDir::isAbsolutePath(absPath));

    QDir().mkpath(absPath);
    if (!QDir().exists(absPath)) {
        qDebug("Failed to set dump path which not exists: %s", qPrintable(absPath));
        return;
    }

    d->dumpPath = absPath;

// NOTE: ExceptionHandler initialization
#if defined(Q_OS_WIN32)
    d->pExptHandler = new google_breakpad::ExceptionHandler(absPath.toStdWString(), /*FilterCallback*/ nullptr,
                                                        DumpCallback, /*context*/ nullptr,
                                                        google_breakpad::ExceptionHandler::HANDLER_ALL);
#elif defined(Q_OS_MAC)
    d->pExptHandler = new google_breakpad::ExceptionHandler(absPath.toStdString(),
                                                            /*FilterCallback*/ nullptr,
                                                        DumpCallback, /*context*/ nullptr, true, nullptr);
#else
    d->pExptHandler = new google_breakpad::ExceptionHandler(google_breakpad::MinidumpDescriptor(absPath.toStdString()),
                                                            /*FilterCallback*/ 0,
                                                            DumpCallback,
                                                            /*context*/ 0,
                                                            true,
                                                            -1);
#endif
}


QString BreakpadHandler::GetBreakPadDumpPath() const
{
    return d->dumpPath;
}

void BreakpadHandler::setUploadUrl(const QUrl &url)
{
    if(!url.isValid() || url.isEmpty())
        return;

    d->uploadUrl = url;
}

QString BreakpadHandler::uploadUrl() const
{
    return d->uploadUrl.toString();
}

QStringList BreakpadHandler::GetDumpFileList() const
{
    if(!d->dumpPath.isNull() && !d->dumpPath.isEmpty()) {
        QDir dumpDir(d->dumpPath);
        dumpDir.setNameFilters(QStringList()<<"*.dmp");
        return dumpDir.entryList();
    }

    return QStringList();
}

void BreakpadHandler::UploadDumpsFiles(QStringList dumpFiles)
{
    foreach(QString itDmpFileName, dumpFiles) {
        qDebug() << "Sending " << QString(itDmpFileName);
        QBreakpadHttpUploader *sender = new QBreakpadHttpUploader(d->uploadUrl);
        sender->uploadDump(d->dumpPath + "/" + itDmpFileName);
    }
}

void BreakpadHandler::CallOnCrash(bool is_success, QString dump_dir, QString dump_file_name) {
   emit onCrash(is_success, dump_dir, dump_file_name);
}

bool  BreakpadHandler::IsHadCrashedDumpFiles() {
    return (GetDumpFileList().count() > 0);
}

void  BreakpadHandler::DeleteAllOfTheDumpFiles() {
    QStringList dump_list =GetDumpFileList();
    foreach(QString itDmpFileName, dump_list) {
        QString old_dump_file_full_path = d->dumpPath + "/" + itDmpFileName;
        QFile fileTemp(old_dump_file_full_path);
        fileTemp.remove();
    }
}
