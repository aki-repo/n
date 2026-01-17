{ config, pkgs, lib, ... }:
{
# Bash configuration
  programs.bash = {
    enable = true;

    shellAliases = {
      # Home Manager
      hm = "home-manager switch --flake ~/.config/home-manager#tp";

      # ls replacements
      ls = "eza --icons";
      ll = "eza -la --icons";
      la = "eza -la --icons";
      lt = "eza --tree --icons";

      # Modern replacements
      cat = "bat";
      grep = "rg";
      find = "fd";

      # Git shortcuts
      g = "git";
      gst = "git status";
      gco = "git checkout";
      gcm = "git commit -m";
      gcam = "git commit -am";

      # Navigation
      ".." = "cd ..";
      "..." = "cd ../..";
      "...." = "cd ../../..";
    };

    initExtra = ''

    # Initialize starship prompt
    eval "$(starship init bash)"

    # Initialize zoxide
    eval "$(zoxide init bash)"

    # Custom functions
     mkcd() {
       mkdir -p "$1" && cd "$1"
     }

    # Better cd with zoxide fallback
    cd() {
      if [ -d "$1" ] || [ -z "$1" ]; then
        builtin cd "$@"
      else
        z "$@"
      fi
    }
    '';
  };
  }
