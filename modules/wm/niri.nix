{ inputs, pkgs, ...}:

{
  programs.niri.enable = true;
  programs.niri.settings = {
    outputs."eDP-1".scale = 1.67;
  };
}
