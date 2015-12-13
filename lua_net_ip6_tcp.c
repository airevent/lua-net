//

static int lua_net_ip6_tcp_nslookup( lua_State *L ) {
    const char *node = luaL_checkstring(L, 1); // domain or ip

    struct addrinfo hints, *res, *rp;
    char ip[INET6_ADDRSTRLEN];
    int r, i;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    r = getaddrinfo(node, NULL, &hints, &res);
    if ( r != 0 ) lua_fail(L, gai_strerror(r), r);

    lua_newtable(L);

    for ( rp=res, i=1; rp != NULL; ++i, rp=rp->ai_next ) {
        inet_ntop(hints.ai_family, &((struct sockaddr_in6 *)(rp->ai_addr))->sin6_addr, ip, INET6_ADDRSTRLEN);
        lua_pushnumber(L, i);
        lua_pushstring(L, ip);
        lua_settable(L, -3);
    }

    freeaddrinfo(res);

    return 1;
}
