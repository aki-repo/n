# hyprland configuration

{inputs, pkgs, ...}: {


  home.packages = with pkgs; [
    fuzzel
    papirus-icon-theme
    xwayland-satellite
    nemo
    vscode
		adw-gtk3
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
