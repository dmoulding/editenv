#include <cassert>
#include <limits>
#include <windows.h>

#undef max // unbelievable

#include "EnvVar.hpp"

using namespace editenv;

// Global Constants
static UINT const  broadcastTimeout = 100; // in milliseconds
static char const *userEnvSubKey    = "Environment";
static char const *systemEnvSubKey  = "System\\CurrentControlSet\\Control\\"
                                      "Session Manager\\Environment";

EnvVar::EnvVar (env_scope scope, std::string const &name)
    : name_(name),
      scope_(es_invalid)
{
    PBYTE       data;
    HKEY        key;
    DWORD       size;
    LONG        status;
    HKEY        subKey;
    char const *subKeyName;

    switch (scope) {
    case es_system:
        key = HKEY_LOCAL_MACHINE;
        subKeyName = systemEnvSubKey;
        break;

    case es_user:
        key = HKEY_CURRENT_USER;
        subKeyName = userEnvSubKey;
        break;

    default:
        assert(false);
        return;
    }
    scope_ = scope;

    RegOpenKeyEx(key, subKeyName, 0, KEY_QUERY_VALUE | KEY_SET_VALUE, &subKey);
    status = RegQueryValueEx(subKey, name_.c_str(), 0, NULL, NULL, &size);
    if (ERROR_SUCCESS != status) {
        // This environment variable doesn't exist. Assign this EnvVar object's
        // value the empty string.
        value_ = "";
    } else {
        // This environment variable already exists. Assign its value to this
        // EnvVar object.
        data = new BYTE [size];
        RegQueryValueEx(subKey, name_.c_str(), 0, NULL, data, &size);
        value_ = reinterpret_cast<char const *>(data);
        delete [] data;
    }
    RegCloseKey(key);
}

EnvVar::EnvVar (EnvVar const &other)
{
    copy_(other);
}

EnvVar::~EnvVar ()
{
    destroy_();
}

EnvVar & EnvVar::operator = (EnvVar const &other)
{
    if (this != &other) {
        destroy_();
        copy_(other);
    }

    return *this;
}

unsigned int EnvVar::cut (std::string const &text)
{
    size_t const sizeMax = std::numeric_limits<size_t>::max();

    unsigned int  count = 0;
    HKEY          key;
    size_t        length;
    size_t        pos;
    HKEY          subKey;
    char const   *subKeyName;

    if (es_invalid == scope_) {
        return 0;
    }

    switch (scope_) {
    case es_system:
        key = HKEY_LOCAL_MACHINE;
        subKeyName = systemEnvSubKey;
        break;

    case es_user:
        key = HKEY_CURRENT_USER;
        subKeyName = userEnvSubKey;
        break;
    }

    // Replace every instance of text with the empty string.
    pos = value_.find(text);
    length = text.length();
    while (sizeMax != pos) {
        ++count;
        value_.replace(pos, length, "");
        pos = value_.find(text);
    }

    // Write the new value to the registry.
    RegOpenKeyEx(key, subKeyName, 0, KEY_QUERY_VALUE | KEY_SET_VALUE, &subKey);
    RegSetValueEx(subKey,
                  name_.c_str(),
                  0,
                  REG_EXPAND_SZ,
                  reinterpret_cast<BYTE const *>(value_.c_str()),
                  value_.length() + 1);
    RegCloseKey(key);

    // Notify everyone of the change.
    broadcastChange_();

    return count;
}

void EnvVar::paste (std::string const &text)
{
    HKEY        key;
    HKEY        subKey;
    char const *subKeyName;

    if (es_invalid == scope_) {
        return;
    }

    switch (scope_) {
    case es_system:
        key = HKEY_LOCAL_MACHINE;
        subKeyName = systemEnvSubKey;
        break;

    case es_user:
        key = HKEY_CURRENT_USER;
        subKeyName = userEnvSubKey;
        break;
    }

    // Append text to the current value.
    value_ += text;

    // Write the new value to the registry.
    RegOpenKeyEx(key, subKeyName, 0, KEY_QUERY_VALUE | KEY_SET_VALUE, &subKey);
    RegSetValueEx(subKey,
                  name_.c_str(),
                  0,
                  REG_EXPAND_SZ,
                  reinterpret_cast<BYTE const *>(value_.c_str()),
                  value_.length());
    RegCloseKey(key);

    // Notify everyone of the change.
    broadcastChange_();
}

void EnvVar::set (std::string const &text)
{
    HKEY        key;
    HKEY        subKey;
    char const *subKeyName;

    if (es_invalid == scope_) {
        return;
    }

    switch (scope_) {
    case es_system:
        key = HKEY_LOCAL_MACHINE;
        subKeyName = systemEnvSubKey;
        break;

    case es_user:
        key = HKEY_CURRENT_USER;
        subKeyName = userEnvSubKey;
        break;
    }

    // Assign the new value.
    value_ = text;

    // Write the new value to the registry.
    RegOpenKeyEx(key, subKeyName, 0, KEY_SET_VALUE, &subKey);
    RegSetValueEx(subKey,
                  name_.c_str(),
                  0,
                  REG_EXPAND_SZ,
                  reinterpret_cast<const BYTE *>(value_.c_str()),
                  value_.length());
    RegCloseKey(key);

    // Notify everyone of the change.
    broadcastChange_();
}

void EnvVar::unset ()
{
    HKEY        key;
    HKEY        subKey;
    char const *subKeyName;

    if (es_invalid == scope_) {
        return;
    }

    switch (scope_) {
    case es_system:
        key = HKEY_LOCAL_MACHINE;
        subKeyName = systemEnvSubKey;
        break;

    case es_user:
        key = HKEY_CURRENT_USER;
        subKeyName = userEnvSubKey;
        break;
    }

    // Assign the empty string for the EnvVar object's value.
    value_ = "";

    // Delete the value from the registry.
    RegOpenKeyEx(key, subKeyName, 0, KEY_SET_VALUE, &subKey);
    RegDeleteValue(subKey, name_.c_str());
    RegCloseKey(key);

    // Notify everyone of the change.
    broadcastChange_();
}

std::string EnvVar::value ()
{
    return value_;
}

void EnvVar::broadcastChange_ ()
{
    DWORD_PTR result;

    // Broadcast WM_SETTINGCHANGE
    SendMessageTimeout(HWND_BROADCAST,
                       WM_SETTINGCHANGE,
                       NULL,
                       reinterpret_cast<LPARAM>("Environment"),
                       SMTO_NORMAL,
                       broadcastTimeout,
                       &result);
}

void EnvVar::copy_ (EnvVar const &other)
{
    name_  = other.name_;
    scope_ = other.scope_;
    value_ = other.value_;
}

void EnvVar::destroy_ ()
{
}