#include "FilterController.h"

FilterController::FilterController(FilterProxyModel *proxyModel, QLineEdit *filterEdit, QObject *parent)
    : proxyModel(proxyModel), filterEdit(filterEdit), QObject(parent) {
    delayTimer = new QTimer(this);
    delayTimer->setSingleShot(true);
    delayTimer->setInterval(delayMs);

    connect(filterEdit, &QLineEdit::textChanged, this, &FilterController::onFilterTextChanged);
}

void FilterController::onFilterTextChanged(const QString &text) {
    if (text.isEmpty()) {
        proxyModel->setFilterRegularExpression(QRegularExpression());
        delayTimer->stop();
        return;
    }
    delayTimer->stop();
    delayTimer->callOnTimeout([this, text] { applyFilters(text); });
    delayTimer->start();
}

void FilterController::applyFilters(const QString &text) {
    proxyModel->setFilterRegularExpression(QRegularExpression::escape(text));
}