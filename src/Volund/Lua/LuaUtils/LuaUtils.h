#pragma once

#include "SerialTable/SerialTable.h"
#include <sol/sol.hpp>

namespace Volund::LuaUtils
{
    SerialTable DeserializeTable(sol::table table);

    sol::protected_function_result ScriptFile(std::shared_ptr<sol::state> state, std::string const& filepath);
}
