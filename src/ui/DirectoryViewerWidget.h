#pragma once

#include <QWidget>
#include <QtWidgets>
#include <QSizePolicy>
#include "../utils/Options.h"

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

    QFileSystemModel model;
    QTreeView tree;
};