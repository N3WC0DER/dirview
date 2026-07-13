#include "DirectoryViewerWidget.h"

DirectoryViewerWidget::DirectoryViewerWidget(const Options &options, QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("dirview");

    // file models
    ModelFactory modelFactory(options);
    model = modelFactory.createFileSystemModel(rootPath, this);
    filterProxyModel = modelFactory.createFilterProxyModel(model, this);
    filterProxyModel->setProxyRootPath(model->rootPath());
    folderSizeProxyModel = modelFactory.createFolderSizeProxyModel(filterProxyModel, this);

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
    auto *filterController = new FilterController(filterProxyModel, filter, this);
    layout->addWidget(filter);

    configureTreeView();
    layout->addWidget(tree);
    layout->setStretchFactor(tree, 1);

    setCentralWidget(central);
    resize(BASE_SIZE);
}

void DirectoryViewerWidget::configureTreeView() {
    tree = new QTreeView(this);
    tree->setModel(folderSizeProxyModel);

    tree->setSortingEnabled(true);
    tree->header()->setSectionResizeMode(0, QHeaderView::Stretch);
    tree->header()->setSectionResizeMode(1, QHeaderView::Interactive);

    tree->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(tree, &QTreeView::customContextMenuRequested,
        this, &DirectoryViewerWidget::onDirContextMenuRequested);
}

void DirectoryViewerWidget::calculateFolderSize(const QString &folderPath) {
    QFuture<quint64> future = QtConcurrent::run(getDirSize, folderPath);
            
    auto *watcher = new QFutureWatcher<quint64>(this);
    connect(watcher, &QFutureWatcher<quint64>::finished, this, [this, watcher, folderPath]() {
        quint64 totalSize = watcher->result();
        
        folderSizeProxyModel->updateFolderSize(folderPath, totalSize);
        
        watcher->deleteLater();
    });
    watcher->setFuture(future);
}

void DirectoryViewerWidget::setHomeDirectory(const QString &loadedPath) {
    if (loadedPath == rootPath) {
        QModelIndex rootIndex = model->index(loadedPath);
        if (rootIndex.isValid()) {
            QModelIndex filterProxyIndex = filterProxyModel->mapFromSource(rootIndex);
            QModelIndex folderSizeProxyIndex = folderSizeProxyModel->mapFromSource(filterProxyIndex);
            tree->setRootIndex(folderSizeProxyIndex);
        }
    }
}

void DirectoryViewerWidget::onDirContextMenuRequested(const QPoint &point) {
    QModelIndex folderSizeProxyIndex = tree->indexAt(point);
    if (!folderSizeProxyIndex.isValid()) return;

    QModelIndex filterProxyIndex = folderSizeProxyModel->mapToSource(folderSizeProxyIndex);
    if (!filterProxyIndex.isValid()) return;

    QModelIndex index = filterProxyModel->mapToSource(filterProxyIndex);
    if(!index.isValid()) return;

    QString absolutePath = model->filePath(index);
    QFileInfo fileInfo(absolutePath);

    // Контекстное меню для директории
    if (fileInfo.isDir()) {
        QMenu contextMenu(this);
        QAction *calculateDirSize = contextMenu.addAction(tr("Вычислить размер папки"));

        QAction *selectedAction = contextMenu.exec(tree->viewport()->mapToGlobal(point));

        if (selectedAction == calculateDirSize) {
            calculateFolderSize(absolutePath);
        }
    }
}