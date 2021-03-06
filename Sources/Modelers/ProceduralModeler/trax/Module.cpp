/*
This source file is part of Solipsis
    (Solipsis is an opensource decentralized Metaverse platform)
For the latest info, see http://www.solipsis.org/

Copyright (C) 2006-2008 ANR-RIAM (IRISA, Archivideo, Artefacto, Rennes 2 University, Orange Labs)
Author HUIBAN Vincent

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

#include "Module.h"

std::map< pm_trax::Module::ModuleMeaning, pm_trax::Symbol > pm_trax::Module::m_moduleSymbol;

void pm_trax::Module::init()
{
	// definition constants
	m_moduleSymbol[pm_trax::Module::CONTEXT] = 'C'; // asks geometry attributes to context features
	m_moduleSymbol[pm_trax::Module::NEW_SEGMENT] = 'S'; // creates a new segment module
	m_moduleSymbol[pm_trax::Module::NEW_BRANCH] = 'B'; // creates a new branch module
	m_moduleSymbol[pm_trax::Module::FORWARD] = 'F'; // terminal module, adds a line segment to current geometry
	m_moduleSymbol[pm_trax::Module::BEGIN_BRANCH] = '['; // terminal module, creates a branch 
	m_moduleSymbol[pm_trax::Module::END_BRANCH] = ']'; // terminal module, closes a branch
	m_moduleSymbol[pm_trax::Module::ROTATE] = '+'; // terminal, rotates current geometry
	m_moduleSymbol[pm_trax::Module::DEFAULT] = 'D'; // terminal empty char
}
