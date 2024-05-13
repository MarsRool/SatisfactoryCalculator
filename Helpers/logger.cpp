#include "Helpers/logger.h"

Logger *Logger::logSingleInstance = nullptr;
FILE *Logger::logfile = nullptr;
char *Logger::filenameLog = nullptr;
int Logger::maxCountFiles = 10;

Logger::Logger()
{
	qInstallMessageHandler(myMessageOutput);
	CreateFolders();
	renameLog();
}

void Logger::renameLog()
{
#ifdef WIN32
	QString prefix = qApp->applicationDirPath();
#elif __ANDROID__
    QString prefix = "/sdcard/" + qApp->applicationName();
#endif
    QDir qdir(prefix+"/data/log/");
	int a = 100;
	QFileInfoList list = qdir.entryInfoList(QDir::Filter::Files,QDir::SortFlag::Time);
	while (list.size() > maxCountFiles && a > 0)
	{
		QFileInfo fileinfo = list.last();
		QString deletingFileName = fileinfo.filePath();
		QFile deleting(deletingFileName);
		if (deleting.exists())
		{
			deleting.remove();
			list.pop_front();
		}
		a--;
	}

    QString qfilename = QString(prefix+"/data/log/log"+QDateTime::currentDateTime().toString("dd_MM_yyyy-hh_mm_ss")+".log");
	filenameLog = new char[static_cast<unsigned int>(qfilename.length()+1)];
	for (int i = 0; i < qfilename.length(); i++)
		filenameLog[i] = qfilename.at(i).toLatin1();
	filenameLog[qfilename.length()] = '\0';
}

void Logger::myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	if (QFile(filenameLog).size() > 10485760)
	{
		renameLog();
	}
	logfile = fopen(filenameLog,"a");
	if (!logSingleInstance)
		return;
	QString dateTimeNow = QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss: ").toLocal8Bit();
	QByteArray localMsg = (dateTimeNow + msg).toLocal8Bit();
	switch (type)
	{
	case QtDebugMsg:
		fprintf(logfile, "Debug: %s\n", localMsg.constData());
		break;
	case QtInfoMsg:
		fprintf(logfile, "Info: %s\n", localMsg.constData());
		break;
	case QtWarningMsg:
		fprintf(logfile, "Warning: %s\n", localMsg.constData());
		break;
	case QtCriticalMsg:
		fprintf(logfile, "Critical: %s\n", localMsg.constData());
		break;
	case QtFatalMsg:
		fprintf(logfile, "Fatal: %s\n", localMsg.constData());
	}
	fclose(logfile);
	Q_UNUSED(context)
}

void Logger::CreateFolders()
{
#ifdef WIN32
    QString prefix = qApp->applicationDirPath();
#elif __ANDROID__
    QString prefix = "/sdcard/" + qApp->applicationName();
#endif

    QDir qdirLog(prefix+"/data/log/");
	if(!qdirLog.exists())
	{
        qdirLog.mkpath(prefix+"/data/log/");
        qDebug() << "mkpath "+prefix+"/data/log/";
	}
}

Logger *Logger::getInstance()
{
	if (logSingleInstance == nullptr)
		logSingleInstance = new Logger();
	return logSingleInstance;
}

