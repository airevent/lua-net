//

static int lua_net_epoll( lua_State *L ) {
    int cloexec = luaL_optinteger(L, 2, 1) ? EPOLL_CLOEXEC : 0;

    lua_ud_socket *sock = (lua_ud_socket *)lua_newuserdata(L, sizeof(lua_ud_socket));

    if ( !sock ) {
        lua_fail(L, "lua_ud_socket alloc failed", 0);
    }

    sock->id = inc_id();
    sock->fd = epoll_create1(cloexec);

    if ( sock->fd < 0 ) {
        lua_errno(L);
    }

    luaL_setmetatable(L, LUA_MT_NET_EPOLL);

    return 1;
}

static int lua_net_epoll_start( lua_State *L ) {
    return 0;
}

static int lua_net_epoll_gc( lua_State *L ) {
    lua_ud_socket *sock = luaL_checkudata(L, 1, LUA_MT_NET_EPOLL);

    if ( sock->fd > -1 ) {
        close(sock->fd);
        sock->fd = -1;
    }

    return 0;
}

static int lua_net_epoll_watch( lua_State *L ) {
    return 0;
}

static int lua_net_epoll_unwatch( lua_State *L ) {
    return 0;
}
