#pragma once

#include <QObject>
#include <QFileSystemModel>
#include "FilterProxyModel.h"
#include "FolderSizeProxyModel.h"
#include "../utils/Options.hpp"

/**
 * @brief Фабрика для создания моделей файловой системы и прокси-фильтрации.
 * 
 * Инкапсулирует настройки (Options) и предоставляет методы для создания
 * QFileSystemModel и FilterProxyModel с учётом переданных опций.
 */
class ModelFactory
{

public:
    /**
     * @brief Конструктор, сохраняет опции для дальнейшего использования.
     * @param options Опции командной строки (например, отключают отслеживание изменений).
     * @param parent Родительский объект (передаётся в QObject).
     */
    explicit ModelFactory(const Options options, QObject *parent = nullptr);

    /**
     * @brief Создаёт экземпляр QFileSystemModel с указанной корневой папкой.
     * @param rootPath Путь к корневой директории.
     * @param parent Родительский объект.
     * @return Указатель на созданную модель (владелец - parent).
     */
    QFileSystemModel* createFileSystemModel(const QString &rootPath, QObject *parent);

    /**
     * @brief Создаёт прокси-модель фильтрации на основе модели файловой системы.
     * @param model Модель-источник.
     * @param parent Родительский объект.
     * @return Указатель на FilterProxyModel (владелец - parent).
     */
    FilterProxyModel* createFilterProxyModel(QAbstractItemModel *model, QObject *parent);

    /**
     * @brief Создаёт прокси-модель для отображения размеров папок.
     * @param model Исходная модель (обычно QFileSystemModel или её прокси).
     * @param parent Родительский объект для прокси-модели.
     * @return Указатель на созданный FolderSizeProxyModel (владелец — parent).
     */
    FolderSizeProxyModel* createFolderSizeProxyModel(QAbstractItemModel *model, QObject *parent);

private:

    Options options;
};