#include "DirectoryViewerWidget.h"

DirectoryViewerWidget::DirectoryViewerWidget(const Options &options, QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("dirview");

    // file models
    ModelFactory modelFactory(options);
    model = modelFactory.createFileSystemModel(rootPath, this);
    proxyModel = modelFactory.createFilterProxyModel(model, this);

    // Set home directory after loading
    connect(model, &QFileSystemModel::directoryLoaded,
        this, &DirectoryViewerWidget::setHomeDirectory,
        Qt::UniqueConnection);    

    // UI
    auto *central = new QWidget(this);
    central->setObjectName("centralwidget");

    auto *layout = new QVBoxLayout(central);

    // Filter line
    filter = new QLineEdit(this);
    filter->setPlaceholderText(tr("Фильтр"));
    auto *filterController = new FilterController(proxyModel, filter, this);
    layout->addWidget(filter);

    configureTreeView();
    layout->addWidget(tree);
    layout->setStretchFactor(tree, 1);

    setCentralWidget(central);
    resize(BASE_SIZE);
}

void DirectoryViewerWidget::configureTreeView() {
    tree = new QTreeView(this);
    tree->setModel(proxyModel);

    tree->setSortingEnabled(true);
    tree->header()->setSectionResizeMode(0, QHeaderView::Stretch);
    tree->header()->setSectionResizeMode(1, QHeaderView::Interactive);
}

void DirectoryViewerWidget::setHomeDirectory(const QString &loadedPath) {
    if (loadedPath == rootPath) {
        QModelIndex rootIndex = model->index(loadedPath);
        if (rootIndex.isValid()) {
            tree->setRootIndex(proxyModel->mapFromSource(rootIndex));
        }
    }
}