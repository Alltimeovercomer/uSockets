/* Public interfaces for contexts */

/* A socket context holds shared callbacks and user data extension for associated sockets */
WIN32_EXPORT struct us_socket_context *us_create_socket_context(struct us_loop *loop, int ext_size);

/* */
WIN32_EXPORT void us_socket_context_free(struct us_socket_context *context);

/* Setters of various async callbacks */
WIN32_EXPORT void us_socket_context_on_open(struct us_socket_context *context, void (*on_open)(struct us_socket *s));
WIN32_EXPORT void us_socket_context_on_close(struct us_socket_context *context, void (*on_close)(struct us_socket *s));
WIN32_EXPORT void us_socket_context_on_data(struct us_socket_context *context, void (*on_data)(struct us_socket *s, char *data, int length));
WIN32_EXPORT void us_socket_context_on_writable(struct us_socket_context *context, void (*on_writable)(struct us_socket *s));
WIN32_EXPORT void us_socket_context_on_timeout(struct us_socket_context *context, void (*on_timeout)(struct us_socket *s));

/* Emitted when a socket has been half-closed */
WIN32_EXPORT void us_socket_context_on_end(struct us_socket_context *context, void (*on_end)(struct us_socket *s));

/* Returns user data extension for this socket context */
WIN32_EXPORT void *us_socket_context_ext(struct us_socket_context *context);

/* Listen for connections. Acts as the main driving cog in a server. Will call set async callbacks. */
WIN32_EXPORT struct us_listen_socket *us_socket_context_listen(struct us_socket_context *context, const char *host, int port, int options, int socket_ext_size);

/* listen_socket.c/.h */
WIN32_EXPORT void us_listen_socket_close(struct us_listen_socket *ls);

/* Land in on_open or on_close or return null or return socket */
WIN32_EXPORT struct us_socket *us_socket_context_connect(struct us_socket_context *context, const char *host, int port, int options, int socket_ext_size);

/* (Explicitly) associate a socket with this socket context. A socket can only belong to one single socket context at any one time */
WIN32_EXPORT void us_socket_context_link(struct us_socket_context *context, struct us_socket *s);

/* */
WIN32_EXPORT void us_socket_context_unlink(struct us_socket_context *context, struct us_socket *s);

/* */
WIN32_EXPORT struct us_loop *us_socket_context_loop(struct us_socket_context *context);

// you need a way to "move" a socket from one context of other kind (http -> websocket)
// you need to make sure the shared SSL_context is up-referenced so that removing the old context does not mess up the new
// or, simply say that a socket always belongs to where it was created but can be transformed into other contexts
WIN32_EXPORT struct us_socket *us_socket_context_transform_socket(struct us_socket_context *context, struct us_socket *s);
