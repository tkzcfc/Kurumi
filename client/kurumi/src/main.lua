function __G__TRACKBACK__(errorMessage)
    print("----------------------------------------")
    print("LUA ERROR: " .. tostring(errorMessage) .. "\n")
    print(debug.traceback("", 2))
    print("----------------------------------------")

    if errlog then
        local msg = tostring(errorMessage) .. "\n" .. debug.traceback("", 2)
        errlog:send(msg)
    end
end

errlog = require("errlog")
require("entry")()
