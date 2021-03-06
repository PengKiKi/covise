/* This file is part of COVISE.

   You can use it under the terms of the GNU Lesser General Public License
   version 2.1 or later, see lgpl-2.1.txt.

 * License: LGPL 2+ */

#include <cover/coVRPluginSupport.h>
#include <cover/VRSceneGraph.h>
#include <cover/input/VRKeys.h>
#include "BoxSelection.h"
#include "BoxSelectionInteractor.h"

#include <util/common.h>

#include <OpenVRUI/coSubMenuItem.h>
#include <OpenVRUI/coRowMenu.h>
#include <OpenVRUI/coCheckboxMenuItem.h>
#include <OpenVRUI/coLabelMenuItem.h>

using namespace vrui;
using namespace opencover;

float BoxSelection::s_xmin = 0.;
float BoxSelection::s_ymin = 0.;
float BoxSelection::s_zmin = 0.;
float BoxSelection::s_xmax = 0.;
float BoxSelection::s_ymax = 0.;
float BoxSelection::s_zmax = 0.;
BoxSelectionInteractor *BoxSelection::s_boxSelectionInteractor = NULL;
void (*BoxSelection::s_interactionFinished)() = NULL;

BoxSelection::BoxSelection(coRowMenu *parentMenu, const char *name, const char *title)
    : coMenuItem(name)
{
    // m_title = strcpy ( new char[ strlen(title)+1 ] , title );
    m_parentListener = NULL;

    m_selectionSubMenu = new coRowMenu(title, parentMenu);
    createSubMenu();

    m_infoSubMenuItem = new coSubMenuItem(name);
    m_infoSubMenuItem->setMenu(m_selectionSubMenu);

    s_boxSelectionInteractor = new BoxSelectionInteractor(
        coInteraction::ButtonA, "BoxSelection", coInteraction::High);
    s_boxSelectionInteractor->registerInteractionFinishedCallback(interactionFinished);
    s_boxSelectionInteractor->registerInteractionRunningCallback(interactionRunning);

    m_useBoxSelection = new coCheckboxMenuItem(title, false, groupPointerArray[0]);
    m_useBoxSelection->setMenuListener(this);
}

BoxSelection::~BoxSelection()
{
    delete m_selectionSubMenu;
    delete m_infoSubMenuItem;
    delete s_boxSelectionInteractor;
    deleteSubMenu();
}

void
BoxSelection::setMenuListener(coMenuListener *parentListener)
{
    m_parentListener = parentListener;
}

coMenuListener *BoxSelection::getMenuListener() const
{
    return m_parentListener;
}

void BoxSelection::createSubMenu()
{

    m_xminItem = new coLabelMenuItem("xmin: ");
    m_yminItem = new coLabelMenuItem("ymin: ");
    m_zminItem = new coLabelMenuItem("zmin: ");
    m_xmaxItem = new coLabelMenuItem("xmax: ");
    m_ymaxItem = new coLabelMenuItem("ymax: ");
    m_zmaxItem = new coLabelMenuItem("zmax: ");

    m_selectionSubMenu->add(m_xminItem);
    m_selectionSubMenu->add(m_yminItem);
    m_selectionSubMenu->add(m_zminItem);
    m_selectionSubMenu->add(m_xmaxItem);
    m_selectionSubMenu->add(m_ymaxItem);
    m_selectionSubMenu->add(m_zmaxItem);
}

void BoxSelection::deleteSubMenu()
{
    delete m_useBoxSelection;
    delete m_xminItem;
    delete m_yminItem;
    delete m_zminItem;
    delete m_xmaxItem;
    delete m_ymaxItem;
    delete m_zmaxItem;
}

void BoxSelection::interactionRunning()
{
    s_boxSelectionInteractor->getBox(s_xmin, s_ymin, s_zmin, s_xmax, s_ymax, s_zmax);
}

#if 0 //currently not used
void
BoxSelection::update(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax)
{
   m_xminItem->setLabel(std::string("xmin: ") + stringify(xmin));
   m_yminItem->setLabel(std::string("ymin: ") + stringify(ymin));
   m_zminItem->setLabel(std::string("zmin: ") + stringify(zmin));
   m_xmaxItem->setLabel(std::string("xmax: ") + stringify(xmax));
   m_ymaxItem->setLabel(std::string("ymax: ") + stringify(ymax));
   m_zmaxItem->setLabel(std::string("zmax: ") + stringify(zmax));
}

#endif

inline std::string
BoxSelection::stringify(float x)
{
    std::ostringstream o;
    if (o << x)
        return o.str();
    else
        return "";
}

bool BoxSelection::getCheckboxState() const
{
    if (m_useBoxSelection)
        return m_useBoxSelection->getState();
    else
        return false;
}

coCheckboxMenuItem *BoxSelection::getCheckbox() const
{
    return m_useBoxSelection;
}

coSubMenuItem *BoxSelection::getSubMenu() const
{
    return m_infoSubMenuItem;
}

void BoxSelection::interactionFinished()
{
    interactionRunning();
    if (s_interactionFinished)
        s_interactionFinished();
}

void BoxSelection::getBox(float &xmin, float &ymin, float &zmin, float &xmax, float &ymax, float &zmax)
{
    xmin = s_xmin;
    ymin = s_ymin;
    zmin = s_zmin;
    xmax = s_xmax;
    ymax = s_ymax;
    zmax = s_zmax;
}

void BoxSelection::registerInteractionFinishedCallback(void (*interactionFinished)())
{
    s_interactionFinished = interactionFinished;
}

void BoxSelection::unregisterInteractionFinishedCallback()
{
    s_interactionFinished = NULL;
}

void BoxSelection::menuEvent(coMenuItem *menuItem)
{
    if (menuItem == m_useBoxSelection)
    {
        if (m_parentListener)
            m_parentListener->menuEvent(this);

        if (m_useBoxSelection->getState())
        {
            // enable interaction
            printf("register boxSelectionInteractor\n");
            VRSceneGraph::instance()->setPointerType(HAND_SPHERE);
            coInteractionManager::the()->registerInteraction(s_boxSelectionInteractor);
        }
        else
        {
            printf("unregister boxSelectionInteractor\n");
            coInteractionManager::the()->unregisterInteraction(s_boxSelectionInteractor);
        }
    }
}
