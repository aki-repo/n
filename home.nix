{ config, pkgs, ... }:

let
    dotfiles = "${config.home.homeDirectory}/nix/config";
    create_symlink = path: config.lib.file.mkOutOfStoreSymlink path;
in

{
    xdg.configFile."qtile" = {
        source = create_symlink "${dotfiles}/qtile";
        recursive = true;
    };

  imports = [
    ./modules/neovim.nix
    ./modules/helix.nix
    ./modules/bash.nix
    ./modules/starship.nix
    ./modules/noctalia.nix
    #./modules/theme.nix
    ./modules/wm/hyprland.nix
    #./modules/wm/niri.nix
    ./modules/wm/common.nix
];

  home.username = "aki";
  home.homeDirectory = "/home/aki";
  home.stateVersion = "25.11";

  # Git configuration
    programs.git = {
      enable = true;
      settings.user.name = "Andreas Taenzer";  # Replace with your name
      settings.user.email = "andreast.work@gmail.com";  # Replace with your email
      };

  # Essential packages
  home.packages = with pkgs; [
    # Development tools
    tmux
    starship
    fzf
    zoxide

    # System utilities
    bat
    btop
    curl
    eza
    wget
    unzip
    tree
    jq
    yazi

    # Modern CLI tools
    lazygit       # Git TUI
    ];

}
