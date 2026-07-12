#pragma once

#include <QWidget>
#include <QtWidgets>
#include <QSizePolicy>
#include "../utils/Options.hpp"
#include "../fs/FilterProxyModel.h"
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
    FilterProxyModel *proxyModel;
    QTreeView *tree;

    inline static const QSize BASE_SIZE = QSize(1000, 600);

    inline static const QString rootPath = QDir::homePath();

    void configureTreeView();

private slots:

    /**
     * @brief Устанавливает корневую директорию в модели, если она совпадает с домашней.
     * Используется после загрузки директорий в модели.
     * @param loadedPath Путь к директории.
     */
    void setHomeDirectory(const QString &loadedPath);
};