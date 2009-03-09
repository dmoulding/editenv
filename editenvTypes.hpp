////////////////////////////////////////////////////////////////////////////////
//
//  editenv - Environment Variable Editor Types
//  Copyright (c) 2009 Dan Moulding
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
//  See COPYING.txt for the full terms of the GNU Lesser General Public License.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef EDITENV_EDITENV_TYPES_HPP
#define EDITENV_EDITENV_TYPES_HPP

#ifdef EDITENV_BUILD
#define EDITENV_API __declspec(dllexport)
#else
#define EDITENV_API __declspec(dllimport)
#endif // EDITENV_BUILD

namespace editenv {
    // Possible environment variable scopes:
    enum env_scope {
        es_invalid, // Unspecified (do not use this value)
        es_system,  // System environment variables
        es_user     // Current user's environment variables
    };

    class EDITENV_API EnvVar;
}

#endif // EDITENV_EDITENV_TYPES_HPP