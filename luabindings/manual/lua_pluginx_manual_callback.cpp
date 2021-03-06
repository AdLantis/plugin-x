#include "lua_pluginx_manual_callback.h"
#include "PluginManager.h"
#include "ProtocolAnalytics.h"
#include "ProtocolIAP.h"
#include "ProtocolAds.h"
#include "ProtocolShare.h"
#include "ProtocolSocial.h"
#include "ProtocolUser.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "CCLuaValue.h"
#include "CCLuaEngine.h"
#include "lua_pluginx_basic_conversions.h"

using namespace cocos2d::plugin;

int lua_pluginx_protocols_ProtocolIAP_payForProduct(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::ProtocolIAP* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.ProtocolIAP",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::plugin::ProtocolIAP*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolIAP_payForProduct'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            TProductInfo arg0;
            ok &= pluginx::luaval_to_TProductInfo(tolua_S, 2, &arg0);
            
            if (!ok) { break; }
            LUA_FUNCTION callback = toluafix_ref_function(tolua_S, 3, 0);
            cobj->payForProduct(arg0, [=](int ret, std::string& productInfo) {
                tolua_pushnumber(tolua_S, ret);
                tolua_pushstring(tolua_S, productInfo.c_str());
                LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(callback, 2);
                LuaEngine::getInstance()->removeScriptHandler(callback);
            });
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            TProductInfo arg0;
            ok &= pluginx::luaval_to_TProductInfo(tolua_S, 2, &arg0);
            
            if (!ok) { break; }
            cobj->payForProduct(arg0);
            return 0;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "payForProduct",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolIAP_payForProduct'.",&tolua_err);
#endif
    
    return 0;
}

static void extendProtocolIAP(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "plugin.ProtocolIAP");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"payForProduct");
        lua_pushcfunction(tolua_S,lua_pluginx_protocols_ProtocolIAP_payForProduct);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

int register_all_pluginx_manual_callback(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    extendProtocolIAP(tolua_S);
    return 0;
}
