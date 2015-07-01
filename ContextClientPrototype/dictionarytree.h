#ifndef DICTIONARYTREE_H
#define DICTIONARYTREE_H

#include <QApplication>

#include <QSplitter>

#include <QTreeView>
#include <QList>

#include <QStandardItemModel>


#include <QFile>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttributes>
#include <stdio.h>

class DictionaryTree : public QTreeView
{
    Q_OBJECT

public:
    DictionaryTree(QWidget *parent = 0);
    ~DictionaryTree(){}

    int appendNode(QStandardItemModel *model, QString text, QVariant data, int level, QStandardItem *currentItem = NULL);

    void loadDictionaryXml(QFile *file);

    QWidget* prepareDisplay(QString selectionText = "");

    QList<QVariant> getSelectedData();

    QStandardItemModel model;

    int getRowCount() const {
        return rowCount;
    }
    void setRowCount(int rows) {
        rowCount = rows;
    }

    int getMinimumSize() {
        return minimumSize;
    }

    int getNumberInQueue() {
        return numberInQueue;
    }

    void setNumberInQueue(int number) {
        numberInQueue = number;
    }

    bool hasSelection() {
        return selectedIndexes().isEmpty();
    }

    // Attributes
    QString getBrickCount() const {
        return brickCount;
    }
    void setBrickCount(QString brickCount) {
        this->brickCount = brickCount;
    }

    QString getName() const {
        return name;
    }
    void setName(QString name) {
        this->name = name;
    }

    QString getSourceType() const {
        return sourceType;
    }
    void setSourceType(QString sourceType) {
        this->sourceType = sourceType;
    }

    QString getSourceLocation() const {
        return sourceLocation;
    }
    void setSourceLocation(QString sourceLocation) {
        this->sourceLocation = sourceLocation;
    }

    QString getSourceFormat() const {
        return sourceFormat;
    }
    void setSourceFormat(QString sourceFormat) {
        this->sourceFormat = sourceFormat;
    }

signals:
    void requestContextData();
    void answerContextData(QList<QVariant> data);

public slots:
    void answerContextData();

private:

    QString xmlType;
    QString xmlName;
    QString source;

    QString brickCount;
    QString itemId;
    QString name;
    QString sourceType;
    QString sourceLocation;
    QString sourceFormat;


    QXmlStreamReader::TokenType type;
    QXmlStreamReader::TokenType lastType;

    QString lastName;

    int rowCount;
    int minimumSize;

    int level;
    int maxLevel;
    int levelRowCount;

    QList<int> levelRowCounts;

    int binaryCeil;
    QList<int> levelBinaryCeils;

    int numberInQueue;

};
#endif // DICTIONARYTREE_H

