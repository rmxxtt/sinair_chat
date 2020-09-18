#include "json.h"

QJsonObject jsonStrToObj(QString jsonString)
{
    QJsonObject jsonObj;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());

    if (!jsonDoc.isNull()) {
        if (jsonDoc.isObject()) {
            jsonObj = jsonDoc.object();
        }
        else {
            qDebug() << "Document is not object";
        }
    }
    else {
        qDebug() << "Invalid JSON";
    }

    return jsonObj;
}
