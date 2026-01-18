# hyprland configuration

{inputs, pkgs, ...}: {


  home.packages = with pkgs; [
    fuzzel
    xwayland-satellite
    nemo
    vscode
		adw-gtk3
    papirus-icon-theme
		vesktop 
    librewolf
    chromium
    matugen
		microfetch
    nwg-look
    qutebrowser
    google-chrome
    easyeffects
    mpd
    rmpc
    ];


}
