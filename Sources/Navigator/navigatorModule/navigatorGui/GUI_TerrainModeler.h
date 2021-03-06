/*
This source file is part of Solipsis
(Solipsis is an opensource decentralized Metaverse platform)
For the latest info, see http://www.solipsis.org/

Copyright (C) 2006-2008 ANR-RIAM (IRISA, Archivideo, Artefacto, Rennes 2 University, Orange Labs)
Author JAN Gregory

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef __GUI_TerrainModeler_h__
#define __GUI_TerrainModeler_h__

#include "NavigatorGui.h"
#include "MainApplication/Navigator.h"
#include "GUI_Panel.h"

using namespace NaviLibrary;

namespace Solipsis 
{
    class Navigator;

    class GUI_TerrainModeler : public GUI_Panel
    {
    public:
        // switch between show and hide
        static void showPanel();
        static void unloadPanel();
        static void addText(const std::wstring& txt);
        virtual bool show();

        // Modeler Scene From Text Setup properties page callbacks
        void onPageLoaded(Navi* caller, const Awesomium::JSArguments& args);
        void onExec(Navi* caller, const Awesomium::JSArguments& args);	
        void onCancelled(Navi* caller, const Awesomium::JSArguments& args);

    protected:
        GUI_TerrainModeler();
		~GUI_TerrainModeler();
        static GUI_TerrainModeler * stGUI_TerrainModeler;
    };
} // namespace Solipsis

#endif // #ifndef __GUI_TerrainModeler_h__