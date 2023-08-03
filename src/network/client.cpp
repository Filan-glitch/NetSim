#include "client.h"
#include "src/protocols/tcp.h"
#include "src/protocols/http.h"


Client::Client(const NetworkCard &networkCard) : Host(networkCard)
{}

