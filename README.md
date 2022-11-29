# Iptables WireGuard obfuscation extension

The sender and receiver share a secret key, which is used by chacha8 to hash
the same input into identical pseudo-random numbers. These pseudo-random
numbers are used in obfuscation.

- The first 16 bytes of WG message is obfuscated.
- The mac2 field is also obfuscated, if it is all zeros.
- Padding WG message with random long random bytes.
- Drop keepalive message with 80% probability.
- Change the Diffserv field to zero.

Chacha8 is used here since the goal is not encryption.

Tested working on Alpine linux kernel 5.15 and CentOS 7 kernel 3.10.


### Build dependence

- Alpine: alpine-sdk, iptables-dev, linux-lts-dev or linux-virt-dev
- CentOS 7: iptables-devel, kernel-devel
- Debian: iptables-dev, linux-headers


### Build and install

Build:

```shell
./autogen.sh
./configure
make
```

Install:

```shell
sudo make install
```

One may need run `depmod -a && modprobe xt_WGOBFS` to load the kernel module.

### Usage

This extension takes two parameters.

`--key` for a shared secret between client and server. If a key is a long
string, it will be cut at 32 characters; if a key is short, then it will be
repeated until reaches 32 characters. This 32 characters long string is the key
used by chacha8 hash.

`--obfs` or `--unobfs` to indicate the operation mode.

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


## TCP MSS fix

It is necessary to clamp TCP MSS on TCP traffic over tunnel. Symptoms of TCP
MSS problems including HTTP not working on some websites, ssh works but scp
doesn’t work.

```shell
iptables -t mangle -A FORWARD -p tcp --tcp-flags SYN,RST SYN -j TCPMSS --clamp-mss-to-pmtu
```


### Performance

Test in two Alpine linux VMs on same host. Each VM has 1 CPU and 256M RAM.
Iperf3 over wg reports 1.1Gbits/sec without obfuscation, 950Mbits/sec with
obfuscation.


### OpenWrt

See [openwrt/package/README.md](/openwrt/package/README.md)


### License

GPL v2
