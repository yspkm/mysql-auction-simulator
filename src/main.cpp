#include <vector>
#include <string>
#include <stdlib.h>
#include <regex>
#include <assert.h>
#include <string>

#include "../include/Query.hpp"
#include "../include/Menu.hpp"
#include "../include/User.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    Menu menu;
    regex re;
    smatch match;
    string argv1 = argv[1], argv2 = argv[2], argv3 = argv[3];
    re.assign("[j|o]{1}dbc:mysql://(\\w*):(\\d*)/(\\w*)");
    assert(regex_match(argv1, match, re) != 0);

    menu.init(match[1].str(), argv2, argv3, match[3].str(), (unsigned)stoi(match[2].str()));
    while (true)
    {
        menu.enterInitMenu();
        if (menu.user.is_admin)
            while (menu.enterAdminMainMenu())
                ;
        else
            while (menu.enterMainMenu())
                ;
    }
    menu.clear();
    return 0;
}
