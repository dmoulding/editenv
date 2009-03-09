#ifndef EDITENV_ENV_VAR
#define EDITENV_ENV_VAR

#include <string>

#include "editenvTypes.hpp"

class editenv::EnvVar
{
public:
    EnvVar (env_scope scope, std::string const &name);
    EnvVar (EnvVar const &other);
    ~EnvVar ();

    EnvVar & operator = (EnvVar const &other);

    unsigned int cut (std::string const &text);
    void         paste (std::string const &text);
    void         set (std::string const &text);
    void         unset ();
    std::string  value ();
    
private:
    void broadcastChange_ ();
    void copy_ (EnvVar const &other);
    void destroy_ ();

    std::string name_;
    env_scope   scope_;
    std::string value_;
};

#endif // EDITENV_ENV_VAR