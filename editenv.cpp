////////////////////////////////////////////////////////////////////////////////
//
//  editenv - Environment Variable Editor C APIs
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

#include <limits>
#define NOMINMAX
#include <windows.h>
#undef NOMINMAX

#include "editenv.hpp"

using namespace editenv;

// Cuts all matching instances of "text" from the named variable's value.
unsigned int envCut (env_scope scope, char const *name, char const *text)
{
    EnvVar var(scope, name);

    return var.cut(text);
}

// Append's "text" to the named variable's value.
void envPaste (env_scope scope, char const *name, char const *text)
{
    EnvVar var(scope, name);

    var.paste(text);
}

// Sets (replaces) the named variable's value with "text". Creates the variable
// if it does not yet exist in the environment.
void envSet (env_scope scope, char const *name, char const *text)
{
    EnvVar var(scope, name);

    var.set(text);
}

// Deletes the named variable from the environment.
void envUnset (env_scope scope, char const *name)
{
    EnvVar var(scope, name);

    var.unset();
}

// Retrieves the named variable's current value.
char const * envValue (env_scope scope, char const *name)
{
    EnvVar var(scope, name);

    return var.value().c_str();
}

// Appends the specified path to the "Path" environment variable. Only appends
// it to the Path variable if it is not already in the Path.
void pathAdd (env_scope scope, char const *path)
{
    size_t const sizeMax = std::numeric_limits<size_t>::max();

    size_t      length = std::string(path).length();
    size_t      pos;
    std::string value;
    EnvVar      var(scope, "Path");

    value = var.value();
    pos = value.find(path, 0);
    while (sizeMax != pos) {
        if (((0 == pos) ||
             (';' == value[pos - 1])) &&
            ((pos + length == value.length()) ||
             (';' == value[pos + length]))) {
            // Found the path in the "Path" environment variable already.
            return;
        }
        pos = value.find(path, pos + 1);
    }

    if (0 == var.value().length()) {
        // Nothing is in the Path environment variable yet.
        var.set(path);
    } else {
        var.paste(std::string(";") + path);
    }
}

void pathAddImmediate (env_scope scope, char const *path)
{
	size_t const sizeMax = std::numeric_limits<size_t>::max();

	size_t      length = std::string(path).length();
	size_t      pos;

	char currPath[8096] = {0};
	GetEnvironmentVariableA("PATH", currPath, 8096);

	std::string value = currPath;
	pos = value.find(path, 0);
	while (sizeMax != pos) {
		if (((0 == pos) ||
			(';' == value[pos - 1])) &&
			((pos + length == value.length()) ||
			(';' == value[pos + length]))) {
				// Found the path in the "Path" environment variable already.
				return;
		}
		pos = value.find(path, pos + 1);
	}

	if (0 != value.length()) {
		// Nothing is in the Path environment variable yet.
		value.append(";");
	}
	value.append(path);

	// add to local process
	SetEnvironmentVariableA("PATH", value.c_str());
}

// Removes all matching instances of the specified path from the Path
// environment variable.
unsigned int pathRemove (env_scope scope, char const *path)
{
    size_t const sizeMax = std::numeric_limits<size_t>::max();

    unsigned int count = 0;
    size_t       length = std::string(path).length();
    size_t       pos;
    std::string  value;
    EnvVar       var(scope, "Path");

    value = var.value();
    pos = value.find(path);
    while (sizeMax != pos) {
        if (((0 == pos) ||
             (';' == value[pos - 1])) &&
            ((pos + length == value.length()) ||
             (';' == value[pos + length]))) {
            // Found a match in the path environment variable.
            ++count;
            if (0 == pos) {
                // This is the first directory in the path, so there is no
                // preceding semicolon to remove.
                if (length == value.length()) {
                    // There is no trailing semicolon, either because this is
                    // the only directory in the path.
                    value = "";
                } else {
                    // Instead of removing the preceding semicolon (which
                    // isn't there), remove the following semicolon so that the
                    // new path value doesn't begin with a semicolon.
                    value.replace(pos, length + 1, "");
                }
            } else {
                // Remove the preceding semicolon along with the path string.
                value.replace(pos - 1, length + 1, "");
            }
            pos = value.find(path, pos);
        } else {
            pos = value.find(path, pos + 1);
        }
    }

    // Set the new path environment variable.
    var.set(value);

    return count;
}