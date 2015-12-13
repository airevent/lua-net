--

local net = require "net"
local trace = require "trace"

--

local s = assert(net.ip4.tcp.socket(0))

--assert(s:set(net.f.O_NONBLOCK, 1))

local host = "www.google.ru"
local ips = net.ip4.tcp.nslookup(host)
local ip = ips[1]

assert(s:connect(ip, 80))

assert(s:send("GET / HTTP/1.0\r\nHost: "..host.."\r\n\r\n"))

trace(s:recv())
