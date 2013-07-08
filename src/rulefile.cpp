#include "rulefile.h"
#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QFileInfo>

RuleFile::RuleFile(QObject *parent) :
    QObject(parent)
{
}

bool RuleFile::canWriteFile()
{
    QFileInfo file(RULE_FILE);
    return file.isWritable();
}

void RuleFile::readFile()
{
    QFile file(RULE_FILE);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);

    QString line;
    do {
        line = in.readLine();
        if(line.startsWith("ATTRS")) {
            QString vid = line.split("\"").at(1);
            QString pid = line.split("\"").at(3);
            if(vid.length() >= 4 && pid.length() >= 4) {
                QString usbId = vid + ":" + pid;
                emit deviceHasRule(usbId);
            }
        }
    } while(!line.isNull());
    file.close();
}

void RuleFile::writeFile(QStringList allowedIds)
{
    qDebug() << Q_FUNC_INFO << allowedIds;
    QFile file(RULE_FILE);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << "# This file has been generated by perse. Do not edit by hand.\n";
    foreach(QString usbId, allowedIds) {
        QString vid = usbId.split(":").at(0);
        QString pid = usbId.split(":").at(1);
        out << "ATTRS{idVendor}==\"" << vid << "\", ATTRS{idProduct}==\"" << pid << "\", MODE:=\"666\"\n";
    }
    file.close();
}
