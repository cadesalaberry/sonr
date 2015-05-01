# sonr

A dead simple App to see what is happening on your network.

*NOTE THAT IT'S A WIP*


## Limitations

For now the interface can just see traffic comming from your computer, but the [dot11decrypt](https://github.com/mfontanini/dot11decrypt) should be of some help to see the entire network.


## Requirements

* [libtins](http://libtins.github.io/)
* [websocketpp](https://github.com/zaphoyd/websocketpp)
* boost-dev (`sudo dnf install boost-devel` on fedora)
* You need `sudo` at runtime to access the networking interface.

If you don't use sudo, you will get the following error:
```
terminate called after throwing an instance of 'std::runtime_error'
  what():  socket: Operation not permitted
Aborted (core dumped)
```


## How To Use

```
g++ sonr.cpp -o sonr -ltins -lboost_system -std=c++11
```

then run the server with `./sonr`.

you can see the app in action in the terminal, or by opening the `index.html` file.
