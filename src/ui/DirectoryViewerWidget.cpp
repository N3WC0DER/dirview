#include "DirectoryViewerWidget.h"

DirectoryViewerWidget::DirectoryViewerWidget(const QCommandLineParser &parser, QWidget *parent)
    : QMainWindow(parent)
{
    model.setRootPath("");
    if (parser.isSet(Options::dontUseCustomDirectoryIcons))
        model.setOption(QFileSystemModel::DontUseCustomDirectoryIcons);
    if (parser.isSet(Options::dontWatch))
        model.setOption(QFileSystemModel::DontWatchForChanges);
    
    tree.setModel(&model);

    // Demonstrating look and feel features
    tree.setAnimated(false);
    tree.setIndentation(20);
    tree.setSortingEnabled(true);
    tree.setColumnWidth(0, tree.width() / 3);

    // Make it flickable on touchscreens
    QScroller::grabGesture(&tree, QScroller::TouchGesture);

    auto *central = new QWidget(this);
    central->setObjectName("centralwidget");

    auto *layout = new QVBoxLayout(central);
    layout->addWidget(&tree);
    layout->setStretchFactor(&tree, 1);

    setCentralWidget(central);
    // QFileSystemModel::setNameFilters()
}