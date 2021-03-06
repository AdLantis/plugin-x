#include "lua_pluginx_basic_conversions.h"

using namespace cocos2d::plugin;

namespace pluginx {

bool luaval_to_TIAPDeveloperInfo(lua_State *L, int lo, TIAPDeveloperInfo* outValue)
{
    ValueMap ret;
    if (!luaval_to_ccvaluemap(L, lo, &ret)) return false;
    TIAPDeveloperInfo& dict = *outValue;
    for (auto e : ret) {
        dict[e.first] = e.second.asString();
    }
    return true;
}

bool luaval_to_TProductInfo(lua_State *L, int lo, cocos2d::plugin::TProductInfo* outValue)
{
    return luaval_to_TIAPDeveloperInfo(L, lo, outValue);
}

}// namespace pluginx {
