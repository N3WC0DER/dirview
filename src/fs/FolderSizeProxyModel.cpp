#include "FolderSizeProxyModel.h"

FolderSizeProxyModel::FolderSizeProxyModel(QObject *parent) : QIdentityProxyModel(parent) { }

void FolderSizeProxyModel::updateFolderSize(const QString &path, quint64 size) {
    sizesCache[path] = size;
    
    // Обновляем колонку с размером
    auto filterProxyModel = qobject_cast<FilterProxyModel*>(sourceModel());
    if (!filterProxyModel) return;

    auto fsModel = qobject_cast<QFileSystemModel*>(filterProxyModel->sourceModel());
    if (!fsModel) return;

    QModelIndex srcIndex = fsModel->index(path);
    QModelIndex srcSizeIndex = fsModel->index(srcIndex.row(), 1, srcIndex.parent());
    QModelIndex filterProxyIndex = filterProxyModel->mapFromSource(srcSizeIndex);
    QModelIndex proxyIndex = mapFromSource(filterProxyIndex);
    
    emit dataChanged(proxyIndex, proxyIndex, {Qt::DisplayRole});
}

QVariant FolderSizeProxyModel::data(const QModelIndex &proxyIndex, int role) const {
    if (!proxyIndex.isValid()) return QVariant();

    if (proxyIndex.column() == 1 && role == Qt::DisplayRole) {
        auto filterProxyModel = qobject_cast<FilterProxyModel*>(sourceModel());
        if (filterProxyModel) {
            auto fsModel = qobject_cast<QFileSystemModel*>(filterProxyModel->sourceModel());
            if (fsModel) {
                QModelIndex filterProxyIndex = mapToSource(proxyIndex);
                QModelIndex srcIndex = filterProxyModel->mapToSource(filterProxyIndex);
                QString path = fsModel->filePath(srcIndex);
                
                if (fsModel->isDir(srcIndex) && sizesCache.contains(path)) {
                    return formatSize(sizesCache[path]);
                }
            }
        }
    }
    return QIdentityProxyModel::data(proxyIndex, role);
}

QString FolderSizeProxyModel::formatSize(quint64 bytes) {
    QStringList units = {tr("Б"), tr("КБ"), tr("МБ"), tr("ГБ"), tr("ТБ")};
    double size = bytes;
    int unitIndex = 0;
    while (size >= 1024 && unitIndex < units.size() - 1) {
        size /= 1024;
        unitIndex++;
    }
    return QString("%1 %2").arg(size, 0, 'f', 1).arg(units[unitIndex]);
}