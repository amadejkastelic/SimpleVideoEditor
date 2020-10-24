#pragma once

#include <QSyntaxHighlighter>
#include <QRegularExpression>

class Highlighter : public QSyntaxHighlighter {

    Q_OBJECT

public:
    explicit Highlighter(QTextDocument *parent = nullptr);

protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightingRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> rules;

    QTextCharFormat keywordFormat;
    QTextCharFormat seperatorFormat;
    QTextCharFormat startArrayFormat;
    QTextCharFormat valueFormat;
};