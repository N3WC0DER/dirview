#pragma once

#include <QSortFilterProxyModel>

/**
 * @brief Класс-прокси для фильтрации файлового дерева.
 * Для фильтрации используется contains.
 */
class FilterProxyModel : public QSortFilterProxyModel {
    Q_OBJECT
public:
    using QSortFilterProxyModel::QSortFilterProxyModel;

    /** Максимальная глубина поиска */
    static const int MAX_DEPTH = 3;

    void setProxyRootPath(const QString &path) {
        rootPath = QDir::cleanPath(path);
    }

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override {
        QModelIndex index = sourceModel()->index(source_row, 0, source_parent);
        if (!index.isValid()) return false;

        QFileSystemModel *fileModel = qobject_cast<QFileSystemModel*>(sourceModel());
        if (!fileModel) {
            return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
        }

        if (!fileModel->isDir(index)) {
            QString text = fileModel->fileName(index);
            return text.contains(filterRegularExpression());
        }

        return checkFolderHasMatches(index, fileModel, 1);
    }

private:

    /** Храним путь корня для фиксирования независимо от фильтра */
    QString rootPath;

    /**
     * @brief Вспомогательный метод для рекурсивной проверки папки
     * 
     * @param folderIndex Индекс исходной папки
     * @param fileModel 
     * @param currentDepth Для контроля уровня вложенности
     * @return true В папке есть подходящие фильтру файлы
     * @return false В папке нет подходящих фильтру файлов
     */
    bool checkFolderHasMatches(const QModelIndex &folderIndex, QFileSystemModel *fileModel, int currentDepth) const {
        if (fileModel->filePath(folderIndex) == rootPath) {
            return true; 
        }
        
        if (currentDepth > MAX_DEPTH) {
            return false;
        }

        QFileInfo dirInfo(fileModel->filePath(folderIndex));
        if (!dirInfo.isReadable()) return false;
        
        int rowCount = fileModel->rowCount(folderIndex);
        
        if (rowCount == 0) {
            
            if (fileModel->canFetchMore(folderIndex)) {
                fileModel->fetchMore(folderIndex);
            }
            return false;
        }

        // Обходим все элементы внутри папки
        for (int i = 0; i < rowCount; ++i) {
            QModelIndex childIndex = fileModel->index(i, 0, folderIndex);
            
            if (fileModel->isDir(childIndex)) {
                if (checkFolderHasMatches(childIndex, fileModel, currentDepth + 1)) {
                    return true;
                }
            } else {
                QString fileName = fileModel->fileName(childIndex);
                if (fileName.contains(filterRegularExpression())) {
                    return true;
                }
            }
        }

        return false;
    }
};
