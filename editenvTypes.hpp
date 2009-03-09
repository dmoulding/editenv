#ifndef EDITENV_EDITENV_TYPES_HPP
#define EDITENV_EDITENV_TYPES_HPP

#ifdef EDITENV_BUILD
#define EDITENV_API __declspec(dllexport)
#else
#define EDITENV_API __declspec(dllimport)
#endif // EDITENV_BUILD

namespace editenv {
    enum env_scope {
        es_invalid,
        es_system,
        es_user
    };

    class EDITENV_API EnvVar;
}

#endif // EDITENV_EDITENV_TYPES_HPP