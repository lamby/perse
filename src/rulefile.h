#ifndef RULEFILE_H
#define RULEFILE_H

#include <QObject>
#include <QStringList>

#define RULE_FILE "/lib/udev/rules.d/50-perse.rules"

/**
 * Handles loading & saving the rule file
 */
class RuleFile : public QObject
{
    Q_OBJECT
public:
    explicit RuleFile(QObject *parent = 0);
    bool canWriteFile();
    void readFile();
    void writeFile(QStringList allowedIds);
signals:
    void deviceHasRule(QString usbId);
};

#endif // RULEFILE_H
