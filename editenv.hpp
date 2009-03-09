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

EDITENV_API unsigned int envCut (editenv::env_scope  scope,
                                 char const         *name,
                                 char const         *value);

EDITENV_API void envPaste (editenv::env_scope  scope,
                           char const         *name,
                           char const         *value);

EDITENV_API void envSet (editenv::env_scope  scope,
                         char const         *name,
                         char const         *value);

EDITENV_API void envUnset (editenv::env_scope scope, char const *name);

EDITENV_API char const * envValue (editenv::env_scope scope, char const *name);

EDITENV_API void pathAdd (editenv::env_scope, char const *path);

EDITENV_API void pathRemove (editenv::env_scope, char const *path);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus


#endif // EDITENV_EDITENV_HPP