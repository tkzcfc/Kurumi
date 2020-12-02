#include "lua_http.hpp"

#include <memory>
#include <string>
#include <sstream>

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

#include "network/HttpClient.h"
#include "lua_function/LuaFunction.h"

struct Request {
    typedef cocos2d::network::HttpRequest::Type Method;
	Request()
    {
        client = cocos2d::network::HttpClient::getInstance();
        req = new cocos2d::network::HttpRequest();
    }
    void init(lua_State* L, int idx)
    {
        switch (lua_type(L, idx))
        {
            case LUA_TSTRING:
                initWithURL(L, idx);
                break;
            case LUA_TTABLE:
                initWithOptions(L, idx);
                break;
            default:
                luaL_argerror(L, idx, "expected a options table or url string");
        }
    }
    ~Request()
    {
        req->release();
    }
    void done()
    {
        req->setRequestData(data.data(), data.size());
        //static const char* const http_methods[] = { "GET","POST","PUT","DELETE","UNKNOWN"};
        //CCLOG("%s: %s", http_methods[static_cast<int>(req->getRequestType())], req->getUrl());
        client->send(req);
    }
    void write(const char* s, size_t l)
    {
        data.append(s, l);
    }
    void setTimeout(int seconds)
    {
        client->setTimeoutForConnect(seconds);
    }
    cocos2d::network::HttpClient* client;
    cocos2d::network::HttpRequest* req;

private:

    std::string data;

    void initWithURL(lua_State* L, int idx)
    {
        req->setRequestType(Method::GET);
        req->setUrl(lua_tostring(L, idx));
    }
    void initWithOptions(lua_State* L, int idx)
    {
        lua_pushvalue(L, idx);

        // 1. method
        Method method = methodFromString(getStringField(L, -1, "method", "UNKNOWN"));
        if (method == Method::UNKNOWN)
            luaL_argerror(L, 1, "except method to be 'GET'|'POST'|'PUT'|'DELETE'");
        req->setRequestType(method);

        // 2. URL ( = protocol + host + path )

		std::string url = getStringField(L, -1, "url", "");
		if (url.empty())
		{
			std::string protocol = getStringField(L, -1, "protocol", "http");
			std::string host = getStringField(L, -1, "host");
			std::string path = getStringField(L, -1, "path");
			url = std::string(protocol + "://" + host + path);
		}
        req->setUrl(url.data());


        // 3. headers
        lua_getfield(L, -1, "headers");
        if (lua_type(L, -1) == LUA_TTABLE)
        {
            std::vector<std::string> headers;
            lua_pushnil(L); // [table, nil]

            while (lua_next(L, -2))
            {
                // [table, key, value]
                lua_pushvalue(L, -2); // [table, key, value, key]

                std::string key = toString(L, -1);
                std::string value = toString(L, -2);
                headers.push_back(key+":"+value);

                // pop value + copy of key, leaving original key
                lua_pop(L, 2); // [table, key]
            }
            lua_pop(L, 2); // pop the last key and the table
            req->setHeaders(headers);
        }
    }
    static Method methodFromString(const std::string& s)
    {
        static std::map<std::string, Method> methods;
        if (methods.empty())
        {
            methods["GET"] = Method::GET;
			methods["POST"] = Method::POST;
			methods["PUT"] = Method::PUT;
			methods["DELETE"] = Method::DELETE;
        }
        auto it = methods.find(s);
        return (it != methods.end()) ? it->second : Method::UNKNOWN;
    }

    static std::string getStringField(lua_State* L, int idx, const char* field, const char* def = nullptr)
    {
        lua_getfield(L, -1, field);
        size_t len;
        const char* s = luaL_optlstring(L, -1, def, &len);
        if (s == nullptr)
            luaL_error(L, "requires field '%s' to be a valid string", field);
        std::string r(s, len);
        lua_pop(L, 1);
        return r;
    }

    static std::string toString(lua_State* L, int idx)
    {
        size_t len;
        const char* s = lua_tolstring(L, idx, &len);
        if (!s)
            luaL_error(L, "needs to be a string.");
        return std::string(s, len);

    }
};


static int http_fetch(lua_State* L)
{
	Request req;
    req.init(L, 1);
	std::string filename(tolua_ext_checkString(L, 2));
	int handle = toluafix_ref_function(L, 3, 0);

    req.req->setResponseCallback([handle, filename](cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response) mutable
    {
        bool ok = response->getResponseCode() == 200;
        if (ok)
        {
            std::vector<char>* buffer = response->getResponseData();
			Data data;
			data.fastSet((unsigned char*)buffer->data(), (ssize_t)buffer->size());
			FileUtils::getInstance()->writeDataToFile(data, filename);
			data.fastSet(NULL, 0);
        }
		LuaFunction callback(handle);
		if (callback.isvalid())
		{
			callback.ppush();
			callback.pusharg(ok);
			callback.pusharg(filename);
			callback.pcall();
		}
    });

    req.done();
    return 0;
}

