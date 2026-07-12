#include "DirectoryViewerWidget.h"

DirectoryViewerWidget::DirectoryViewerWidget(const QCommandLineParser &parser, QWidget *parent)
    : QMainWindow(parent)
{
    model.setRootPath("/");
    if (parser.isSet(Options::dontUseCustomDirectoryIcons))
        model.setOption(QFileSystemModel::DontUseCustomDirectoryIcons);
    if (parser.isSet(Options::dontWatch))
        model.setOption(QFileSystemModel::DontWatchForChanges);
    
    model.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden | QDir::AllDirs);
    
    tree.setModel(&model);

    tree.setAnimated(false);
    int identation = 20;
    tree.setIndentation(identation);
    tree.setSortingEnabled(true);
    tree.setColumnWidth(0, tree.width() / 3);

    // Home directory
    const QModelIndex rootIndex = model.index(QDir::cleanPath(QDir::homePath()));
    if (rootIndex.isValid())
        tree.setRootIndex(rootIndex);

    auto *central = new QWidget(this);
    central->setObjectName("centralwidget");

    auto *layout = new QVBoxLayout(central);
    layout->addWidget(&tree);
    layout->setStretchFactor(&tree, 1);

    setCentralWidget(central);
}