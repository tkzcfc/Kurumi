-- @Author: fangcheng
-- @Date:   2021-04-17 17:25:43
-- @remark: 

local TestScene = class("TestScene", G_Class.SceneBase)

function TestScene:onCreate()
    TestScene.super.onCreate(self)

    
	-- self.ui = G_Helper.loadStudioFile("scenes.UI_MainScene", self)
 --    self:addChild(self.ui.root)

     self:test_http()
     -- self:test_client()
end

function TestScene:test_client()
    local client = TCPClient:create()
    client:retain()
    client:registerLuaHandle("onClientCloseCallback", function()
        print("onClientCloseCallback--->")
    end)
    client:registerLuaHandle("onConnectCallback", function(session, status)
        -- 0:failed 1:succeeded 2:timed out
        print("onConnectCallback--->", session, status)

        local data = "HTTP 1.0\n"
        session:send(data, string.len(data))
    end)
    client:registerLuaHandle("onDisconnectCallback", function(session)
        print("onDisconnectCallback--->", session)
    end)
    client:registerLuaHandle("onRecvCallback", function(session, data)
        print("onRecvCallback--->", session, data)
    end)
    client:registerLuaHandle("onRemoveSessionCallback", function(session)
        print("onRemoveSessionCallback--->", session)
    end)
    client:connect("www.baidu.com", 80, 1)
end

function TestScene:test_http()
    -- http测试
    -- local url = "http://img.jj20.com/up/img/78442.jpg"
    local url = "http://img.jj20.com/up/allimg/1114/041621124255/210416124255-1-1200.jpg"

    local token
    token = _MyG.HttpManager:fetch(url, function(ok, file) print("1 request") end)
    _MyG.HttpManager:cancel(token)
    token = _MyG.HttpManager:fetch(url, function(ok, file) 
    	if not ok then return end
    	print("2 request", file)
    	
    	local sp = display.newSprite(file)
    	sp:move(display.center)
        sp:setScale(0.8)
    	self:addChild(sp, 0xff)
    end)
end


return TestScene
