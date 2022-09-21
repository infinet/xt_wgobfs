# Iptables WireGuard obfuscation extension

The sender and receiver share a secret key, which is used by SipHash to create
identical pseudo-random numbers with same input. These pseudo-random numbers
are used in obfuscation.

- The first 16 bytes of WG message is obfuscated.
- The mac2 field is also obfuscated, if it is all zeros.
- Padding WG message with random long random bytes.
- Drop keepalive message with 80% probability.
- Change the Diffserv field to zero.

SipHash 1-2 is used here since the goal is not encryption.

Tested working on Alpine linux kernel 5.15 and CentOS 7 kernel 3.10.


### Build dependence

- Alpine: alpine-sdk, iptables-dev, linux-lts-dev or linux-virt-dev
- CentOS 7: iptables-devel, kernel-devel
- Debian: iptables-dev, linux-headers


### Build and install

Run `make` in kernel/ to build kernel module. `sudo make install` will install
the kernel module; or, copy `xt_WGOBFS.ko` to
/lib/modules/yourkernelversion/kernel/net/netfilter/ manually, followed by
`depmod -a && modprobe xt_WGOBFS`.

Run `make` in xtables/ to build iptables extension. Copy `libxt_WGOBFS.so` to
xtables directory.

    - Alpine: /usr/lib/xtables/
    - CentOS 7: /usr/lib64/xtables
    - Debian: /usr/lib/x86_64-linux-gnu/xtables


### Usage

This extension takes two parameters. `--key` for a shared secret between client
and server. It is for generating a 128 bits shared secret key used by SipHash.
And `--obfs` or `--unobfs` to indicate the operation mode.

**Before** bring up wg, on client, insert two iptables rules:

```shell
iptables -t mangle -I INPUT -p udp -m udp --sport 6789 -j WGOBFS --key mysecretkey --unobfs
iptables -t mangle -I OUTPUT -p udp -m udp --dport 6789 -j WGOBFS --key mysecretkey --obfs
```

The above rules assuming remote server is listening on port 6789. On server, do
the opposite:

```shell
iptables -t mangle -I INPUT -p udp -m udp --dport 6789 -j WGOBFS --key mysecretkey --unobfs
iptables -t mangle -I OUTPUT -p udp -m udp --sport 6789 -j WGOBFS --key mysecretkey --obfs
```

Mangle FORWARD chain shall also work.


### Performance

Test in two Alpine linux VMs on same host. Each VM has 1 CPU and 256M RAM.
Iperf3 over wg reports 1.1Gbits/sec without obfuscation, 860Mbits/sec with
obfuscation.


### License

GPL v2
