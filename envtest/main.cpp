#include <editenv.hpp>

int main (int argc, char *argv [])
{
    using namespace editenv;

    envSet(es_user,
           "TestPath",
           "C:\\Program Files;"
           "C:\\Windows;"
           "C:\\Program Files\\Meh;"
           "C:\\Program Files;"
           "C:\\Program Files\\Foo\\Bar;"
           "C:\\Program Files");

    pathAdd(es_user, "C:\\Program Files");

    pathRemove(es_user, "C:\\Program Files");
    pathRemove(es_user, "C:\\Program Files");

    return 0;
}