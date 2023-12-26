#include <budp/address.h>

class UdpSocket {
   public:
    UdpSocket();
    ~UdpSocket();

    void bind(Address const& address);
    void send(Address const& to_address, const char* buffer,
              unsigned int length);
    int receive(char* buffer, unsigned int max_length,
                Address const& from_address);
}