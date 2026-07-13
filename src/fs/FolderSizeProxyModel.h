#pragma once

#include <QFileSystemModel>
#include <QIdentityProxyModel>
#include <QHash>
#include <QDebug>
#include "FilterProxyModel.h"

/**
 * @brief Прокси-модель для отображения размера папок.
 * 
 * Кэширует вычисленные размеры папок и подставляет их в данные модели
 * для роли Qt::DisplayRole. Размеры форматируются в удобочитаемый вид.
 */
class FolderSizeProxyModel : public QIdentityProxyModel {
    Q_OBJECT
public:

    explicit FolderSizeProxyModel(QObject *parent = nullptr);

    /**
     * @brief Обновляет кэш размера для указанной папки и отправляет сигнал для обновления колонки.
     * @param path Путь к папке.
     * @param size Размер в байтах.
     */
    void updateFolderSize(const QString &path, quint64 size);

    /**
     * @brief Переопределённый метод доступа к данным.
     * 
     * Если роль Qt::DisplayRole и индекс соответствует колонке с размером,
     * возвращает отформатированную строку размера из кэша.
     * В остальных случаях делегирует родительской модели.
     */
    QVariant data(const QModelIndex &proxyIndex, int role = Qt::DisplayRole) const override;

private:

    /** Кэш размеров папок (путь -> размер в байтах). */
    QHash<QString, quint64> sizesCache;

    /**
     * @brief Преобразует размер в байтах в читаемую строку (например, "1.2 МБ").
     * @param bytes Размер в байтах.
     * @return Отформатированная строка.
     */
    static QString formatSize(quint64 bytes);
};