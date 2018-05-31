require "lfs"
require "app.models.net.protobuf"

local msglist = require("netmsg.pb.msglist")

print("---------------------------------------------")
for i = 1, #msglist do
    print("register file", msglist[i])
    protobuf.register_file(msglist[i])
end
print("---------------------------------------------\n\n")
