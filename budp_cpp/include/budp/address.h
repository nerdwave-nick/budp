class IPv4Address {
   public:
    IPv4Address();
    IPv4Address(unsigned char a, unsigned char b, unsigned char c,
                unsigned char d, unsigned short port);
    IPv4Address(unsigned int address, unsigned short port);

    unsigned int get_address() const;
    unsigned short get_port() const;

   private:
    unsigned int m_address;
    unsigned short m_port;
};