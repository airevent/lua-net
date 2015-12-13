--

local net = require "net"
local trace = require "trace"

--

trace(net)

--

--local domain = "fuck.world"

--trace(net.ip4.tcp.nslookup(domain))
--trace(net.ip6.tcp.nslookup(domain))

--

local rep = "\1\7\0\1\0\23\1\0Primary script unknown\x0A\0\1\6\0\1\0Q\7\0Status: 404 Not Found\13\x0AContent-type: text/html; charset=UTF-8\13\x0A\13\x0AFile not found.\x0A\0\0\0\0\0\0\0\1\3\0\1\0\8\0\0\0\0\0\0\0\0\0\0"

local sock = assert(net.ip4.tcp.socket())
assert(sock:bind("0.0.0.0", 12345))
assert(sock:listen(1024))

local client, msg, len

while true do
    print("w8 for clients ... ")

    client = assert(sock:accept())

    --print("caught, fd:", client:fd())

    while true do
        msg, len = assert(client:recv())

        --trace(msg, len)

        if msg == "" then
            break
        else
            assert(client:send(rep))
        end
    end

    client:close()
end
