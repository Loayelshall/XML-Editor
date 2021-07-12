#include "syntaxhighlighter.h"

syntaxHighlighter::syntaxHighlighter(QTextEdit * parent) : QSyntaxHighlighter(parent)
{
    setRegexes();
    setFormats();
}


void syntaxHighlighter::highlightBlock(const QString &text){
    int xmlElementIndex = m_xmlElementRegex.indexIn(text);
    while(xmlElementIndex >= 0)
       {
           int matchedPos = m_xmlElementRegex.pos(1);
           int matchedLength = m_xmlElementRegex.cap(1).length();
           setFormat(matchedPos, matchedLength, m_xmlElementFormat);

           xmlElementIndex = m_xmlElementRegex.indexIn(text, matchedPos + matchedLength);
       }
       typedef QList<QRegExp>::const_iterator Iter;
       Iter xmlKeywordRegexesEnd = m_xmlKeywordRegexes.end();
       for(Iter it = m_xmlKeywordRegexes.begin(); it != xmlKeywordRegexesEnd; ++it) {
           const QRegExp & regex = *it;
           highlightByRegex(m_xmlKeywordFormat, regex, text);
       }

       highlightByRegex(m_xmlAttributeFormat, m_xmlAttributeRegex, text);
       highlightByRegex(m_xmlCommentFormat, m_xmlCommentRegex, text);
       highlightByRegex(m_xmlValueFormat, m_xmlValueRegex, text);
       highlightByRegex(m_xmlErrorFormat, m_xmlErrorRegex, text);
}


void syntaxHighlighter::highlightByRegex(const QTextCharFormat & format, const QRegExp & regex, const QString & text){
    int index = regex.indexIn(text);

       while(index >= 0)
       {
           int matchedLength = regex.matchedLength();
           setFormat(index, matchedLength, format);

           index = regex.indexIn(text, index + matchedLength);
       }
}

void syntaxHighlighter::setRegexes(){
    m_xmlElementRegex.setPattern("<[?\\s]*[/]?[\\s]*([^\\n][^>]*)(?=[\\s/>])");
    m_xmlAttributeRegex.setPattern("\\w+(?=\\=)");
    m_xmlValueRegex.setPattern("\"[^\\n\"]+\"(?=[?\\s/>])");
    m_xmlCommentRegex.setPattern("<!--[^\\n]*-->");
    m_xmlErrorRegex.setPattern("!Error <--[^\\n]*-->");
    m_xmlKeywordRegexes = QList<QRegExp>() << QRegExp("<\\?") << QRegExp("/>")
                                              << QRegExp(">") << QRegExp("<") << QRegExp("</")
                                              << QRegExp("\\?>");
}

void syntaxHighlighter::setFormats(){
    m_xmlKeywordFormat.setForeground(Qt::blue);
    m_xmlKeywordFormat.setFontWeight(QFont::Bold);

    m_xmlElementFormat.setForeground(Qt::darkMagenta);
    m_xmlElementFormat.setFontWeight(QFont::Bold);

    m_xmlAttributeFormat.setForeground(Qt::darkGreen);
    m_xmlAttributeFormat.setFontWeight(QFont::Bold);
    m_xmlAttributeFormat.setFontItalic(true);

    m_xmlValueFormat.setForeground(Qt::darkRed);

    m_xmlCommentFormat.setForeground(Qt::gray);

    m_xmlErrorFormat.setFontUnderline(true);
    m_xmlErrorFormat.setForeground(Qt::red);
}
