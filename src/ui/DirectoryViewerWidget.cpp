#include "DirectoryViewerWidget.h"

DirectoryViewerWidget::DirectoryViewerWidget(const QCommandLineParser &parser, QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("dirview");

    filterDelayTimer = new QTimer(this);
    filterDelayTimer->setSingleShot(true);
    filterDelayTimer->setInterval(filterDelay);

    auto *model = new QFileSystemModel(this);
    model->setRootPath(homePath);
    if (parser.isSet(Options::dontUseCustomDirectoryIcons))
        model->setOption(QFileSystemModel::DontUseCustomDirectoryIcons);
    if (parser.isSet(Options::dontWatch))
        model->setOption(QFileSystemModel::DontWatchForChanges);
    
    model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden | QDir::AllDirs);

    auto *proxyModel = new FilterProxyModel(this);
    proxyModel->setSourceModel(model);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    
    auto *tree = new QTreeView(this);
    tree->setModel(proxyModel);

    tree->setSortingEnabled(true);
    tree->setColumnWidth(0, BASE_SIZE.width() / 3);

    // Home directory
    proxyModel->setProxyRootPath(homePath);
    connect(model, &QFileSystemModel::directoryLoaded, this, [=](const QString &loadedPath) {
        if (loadedPath == homePath) {
            QModelIndex rootIndex = model->index(loadedPath);
            
            if (rootIndex.isValid()) {
                QModelIndex proxyIndex = proxyModel->mapFromSource(rootIndex);
                tree->setRootIndex(proxyIndex);
            }
        }
    }, Qt::UniqueConnection);

    auto *central = new QWidget(this);
    central->setObjectName("centralwidget");

    auto *layout = new QVBoxLayout(central);

    // Filter line
    filter = new QLineEdit(this);
    filter->setPlaceholderText(tr("Фильтр"));
    connect(filter, &QLineEdit::textChanged, proxyModel, [this, proxyModel](const QString &text) {
        if (text.isEmpty()) {
            proxyModel->setFilterRegularExpression(QRegularExpression());
            filterDelayTimer->stop();
            return;
        }
        filterDelayTimer->stop();
        filterDelayTimer->callOnTimeout([proxyModel, text] () {
            proxyModel->setFilterRegularExpression(QRegularExpression::escape(text));
        });
        filterDelayTimer->start();
    });
    connect(model, &QFileSystemModel::directoryLoaded, proxyModel, &FilterProxyModel::invalidate, Qt::UniqueConnection);
    layout->addWidget(filter);

    layout->addWidget(tree);
    layout->setStretchFactor(tree, 1);

    setCentralWidget(central);
    resize(BASE_SIZE);
}