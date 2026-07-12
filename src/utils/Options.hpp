#pragma once

#include <QCommandLineParser>

/**
 * @brief Опции командной строки для QFileSystemModel
 * Поддерживаются ключи:
 *   - `-c` -> отключает использование пользовательских значков папок
 *   - `-w` -> отключает отслеживание изменений (watch mode)
 */
struct Options {
    bool dontUseCustomDirectoryIcons = false;
    bool dontWatch = false;
};

/**
 * @brief Создаёт и настраивает парсер командной строки с опциями -c и -w.
 * @param app Ссылка на приложение, необходимая для обработки аргументов.
 * @return std::unique_ptr<QCommandLineParser> Умный указатель с
 * проинициализированным и обработавшим аргументы парсером.
 */
inline std::unique_ptr<QCommandLineParser> initParser(QCoreApplication &app) {
    auto parser = std::make_unique<QCommandLineParser>();
    parser->setApplicationDescription("Qt Dir View");
    parser->addHelpOption();
    parser->addVersionOption();
    QCommandLineOption dontUseCustomDirectoryIconsOption("c", "Set QFileSystemModel::DontUseCustomDirectoryIcons");
    parser->addOption(dontUseCustomDirectoryIconsOption);
    QCommandLineOption dontWatchOption("w", "Set QFileSystemModel::DontWatch");
    parser->addOption(dontWatchOption);
    parser->process(app);
    return parser;
}

/**
 * @brief Преобразует данные командной строки в структуру Options.
 * @param parser Инициализированный парсер (уже разобранные аргументы).
 * @return Опции с флагами, соответствующими ключам -c и -w.
 */
inline Options parseOptions(const QCommandLineParser *parser) {
    Options opt;
    opt.dontUseCustomDirectoryIcons = parser->isSet("c");
    opt.dontWatch = parser->isSet("w");
    return opt;
}