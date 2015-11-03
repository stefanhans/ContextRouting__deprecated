#include "bitmatrixmodel.h"

BitMatrixModel::BitMatrixModel(QObject *parent)
    :QAbstractTableModel(parent)
{
}


int BitMatrixModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

int BitMatrixModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

QVariant BitMatrixModel::data(const QModelIndex &index, int role) const
{
    // dummy
    return QVariant();
}
