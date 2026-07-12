#pragma once

#include <QObject>
#include <QTimer>
#include <qlineedit.h>
#include "FilterProxyModel.h"

/**
 * @brief Контроллер фильтрации: применяет ввод из QLineEdit к прокси-модели с задержкой 300 мс.
 * 
 * Подключает сигнал textChanged к отложенному применению фильтра для снижения нагрузки.
 */
class FilterController : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief Конструктор, запоминает прокси-модель и поле ввода.
     * @param proxyModel Прокси-модель, к которой применяется фильтр.
     * @param filterEdit Поле ввода, откуда берётся текст фильтра.
     * @param parent Родительский объект (передаётся в QObject).
     */
    explicit FilterController(FilterProxyModel *proxyModel, QLineEdit *filterEdit, QObject *parent = nullptr);
    
public slots:

    /**
     * @brief Слот для сигнала textChanged, запускает таймер задержки.
     * @param text Новый текст из поля ввода.
     */
    void onFilterTextChanged(const QString &text);

private slots:

    /**
     * @brief Применяет фильтр к прокси-модели по истечении таймера.
     * @param text Текст для фильтрации (передаётся из таймера).
     */
    void applyFilters(const QString &text);

private:

    FilterProxyModel *proxyModel;
    QLineEdit *filterEdit;
    QTimer *delayTimer;
    static const int delayMs = 300;
};