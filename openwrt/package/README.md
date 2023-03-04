# Build for OpenWrt

[Setup OpenWrt build system][1]

Download [OpenWrt SDK][2] of a specific target. Update the package feeds:

```shell
./scripts/feeds update -a

# It has similar dependencies as xtables-addon. Install these dependencies by
# preparing for xtables-addons.
./scripts/feeds install xtables-addons
```

At the SDK root directory:

```shell
mkdir -p package/feeds/packages/xtables-wgobfs
```

Copy `Makefile` to the newly created directory. Build OpenWrt package with:

```shell
make menuconfig  # select Network -> Firewall -> iptables-mod-wgobfs
make package/xtables-wgobfs/compile V=s
```

The build result is two packages under `bin/`. They are `kmod-ipt-wgobfs_xxx.ipk` and `iptables-mod-wgobfs_xxx.ipk`.

[1]: https://openwrt.org/docs/guide-developer/toolchain/install-buildsystem
[2]: https://openwrt.org/docs/guide-developer/toolchain/using_the_sdk
