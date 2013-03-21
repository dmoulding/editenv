////////////////////////////////////////////////////////////////////////////////
//
//  editenv - Environment Variable Editor Library Header File
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

#ifndef EDITENV_EDITENV_HPP
#define EDITENV_EDITENV_HPP

#ifdef EDITENV_BUILD
#define EDITENV_API __declspec(dllexport)
#else
#define EDITENV_API __declspec(dllimport)
#endif // EDITENV_BUILD

#include "editenvTypes.hpp"
#include "EnvVar.hpp"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// Removes all matching instances of the specified value from the named
// environment variable's value.
//
// scope [in]    Environment scope (user environment or system environment).
//
// name  [in]    Name of the variable to edit.
//
// value [in]    String to match against and cut from the variable.
//
// Return Value: Returns the number of matching instances within the variable's
//               value that were cut.
EDITENV_API unsigned int envCut (editenv::env_scope  scope,
                                 char const         *name,
                                 char const         *value);

// Appends the specified value to the name environment variable's value.
//
// scope [in]    Environment scope (user environment or system environment).
//
// name  [in]    Name of the variable to edit.
//
// value [in]    Value to paste to at the end of the variable's value.
//
// Return Value: Nothing.    
EDITENV_API void envPaste (editenv::env_scope  scope,
                           char const         *name,
                           char const         *value);

// Sets the named environment variable's value to the specified value. Creates
// the variable if it does not yet exist in the environment.
//
// scope [in]    Environment scope (user environment or system environment).
//
// name  [in]    Name of the variable to set.
//
// value [in]    Value to be assigned to the variable.
//
// Return Value: Nothing.
EDITENV_API void envSet (editenv::env_scope  scope,
                         char const         *name,
                         char const         *value);

// Deletes the named environment variable.
//
// scope [in]    Environment scope (user environment or system environment).
//
// name  [in]    Name of the variable to delete.
//
// Return Value: Nothing.
EDITENV_API void envUnset (editenv::env_scope scope, char const *name);

// Retrieves the value currently assigned to the named variable.
//
// scope [in]    Environment scope (user environment or system environment).
//
// name  [in]    Name of the variable whose value to retrieve.
//
// Return Value: Returns a const string containing the variable's value.
EDITENV_API char const * envValue (editenv::env_scope scope, char const *name);

// Appends the specified path to the Path environment variable. Only adds to
// the Path environment variable if the specified path is not already in the
// Path environment variable (i.e. calling this function will not add duplicate
// entries to the Path environment variable).
//
// scope [in]    Environment scope (user path or system path).
//
// path  [in]    Path to append to the Path environment variable.
//
// Return Value: Nothing.
EDITENV_API void pathAdd (editenv::env_scope, char const *path);

// Almost the same as pathAdd, but only adds to the local path variable for
// the calling process.
EDITENV_API void pathAddImmediate (editenv::env_scope, char const *path);

// Removes all matching instances of the specified path from the Path
// environment variable.
//
// scope [in]    Environment scope (user path or system path).
//
// path  [in]    Path to remove from the Path environment variable.
//
// Return value: Returns the number of matching instances that were removed.
EDITENV_API unsigned int pathRemove (editenv::env_scope, char const *path);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus


#endif // EDITENV_EDITENV_HPP