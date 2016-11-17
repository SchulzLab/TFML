/*********************************************************************
*
*   MODULE NAME:
*       WebPage.hpp
*
* Copyright 2016 by Tzung-Chien Hsieh.
*
*********************************************************************/
#ifndef WEBPAGE_HPP
#define WEBPAGE_HPP

#include "QWebEnginePage"

class WebPage : public QWebEnginePage
{
    Q_OBJECT

public:
    WebPage
        (
        QObject* parent = 0
        );

    bool acceptNavigationRequest
        (
        const QUrl &url,
        QWebEnginePage::NavigationType type,
        bool aIsMainFrame
        );

signals:
    void linkClicked(const QUrl&);
};
#endif // WEBPAGE_HPP
