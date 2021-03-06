#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent) : QSyntaxHighlighter(parent) {
    HighlightingRule rule;

    keywordFormat.setForeground(QBrush(QColor(255, 203, 107)));
    keywordFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression(QStringLiteral("^.*?(?=:)"));
    rule.format = keywordFormat;
    rules.append(rule);

    separatorFormat.setForeground(QBrush(QColor(137, 221, 255)));
    separatorFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression(QStringLiteral("[:]"));
    rule.format = separatorFormat;
    rules.append(rule);

    valueFormat.setForeground(QBrush(QColor(238, 255, 255)));
    rule.pattern = QRegularExpression(QStringLiteral("[^:]*$"));
    rule.format = valueFormat;
    rules.append(rule);

    startArrayFormat.setForeground(QBrush(QColor(137, 221, 255)));
    startArrayFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression(QStringLiteral("[-]"));
    rule.format = startArrayFormat;
    rules.append(rule);

    variableFormat.setForeground(QBrush(QColor(130, 170, 255)));
    variableFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression(QStringLiteral("[$][a-zA-Z-_]+"));
    rule.format = variableFormat;
    rules.append(rule);

    commentFormat.setForeground(QBrush(QColor(128, 128, 128)));
    rule.pattern = QRegularExpression(QStringLiteral("#(.*)"));
    rule.format = commentFormat;
    rules.append(rule);
}

void Highlighter::highlightBlock(const QString &text) {
    for (const HighlightingRule &rule: qAsConst(rules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}
