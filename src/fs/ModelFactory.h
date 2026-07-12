#pragma once

#include <QObject>
#include <QFileSystemModel>
#include "FilterProxyModel.h"
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
     * @param model Модель-источник (QFileSystemModel).
     * @param parent Родительский объект.
     * @return Указатель на FilterProxyModel (владелец - parent).
     */
    FilterProxyModel* createFilterProxyModel(QFileSystemModel *model, QObject *parent);

private:

    Options options;
};