#pragma once

#include <QDirIterator>

/**
 * @brief Получает общий размер файлов в указанной директории.
 * Рекомендуется выполнять асинхронно.
 * 
 * @param dirPath Путь до папки.
 * @return quint64 Размер папки.
 */
inline quint64 getDirSize(const QString &dirPath) {
    quint64 size = 0;
    QDirIterator it(dirPath, QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        it.next();
        size += it.fileInfo().size();
    }
    return size;
}