////////////////////////////////////////////////////////////////////////////////
//
//  editenv - Environment Variable Editor C++ Class Implementation
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

#ifndef EDITENV_ENV_VAR
#define EDITENV_ENV_VAR

#include <string>

#include "editenvTypes.hpp"

// This class provides a convenient object interface to environment variables.
class editenv::EnvVar
{
public:
    // Constructs an environment variable object with the given name. Merely
    // constructing an object does not create a corresponding variable in the
    // specified environment. To actually create the environment variable
    // (assuming it does not already exist), use EnvVar::set.
    //
    // scope [in]    Environment scope (user or system environment).
    //
    // name [in]     The environment variable's name.
    EnvVar (env_scope scope, std::string const &name);

    // Copies an environment variable object.
    //
    // other [in]    Environment variable object to make a copy from.
    EnvVar (EnvVar const &other);

    // Destroys the environment variable object.
    ~EnvVar ();

    // Copies an environment variable object.
    //
    // other [in]    Environment variable object to make a copy from.
    //
    // Return Value: Reference to the copy.
    EnvVar & operator = (EnvVar const &other);

    // Removes all matching instance of the specified text from the environment
    // variable's value.
    //
    // text [in]    Text to cut from the variable's value.
    //
    // Return Value: Returns the number of matching instances that were cut.
    unsigned int cut (std::string const &text);

    // Appends the specified text to the variable's current value.
    //
    // text [in]    Text to append to the variable's value.
    //
    // Return Value: Nothing.
    void paste (std::string const &text);

    // Assigns the specified text as the variable's value. Creats the variable
    // if it does not yet exist in the environment.
    //
    // text [in]    Text to assign as the variable's value.
    //
    // Retuvn Value: Nothing.
    void set (std::string const &text);

    // Deletes the variable from the environment.
    //
    // Return Value: Nothing.
    void unset ();

    // Retrieves the variable's current value.
    //
    // Return Value: A copy of the variable's value. Modifying the returned
    //               string has no effect on the variable's value.
    std::string value () const;
    
private:
    // Private function that broadcasts a WM_SETTINGCHANGE message to notify
    // that the environment has been changed.
    //
    // Return Value: Nothing.
    void broadcastChange_ ();

    // Private function that copies the specified environment variable object's
    // data to the current object.
    //
    // other [in]    Reference to the environment variable object to copy.
    //
    // Return Value: Nothing.
    void copy_ (EnvVar const &other);

    // Private function that releases all resources used by the environment
    // variable object.
    //
    // Note: As of this writing, environment variable objects do not allocate
    //       any dynamic resources, so calling this function is effectively a
    //       no-op.
    //
    // Return Value: Nothing.
    void destroy_ ();

    // Private Data:
    std::string name_;  // The environment variable's name.
    env_scope   scope_; // Scope of the environment variable (user or system).
    std::string value_; // The environment variable's value.
};

#endif // EDITENV_ENV_VAR