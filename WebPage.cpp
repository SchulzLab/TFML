/*********************************************************************
*
*   MODULE NAME:
*       WebPage.cpp
*
* Copyright 2016 by Tzung-Chien Hsieh.
*
*********************************************************************/

#include "WebPage.hpp"

//---------------------------------------------------------------------------------
//! Constructor
//---------------------------------------------------------------------------------
WebPage::WebPage
    (
    QObject* parent
    )
    : QWebEnginePage( parent )
{

} // end of function WebPage::WebPage()

//---------------------------------------------------------------------------------
//! Handle navigation request
//---------------------------------------------------------------------------------
bool WebPage::acceptNavigationRequest
    (
    const QUrl &aUrl,
    QWebEnginePage::NavigationType aType,
    bool aIsMainFrame
    )
{
    if( aType == QWebEnginePage::NavigationTypeLinkClicked )
    {
        emit linkClicked( aUrl );
        return false;
    }
    return true;
} // end of function WebPage::acceptNavigationRequest()

