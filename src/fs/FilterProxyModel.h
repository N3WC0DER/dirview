#pragma once

#include <QSortFilterProxyModel>
#include <QDir>
#include <QFileSystemModel>

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

    void setProxyRootPath(const QString &path);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

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
    bool checkFolderHasMatches(const QModelIndex &folderIndex, QFileSystemModel *fileModel, int currentDepth) const;
};
