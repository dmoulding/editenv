////////////////////////////////////////////////////////////////////////////////
//
//  envtest - Environment Variable Editor Test Program
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

#include <editenv.hpp>

// This provides a skeleton program/project for testing the environment variable
// editor DLL (editenv.dll). Modify this main function to suit your testing
// needs.
int main (int argc, char *argv [])
{
    using namespace editenv;

    pathAdd(es_user, "%SystemRoot%\\Meh");

    pathAdd(es_system, "%SystemRoot%\\Foo");

    pathRemove(es_user, "%SystemRoot%\\Meh");

    pathRemove(es_system, "%SystemRoot%\\Foo");

    return 0;
}