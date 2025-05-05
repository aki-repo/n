services.xserver.windowManager.dwm.package = pkgs.dwm.override {
  conf = ./config.def.h;
  patches = [
    # for local patch files, replace with relative path to patch file
    # ./path/to/local.patch
    # for external patches
    alwayscenter = pkgs.fetchpatch {
    url = "https://dwm.suckless.org/patches/alwayscenter/dwm-alwayscenter-20200625-f04cac6.diff";
    hash = "sha256-XJHBTVmFRFM5kqi9Y0XI/DmUBnjCdiAO8X2PIDNL+MM=";
  };

  autostart = pkgs.fetchpatch {
    url = "https://dwm.suckless.org/patches/autostart/dwm-autostart-20210120-cb3f58a.diff";
    hash = "sha256-14cRWH5tVU3l3EetygD8HrbI+MoRyedUEdqNpg6uer4=";
  };

  useless-gap = pkgs.fetchpatch {
    url = "https://dwm.suckless.org/patches/uselessgap/dwm-uselessgap-20211119-58414bee958f2.diff";
    hash = "sha256-gMt6da4fOP58oWfWNvuOkFBt3dYWXC8yy7DdGwLv9XY=";
  };
    
  pertag = pkgs.fetchpatch {
      # replace with actual URL
      # url = "https://dwm.suckless.org/patches/pertag/dwm-pertag-20200914-61bb8b2.diff";
      # replace hash with the value from `nix-prefetch-url "https://dwm.suckless.org/patches/path/to/patch.diff" | xargs nix hash to-sri --type sha256`
      # or just leave it blank, rebuild, and use the hash value from the error
      #hash = "";
    };
  ];
};

# st
environment.systemPackages = [
    (pkgs.st.override {
      conf = ./config.def.h;
      patches = [ ./my-fix.patch ]; # Or some `fetchPatch` thing
    })
  ];

