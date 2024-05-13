#pragma once

#include <QGuiApplication>
#include <QFile>
#include <QDir>
#include <QString>
#include <QDebug>
#include <QDateTime>
#include <QFileInfoList>

class Logger
{
	Logger();
public:
	static void renameLog();
	static void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);
	static void CreateFolders();

	static Logger *getInstance();
private:
	static FILE *logfile;
	static char *filenameLog;
	static int maxCountFiles;

	static Logger *logSingleInstance;

    static const QString appName;
};
