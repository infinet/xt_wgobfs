# Build for OpenWrt

[Setup OpenWrt build system][1]

Download [OpenWrt SDK][2] of a specific target. Update the package feeds:

```shell
./scripts/feeds update -a
```

At the SDK root directory:

```shell
mkdir -p package/feeds/packages/xt_wgobfs
```

Copy `Makefile` to the newly created directory. Build OpenWrt package with:

```shell
make menuconfig  # select Network -> Firewall -> iptables-mod-wgobfs
make package/xt_wgobfs/compile V=s
```

[1]: https://openwrt.org/docs/guide-developer/toolchain/install-buildsystem
[2]: https://openwrt.org/docs/guide-developer/toolchain/using_the_sdk
