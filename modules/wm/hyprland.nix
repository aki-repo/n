# hyprland configuration

{inputs, pkgs, ...}: {

  # Optional, hint Electron apps to use Wayland:
  home.sessionVariables.NIXOS_OZONE_WL = "1";

  home.packages = with pkgs; [
    swaybg
    hyprlauncher
    hypridle
    grimblast
    xdg-desktop-portal-hyprland
    hyprpolkitagent
    waybar
    wl-clipboard
    ];


}
