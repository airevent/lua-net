--

local net = require "net"
local trace = require "trace"

--

local ep = assert(net.epoll(0))

trace(getmetatable(ep))
