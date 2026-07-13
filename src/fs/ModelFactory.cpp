#include "ModelFactory.h"

ModelFactory::ModelFactory(const Options options, QObject *parent) : options(options) {}

QFileSystemModel *ModelFactory::createFileSystemModel(const QString &rootPath, QObject *parent) {
    auto *model = new QFileSystemModel(parent);
    model->setRootPath(rootPath);

    // options
    if (options.dontUseCustomDirectoryIcons)
        model->setOption(QFileSystemModel::DontUseCustomDirectoryIcons);
    if (options.dontWatch)
        model->setOption(QFileSystemModel::DontWatchForChanges);
    
    // all entries
    model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden | QDir::AllDirs);

    return model;
}

FilterProxyModel *ModelFactory::createFilterProxyModel(QAbstractItemModel *model, QObject *parent) {
    auto *proxyModel = new FilterProxyModel(parent);
    proxyModel->setSourceModel(model);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    return proxyModel;
}

FolderSizeProxyModel *ModelFactory::createFolderSizeProxyModel(QAbstractItemModel *model, QObject *parent) {
    auto *proxyModel = new FolderSizeProxyModel(parent);
    proxyModel->setSourceModel(model);
    return proxyModel;
}