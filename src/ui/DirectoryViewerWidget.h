#pragma once

#include <QWidget>
#include <QtWidgets>
#include <QSizePolicy>
#include <QFuture>
#include <QtConcurrent/qtconcurrentrun.h>
#include "../utils/Options.hpp"
#include "../utils/CalculateSize.hpp"
#include "../fs/FilterProxyModel.h"
#include "../fs/FolderSizeProxyModel.h"
#include "../fs/FilterController.h"
#include "../fs/ModelFactory.h"

/**
 * @brief Главное окно просмотра файловой системы с фильтрацией по имени.
 * 
 * Содержит QTreeView с QFileSystemModel и прокси-моделью FilterProxyModel.
 * Корневая директория по умолчанию — домашняя папка пользователя.
 */
class DirectoryViewerWidget : public QMainWindow
{
    Q_OBJECT

public:

    /**
     * @param options Опции командной строки (влияют на поведение модели).
     * @param parent Родительский виджет (передаётся в QMainWindow).
     */
    explicit DirectoryViewerWidget(const Options &options, QWidget *parent = nullptr);

private:

    QLineEdit *filter;
    QFileSystemModel *model;
    FolderSizeProxyModel *folderSizeProxyModel;
    FilterProxyModel *filterProxyModel;
    QTreeView *tree;

    inline static const QSize BASE_SIZE = QSize(1000, 600);

    inline static const QString rootPath = QDir::homePath();

    void configureTreeView();

    /**
     * @brief Запускает асинхронную функцию расчета общего размера файлов в указанной директории.
     * Передает результат в прокси модель folderSizeProxyModel.
     * @param folderPath Путь к папке.
     */
    void calculateFolderSize(const QString &folderPath);

private slots:

    /**
     * @brief Устанавливает корневую директорию в модели, если она совпадает с домашней.
     * Используется после загрузки директорий в модели.
     * @param loadedPath Путь к директории.
     */
    void setHomeDirectory(const QString &loadedPath);

    /**
     * @brief Вызывает контекстное меню при нажатии ПКМ на папку.
     * Есть возможность рассчитать размер папки.
     * 
     * @param point 
     */
    void onDirContextMenuRequested(const QPoint &point);
};