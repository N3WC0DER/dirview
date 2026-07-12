#pragma once

#include <QWidget>
#include <QtWidgets>
#include <QSizePolicy>
#include "../utils/Options.h"
#include "../utils/FilterProxyModel.hpp"

/**
 * @brief Main window
 * 
 */
class DirectoryViewerWidget : public QMainWindow
{
    Q_OBJECT

public:

    explicit DirectoryViewerWidget(const QCommandLineParser &parser, QWidget *parent = nullptr);

private:

    QLineEdit *filter;

    inline static const QSize BASE_SIZE = QSize(1000, 600);

    /** Задержка ввода для оптимизации */
    inline static const int filterDelay = 200;
    QTimer *filterDelayTimer;

    /** Корневая директория */
    inline static const QString homePath = QDir::homePath();
};