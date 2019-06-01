# SYNOPSIS
A very simple request router for C++17. You can use this with embeddable HTTP servers which do not provide a router, for example [Cesanta's Mongoose](https://github.com/cesanta/mongoose).

# EXAMPLE
This example uses the [`libuv-http`](https://github.com/hij1nx/libuv-http)
server.

```cpp
#include "http.h"
#include "route.h"

int main() {

  Router router;

  Server hs([](auto &req, auto &res) {

    auto match = router.set(req.url);

    if (match.test("/books/:id") {

      res.setStatus(200);
      res.setHeader("Content-Type", "text/plain");
      res.setHeader("Connection", "keep-alive");

      res << "You ordered #" << match.get("id") << res.end();
    }

  });

  hs.listen("0.0.0.0", 8000);
}
```

# TEST
Build the test target with `cmake --build <YOUR BUILD DIRECTORY> --target http-router-test`, then run the executable.
