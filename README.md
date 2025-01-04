# Iptables WireGuard obfuscation extension

The sender and receiver share a secret key, which is used by `chacha6` to hash
the same input into identical pseudo-random numbers. These pseudo-random
numbers are used in obfuscation.

- The first 16 bytes of WG message is obfuscated.
- The mac2 field is also obfuscated, if it is all zeros.
- Padding WG message with random long random bytes.
- Drop keepalive message with 80% probability.
- Change the Diffserv field to zero.

`Chacha6` is chosen for its speed, as the goal is not encryption.

Tested working on Alpine linux kernel 5.15, CentOS 7, Debian 10/11/12 and
openSUSE 15.5.


### Build dependence

- Alpine: alpine-sdk iptables-dev linux-lts-dev or linux-virt-dev
- CentOS 7: iptables-devel kernel-devel
- Debian 10/11/12 : autoconf libtool libxtables-dev linux-headers pkg-config
- openSUSE 15: autoconf automake gcc kernel-default-devel libtool libxtables-devel make


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

By default, openSUSE does not allow unsupported kernel modeule. To override,
create or modify `/etc/modprobe.d/10-unsupported-modules.conf`, add the
following line:

```shell
allow_unsupported_modules 1
```


### DKMS

To use DKMS, first generate a source tarball, then install it as superuser:

```shell
./autogen.sh
./configure
make tarball
sudo make dkms-install
```


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

### As a relay

Since this is a Linux kernel module, users on Windows, Mac, or mobile devices
will not be able to use it directly. However, a possible workaround is to use it
through a relay.

For setting it up on a relay server (assuming default policy for FORWARD chain is
ACCEPT):


```shell
iptables -t nat -A PREROUTING -p udp -d RELAY_WAN_IP --dport 6789 -j DNAT --to-destination real_wg_server_ip:6789
iptables -t nat -A POSTROUTING -p udp -d real_wg_server_ip --dport 6789 -j MASQUERADE

iptables -t mangle -A FORWARD -p udp -d real_wg_server_ip --dport 6789 -j WGOBFS --key mysecretkey --obfs
iptables -t mangle -A FORWARD -p udp -s real_wg_server_ip --sport 6789 -j WGOBFS --key mysecretkey --unobfs

```

Windows, Mac or mobile clients then use the IP and port of the relay as WG
server endpoint. The setup for the remote WG server is the same as in previous
section.


### IPv6

For IPv6, replace `iptables` with `ip6tables` in rules. It is also necessary to
reduce the MTU of wireguard interface, for example, set the MTU to 1280.


### TCP MSS fix

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