static int http_read(lua_State* L)
{
    Request req;
    req.init(L, 1);
    int handle = toluafix_ref_function(L, 2, 0);

    req.req->setResponseCallback([handle](cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response) mutable
    {
        bool ok = response->getResponseCode() == 200;
        std::string buf;
        if (ok)
        {
            std::vector<char>* buffer = response->getResponseData();
            buf.assign(buffer->begin(), buffer->end());
        }
		LuaFunction callback(handle);
		if (callback.isvalid())
		{
			callback.ppush();
			callback.pusharg(ok);
			callback.pusharg(buf);
			callback.pcall();
		}
    });

    req.done();
    return 0;
}



#define RequestMETA  "http.c.Request"

static void pushRequest(lua_State* L, Request* req)
{
    Request** w = (Request**)lua_newuserdata(L, sizeof(*w));
    *w = req;
    luaL_getmetatable(L, RequestMETA);
    lua_setmetatable(L, -2);
}

static inline Request** toRequestp(lua_State* L){
    return (Request**)luaL_checkudata(L, 1, RequestMETA);
}

Request* toRequest(lua_State* L) {
    auto w = toRequestp(L);
    if (*w == NULL)
        luaL_error(L, "Request already closed");
    return *w;
}

static int http_request(lua_State* L)
{
	Request* req = new Request();
    req->init(L, 1);

    int handle = toluafix_ref_function(L, 2, 0);

	req->req->setResponseCallback([handle](cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response) mutable
	{
		auto stack = LuaEngine::getInstance()->getLuaStack();
		if (stack == NULL)
		{
			return;
		}

		auto luaState = stack->getLuaState();

		LuaFunction callback(handle);
        callback.ppush();

        lua_newtable(luaState); // response

        lua_pushliteral(luaState, "statusCode");
        lua_pushinteger(luaState, response->getResponseCode());
        lua_rawset(luaState, -3);

		std::vector<char>* headers = response->getResponseHeader();
		if (!headers->empty())
		{
			lua_pushliteral(luaState, "headers");

			std::stringstream ss(std::string(headers->begin(), headers->end()));
			std::string line;
			lua_createtable(luaState, 0, 8);
			while (std::getline(ss, line, '\n'))
			{
				auto pos = line.find(':');
				if (pos != std::string::npos)
				{
					std::string key(line.data(), pos);

					lua_pushlstring(luaState, line.data(), pos);
					pos = line.find_first_not_of(" ", pos + 1);
					std::string value(line.data() + pos, line.size() - pos);
					lua_pushlstring(luaState, line.data() + pos, line.size() - pos);
					lua_rawset(luaState, -3);
				}
			}
			lua_rawset(luaState, -3);
		}

		std::vector<char>* body = response->getResponseData();
		if (!body->empty())
		{
			lua_pushliteral(luaState, "body");
			lua_pushlstring(luaState, &body->front(), body->size());
			lua_rawset(luaState, -3);
		}

		if (!response->isSucceed())
		{
			lua_pushliteral(luaState, "error");
			lua_pushstring(luaState, response->getErrorBuffer());
			lua_rawset(luaState, -3);
		}
        callback.pcallEx(1);
	});

    pushRequest(L, req);
	return 1;
}




static int Request_tostring(lua_State* L)
{
    auto w = toRequestp(L);
    if (*w)
        lua_pushfstring(L, "Request (%p)", *w);
    else
        lua_pushliteral(L, "Request (closed)");
    return 1;
}


static int Request_gc(lua_State* L)
{
    auto w = toRequestp(L);

    printf("finalizing LUA object (%s)\n", RequestMETA);

    if (!*w)
        return 0;

    delete *w;
    *w = nullptr; // mark as closed
    return 0;
}


static int Request_done(lua_State* L)
{
    auto req = toRequest(L);
    req->done();
    return 0;
}

static int Request_write(lua_State* L)
{
    auto req = toRequest(L);
    size_t size = 0;
    const char* data = luaL_checklstring(L, 2, &size);
    req->write(data, size);

    return 0;
}

static int Request_setTimeout(lua_State* L)
{
    auto req = toRequest(L);
    int seconds = static_cast<int>(luaL_checkinteger(L, 2));
    req->setTimeout(seconds);
    return 0;
}


static luaL_Reg methods[] = {
    { "__gc", Request_gc },
    { "__tostring", Request_tostring },
    { "setTimeout", Request_setTimeout },
    { "done", Request_done },
    { "write", Request_write },

    { NULL, NULL },
};

static const luaL_Reg functions[] = {
    { "fetch", http_fetch },
    { "read", http_read },
	{ "request", http_request },
    { NULL, NULL }
};

int luaopen_http(lua_State *L)
{
    // create the Request class Metatable
    luaL_newmetatable(L, RequestMETA);
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, methods);
    lua_pop(L, 1);

    lua_newtable(L);
    luaL_register(L, NULL, functions);
    return 1;
}
